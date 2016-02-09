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
    Author:        Ubiquitatis
*/

#include "eve-server.h"

#include "Client.h"
#include "PyServiceCD.h"
#include "cache/ObjCacheService.h"
#include "corporation/CorpBookmarkMgrService.h"
#include "CorporationDB.h"
#include "PyServiceMgr.h"

PyCallable_Make_InnerDispatcher(CorpBookmarkMgrService)

CorpBookmarkMgrService::CorpBookmarkMgrService()
: PyService("corpBookmarkMgr"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(CorpBookmarkMgrService, GetBookmarks);
}

CorpBookmarkMgrService::~CorpBookmarkMgrService()
{
    delete m_dispatch;
}

PyResult CorpBookmarkMgrService::Handle_GetBookmarks(PyCallArgs& call)
{
    ObjectCachedMethodID method_id(GetName(), "GetBookmarks");
    if (!PyServiceMgr::cache_service->IsCacheLoaded(method_id))
    {
        PyDict *res = CorporationDB::GetBookmarks(call.client->GetCorporationID());
        if(res == NULL)
            return NULL;

        PyRep* result = NULL;

        PyTuple *tuple = new PyTuple(2);
        tuple->items[0] = res;
        tuple->items[1] = new PyDict();

        result = tuple;
        PyServiceMgr::cache_service->GiveCache(method_id, &result);
    }

    return (PyServiceMgr::cache_service->MakeObjectCachedMethodCallResult(method_id));
}
