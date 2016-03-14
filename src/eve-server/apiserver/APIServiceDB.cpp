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
    Author:        Aknor Jaden
*/

#include "eve-server.h"

#include "apiserver/APIServiceDB.h"

APIServiceDB::APIServiceDB()
{
}

bool APIServiceDB::GetAccountIdFromUsername(std::string username, std::string * accountID)
{
    DBQueryResult res;

    // Find accountID in 'srvAccount' table using accountName:
    if( !DBcore::RunQuery(res,
        "SELECT"
        "    accountID "
                          " FROM srvAccount "
        " WHERE accountName='%s'" , username.c_str() ))
    {
        SysLog::Error( "APIServiceDB::GetAccountIdFromUsername()", "Cannot find accountID for username %s", username.c_str() );
        return false;
    }

    DBResultRow row;
    if( !res.GetRow(row) )
    {
        SysLog::Error( "APIServiceDB::GetAccountIdFromUsername()", "res.GetRow(row) failed for unknown reason." );
        return false;
    }

    *accountID = row.GetText(0);        // Grab accountID from the retrieved row from the 'account' table
    return true;
}

bool APIServiceDB::GetAccountIdFromUserID(std::string userID, uint32 * accountID)
{
    DBQueryResult res;

    // Find accountID in 'srvAccountApi' table using userID:
    if( !DBcore::RunQuery(res,
        "SELECT"
        "    accountID "
        " FROM srvAccountApi "
        " WHERE userID='%s'" , userID.c_str() ))
    {
        SysLog::Error( "APIServiceDB::GetAccountIdFromUserID()", "Cannot find accountID for userID %s", userID.c_str() );
        return false;
    }

    DBResultRow row;
    if( !res.GetRow(row) )
    {
        SysLog::Error( "APIServiceDB::GetAccountIdFromUserID()", "res.GetRow(row) failed for unknown reason." );
        return false;
    }

    *accountID = row.GetUInt(0);        // Grab accountID from the retrieved row from the 'srvAccountApi' table
    return true;
}

bool APIServiceDB::GetApiAccountInfoUsingAccountID(std::string accountID, uint32 * userID, std::string * apiFullKey,
    std::string * apiLimitedKey, uint32 * apiRole)
{
    DBQueryResult res;

    // Find userID, fullKey, limitedKey, and apiRole from 'srvAccountApi' table using accountID obtained from 'account' table:
    if( !DBcore::RunQuery(res,
        "SELECT"
        "    userID, fullKey, limitedKey, apiRole "
        " FROM srvAccountApi "
        " WHERE accountID='%s'" , accountID.c_str() ))
    {
        SysLog::Error( "APIServiceDB::GetApiAccountInfoUsingAccountID()", "Cannot find accountID '%s' in 'srvAccountApi' table", accountID.c_str() );
        return false;
    }

    DBResultRow row;
    if( !res.GetRow(row) )
    {
        SysLog::Error( "APIServiceDB::GetApiAccountInfoUsingAccountID()", "res.GetRow(row) failed for unknown reason." );
        return false;
    }

    *userID = row.GetUInt(0);            // Grab userID from retrieved row from the 'srvAccountApi' table
    *apiFullKey = row.GetText(1);        // Grab Full API Key from retrieved row from the 'srvAccountApi' table
    *apiLimitedKey = row.GetText(2);    // Grab Limited API Key from retrieved row from the 'srvAccountApi' table
    *apiRole = row.GetUInt(3);            // Grab API Role from retrieved row from the 'srvAccountApi' table
    return true;
}

bool APIServiceDB::GetApiAccountInfoUsingUserID(std::string userID, std::string * apiFullKey, std::string * apiLimitedKey, uint32 * apiRole)
{
    DBQueryResult res;

    // Find fullKey, limitedKey, and apiRole from 'srvAccountApi' table using userID supplied from an API query string:
    if( !DBcore::RunQuery(res,
        "SELECT"
        "    fullKey, limitedKey, apiRole "
        " FROM srvAccountApi "
        " WHERE userID='%s'" , userID.c_str() ))
    {
        SysLog::Error( "APIServiceDB::GetApiAccountInfoUsingUserID()", "Cannot find userID '%s' in 'srvAccountApi' table", userID.c_str() );
        return false;
    }

    DBResultRow row;
    if( !res.GetRow(row) )
    {
        SysLog::Error( "APIServiceDB::GetApiAccountInfoUsingUserID()", "res.GetRow(row) failed for unknown reason." );
        return false;
    }

    *apiFullKey = row.GetText(0);        // Grab Full API Key from retrieved row from the 'srvAccountApi' table
    *apiLimitedKey = row.GetText(1);    // Grab Limited API Key from retrieved row from the 'srvAccountApi' table
    *apiRole = row.GetUInt(2);            // Grab API Role from retrieved row from the 'srvAccountApi' table
    return true;
}

bool APIServiceDB::UpdateUserIdApiKeyDatabaseRow(uint32 userID, std::string apiFullKey, std::string apiLimitedKey)
{
    // Check key lengths and report error and return if either are incorrect:
    if( apiLimitedKey.length() != 64 )
    {
        SysLog::Error( "APIServiceDB::UpdateUserIdApiKeyDatabaseRow()", "limitedApiKey length != 64, but rather %u", apiLimitedKey.length() );
        return false;
    }

    if( apiFullKey.length() != 64 )
    {
        SysLog::Error( "APIServiceDB::UpdateUserIdApiKeyDatabaseRow()", "fullApiKey length != 64, but rather %u", apiFullKey.length() );
        return false;
    }

    // Update fullKey and limitedKey in the 'srvAccountApi' table using userID:
    DBerror err;

    if( !DBcore::RunQuery(err,
        "UPDATE"
        " srvAccountApi"
        " SET fullKey = '%s', limitedKey = '%s'"
        " WHERE userID = %u",
        apiFullKey.c_str(), apiLimitedKey.c_str(), userID ))
    {
        SysLog::Error( "", "Error in query: %s.", err.c_str());
        return false;
    }
    else
        return true;
}

bool APIServiceDB::InsertNewUserIdApiKeyInfoToDatabase(uint32 accountID, std::string apiFullKey, std::string apiLimitedKey, uint32 apiRole)
{
    // Check key lengths and report error and return if either are incorrect:
    if( apiLimitedKey.length() != 64 )
    {
        SysLog::Error( "APIServiceDB::UpdateUserIdApiKeyDatabaseRow()", "limitedApiKey length != 64, but rather %u", apiLimitedKey.length() );
        return false;
    }

    if( apiFullKey.length() != 64 )
    {
        SysLog::Error( "APIServiceDB::UpdateUserIdApiKeyDatabaseRow()", "fullApiKey length != 64, but rather %u", apiFullKey.length() );
        return false;
    }

    DBerror err;

    if( !DBcore::RunQuery(err,
        "INSERT INTO"
        " srvAccountApi ("
        "    accountID, fullKey, limitedKey, apiRole"
        " ) VALUES ("
        "    %u, '%s', '%s', %u"
        " )",
            accountID, apiFullKey.c_str(), apiLimitedKey.c_str(), apiRole
            ))
    {
        SysLog::Error( "", "Error in query: %s.", err.c_str());
        return false;
    }
    else
        return true;
}

bool APIServiceDB::UpdateUserIdApiRole(uint32 userID, uint32 apiRole)
{
    // Update fullKey and limitedKey in the 'srvAccountApi' table using userID:
    DBerror err;

    if( !DBcore::RunQuery(err,
        "UPDATE"
        " srvAccountApi"
        " SET apiRole = %u"
        " WHERE userID = %u",
        apiRole, userID ))
    {
        SysLog::Error( "", "Error in query: %s.", err.c_str());
        return false;
    }
    else
        return true;
}

