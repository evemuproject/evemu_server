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

#ifndef __IMAGESERVER__H__INCL__
#define __IMAGESERVER__H__INCL__

#include "../EVEServerConfig.h"

class ImageServerListener;

/**
 * \class ImageServer
 *
 * @brief Handles distribution of character and related game images
 *
 * A very limited HTTP server that can efficiently deliver character and other images to clients
 * Uses asio for efficient asynchronous network communication
 *
 * @author caytchen
 * @date April 2011
 */
class ImageServer
{
private:
    ImageServer() = delete;
public:
    static void run();
    static void stop();

    static std::string getURL(EVEServerConfig::EVEConfigNet &network);

    static std::string getFilePath(std::string& category, uint32 id, uint32 size);
    static std::shared_ptr<std::vector<char> > getImage(std::string& category, uint32 id, uint32 size);

    static const char *const Categories[];
    static const uint32 CategoryCount;

    // used when the ImageServer can't find the image requested
    // this way we don't have to transfer over all the static NPC images
    static const char *const FallbackURL;

private:
    static void runInternal();
    static bool validateCategory(std::string& category);
    static bool validateSize(std::string& category, uint32 size);

    static std::shared_ptr<boost::asio::detail::thread> _ioThread;
    static std::shared_ptr<boost::asio::io_service> _io;
    static std::shared_ptr<ImageServerListener> _listener;
    static std::string _basePath;

};

#endif // __IMAGESERVER__H__INCL__
