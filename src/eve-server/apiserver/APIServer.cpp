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
    Author:        Aknor Jaden, adapted from ImageServer.h authored by caytchen
*/

#include "eve-server.h"

#include "EVEServerConfig.h"
#include "apiserver/APIAccountManager.h"
#include "apiserver/APIActiveObjectManager.h"
#include "apiserver/APIAdminManager.h"
#include "apiserver/APICharacterManager.h"
#include "apiserver/APICorporationManager.h"
#include "apiserver/APIEveSystemManager.h"
#include "apiserver/APIMapManager.h"
#include "apiserver/APIServer.h"
#include "apiserver/APIServerManager.h"

const char *const APIServer::FallbackURL = "http://api.eveonline.com/";

std::unique_ptr<boost::asio::detail::thread> APIServer::_ioThread;
std::unique_ptr<boost::asio::io_service> APIServer::_io;
std::unique_ptr<APIServerListener> APIServer::_listener;
std::string APIServer::_url;
std::string APIServer::_basePath;
boost::asio::detail::mutex APIServer::_limboLock;
bool APIServer::runonce = false;

std::shared_ptr<std::string> APIServer::m_xmlString;

std::map<std::string, APIServiceManager *> APIServer::m_APIServiceManagers; // We own these

APIServer::APIServer()
{
    runonce = false;
}

void APIServer::CreateServices()
{
    if (!runonce)
    {
        return;
    }
    runonce = true;
    std::stringstream urlBuilder;
    urlBuilder << "http://" << EVEServerConfig::net.apiServer << ":" << (EVEServerConfig::net.apiServerPort) << "/";
    _url = urlBuilder.str();
    m_APIServiceManagers.insert(std::make_pair("base", new APIServiceManager()));
    m_APIServiceManagers.insert(std::make_pair("account", new APIAccountManager()));
    m_APIServiceManagers.insert(std::make_pair("admin", new APIAdminManager()));
    m_APIServiceManagers.insert(std::make_pair("char", new APICharacterManager()));
    m_APIServiceManagers.insert(std::make_pair("corp", new APICorporationManager()));
    m_APIServiceManagers.insert(std::make_pair("eve", new APIEveSystemManager()));
    m_APIServiceManagers.insert(std::make_pair("map", new APIMapManager()));
    m_APIServiceManagers.insert(std::make_pair("object", new APIActiveObjectManager()));
    m_APIServiceManagers.insert(std::make_pair("server", new APIServerManager()));
}

std::shared_ptr<std::vector<char> > APIServer::GetXML(const APICommandCall * pAPICommandCall)
{
    //if( m_APIServiceManagers.find(pAPICommandCall->at(0).first) != m_APIServiceManagers.end() )
    if( pAPICommandCall->find( "service" ) == pAPICommandCall->end() )
    {
        SysLog::Error( "APIserver::GetXML()", "Cannot find 'service' specifier in pAPICommandCall packet" );
        return std::shared_ptr<std::vector<char> >(new std::vector<char>() );
        //return std::shared_ptr<std::string>(new std::string(""));
    }

    if( m_APIServiceManagers.find(pAPICommandCall->find( "service" )->second) != m_APIServiceManagers.end() )
    {
        // Get reference to service manager object and call ProcessCall() with the pAPICommandCall packet
        //m_xmlString = m_APIServiceManagers.find("base")->second->ProcessCall(pAPICommandCall);
        m_xmlString = m_APIServiceManagers.find( pAPICommandCall->find( "service" )->second )->second->ProcessCall( pAPICommandCall );

        // Convert the std::string to the std::vector<char>:
        std::shared_ptr<std::vector<char> > ret = std::shared_ptr<std::vector<char> >(new std::vector<char>());
        unsigned long len = m_xmlString->length();
        for(size_t i=0; i<m_xmlString->length(); i++)
            ret->push_back(m_xmlString->at(i));

        return ret;
    }
    else
    {
        // Service call not found, so return NULL:
        return std::shared_ptr<std::vector<char> >(new std::vector<char>() );
        //return NULL;
        //m_xmlString = m_APIServiceManagers.find("base")->second->ProcessCall(pAPICommandCall);
    }
}

std::string& APIServer::url()
{
    return _url;
}

void APIServer::Run()
{
    _ioThread = std::unique_ptr<boost::asio::detail::thread>(new boost::asio::detail::thread(std::bind(&APIServer::RunInternal)));
}

void APIServer::Stop()
{
    _io->stop();
    _ioThread->join();
}

void APIServer::RunInternal()
{
    _io = std::unique_ptr<boost::asio::io_service>(new boost::asio::io_service());
    _listener = std::unique_ptr<APIServerListener>(new APIServerListener(*_io));
    _io->run();
}

APIServer::Lock::Lock(boost::asio::detail::mutex& mutex)
    : _mutex(mutex)
{
    _mutex.lock();
}

APIServer::Lock::~Lock()
{
    _mutex.unlock();
}
