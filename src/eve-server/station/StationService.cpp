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
    Author:        Zhur
*/

#include "eve-server.h"

#include "EntityList.h"
#include "PyServiceCD.h"
#include "station/StationService.h"

PyCallable_Make_InnerDispatcher(StationService)

StationService::StationService(PyServiceMgr *mgr)
: PyService(mgr, "station"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(StationService, GetGuests);
    PyCallable_REG_CALL(StationService, GetSolarSystem);
}

StationService::~StationService() {
    delete m_dispatch;
}

PyResult StationService::Handle_GetSolarSystem(PyCallArgs &call) {
    Call_SingleIntegerArg arg;
    if (!arg.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "%s: Failed to decode arguments.", GetName());
        return NULL;
    }

    // this needs to return some cache status?
    return new PyObject("util.CachedObject", new PyInt(arg.arg));
}

PyResult StationService::Handle_GetGuests(PyCallArgs &call) {
    std::vector<Client*> clients;
    clients.clear();
    sEntityList.GetStationGuestList(call.client->GetStationID(), clients);
    PyList* res = new PyList();
    for (auto cur : clients) {
        PyTuple* t = new PyTuple(4);
			t->items[0] = new PyInt(cur->GetCharacterID());
			t->items[1] = new PyInt(cur->GetCorporationID());
			t->items[2] = new PyInt(cur->GetAllianceID());
			t->items[3] = new PyInt(cur->GetWarFactionID());
        res->AddItem(t);
    }

	return res;
}
