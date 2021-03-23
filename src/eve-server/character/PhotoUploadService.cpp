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
    Author:     caytchen
*/

#include "eve-server.h"

#include "PyServiceCD.h"
#include "character/PhotoUploadService.h"
#include "imageserver/ImageServer.h"

PyCallable_Make_InnerDispatcher(PhotoUploadService)

PhotoUploadService::PhotoUploadService(PyServiceMgr* mgr)
: PyService(mgr, "photoUploadSvc"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(PhotoUploadService, Upload);
}

PhotoUploadService::~PhotoUploadService()
{
    delete m_dispatch;
}

PyResult PhotoUploadService::Handle_Upload(PyCallArgs &call)
{
    Call_SingleStringArg arg;
    if (!arg.Decode(&call.tuple))
    {
        codelog(SERVICE__ERROR, "%s: Failed to decode arguments.", GetName());
        return  new PyBool(false);
    }

    std::shared_ptr<std::vector<char> > data(new std::vector<char>(arg.arg.begin(), arg.arg.end()));
    sImageServer.ReportNewImage(call.client->GetUserID(), data);

    call.client->SetPicRec(true);
    sLog.Magenta("   PhotoUploadSvc", "Received image from account %u, size: %u", call.client->GetUserID(), (uint32)arg.arg.size());

    return new PyBool(true);
}
