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
    Author:     Zhur
*/

#include "eve-server.h"

#include "EVEServerConfig.h"
#include "ServiceDB.h"

/**
 * @todo add auto account stuff ...//sConfig.account.autoAccountRole
 *       accountID = CreateNewAccount( login, pass, sConfig.account.autoAccountRole );
 *       role = sConfig.account.autoAccountRole;
 */

bool ServiceDB::GetAccountInformation( const char* username, const char* password, AccountInfo & account_info )
{
    std::string _username = username;
    std::string _escaped_username;

    sDatabase.DoEscapeString(_escaped_username, _username);

    DBQueryResult res;
    if( !sDatabase.RunQuery( res, "SELECT accountID, password, hash, role, online, banned, logonCount, lastLogin FROM account WHERE accountName = '%s'", _escaped_username.c_str() ) )
    {
        sLog.Error( "ServiceDB", "Error in query: %s.", res.error.c_str() );
        return false;
    }

    DBResultRow row;
    if (!res.GetRow( row )) {
		// account not found, create new one if autoAccountRole is not zero (0)
		if(sConfig.account.autoAccountRole > 0) {
			uint32 accountID = CreateNewAccount( _username.c_str(), password, sConfig.account.autoAccountRole);
			if( accountID > 0 ) {
				// add new account successful, get account info again
				bool ret = GetAccountInformation(username, password, account_info);
				return ret;
			}
			else
				return false;
		}
		else
			return false;
	}

    /* when any of the text gets are NULL it will fail... I think.. */
    account_info.id         = row.GetUInt(0);

    if (!row.IsNull(1))
        account_info.password = row.GetText(1);

    if (!row.IsNull(2))
        account_info.hash   = row.GetText(2);

    account_info.name       = _escaped_username;
    account_info.role       = row.GetUInt64(3);
    account_info.online     = row.GetBool(4);
    account_info.banned     = row.GetBool(5);
    account_info.visits     = row.GetUInt(6);

    if (!row.IsNull(7))
        account_info.last_login = row.GetText(7);

    return true;
}

bool ServiceDB::UpdateAccountHash( const char* username, std::string & hash )
{
    DBerror err;
    std::string user_name = username;
    std::string escaped_hash;
    std::string escaped_username;

    sDatabase.DoEscapeString(escaped_hash, hash);
    sDatabase.DoEscapeString(escaped_username, user_name);

    if(!sDatabase.RunQuery(err, "UPDATE account SET password='',hash='%s' where accountName='%s'", escaped_hash.c_str(), escaped_username.c_str())) {

        sLog.Error( "AccountDB", "Unable to update account information for: %s.", username );
        return false;
    }

    return true;
}

bool ServiceDB::UpdateAccountInformation( const char* username, bool isOnline )
{
    DBerror err;
    std::string user_name = username;
    std::string escaped_username;

    sDatabase.DoEscapeString(escaped_username, user_name);
    if(!sDatabase.RunQuery(err, "UPDATE account SET lastLogin=now(), logonCount=logonCount+1, online=%u where accountName='%s'", isOnline, escaped_username.c_str())) {
        sLog.Error( "AccountDB", "Unable to update account information for: %s.", username );
        return false;
    }

    return true;
}

uint32 ServiceDB::CreateNewAccount( const char* login, const char* pass, uint64 role )
{
    uint32 accountID;

    DBerror err;
    if( !sDatabase.RunQueryLID( err, accountID,
        "INSERT INTO account ( accountName, hash, role )"
        " VALUES ( '%s', '%s', %" PRIu64 " )",
        login, pass, role ) )
    {
        sLog.Error( "ServiceDB", "Failed to create a new account '%s': %s.", login, err.c_str() );
        return 0;
    }

    return accountID;
}

PyObject *ServiceDB::GetSolRow(uint32 systemID) const
{
    DBQueryResult res;

    if(!sDatabase.RunQuery(res,
        //not sure if this is gunna be valid all the time...
        "SELECT "
        "    itemID,entity.typeID,ownerID,locationID,flag,contraband,singleton,quantity,"
        "    invGroups.groupID, invGroups.categoryID,"
        "    customInfo"
        " FROM entity "
        "    LEFT JOIN invTypes ON entity.typeID=invTypes.typeID"
        "    LEFT JOIN invGroups ON invTypes.groupID=invGroups.groupID"
        " WHERE entity.itemID=%u",
        systemID
    ))
    {
        _log(SERVICE__ERROR, "Error in GetSolRow query: %s", res.error.c_str());
        return(0);
    }

    DBResultRow row;
    if(!res.GetRow(row)) {
        _log(SERVICE__ERROR, "Error in GetSolRow query: unable to find sol info for system %d", systemID);
        return(0);
    }

    return(DBRowToRow(row, "util.Row"));
}

//this function is temporary, I dont plan to keep this crap in the DB.
PyObject *ServiceDB::GetSolDroneState(uint32 systemID) const {
    DBQueryResult res;

    if(!sDatabase.RunQuery(res,
        //not sure if this is gunna be valid all the time...
        "SELECT "
        "    droneID, solarSystemID, ownerID, controllerID,"
        "    activityState, typeID, controllerOwnerID"
        " FROM droneState "
        " WHERE solarSystemID=%u",
        systemID
    ))
    {
        _log(SERVICE__ERROR, "Error in GetSolDroneState query: %s", res.error.c_str());
        return NULL;
    }

    return DBResultToRowset(res);
}

bool ServiceDB::GetSystemInfo(uint32 systemID, uint32 *constellationID, uint32 *regionID, std::string *name, std::string *securityClass) {
    if(       constellationID == NULL
        && regionID == NULL
        && name == NULL
        && securityClass == NULL
    )
        return true;

    DBQueryResult res;
    if(!sDatabase.RunQuery(res,
        "SELECT"
        " constellationID,"
        " regionID,"
        " solarSystemName,"
        " securityClass"
        " FROM mapSolarSystems"
        " WHERE solarSystemID = %u",
        systemID))
    {
        _log(DATABASE__ERROR, "Failed to query info for system %u: %s.", systemID, res.error.c_str());
        return false;
    }

    DBResultRow row;
    if(!res.GetRow(row)) {
        _log(DATABASE__ERROR, "Failed to query info for system %u: System not found.", systemID);
        return false;
    }

    if(constellationID != NULL)
        *constellationID = row.GetUInt(0);
    if(regionID != NULL)
        *regionID = row.GetUInt(1);
    if(name != NULL)
        *name = row.GetText(2);
    if(securityClass != NULL)
        *securityClass = row.IsNull(3) ? "" : row.GetText(3);

    return true;
}

bool ServiceDB::GetStaticItemInfo(uint32 itemID, uint32 *systemID, uint32 *constellationID, uint32 *regionID, GPoint *position) {
    if(       systemID == NULL
        && constellationID == NULL
        && regionID == NULL
        && position == NULL
    )
        return true;

    DBQueryResult res;
    if(!sDatabase.RunQuery(res,
        "SELECT"
        " solarSystemID,"
        " constellationID,"
        " regionID,"
        " x, y, z"
        " FROM mapDenormalize"
        " WHERE itemID = %u",
        itemID))
    {
        _log(DATABASE__ERROR, "Failed to query info for static item %u: %s.", itemID, res.error.c_str());
        return false;
    }

    DBResultRow row;
    if(!res.GetRow(row)) {
        _log(DATABASE__ERROR, "Failed to query info for static item %u: Item not found.", itemID);
        return false;
    }

    if(systemID != NULL)
        *systemID = row.GetUInt(0);
    if(constellationID != NULL)
        *constellationID = row.GetUInt(1);
    if(regionID != NULL)
        *regionID = row.GetUInt(2);
    if(position != NULL)
        *position = GPoint(
            row.GetDouble(3),
            row.GetDouble(4),
            row.GetDouble(5)
        );

    return true;
}

bool ServiceDB::GetStationInfo(uint32 stationID, uint32 *systemID, uint32 *constellationID, uint32 *regionID, GPoint *position, GPoint *dockPosition, GVector *dockOrientation) {
    if(       systemID == NULL
        && constellationID == NULL
        && regionID == NULL
        && position == NULL
        && dockPosition == NULL
        && dockOrientation == NULL
    )
        return true;

    DBQueryResult res;
    if(!sDatabase.RunQuery(res,
        "SELECT"
        " solarSystemID,"
        " constellationID,"
        " regionID,"
        " x, y, z,"
        " dockEntryX, dockEntryY, dockEntryZ,"
        " dockOrientationX, dockOrientationY, dockOrientationZ"
        " FROM staStations"
        " LEFT JOIN staStationTypes USING (stationTypeID)"
        " WHERE stationID = %u",
        stationID))
    {
        _log(DATABASE__ERROR, "Failed to query info for station %u: %s.", stationID, res.error.c_str());
        return false;
    }

    DBResultRow row;
    if(!res.GetRow(row)) {
        _log(DATABASE__ERROR, "Failed to query info for station %u: Station not found.", stationID);
        return false;
    }

    if(systemID != NULL)
        *systemID = row.GetUInt(0);
    if(constellationID != NULL)
        *constellationID = row.GetUInt(1);
    if(regionID != NULL)
        *regionID = row.GetUInt(2);
    if(position != NULL)
        *position = GPoint(
            row.GetDouble(3),
            row.GetDouble(4),
            row.GetDouble(5)
        );
    if(dockPosition != NULL)
        *dockPosition = GPoint(
            row.GetDouble(3) + row.GetDouble(6),
            row.GetDouble(4) + row.GetDouble(7),
            row.GetDouble(5) + row.GetDouble(8)
        );
    if(dockOrientation != NULL) {
        *dockOrientation = GVector(
            row.GetDouble(9),
            row.GetDouble(10),
            row.GetDouble(11)
        );
        // as it's direction, it should be normalized
        //dockOrientation->normalize();
    }

    return true;
}

uint32 ServiceDB::GetDestinationStargateID(uint32 fromSystem, uint32 toSystem) {
    DBQueryResult res;

    if(!sDatabase.RunQuery(res,
        " SELECT "
        "    fromStargate.solarSystemID AS fromSystem,"
        "    fromStargate.itemID AS fromGate,"
        "    toStargate.itemID AS toGate,"
        "    toStargate.solarSystemID AS toSystem"
        " FROM mapJumps AS jump"
        " LEFT JOIN mapDenormalize AS fromStargate"
        "    ON fromStargate.itemID = jump.stargateID"
        " LEFT JOIN mapDenormalize AS toStargate"
        "    ON toStargate.itemID = jump.celestialID"
        " WHERE fromStargate.solarSystemID = %u"
        "    AND toStargate.solarSystemID = %u",
        fromSystem, toSystem
    ))
    {
        codelog(SERVICE__ERROR, "Error in query: %s", res.error.c_str());
        return(0);
    }

    DBResultRow row;
    if(!res.GetRow(row)) {
        codelog(SERVICE__ERROR, "Error in query: no data for %d, %d", fromSystem, toSystem);
        return(0);
    }

    return row.GetUInt(2);
}

bool ServiceDB::GetConstant(const char *name, uint32 &into) {
    DBQueryResult res;

    std::string escaped;
    sDatabase.DoEscapeString(escaped, name);

    if(!sDatabase.RunQuery(res,
    "SELECT"
    "    constantValue"
    " FROM eveConstants"
    " WHERE constantID='%s'",
        escaped.c_str()
    ))
    {
        codelog(SERVICE__ERROR, "Error in query: %s", res.error.c_str());
        return false;
    }

    DBResultRow row;
    if(!res.GetRow(row)) {
        codelog(SERVICE__ERROR, "Unable to find constant %s", name);
        return false;
    }

    into = row.GetUInt(0);

    return true;
}

void ServiceDB::ProcessStringChange(const char * key, const std::string & oldValue, const std::string & newValue, PyDict * notif, std::vector<std::string> & dbQ) {
    if (oldValue != newValue) {
        std::string newEscValue;
        std::string qValue(key);

        sDatabase.DoEscapeString(newEscValue, newValue);

        // add to notification
        PyTuple * val = new PyTuple(2);
        val->items[0] = new PyString(oldValue);
        val->items[1] = new PyString(newValue);
        notif->SetItemString(key, val);

        qValue += " = '" + newEscValue + "'";
        dbQ.push_back(qValue);
    }
}

void ServiceDB::ProcessRealChange(const char * key, double oldValue, double newValue, PyDict * notif, std::vector<std::string> & dbQ) {
    if (oldValue != newValue) {
        // add to notification
        std::string qValue(key);

        PyTuple * val = new PyTuple(2);
        val->items[0] = new PyFloat(oldValue);
        val->items[1] = new PyFloat(newValue);
        notif->SetItemString(key, val);

        char cc[10];
        snprintf(cc, 9, "'%5.3lf'", newValue);
        qValue += " = ";
        qValue += cc;
        dbQ.push_back(qValue);
    }
}

void ServiceDB::ProcessIntChange(const char * key, uint32 oldValue, uint32 newValue, PyDict * notif, std::vector<std::string> & dbQ) {
    if (oldValue != newValue) {
        // add to notification
        PyTuple * val = new PyTuple(2);
        std::string qValue(key);

        val->items[0] = new PyInt(oldValue);
        val->items[1] = new PyInt(newValue);
        notif->SetItemString(key, val);

        char cc[10];
        snprintf(cc, 9, "%u", newValue);
        qValue += " = ";
        qValue += cc;
        dbQ.push_back(qValue);
    }
}

//johnsus - characterOnline mod
void ServiceDB::SetCharacterOnlineStatus(uint32 char_id, bool onoff_status) {
    DBerror err;

    _log(CLIENT__TRACE, "ChrStatus: Setting character %u %s.", char_id, onoff_status ? "Online" : "Offline");

    if(!sDatabase.RunQuery(err,
        "UPDATE character_"
        " SET online = %d"
        " WHERE characterID = %u",
        onoff_status, char_id))
    {
        codelog(SERVICE__ERROR, "Error in query: %s", err.c_str());
    }

    if( onoff_status )
    {
        _log(CLIENT__TRACE, "SrvStatus: Incrementing ConnectSinceStartup.");

        if(!sDatabase.RunQuery(err, "UPDATE srvStatus SET config_value = config_value + 1 WHERE config_name = 'connectSinceStartup'"))
        {
            codelog(SERVICE__ERROR, "Error in query: %s", err.c_str());
        }
    }
}

//johnsus - serverStartType mod
void ServiceDB::SetServerOnlineStatus(bool onoff_status) {
    DBerror err;

    _log(onoff_status ? SERVER__INIT : SERVER__SHUTDOWN, "SrvStatus: Server is %s, setting serverStartTime.", onoff_status ? "coming Online" : "going Offline");

    if(!sDatabase.RunQuery(err,
        "REPLACE INTO srvStatus (config_name, config_value)"
        " VALUES ('%s', %s)",
        "serverStartTime",
        onoff_status ? "UNIX_TIMESTAMP(CURRENT_TIMESTAMP)" : "0"))
    {
        codelog(SERVICE__ERROR, "Error in query: %s", err.c_str());
    }

    _log(SERVER__INIT, "SrvStatus: Resetting ConnectSinceStartup.");

    if(!sDatabase.RunQuery(err, "REPLACE INTO srvStatus (config_name, config_value)"
        " VALUES ('%s', '0')",
        "connectSinceStartup"))
    {
        codelog(SERVICE__ERROR, "Error in query: %s", err.c_str());
    }

    _log(CLIENT__TRACE, "ChrStatus: Setting all characters and accounts offline.");

    if(!sDatabase.RunQuery(err,
        "UPDATE character_, account"
        " SET character_.online = 0,"
        "     account.online = 0"))
        {
                codelog(SERVICE__ERROR, "Error in query: %s", err.c_str());
        }
}

void ServiceDB::SetAccountOnlineStatus(uint32 accountID, bool onoff_status) {
    DBerror err;

    _log(CLIENT__TRACE, "AccStatus: Setting account %u %s.", accountID, onoff_status ? "Online" : "Offline");

    if(!sDatabase.RunQuery(err,
        "UPDATE account "
        " SET account.online = %d "
        " WHERE accountID = %u ",
        onoff_status, accountID))
    {
        codelog(SERVICE__ERROR, "Error in query: %s", err.c_str());
    }
}

void ServiceDB::SetAccountBanStatus(uint32 accountID, bool onoff_status) {
    DBerror err;

    _log(CLIENT__TRACE, "AccStatus: %s account %u.", onoff_status ? "Banned" : "Removed ban on", accountID );

    if(!sDatabase.RunQuery(err,
        " UPDATE account "
        " SET account.banned = %d "
        " WHERE accountID = %u ",
        onoff_status, accountID))
    {
        codelog(SERVICE__ERROR, "Error in query: %s", err.c_str());
    }
}




