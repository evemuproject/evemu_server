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
    Author:        Zhur
*/

#include "eve-server.h"

#include "PyServiceCD.h"
#include "cache/ObjCacheService.h"
#include "map/MapService.h"

PyCallable_Make_InnerDispatcher(MapService)

MapService::MapService(PyServiceMgr *mgr)
: PyService(mgr, "map"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(MapService, GetStationExtraInfo)
    PyCallable_REG_CALL(MapService, GetSolarSystemPseudoSecurities)
    PyCallable_REG_CALL(MapService, GetSolarSystemVisits)
    PyCallable_REG_CALL(MapService, GetBeaconCount)
    PyCallable_REG_CALL(MapService, GetHistory)
    PyCallable_REG_CALL(MapService, GetStationCount)

    /**  not handled yet...these are empty calls  */
    PyCallable_REG_CALL(MapService, GetStuckSystems)
    PyCallable_REG_CALL(MapService, GetRecentSovActivity)
    PyCallable_REG_CALL(MapService, GetDeadspaceAgentsMap)
    PyCallable_REG_CALL(MapService, GetDeadspaceComplexMap)
    PyCallable_REG_CALL(MapService, GetIncursionGlobalReport)
    PyCallable_REG_CALL(MapService, GetSystemsInIncursions)
    PyCallable_REG_CALL(MapService, GetSystemsInIncursionsGM)
    PyCallable_REG_CALL(MapService, GetVictoryPoints)
    PyCallable_REG_CALL(MapService, GetMyExtraMapInfo)
    PyCallable_REG_CALL(MapService, GetMyExtraMapInfoAgents)
    PyCallable_REG_CALL(MapService, GetAllianceJumpBridges)
    PyCallable_REG_CALL(MapService, GetLinkableJumpArrays)

}

MapService::~MapService() {
    delete m_dispatch;
}

PyResult MapService::Handle_GetStationExtraInfo(PyCallArgs &call) {
    //takes no arguments
    //returns tuple(
    //     stations: rowset stationID,solarSystemID,operationID,stationTypeID,ownerID
    //     opservices: rowset: (operationID, serviceID) (from staOperationServices)
    //     services: rowset: (serviceID,serviceName) (from staServices)
    // )

    PyRep *result = NULL;

    ObjectCachedMethodID method_id(GetName(), "GetStationExtraInfo");

    //check to see if this method is in the cache already.
    if(!m_manager->cache_service->IsCacheLoaded(method_id)) {
        //this method is not in cache yet, load up the contents and cache it.

        PyTuple *resultt = new PyTuple(3);

        resultt->items[0] = m_db.GetStationExtraInfo();
        if(resultt->items[0] == NULL) {
            codelog(SERVICE__ERROR, "Failed to query station info");
            return NULL;
        }

        resultt->items[1] = m_db.GetStationOpServices();
        if(resultt->items[1] == NULL) {
            codelog(SERVICE__ERROR, "Failed to query op services");
            return NULL;
        }

        resultt->items[2] = m_db.GetStationServiceInfo();
        if(resultt->items[2] == NULL) {
            codelog(SERVICE__ERROR, "Failed to query service info");
            return NULL;
        }

        result = resultt;
        m_manager->cache_service->GiveCache(method_id, &result);
    }

    //now we know its in the cache one way or the other, so build a
    //cached object cached method call result.
    result = m_manager->cache_service->MakeObjectCachedMethodCallResult(method_id);

    return result;
}


PyResult MapService::Handle_GetSolarSystemPseudoSecurities(PyCallArgs &call) {
    PyRep *result = NULL;

    ObjectCachedMethodID method_id(GetName(), "GetSolarSystemPseudoSecurities");

    //check to see if this method is in the cache already.
    if(!m_manager->cache_service->IsCacheLoaded(method_id)) {
        //this method is not in cache yet, load up the contents and cache it.
        result = m_db.GetPseudoSecurities();
        if(result == NULL)
            result = new PyNone();
        m_manager->cache_service->GiveCache(method_id, &result);
    }

    //now we know its in the cache one way or the other, so build a
    //cached object cached method call result.
    result = m_manager->cache_service->MakeObjectCachedMethodCallResult(method_id);

    return result;
}

PyResult MapService::Handle_GetSolarSystemVisits(PyCallArgs &call)
{
    //  will add this complete code with other map data at a later date  -allan 25Jul14

    //uint32 charID = call.client->GetCharacterID();
    //return (m_db.GetSolSystemVisits(charID));
	return new PyNone;
}

PyResult MapService::Handle_GetHistory(PyCallArgs &call) {
    //  will add this complete code with other map data at a later date  -allan 25Jul14

    //return (m_db.GetDynamicData(int1, int2));
	return new PyNone;
}

PyResult MapService::Handle_GetBeaconCount(PyCallArgs &call) {
    //  will add this complete code with other map data at a later date  -allan 25Jul14

    //return (m_db.GetDynamicData(2, 24));
	return new PyNone;
}

PyResult MapService::Handle_GetStationCount(PyCallArgs &call)
{
    //  will add this complete code with other map data at a later date  -allan 25Jul14

    //return (m_db.GetStationCount());
	return new PyNone;
}

/** not handled */
PyResult MapService::Handle_GetStuckSystems(PyCallArgs &call) {
    uint8 none = 0;

    PyTuple* res = NULL;
    PyTuple* tuple0 = new PyTuple( 1 );

    tuple0->items[ 0 ] = new PyInt( none );

    res = tuple0;

    return res;
}

PyResult MapService::Handle_GetRecentSovActivity(PyCallArgs &call)
{
    PyRep *result = NULL;
    result = new PyDict();

    return result;
}

PyResult MapService::Handle_GetDeadspaceAgentsMap(PyCallArgs &call)
{
//   DED Agent Site Report
    PyRep *result = NULL;
    result = new PyDict();

    return result;
}

PyResult MapService::Handle_GetDeadspaceComplexMap(PyCallArgs &call)
{
//  DED Deadspace Report
    PyRep *result = NULL;
    result = new PyDict();

    return result;
}

PyResult MapService::Handle_GetIncursionGlobalReport(PyCallArgs &call)
{
    return NULL;
}

PyResult MapService::Handle_GetSystemsInIncursions(PyCallArgs &call)
{
    return NULL;
}

PyResult MapService::Handle_GetSystemsInIncursionsGM(PyCallArgs &call)
{
    return NULL;
}

PyResult MapService::Handle_GetAllianceSystems(PyCallArgs &call)
{
    return NULL;
}

PyResult MapService::Handle_GetVictoryPoints(PyCallArgs &call)
{
//   factional warfare shit
    return NULL;
}

PyResult MapService::Handle_GetMyExtraMapInfoAgents(PyCallArgs &call)
{
    return NULL;
}

PyResult MapService::Handle_GetMyExtraMapInfo(PyCallArgs &call)
{
    return NULL;
}
PyResult MapService::Handle_GetAllianceJumpBridges(PyCallArgs &call)
{
    return NULL;
}

PyResult MapService::Handle_GetLinkableJumpArrays(PyCallArgs &call)
{
    return NULL;
}
