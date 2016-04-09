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
    Author:     caytchen
*/

#include "eve-server.h"

#include "PyServiceCD.h"
#include "character/PhotoUploadService.h"
#include "imageserver/ImageServer.h"

std::mutex PhotoUploadService::s_limboLock;
std::unordered_map<uint32 /*accountID*/, std::shared_ptr<std::vector<char> > /*imageData*/> PhotoUploadService::s_limboImages;

PyCallable_Make_InnerDispatcher(PhotoUploadService)

PhotoUploadService::PhotoUploadService()
: PyService("photoUploadSvc", new Dispatcher(this))
{
    PyCallable_REG_CALL(PhotoUploadService, Upload)
}

PhotoUploadService::~PhotoUploadService()
{
}

PyResult PhotoUploadService::Handle_Upload(PyCallArgs &call)
{
    Call_SingleStringArg arg;
    if (!arg.Decode(&call.tuple))
    {
        codelog(CLIENT__ERROR, "Failed to decode args for Upload call");
        return NULL;
    }

    SysLog::Log("photo upload", "Received image from account %i, size: %i", call.client->GetAccountID(), arg.arg.size());

    std::shared_ptr<std::vector<char> > data(new std::vector<char>(arg.arg.begin(), arg.arg.end()));
    reportNewImage(call.client->GetAccountID(), data);

    return new PyBool(true);
}

void PhotoUploadService::reportNewImage(uint32 accountID, std::shared_ptr<std::vector<char> > imageData)
{
    std::unique_lock<std::mutex> lock(s_limboLock);

    if(s_limboImages.find(accountID) != s_limboImages.end())
    {
        s_limboImages.insert(std::pair<uint32, std::shared_ptr<std::vector<char> > >(accountID, imageData));
    }
    else
    {
        s_limboImages[accountID] = imageData;
    }
}

void PhotoUploadService::reportNewCharacter(uint32 creatorAccountID, uint32 characterID)
{
    std::unique_lock<std::mutex> lock(s_limboLock);

    // check if we received an image from this account previously
    if(s_limboImages.find(creatorAccountID) == s_limboImages.end())
    {
        return;
    }

    // we have, so save it
    std::string dirName = "Character";
    std::string path(ImageServer::getFilePath(dirName, characterID, 512));
    FILE * fp = fopen(path.c_str(), "wb");

    //stream.open(path, std::ios::binary | std::ios::trunc | std::ios::out);
    std::shared_ptr<std::vector<char> > data = s_limboImages[creatorAccountID];

    fwrite(&((*data)[0]), 1, data->size(), fp);
    fclose(fp);

    // and delete it from our limbo map
    s_limboImages.erase(creatorAccountID);

    SysLog::Log("Photo Upload", "Saved image from %i as %s", creatorAccountID, path.c_str());
}

