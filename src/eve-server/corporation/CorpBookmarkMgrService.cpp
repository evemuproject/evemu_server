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
    Author:        Ubiquitatis
*/

#include "eve-server.h"

#include "Client.h"
#include "PyServiceCD.h"
#include "cache/ObjCacheService.h"
#include "corporation/CorpBookmarkMgrService.h"

PyCallable_Make_InnerDispatcher(CorpBookmarkMgrService)

CorpBookmarkMgrService::CorpBookmarkMgrService(PyServiceMgr* mgr)
: PyService(mgr, "corpBookmarkMgr"),
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
    if(!m_manager->cache_service->IsCacheLoaded(method_id)) {
        PyDict *res = m_db.GetBookmarks(call.client->GetCorporationID());
        if(res == NULL)
            return NULL;

        PyRep* result = NULL;

        PyTuple *tuple = new PyTuple(2);
        tuple->items[0] = res;
        tuple->items[1] = new PyDict();

        result = tuple;
        m_manager->cache_service->GiveCache(method_id, &result);
    }

    return(m_manager->cache_service->MakeObjectCachedMethodCallResult(method_id));
}
