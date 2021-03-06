/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2021 The EVEmu Team
    For the latest information visit https://evemu.dev
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
    Author:        Reve, Allan
*/

//work in progress

#include "eve-server.h"

#include "PyServiceCD.h"
#include "fleet/FleetProxy.h"

PyCallable_Make_InnerDispatcher(FleetProxyService)

FleetProxyService::FleetProxyService(PyServiceMgr *mgr)
: PyService(mgr, "fleetProxy"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(FleetProxyService, GetAvailableFleets);
    PyCallable_REG_CALL(FleetProxyService, ApplyToJoinFleet);
    PyCallable_REG_CALL(FleetProxyService, AddFleetFinderAdvert);
    PyCallable_REG_CALL(FleetProxyService, RemoveFleetFinderAdvert);
    PyCallable_REG_CALL(FleetProxyService, GetMyFleetFinderAdvert);
    PyCallable_REG_CALL(FleetProxyService, UpdateAdvertInfo);
}

FleetProxyService::~FleetProxyService()
{
    delete m_dispatch;
}

PyResult FleetProxyService::Handle_GetAvailableFleets(PyCallArgs &call) {
//empty call

    return m_Mgr.GetAvailableFleets();
}

PyResult FleetProxyService::Handle_ApplyToJoinFleet(PyCallArgs &call) {
  /**
        ret = sm.ProxySvc('fleetProxy').ApplyToJoinFleet(fleetID)
        */

    sLog.Log("FleetProxyService", "Handle_ApplyToJoinFleet() size=%u", call.tuple->size() );

    return NULL;
}

PyResult FleetProxyService::Handle_AddFleetFinderAdvert(PyCallArgs &call) {
 /**
        sm.ProxySvc('fleetProxy').AddFleetFinderAdvert(info)
        */

    sLog.Log("FleetProxyService", "Handle_AddFleetFinderAdvert() size=%u", call.tuple->size() );

    return NULL;
}

PyResult FleetProxyService::Handle_RemoveFleetFinderAdvert(PyCallArgs &call) {

    sLog.Log("FleetProxyService", "Handle_RemoveFleetFinderAdvert() size=%u", call.tuple->size() );

    return NULL;
}

PyResult FleetProxyService::Handle_GetMyFleetFinderAdvert(PyCallArgs &call) {

    sLog.Log("FleetProxyService", "Handle_GetMyFleetFinderAdvert() size=%u", call.tuple->size() );

    return NULL;
}


PyResult FleetProxyService::Handle_UpdateAdvertInfo(PyCallArgs &call) {
  /**
                sm.ProxySvc('fleetProxy').UpdateAdvertInfo(numMembers)
                */

    sLog.Log("FleetProxyService", "Handle_UpdateAdvertInfo() size=%u", call.tuple->size() );

    return NULL;
}
