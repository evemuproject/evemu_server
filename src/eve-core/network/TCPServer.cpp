/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2016 The EVEmu Team
    For the latest information visit http://evemu.org
    ------------------------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any later
    version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
    this program; if not, write to the Free Software Foundation, Inc., 59 Temple
    Place - Suite 330, Boston, MA 02111-1307, USA, or go to
    http://www.gnu.org/copyleft/lesser.txt.
    ------------------------------------------------------------------------------------
    Author:     Zhur
*/

#include "eve-core.h"

#include "network/TCPServer.h"
#include "log/LogNew.h"

const uint32 TCPSRV_ERRBUF_SIZE = 1024;
const uint32 TCPSRV_LOOP_GRANULARITY = 5;

BaseTCPServer::BaseTCPServer()
: mSock( NULL ),
  mPort( 0 )
{
}

BaseTCPServer::~BaseTCPServer()
{
    // Close socket
    Close();

    // Wait until worker thread terminates
    WaitLoop();
}

bool BaseTCPServer::IsOpen() const
{
    bool ret;

    mMSock.Lock();
    ret = ( mSock != NULL );
    mMSock.Unlock();

    return ret;
}

bool BaseTCPServer::Open( uint16 port, char* errbuf )
{
    if( errbuf != NULL )
        errbuf[0] = 0;

    // mutex lock
    MutexLock lock( mMSock );

    if( IsOpen() )
    {
        if( errbuf != NULL )
            snprintf( errbuf, TCPSRV_ERRBUF_SIZE, "Listening socket already open" );
        return false;
    }
    else
    {
        mMSock.Unlock();

        // Wait for thread to terminate
        WaitLoop();

        mMSock.Lock();
    }

    // Setting up TCP port for new TCP connections
    mSock = new Socket( AF_INET, SOCK_STREAM, 0 );

    // Quag: don't think following is good stuff for TCP, good for UDP
    // Mis: SO_REUSEADDR shouldn't be a problem for tcp - allows you to restart
    //      without waiting for conn's in TIME_WAIT to die
    unsigned int reuse_addr = 1;
    mSock->setopt( SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof( reuse_addr ) );

    // Setup internet address information.
    // This is used with the bind() call
    sockaddr_in address;
    memset( &address, 0, sizeof( address ) );

    address.sin_family = AF_INET;
    address.sin_port = htons( port );
    address.sin_addr.s_addr = htonl( INADDR_ANY );

    if( mSock->bind( (sockaddr*)&address, sizeof( address ) ) < 0 )
    {
        if( errbuf != NULL )
            snprintf( errbuf, TCPSRV_ERRBUF_SIZE, "bind(): < 0" );

        SafeDelete( mSock );
        return false;
    }

    unsigned int bufsize = 64 * 1024; // 64kbyte receive buffer, up from default of 8k
    mSock->setopt( SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof( bufsize ) );

#ifdef HAVE_WINSOCK2_H
    unsigned long nonblocking = 1;
    mSock->ioctl( FIONBIO, &nonblocking );
#else /* !HAVE_WINSOCK2_H */
    mSock->fcntl( F_SETFL, O_NONBLOCK );
#endif /* !HAVE_WINSOCK2_H */

    if( mSock->listen() == SOCKET_ERROR )
    {
        if( errbuf != NULL )
#ifdef HAVE_WINSOCK2_H
            snprintf( errbuf, TCPSRV_ERRBUF_SIZE, "listen() failed, Error: %u", WSAGetLastError() );
#else /* !HAVE_WINSOCK2_H */
            snprintf( errbuf, TCPSRV_ERRBUF_SIZE, "listen() failed, Error: %s", strerror( errno ) );
#endif /* !HAVE_WINSOCK2_H */

        SafeDelete( mSock );
        return false;
    }

    mPort = port;

    // Start processing thread
    StartLoop();

    return true;
}

void BaseTCPServer::Close()
{
    MutexLock lock( mMSock );

    SafeDelete( mSock );
    mPort = 0;
}

void BaseTCPServer::StartLoop()
{
#ifdef HAVE_WINDOWS_H
    CreateThread( NULL, 0, TCPServerLoop, this, 0, NULL );
#else /* !HAVE_WINDOWS_H */
    pthread_t thread;
    pthread_create( &thread, NULL, TCPServerLoop, this );
#endif /* !HAVE_WINDOWS_H */
}

void BaseTCPServer::WaitLoop()
{
    //wait for loop to stop.
    mMLoopRunning.Lock();
    mMLoopRunning.Unlock();
}

bool BaseTCPServer::Process()
{
    MutexLock lock( mMSock );

    if( !IsOpen() )
        return false;

    ListenNewConnections();
    return true;
}

void BaseTCPServer::ListenNewConnections()
{
    Socket*         sock;
    sockaddr_in     from;
    unsigned int    fromlen;

    from.sin_family = AF_INET;
    fromlen = sizeof( from );

    MutexLock lock( mMSock );

    // Check for pending connects
    while( ( sock = mSock->accept( (sockaddr*)&from, &fromlen ) ) != NULL )
    {
#ifdef HAVE_WINSOCK2_H
        unsigned long nonblocking = 1;
        sock->ioctl( FIONBIO, &nonblocking );
#else /* !HAVE_WINSOCK2_H */
        sock->fcntl( F_SETFL, O_NONBLOCK );
#endif /* !HAVE_WINSOCK2_H */

        unsigned int bufsize = 64 * 1024; // 64kbyte receive buffer, up from default of 8k
        sock->setopt( SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof( bufsize ) );

        // New TCP connection, this must consume the socket.
        CreateNewConnection( sock, from.sin_addr.s_addr, ntohs( from.sin_port ) );
    }
}

#ifdef HAVE_WINDOWS_H
DWORD WINAPI BaseTCPServer::TCPServerLoop( LPVOID arg )
#else /* !HAVE_WINDOWS_H */
void* BaseTCPServer::TCPServerLoop( void* arg )
#endif /* !HAVE_WINDOWS_H */
{
    BaseTCPServer* tcps = reinterpret_cast< BaseTCPServer* >( arg );
    assert( tcps != NULL );

    tcps->TCPServerLoop();

#ifdef HAVE_WINDOWS_H
    return 0;
#else /* !HAVE_WINDOWS_H */
    return NULL;
#endif /* !HAVE_WINDOWS_H */
}

void BaseTCPServer::TCPServerLoop()
{
#ifdef HAVE_WINDOWS_H
    SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL );
#endif /* HAVE_WINDOWS_H */

#ifndef HAVE_WINDOWS_H
    sLog.Log( "Threading", "Starting TCPServerLoop with thread ID %d", pthread_self() );
#endif /* !HAVE_WINDOWS_H */

    mMLoopRunning.Lock();

    uint32 start = GetTickCount();
    uint32 etime;
    uint32 last_time;

    while( Process() )
    {
        /* UPDATE */
        last_time = GetTickCount();
        etime = last_time - start;

        // do the stuff for thread sleeping
        if( TCPSRV_LOOP_GRANULARITY > etime )
            Sleep( TCPSRV_LOOP_GRANULARITY - etime );

        start = GetTickCount();
    }

    mMLoopRunning.Unlock();

#ifndef HAVE_WINDOWS_H
    sLog.Log( "Threading", "Ending TCPServerLoop with thread ID %d", pthread_self() );
#endif /* !HAVE_WINDOWS_H */
}
