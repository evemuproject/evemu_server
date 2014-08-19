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
    Author: BB2k       
*/

#include "eve-server.h"

#include "PyServiceCD.h"
#include "search/SearchMgrService.h"
#include "search/SearchDB.h"

PyCallable_Make_InnerDispatcher(SearchMgrService)

SearchMgrService::SearchMgrService(PyServiceMgr *mgr)
: PyService(mgr, "search"),
  m_dispatch(new Dispatcher(this))
{

    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(SearchMgrService, QuickQuery);
    PyCallable_REG_CALL(SearchMgrService, Query);
    
}

SearchMgrService::~SearchMgrService() {
    delete m_dispatch;
}


//Objects Types are :
// 1 : agent
// 2 : character
// 3 : corporation
// 4 : alliance
// 5 : faction
// 6 : station
// 7 : solar system
// 8 : constellation
// 9 : region

PyResult SearchMgrService::Handle_QuickQuery(PyCallArgs &call) {

    // the first argument is the searchString
    // the second is the type of searched object
    //  Only one for QuickQuery

    CallSearch args;
    if (!args.Decode(&call.tuple))
    {
        codelog(CLIENT__ERROR, "Failed to decode args for QuickQuery call");
        return NULL;
    }
    return m_db.LookupChars(args.searchString.c_str(), false);
}



PyResult SearchMgrService::Handle_Query(PyCallArgs &call) {


    // the first argument is the searchString
    // the second is a list of object types

    /*CallSearch args;
    if (!args.Decode(&call.tuple))
    {
        codelog(CLIENT__ERROR, "Failed to decode args for Query call");
        //return NULL;
    }*/


    sLog.Debug( "SearcMgrService", "Called Query stub." );

    util_Rowset rs;
    rs.lines = new PyList;

    rs.header.push_back( "characterID" );
    rs.header.push_back( "Name" );

    return rs.Encode();

    //return m_db.LookupChars(args.searchString.c_str(), false);

}

