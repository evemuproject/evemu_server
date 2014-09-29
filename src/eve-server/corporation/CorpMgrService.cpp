/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2011 The EVEmu Team
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
    Author:        Zhur
*/

#include "eve-server.h"

#include "PyServiceCD.h"
#include "corporation/CorpMgrService.h"

PyCallable_Make_InnerDispatcher(CorpMgrService)

CorpMgrService::CorpMgrService(PyServiceMgr *mgr)
: PyService(mgr, "corpmgr"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(CorpMgrService, GetPublicInfo)
    PyCallable_REG_CALL(CorpMgrService, GetCorporations)
    PyCallable_REG_CALL(CorpMgrService, GetAssetInventory)
    PyCallable_REG_CALL(CorpMgrService, GetCorporationStations)
    PyCallable_REG_CALL(CorpMgrService, GetCorporationIDForCharacter)
    PyCallable_REG_CALL(CorpMgrService, GetAssetInventoryForLocation)
}

CorpMgrService::~CorpMgrService() {
    delete m_dispatch;
}

PyResult CorpMgrService::Handle_GetPublicInfo(PyCallArgs &call) {
    Call_SingleIntegerArg corpID;
    if (!corpID.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Bad param");
        return NULL;
    }

    return m_db.GetCorporation(corpID.arg);
}

PyResult CorpMgrService::Handle_GetCorporations(PyCallArgs &call) {

    return NULL;
}

PyResult CorpMgrService::Handle_GetAssetInventory(PyCallArgs &call) {
    //  will add this complete code with other map data at a later date  -allan 25Jul14
    return NULL;
}

PyResult CorpMgrService::Handle_GetCorporationStations(PyCallArgs &call) {
    //  will add this complete code with other map data at a later date  -allan 25Jul14

    return NULL;
}

PyResult CorpMgrService::Handle_GetCorporationIDForCharacter(PyCallArgs &call) {

    return NULL;
}

PyResult CorpMgrService::Handle_GetAssetInventoryForLocation(PyCallArgs &call) {
    //  will add this complete code with other map data at a later date  -allan 25Jul14

    return NULL;
}