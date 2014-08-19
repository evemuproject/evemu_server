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

PyObjectEx *SearchDB::LookupChars(const char *match, bool exact) {
    DBQueryResult res;

    std::string matchEsc;
    sDatabase.DoEscapeString(matchEsc, match);
    if (matchEsc == "__ALL__") {
        if(!sDatabase.RunQuery(res,
            "SELECT "
            "characterID as ownerID, itemName AS ownerName, typeID, gender, ownerID as ownerNameID"
            " FROM character_"
            "  LEFT JOIN entity ON characterID = itemID"
            " WHERE characterID >= %u", EVEMU_MINIMUM_ID))
        {
            _log(SERVICE__ERROR, "Error in LookupChars query: %s", res.error.c_str());
            return NULL;
        }
    } else {
        if(!sDatabase.RunQuery(res,
            "SELECT "
            "characterID as ownerID, itemName AS ownerName, typeID, gender, ownerID as ownerNameID"
            " FROM character_"
            "  LEFT JOIN entity ON characterID = itemID"
            " WHERE itemName %s '%s'"
            " AND characterID >= %u",
            exact?"=":"RLIKE", matchEsc.c_str(),EVEMU_MINIMUM_ID
        ))
        {
            _log(SERVICE__ERROR, "Error in LookupChars query: %s", res.error.c_str());
            return NULL;
        }
    }

    // Dunno what kind of data i have to return :/
    //return(DBResultToCIndexedRowset(res, "characterID"));
    return DBResultToCRowset(res);
}
