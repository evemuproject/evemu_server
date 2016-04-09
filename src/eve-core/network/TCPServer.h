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
    Author:     Zhur, Bloody.Rabbit
 */

#ifndef __NETWORK__TCP_SERVER_H__INCL__
#define __NETWORK__TCP_SERVER_H__INCL__

#include "network/Socket.h"
#include "log/SystemLog.h"

#include <thread>
#include <mutex>

/**
 * Size of error buffer TCPServer uses.
 */
#define TCPSRV_ERRBUF_SIZE 1024
/**
 * Time (in milliseconds) between periodical checks of socket for new connections.
 */
#define TCPSRV_LOOP_GRANULARITY 5

/**
 * @brief Generic class for TCP server.
 * @author Zhur, Bloody.Rabbit
 */
template<typename X>
class TCPServer
{
public:

    /**
     * @brief Creates empty TCP server.
     */
    TCPServer()
    : m_socket(nullptr),
    m_port(0) { }

    /**
     * @brief Cleans server up.
     */
    virtual ~TCPServer()
    {
        // Close socket
        close();
        // Clear the connections.
        X* conn;
        while ((conn = popConnection()))
        {
            SafeDelete(conn);
        }

        // Wait until worker thread terminates
        auto loopLock = getLoopLock();
    }

    /**
     * @return TCP port the server listens on.
     */
    uint16 getPort() const
    {
        return m_port;
    }

    /**
     *  @return True if listening has been opened, false if not.
     */
    bool isOpen() const
    {
        return ( m_socket != nullptr);
    }

    /**
     * @brief Start listening on specified port.
     *
     * @param[in]  port   Port on which listening should be started.
     * @param[out] errbuf Error buffer which receives description of error.
     *
     * @return True if listening has been started successfully, false if not.
     */
    bool open(uint16 port, const std::string &bindAddress, char* errbuf = 0)
    {
        if (errbuf != nullptr)
        {
            errbuf[0] = 0;
        }

        // mutex lock
        auto lock = getSocketLock();
        if (m_socket != nullptr)
        {
            if (errbuf != nullptr)
            {
                snprintf(errbuf, TCPSRV_ERRBUF_SIZE, "Listening socket already open");
            }
            return false;
        }
        else
        {
            lock.unlock();
            // Wait for thread to terminate
            auto loopLock = getLoopLock();
            loopLock.unlock();
            lock.lock();
        }

        // Setting up TCP port for new TCP connections
        m_socket = new Socket(AF_INET, SOCK_STREAM, 0);

        // Quag: don't think following is good stuff for TCP, good for UDP
        // Mis: SO_REUSEADDR shouldn't be a problem for tcp - allows you to restart
        //      without waiting for conn's in TIME_WAIT to die
        unsigned int reuse_addr = 1;
        m_socket->setopt(SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof ( reuse_addr));

        // Setup internet address information.
        // This is used with the bind() call
        sockaddr_in address;
        memset(&address, 0, sizeof ( address));

        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        if (bindAddress.empty())
        {
            address.sin_addr.s_addr = htonl(INADDR_ANY);
        }
        else
        {
            address.sin_addr.s_addr = inet_addr(bindAddress.c_str());
        }

        int bRes = m_socket->bind((sockaddr*) & address, sizeof ( address));
        if (bRes < 0)
        {
            if (errbuf != nullptr)
            {
                snprintf(errbuf, TCPSRV_ERRBUF_SIZE, "Failed to bind socket to port: %u address: %s", port, bindAddress.c_str());
            }

            SafeDelete(m_socket);
            return false;
        }

        unsigned int bufsize = 64 * 1024; // 64kbyte receive buffer, up from default of 8k
        m_socket->setopt(SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof ( bufsize));

#ifdef HAVE_WINSOCK2_H
        unsigned long nonblocking = 1;
        m_socket->ioctl(FIONBIO, &nonblocking);
#else /* !HAVE_WINSOCK2_H */
        m_socket->fcntl(F_SETFL, O_NONBLOCK);
#endif /* !HAVE_WINSOCK2_H */

        if (m_socket->listen() == SOCKET_ERROR)
        {
            if (errbuf != nullptr)
            {
#ifdef HAVE_WINSOCK2_H
                snprintf(errbuf, TCPSRV_ERRBUF_SIZE, "listen() failed, Error: %u", WSAGetLastError());
#else /* !HAVE_WINSOCK2_H */
                snprintf(errbuf, TCPSRV_ERRBUF_SIZE, "listen() failed, Error: %s", strerror(errno));
#endif /* !HAVE_WINSOCK2_H */
            }

            SafeDelete(m_socket);
            return false;
        }

        m_port = port;

        // Start processing thread
        m_thread = std::thread(&TCPServer::serverLoop, this);
        m_thread.detach();

        return true;
    }

    /**
     * @brief Stops started listening.
     */
    void close()
    {
        auto lock = getSocketLock();
        SafeDelete(m_socket);
        m_port = 0;
    }

    /**
     * @brief Pops connection from queue.
     * @return Popped connection.
     */
    X* popConnection()
    {
        auto lock = getQueueLock();
        X* ret = NULL;
        if (!m_queue.empty())
        {
            ret = m_queue.front();
            m_queue.pop();
        }
        return ret;
    }

protected:

    /**
     * @brief Accepts all new connections.
     */
    bool listenForNewConnections()
    {
        Socket* sock;
        sockaddr_in from;
        unsigned int fromlen;

        from.sin_family = AF_INET;
        fromlen = sizeof ( from);

        auto lock = getSocketLock();
        if (m_socket == nullptr)
        {
            // The socket has been closed.
            return false;
        }

        // Check for pending connects
        while ((sock = m_socket->accept((sockaddr*) & from, &fromlen)) != nullptr)
        {
#ifdef HAVE_WINSOCK2_H
            unsigned long nonblocking = 1;
            sock->ioctl(FIONBIO, &nonblocking);
#else /* !HAVE_WINSOCK2_H */
            sock->fcntl(F_SETFL, O_NONBLOCK);
#endif /* !HAVE_WINSOCK2_H */

            unsigned int bufsize = 64 * 1024; // 64kbyte receive buffer, up from default of 8k
            sock->setopt(SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof ( bufsize));

            // New TCP connection, this must consume the socket.
            addConnection(new X(sock, from.sin_addr.s_addr, ntohs(from.sin_port)));
        }
        return true;
    }

    /**
     * @brief Loop for worker threads.
     */
    void serverLoop()
    {
#ifdef HAVE_WINDOWS_H
        SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
#endif /* HAVE_WINDOWS_H */

#ifndef HAVE_WINDOWS_H
        SysLog::Log("Threading", "Starting TCPServerLoop with thread ID %d", pthread_self());
#endif /* !HAVE_WINDOWS_H */

        auto lock = getLoopLock();

        uint32 start = GetTickCount();
        uint32 etime;
        uint32 last_time;

        while (listenForNewConnections())
        {
            /* UPDATE */
            last_time = GetTickCount();
            etime = last_time - start;

            // do the stuff for thread sleeping
            if (TCPSRV_LOOP_GRANULARITY > etime)
            {
                Sleep(TCPSRV_LOOP_GRANULARITY - etime);
            }

            start = GetTickCount();
        }

#ifndef HAVE_WINDOWS_H
        SysLog::Log("Threading", "Ending TCPServerLoop with thread ID %d", pthread_self());
#endif /* !HAVE_WINDOWS_H */
    }

    /**
     * Mutex to protect socket and associated variables.
     */
    mutable std::mutex m_socketMutex;

    std::unique_lock<std::mutex> getSocketLock() const
    {
        return std::unique_lock<std::mutex>(m_socketMutex);
    }
    /**
     * Socket used for listening.
     */
    Socket* m_socket;
    /**
     * Port the socket is listening on.
     */
    uint16 m_port;

    /**
     * Worker thread acquires this mutex before it starts processing; used for thread synchronization.
     */
    mutable std::mutex m_loopRunningMutex;

    std::unique_lock<std::mutex> getLoopLock() const
    {
        return std::unique_lock<std::mutex>(m_loopRunningMutex);
    }

    /**
     * @brief Adds connection to the queue.
     * @param[in] con Connection to be added to the queue.
     */
    void addConnection(X* con)
    {
        auto lock = getQueueLock();
        m_queue.push(con);
    }

    /**
     *  Mutex to protect connection queue.
     */
    std::mutex m_queueMutex;

    std::unique_lock<std::mutex> getQueueLock()
    {
        return std::unique_lock<std::mutex>(m_queueMutex);
    }
    /**
     * Connection queue.
     */
    std::queue<X*> m_queue;

    /**
     * The worker thread.
     */
    std::thread m_thread;
};

#endif /* !__NETWORK__TCP_SERVER_H__INCL__ */
