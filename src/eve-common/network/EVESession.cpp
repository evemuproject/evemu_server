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

#include "eve-common.h"

#include "marshal/EVEMarshal.h"
#include "marshal/EVEUnmarshal.h"
#include "network/EVESession.h"
#include "packets/Crypto.h"
#include "python/PyRep.h"
#include "python/PyPacket.h"
#include "EVEVersion.h"

EVEClientSession::EVEClientSession(EVETCPConnection** n)
: m_tcpConnecton(*n),
m_packetHandler(NULL)
{
    *n = NULL;
}

EVEClientSession::~EVEClientSession()
{
    // Destroy connection we used
    delete m_tcpConnecton;
}

void EVEClientSession::reset()
{
    m_packetHandler = NULL;

    if(getState() != TCPConnection::STATE_CONNECTED)
        // Connection has been lost, there's no point in reset
        return;

    VersionExchangeServer version;
    _GetVersion( version );

    PyRep* r = version.Encode();
    m_tcpConnecton->QueueRep(r);
    PyDecRef( r );

    m_packetHandler = &EVEClientSession::_HandleVersion;
}

void EVEClientSession::fastQueuePacket(PyPacket** p, bool front)
{
    if(p == NULL || *p == NULL)
    {
        return;
    }

    if(is_log_enabled(CLIENT__OUT_ALL))
    {
        std::string pfx = getLogPrefix(CLIENT__OUT_ALL);
        std::ostringstream ss;
        (*p)->dump(ss, pfx);
        outputLogMsg(CLIENT__OUT_ALL, ss.str().c_str());
    }

    PyRep* r = (*p)->Encode();
    // maybe change PyPacket to a object with a reference..
    SafeDelete( *p );
    if( r == NULL )
    {
        SysLog::Error("Network", "%s: Failed to encode a Fast queue packet???", getAddress().c_str());
        return;
    }

    m_tcpConnecton->QueueRep(r, front);
    PyDecRef( r );
}

PyPacket* EVEClientSession::popPacket()
{
    PyRep* r = m_tcpConnecton->PopRep();
    if( r == NULL )
        return NULL;

    if(is_log_enabled(NET__PRES_REP))
    {
        _log(NET__PRES_REP, "%s: Raw Rep Dump:", getAddress().c_str());
        r->Dump(NET__PRES_REP, "    ");
    }

    assert(m_packetHandler);
    return ( this->*m_packetHandler)(r);
}

PyPacket* EVEClientSession::_HandleVersion( PyRep* rep )
{
    //we are waiting for their version information...
    VersionExchangeClient ve;
    if( !ve.Decode( &rep ))
        SysLog::Error("Network", "%s: Received invalid version exchange!", getAddress().c_str());
    else if( _VerifyVersion( ve ))
        m_packetHandler = &EVEClientSession::_HandleCommand;

    // recurse
    return popPacket();
}

PyPacket* EVEClientSession::_HandleCommand( PyRep* rep )
{
    //check if it actually is tuple
    if( !pyIs(Tuple, rep) )
    {
        SysLog::Error("Network", "%s: Invalid packet during waiting for command (tuple expected).", getAddress().c_str());
    }
    // decode
    else if( pyAs(Tuple, rep)->size() == 2 )
    {
        //QC = Queue Check
        NetCommand_QC cmd;
        if( !cmd.Decode( &rep ) )
        {
            SysLog::Error("Network", "%s: Failed to decode 2-arg command.", getAddress().c_str());
        }
        else
        {
            SysLog::Debug("Network", "%s: Got Queue Check command.", getAddress().c_str());

            //they return position in queue
            PyRep* rsp = new PyInt( _GetQueuePosition() );
            m_tcpConnecton->QueueRep(rsp);
            PyDecRef( rsp );

            //now reset connection
            reset();
        }
    }
    else if( pyAs(Tuple, rep)->size() == 3 )
    {
        //this is sent when client is logging in
        NetCommand_VK cmd;
        if( !cmd.Decode( &rep ) )
        {
            SysLog::Error("Network", "%s: Failed to decode 3-arg command.", getAddress().c_str());
        }
        else
        {
            SysLog::Debug("Network", "%s: Got VK command, vipKey=%s.", getAddress().c_str(), cmd.vipKey.c_str());

            if( _VerifyVIPKey( cmd.vipKey ))
                m_packetHandler = &EVEClientSession::_HandleCrypto;
        }
    }
    else
    {
        _log(NET__PRES_ERROR, "%s: Received invalid command packet:", getAddress().c_str());
        rep->Dump(NET__PRES_ERROR, "  ");
    }

    // recurse
    return popPacket();
}

PyPacket* EVEClientSession::_HandleCrypto( PyRep* rep )
{
    CryptoRequestPacket cr;
    if( !cr.Decode( &rep ))
        SysLog::Error("Network", "%s: Received invalid crypto request!", getAddress().c_str());
    else if( _VerifyCrypto( cr ))
        m_packetHandler = &EVEClientSession::_HandleAuthentication;

    // recurse
    return popPacket();
}

PyPacket* EVEClientSession::_HandleAuthentication( PyRep* rep )
{
    //just to be sure
    CryptoChallengePacket ccp;
    if( !ccp.Decode( &rep ))
        SysLog::Error("Network", "%s: Received invalid crypto challenge!", getAddress().c_str());
    else if( _VerifyLogin( ccp ))
        m_packetHandler = &EVEClientSession::_HandleFuncResult;

    return popPacket();
}

PyPacket* EVEClientSession::_HandleFuncResult( PyRep* rep )
{
    CryptoHandshakeResult hr;
    if( !hr.Decode( &rep ))
        SysLog::Error("Network", "%s: Received invalid crypto handshake result!", getAddress().c_str());
    else if( _VerifyFuncResult( hr ))
        m_packetHandler = &EVEClientSession::_HandlePacket;

    // recurse
    return popPacket();
}

PyPacket* EVEClientSession::_HandlePacket( PyRep* rep )
{
    //take the PyRep and turn it into a PyPacket
    PyPacket* p = new PyPacket;
    if( !p->Decode( &rep ) ) //rep is consumed here
    {
        SysLog::Error("Network", "%s: Failed to decode packet rep", getAddress().c_str());
        SafeDelete( p );
    }
    else
        return p;

    // recurse
    return popPacket();
}
