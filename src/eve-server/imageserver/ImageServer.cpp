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
    Author:        caytchen
*/

#include "eve-server.h"

#include "EVEServerConfig.h"
#include "imageserver/ImageServer.h"
#include "imageserver/ImageServerListener.h"

const char *const ImageServer::FallbackURL = "http://image.eveonline.com/";

const char *const ImageServer::Categories[] = {
    "Alliance",
    "Corporation",
    "Character",
    "InventoryType",
    "Render" };

const uint32 ImageServer::CategoryCount = 5;

std::shared_ptr<boost::asio::detail::thread> ImageServer::_ioThread;
std::shared_ptr<boost::asio::io_service> ImageServer::_io;
std::shared_ptr<ImageServerListener> ImageServer::_listener;
std::string ImageServer::_basePath;

std::shared_ptr<std::vector<char> > ImageServer::getImage(std::string& category, uint32 id, uint32 size)
{
    if(!validateCategory(category) || !validateSize(category, size))
    {
        return std::shared_ptr<std::vector<char> >();
    }

    // Get the file path.
    std::string path(getFilePath(category, id, size));
    // Open the file.
    FILE * fp = fopen(path.c_str(), "rb");
    if(fp == NULL)
    {
        // File not found, return empty result.
        return std::shared_ptr<std::vector<char> >();
    }
    // Get file length.
    fseek(fp, 0, SEEK_END);
    size_t length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Allocate memory for file.
    std::shared_ptr<std::vector<char> > ret = std::shared_ptr<std::vector<char> >(new std::vector<char>());
    ret->resize(length);

    // Read the file.
    fread(&((*ret)[0]), 1, length, fp);

    return ret;
}

std::string ImageServer::getFilePath(std::string& category, uint32 id, uint32 size)
{
    std::string extension = category == "Character" ? "jpg" : "png";

    if(category == "Character")
    {
        // HACK: We don't have any other
        size = 512;
    }

    std::stringstream builder;
    builder << _basePath << category << "/" << id << "_" << size << "." << extension;
    return builder.str();
}

bool ImageServer::validateSize(std::string& category, uint32 size)
{
    if (category == "InventoryType")
        return size == 64 || size == 32;

    if (category == "Alliance")
        return size == 128 || size == 64 || size == 32;

    if (category == "Corporation")
        return size == 256 || size == 128 || size == 64 || size == 32;

    // Render and Character
    return size == 512 || size == 256 || size == 128 || size == 64 || size == 32;
}

bool ImageServer::validateCategory(std::string& category)
{
    for (int i = 0; i < 5; i++)
        if (category == Categories[i])
            return true;
    return false;
}

std::string ImageServer::getURL(EVEServerConfig::EVEConfigNet &network)
{
    std::stringstream urlBuilder;
    urlBuilder << "http://" << network.imageServer << ":" << (network.imageServerPort) << "/";
    return urlBuilder.str();
}

void ImageServer::run()
{
    if (_ioThread != nullptr)
    {
        return;
    }
    // Initialize the server.

    _basePath = EVEServerConfig::files.imageDir;
    if (_basePath[_basePath.size() - 1] != '/')
        _basePath += "/";

    CreateDirectory(_basePath.c_str(), NULL);

    for (int i = 0; i < CategoryCount; i++)
    {
        std::string subdir = _basePath;
        subdir.append(Categories[i]);

        CreateDirectory(subdir.c_str(), NULL);
    }

    SysLog::Log("Image Server Init", "our base: %s", _basePath.c_str());

    // Start thread.
    _ioThread = std::shared_ptr<boost::asio::detail::thread>(new boost::asio::detail::thread(std::bind(&ImageServer::runInternal)));
}

void ImageServer::stop()
{
    _io->stop();
    _ioThread->join();
}

void ImageServer::runInternal()
{
    _io = std::shared_ptr<boost::asio::io_service>(new boost::asio::io_service());
    _listener = std::shared_ptr<ImageServerListener>(new ImageServerListener(*_io));
    _io->run();
}
