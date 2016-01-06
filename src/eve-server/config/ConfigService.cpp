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
#include "config/ConfigService.h"

PyCallable_Make_InnerDispatcher(ConfigService)

ConfigService::ConfigService(PyServiceMgr *mgr)
: PyService(mgr, "config"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(ConfigService, GetMultiOwnersEx)
    PyCallable_REG_CALL(ConfigService, GetMultiLocationsEx)
    PyCallable_REG_CALL(ConfigService, GetMultiAllianceShortNamesEx)
    PyCallable_REG_CALL(ConfigService, GetMultiCorpTickerNamesEx)
    PyCallable_REG_CALL(ConfigService, GetUnits)
    PyCallable_REG_CALL(ConfigService, GetMap)
    PyCallable_REG_CALL(ConfigService, GetMapOffices)
    PyCallable_REG_CALL(ConfigService, GetMapObjects)
    PyCallable_REG_CALL(ConfigService, GetMapConnections)
    PyCallable_REG_CALL(ConfigService, GetMultiGraphicsEx)
    PyCallable_REG_CALL(ConfigService, GetMultiInvTypesEx)
    PyCallable_REG_CALL(ConfigService, GetStationSolarSystemsByOwner)
    PyCallable_REG_CALL(ConfigService, GetCelestialStatistic)
    PyCallable_REG_CALL(ConfigService, GetDynamicCelestials)
    PyCallable_REG_CALL(ConfigService, GetMapLandmarks)
    PyCallable_REG_CALL(ConfigService, SetMapLandmarks)
}

ConfigService::~ConfigService() {
    delete m_dispatch;
}

PyResult ConfigService::Handle_GetMultiOwnersEx(PyCallArgs &call) {
    //parse the PyRep to get the list of IDs to query.
    Call_SingleIntList arg;
    if(!arg.Decode(&call.tuple)) {
        _log(SERVICE__ERROR, "Failed to decode arguments.");
        return NULL;
    }

    return(m_db.GetMultiOwnersEx(arg.ints));
}

PyResult ConfigService::Handle_GetMultiAllianceShortNamesEx(PyCallArgs &call) {
    //parse the PyRep to get the list of IDs to query.
    Call_SingleIntList arg;
    if(!arg.Decode(&call.tuple)) {
        _log(SERVICE__ERROR, "Failed to decode arguments.");
        return NULL;
    }

    return(m_db.GetMultiAllianceShortNamesEx(arg.ints));
}


PyResult ConfigService::Handle_GetMultiLocationsEx(PyCallArgs &call) {
    //parse the PyRep to get the list of IDs to query.
    Call_SingleIntList arg;
    if(!arg.Decode(&call.tuple)) {
        _log(SERVICE__ERROR, "Failed to decode arguments.");
        return NULL;
    }

    return(m_db.GetMultiLocationsEx(arg.ints));
}

PyResult ConfigService::Handle_GetMultiCorpTickerNamesEx(PyCallArgs &call) {
    //parse the PyRep to get the list of IDs to query.
    Call_SingleIntList arg;
    if(!arg.Decode(&call.tuple)) {
        _log(SERVICE__ERROR, "Failed to decode arguments.");
        return NULL;
    }

    return(m_db.GetMultiCorpTickerNamesEx(arg.ints));
}

PyResult ConfigService::Handle_GetMultiGraphicsEx(PyCallArgs &call) {
    //parse the PyRep to get the list of IDs to query.
    Call_SingleIntList arg;
    if(!arg.Decode(&call.tuple)) {
        _log(SERVICE__ERROR, "Failed to decode arguments.");
        return NULL;
    }

    return(m_db.GetMultiGraphicsEx(arg.ints));
}



PyResult ConfigService::Handle_GetUnits(PyCallArgs &call) {
    return(m_db.GetUnits());
}


PyResult ConfigService::Handle_GetMap(PyCallArgs &call) {
    Call_SingleIntegerArg args;
    if(!args.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Failed to decode arguments");
        return NULL;
    }

    return(m_db.GetMap(args.arg));
}

PyResult ConfigService::Handle_GetMapOffices(PyCallArgs &call) {
    //  will add this complete code with other map data at a later date  -allan 25Jul14
    Call_SingleIntegerArg args;
    if(!args.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Failed to decode arguments");
        return NULL;
    }

    //return(m_db.GetMapOffices(args.arg));
	return NULL;
}

PyResult ConfigService::Handle_GetMapObjects(PyCallArgs &call) {
/*
  args (entityID,
    wantRegions (given universe),
    wantConstellations (given region),
    wantSystems (given constellation),
    wantStations (given solarsystem),
    unknown (seen 0) )
*/

    /* parsing args the long way until I write a dynamic InlineTuple mechanism */

/*  Call_SingleIntegerArg args;
    if(!args.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Failed to decode arguments");
        return NULL;
    }*/

    PyTuple* t = call.tuple;
    call.tuple = NULL;

    if( t->size() > 6 || t->size() == 0 )
    {
        _log( NET__PACKET_ERROR, "Decode Handle_GetMapObjects failed: tuple0 is the wrong size: expected 1-6, but got %lu", t->size() );

        PyDecRef( t );
        return NULL;
    }

    uint32 arg = 0;
    bool wantRegions = false;
    bool wantConstellations = false;
    bool wantSystems = false;
    bool wantStations = false;

    if( t->size() > 5 )
    {
        //do nothing with this field, we do not understand it.
    }

    if( t->size() > 4 )
    {
        PyRep* v = t->GetItem( 4 );
        if( !v->IsInt() )
        {
            _log( NET__PACKET_ERROR, "Decode Handle_GetMapObjects failed: arg 4 is not an int: %s", v->TypeString() );

            PyDecRef( t );
            return NULL;
        }

        wantStations = ( 0 != v->AsInt()->value() );
    }

    if( t->size() > 3 )
    {
        PyRep* v = t->GetItem( 3 );
        if( !v->IsInt() )
        {
            _log( NET__PACKET_ERROR, "Decode Handle_GetMapObjects failed: arg 3 is not an int: %s", v->TypeString() );

            PyDecRef( t );
            return NULL;
        }

        wantSystems = ( 0 != v->AsInt()->value() );
    }

    if( t->size() > 2 )
    {
        PyRep* v = t->GetItem( 2 );
        if( !v->IsInt() )
        {
            _log( NET__PACKET_ERROR, "Decode Handle_GetMapObjects failed: arg 2 is not an int: %s", v->TypeString() );

            PyDecRef( t );
            return NULL;
        }

        wantConstellations = ( 0 != v->AsInt()->value() );
    }

    if( t->size() > 1 )
    {
        PyRep* v = t->GetItem( 1 );
        if( !v->IsInt() )
        {
            _log( NET__PACKET_ERROR, "Decode Handle_GetMapObjects failed: arg 1 is not an int: %s", v->TypeString() );

            PyDecRef( t );
            return NULL;
        }

        wantRegions = ( 0 != v->AsInt()->value() );
    }

    if( t->size() > 0 )
    {
        PyRep* v = t->GetItem( 0 );
        if( !v->IsInt() )
        {
            _log( NET__PACKET_ERROR, "Decode Handle_GetMapObjects failed: arg 0 is not an int: %s", v->TypeString() );

            PyDecRef( t );
            return NULL;
        }

        arg = v->AsInt()->value();
    }

    PyDecRef( t );

    return m_db.GetMapObjects( arg, wantRegions, wantConstellations, wantSystems, wantStations );
}

PyResult ConfigService::Handle_GetMultiInvTypesEx(PyCallArgs &call) {
    //parse the PyRep to get the list of IDs to query.
    Call_SingleIntList arg;
    if(!arg.Decode(&call.tuple)) {
        _log(SERVICE__ERROR, "Failed to decode arguments.");
        return NULL;
    }

    return(m_db.GetMultiInvTypesEx(arg.ints));
}


PyResult ConfigService::Handle_GetMapConnections(PyCallArgs &call) {
/*
this is cached on clientside.  only called if not in client cache

GetMapConnections(id, sol, reg, con, cel, _c)
      <int name="id" />
      <bool name="sol" />
      <bool name="reg" /> args.reg
      <bool name="con" />
      <int name="cel" />
      <int name="_c" />
*/
/*  will add this complete code with other map data at a later date  -allan 25Jul14
    Call_GetMapConnections args;
    if(!args.Decode(&call.tuple)) {
        _log(SERVICE__ERROR, "Failed to decode args.");
        return new PyInt(0);
    }
    return m_db.GetMapConnections(args.id, args.sol, args.reg, args.con, args.cel, args._c);
*/
	return NULL;
}

PyResult ConfigService::Handle_GetStationSolarSystemsByOwner(PyCallArgs &call) {
    Call_SingleIntegerArg arg;
    if (!arg.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Bad arguments");
        return NULL;
    }

    // No idea what to return... yet...
    // Similar to GetCorpInfo(corpID) / corpSvc
    return m_db.GetStationSolarSystemsByOwner(arg.arg);
}

PyResult ConfigService::Handle_GetCelestialStatistic(PyCallArgs &call) {
    Call_SingleIntegerArg arg;
    if (!arg.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Bad arguments");
        return NULL;
    }

    return m_db.GetCelestialStatistic(arg.arg);
}

PyResult ConfigService::Handle_GetDynamicCelestials(PyCallArgs &call){
    Call_SingleIntegerArg arg;
    if (!arg.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Bad arguments");
        return NULL;
    }

    return m_db.GetDynamicCelestials(arg.arg);
}

PyResult ConfigService::Handle_GetMapLandmarks(PyCallArgs &call) {
    //  will add this complete code with other map data at a later date  -allan 25Jul14
    //return m_db.GetMapLandmarks();
	return NULL;
}

PyResult ConfigService::Handle_SetMapLandmarks(PyCallArgs &call) {
        return NULL;
}
