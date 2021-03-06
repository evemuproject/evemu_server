/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2021 The EVEmu Team
    For the latest information visit https://github.com/evemuproject/evemu_server
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
    Author:        Aknor Jaden, adapted from ImageServer.h authored by caytchen
*/

#include "eve-server.h"

#include "EVEServerConfig.h"
#include "apiserver/APIServerListener.h"

APIServerListener::APIServerListener(boost::asio::io_context& io)
{
    _acceptor = new boost::asio::ip::tcp::acceptor(io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), sConfig.net.apiServerPort));
    sLog.Log("API Server Init", "listening on port %u", (sConfig.net.apiServerPort));
    StartAccept();
}

APIServerListener::~APIServerListener()
{
    delete _acceptor;
}

void APIServerListener::StartAccept()
{
    boost::asio::executor e = _acceptor->get_executor();
    boost::asio::execution_context &e_context = e.context();
    boost::asio::io_context &context_instance = static_cast<boost::asio::io_context&>(e_context);

    std::tr1::shared_ptr<APIServerConnection> connection = APIServerConnection::create(context_instance);
    _acceptor->async_accept(connection->socket(), std::bind(&APIServerListener::HandleAccept, this, connection));
}

void APIServerListener::HandleAccept(std::tr1::shared_ptr<APIServerConnection> connection)
{
    connection->Process();
    StartAccept();
}
