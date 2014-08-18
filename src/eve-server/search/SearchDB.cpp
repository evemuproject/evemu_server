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
    Author:        bb2k
*/

#include "eve-server.h"

#include "search/SearchDB.h"
#include "search/SearchMgrService.h"

PyRep *SearchDB::QuickQuery(const char *match, std::vector<int> *type) {
    DBQueryResult res; 
    uint32 i, size;
    std::stringstream st;
    std::string supplement = "";

  // 1 : agent
  // 2 : character
  // 3 : corporation
  // 4 : alliance
  // 5 : faction
  // 6 : constellation
  // 7 : solar system
  // 8 : region
  // 9 : station


//    int transform[9] = {1,1,2,32,19,15,5,4,3};
    int transform[9] = {1,1,2,32,19,4,5,3,15};

    size = type->size();

    if ((size == 1) && (type->at(0)) == 2)
	supplement = "AND itemId >= 140000000"; 

    for(i=0; i<size; i++)
    {
        st << transform[type->at(i)-1];
        if (i<(size-1))
            st << ", ";
    }  
 
    std::string matchEsc;
    sDatabase.DoEscapeString(matchEsc, match);

    std::string query = "";

    query = "SELECT itemID,itemName,typeID,ownerID FROM entity"
            " WHERE itemName RLIKE '%s' %s" 
            " AND typeID in (SELECT typeID FROM invTypes LEFT JOIN invGroups ON invTypes.groupid = invGroups.groupID"
            " WHERE invGroups.groupID IN (%s))";

   _log(SERVICE__ERROR, query.c_str(), matchEsc.c_str(), supplement.c_str() ,st.str().c_str());

        if(!sDatabase.RunQuery(res,query.c_str(), matchEsc.c_str(), supplement.c_str() , st.str().c_str() ))
        {
            _log(SERVICE__ERROR, "Error in LookupChars query: %s", res.error.c_str());
            return NULL;
        }

    // Dunno what kind of data i have to return :/
    //return(DBResultToCIndexedRowset(res, "itemID"));
    //return(DBResultToIndexRowset(res, "itemID"));
    return DBResultToPackedRowDict(res,"itemID");
}


PyRep *SearchDB::Query(const char *match, int32 searchID) {


   _log(SERVICE__ERROR, "SearchDB::Query", "Search : String = %s, ID = %u", match, searchID );

   DBQueryResult res;

   std::string string;
   sDatabase.DoEscapeString(string, match);

   std::string query = "";

    switch (searchID) {
      case 1:           //  agent
      case 2:           //  char
            query = "SELECT"
                    "   itemID,"
                    "   itemName,"
                    "   locationID"
                    " FROM entity"
                    " WHERE itemName RLIKE '%s' ";
            break;
      case 3:           //  corp            AttributeError: Rowset instance has no attribute 'get'
            query = "SELECT"
                    "   corporationID,"
                    "   corporationName,"
                    "   stationID,"
                    "   graphicID"
                    " FROM corporation"
                    " WHERE corporationName RLIKE '%s' ";
            break;
      case 4:           //  alliance
            query = "SELECT"
                    " FROM "
                    " WHERE  = '%s' ";
            break;
      case 5:           //  faction
            query = "SELECT"
                    " FROM "
                    " WHERE  = '%s' ";
            break;
      case 6:           //  constellation
            query = "SELECT"
                    "   regionID,"
                    "   constellationID,"
                    "   constellationName"
                    " FROM mapConstellations"
                    " WHERE constellationName RLIKE '%s' ";
            break;
      case 7:           //  solar system
            query = "SELECT "
                    "   regionID,"
                    "   constellationID,"
                    "   solarSystemID,"
                    "   solarSystemName"
                    " FROM mapSolarSystems "
                    " WHERE solarSystemName RLIKE '%s' ";
            break;
      case 8:           //  region
            query = "SELECT "
                    "   regionID,"
                    "   regionName"
                    " FROM mapRegions"
                    " WHERE regionName RLIKE '%s' ";
            break;
      case 9:           //  station
            query = "SELECT "
                     "   regionID,"
                    "   constellationID,"
                    "   solarSystemID,"
                    "   stationID,"
                    "   stationName"
                    " FROM staStations "
                    " WHERE stationName RLIKE '%s' ";
            break;
      default:
            codelog(SERVICE__ERROR, "Invalid query '%s' on search %u for %u", query.c_str(), searchID);
            return NULL;
    }

    if (!sDatabase.RunQuery(res, query.c_str(), string.c_str() )) {
        codelog(DATABASE__ERROR, "Error in query: %s", res.error.c_str());
        return NULL;
    }


    DBResultRow row;
    if(res.GetRow(row)) {
            sLog.Success("SearchDB::Query", "res = %s", DBResultToRowset(res) );
            return(DBResultToCIndexedRowset(res, "itemID"));
    } else {
            sLog.Error("SearchDB::Query", "res = NULL : query = %s : string = %s", query.c_str(), string.c_str() );
                return NULL;
    }
}

