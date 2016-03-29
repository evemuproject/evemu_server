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

#include "apiserver/APICharacterDB.h"
#include "inventory/AttributeEnum.h"

APICharacterDB::APICharacterDB()
{
}

bool APICharacterDB::GetCharacterSkillsTrained(uint32 characterID, std::vector<std::string> & skillTypeIDList, std::vector<std::string> & skillPointsList,
    std::vector<std::string> & skillLevelList, std::vector<std::string> & skillPublishedList)
{
    DBQueryResult res;

    // Get list of characters and their corporation info from the accountID:
    if( !DBcore::RunQuery(res,
        " SELECT "
        "   srvEntity.itemID, "
        "   srvEntity.typeID, "
        "   srvEntity_attributes.attributeID, "
        "   srvEntity_attributes.valueInt, "
        "   srvEntity_attributes.valueFloat, "
        "   invTypes.groupID, "
        "   invTypes.published, "
        "   invGroups.categoryID "
        " FROM srvEntity "
                          "   LEFT JOIN srvEntity_attributes Using(itemID) "
                          "   LEFT JOIN invTypes Using(typeID) "
                          "   LEFT JOIN invGroups Using(groupID) "
        " WHERE ownerID = %u AND invGroups.categoryID = 16 ", characterID ))
    {
        SysLog::Error( "APIAccountDB::GetCharacterSkillsTrained()", "Cannot find characterID %u", characterID );
        return false;
    }

    uint32 prevTypeID = 0;
    bool gotSkillPoints = false;
    bool gotSkillLevel = false;
    DBResultRow row;
    std::map<std::string, std::string> charInfo;
    while( res.GetRow( row ) )
    {
        if( prevTypeID != row.GetUInt(1) )
        {
            if( (!gotSkillPoints) && (prevTypeID != 0) )
                skillPointsList.push_back( std::string("0") );

            if( (!gotSkillLevel) && (prevTypeID != 0) )
                skillLevelList.push_back( std::string("0") );

            gotSkillPoints = false;
            gotSkillLevel = false;
            skillTypeIDList.push_back( std::string(row.GetText(1)) );
			skillPublishedList.push_back( std::string(itoa(row.GetBool(6) ? 1 : 0)) );
        }

        prevTypeID = row.GetUInt(1);

        if( row.GetUInt(2) == AttrSkillPoints )
        {
            gotSkillPoints = true;
            if( row.GetText(3) == NULL )
                // Get value from 'srvEntity_attributes' table 'valueFloat' column since 'valueInt' contains 'NULL'
                skillPointsList.push_back( std::string((row.GetText(4) == NULL ? "0.0" : itoa((uint32)(row.GetFloat(4))))) );
            else
                // Get value from 'srvEntity_attributes' table 'valueInt' column since it does not contain 'NULL'
                skillPointsList.push_back( std::string((row.GetText(3) == NULL ? "0" : row.GetText(3))) );
        }

        if( row.GetUInt(2) == AttrSkillLevel )
        {
            gotSkillLevel = true;
            if( row.GetText(3) == NULL )
                // Get value from 'srvEntity_attributes' table 'valueFloat' column since 'valueInt' contains 'NULL'
                skillLevelList.push_back( std::string((row.GetText(4) == NULL ? "0.0" : itoa((uint32)(row.GetFloat(4))))) );
            else
                // Get value from 'srvEntity_attributes' table 'valueInt' column since it does not contain 'NULL'
                skillLevelList.push_back( std::string((row.GetText(3) == NULL ? "0" : row.GetText(3))) );
        }
    }

    return true;
}

bool APICharacterDB::GetCharacterInfo(uint32 characterID, std::vector<std::string> & charInfoList)
{
    DBQueryResult res;

    // Get list of characters and their corporation info from the accountID:
    if( !DBcore::RunQuery(res,
        " SELECT "
        "  srvCharacter.balance, "
        "  srvCharacter.skillPoints, "
        "  srvCharacter.corporationID, "
        "  srvCharacter.corpRole, "
        "  srvCharacter.rolesAtAll, "
        "  srvCharacter.rolesAtBase, "
        "  srvCharacter.rolesAtHQ, "
        "  srvCharacter.rolesAtOther, "
        "  srvCharacter.startDateTime, "
        "  srvCharacter.gender, "
        "  chrAncestries.ancestryName, "
        "  chrBloodlines.bloodlineName, "
        "  chrRaces.raceName, "
        "  srvEntity.itemName, "
        "  srvCorporation.corporationName "
        " FROM srvCharacter "
        "  LEFT JOIN chrAncestries ON srvCharacter.ancestryID = chrAncestries.ancestryID "
        "  LEFT JOIN chrBloodlines ON chrAncestries.bloodlineID = chrBloodlines.bloodlineID "
        "  LEFT JOIN chrRaces ON chrBloodlines.raceID = chrRaces.raceID "
        "  LEFT JOIN srvEntity ON srvEntity.itemID = srvCharacter.characterID "
        "  LEFT JOIN srvCorporation ON srvCorporation.corporationID = srvCharacter.corporationID "
        " WHERE srvCharacter.characterID = %u ", characterID ))
    {
        SysLog::Error( "APIAccountDB::GetCharacterSkillsTrained()", "Cannot find characterID %u", characterID );
        return false;
    }

    DBResultRow row;
    if( !res.GetRow(row) )
    {
        SysLog::Error( "APIServiceDB::GetAccountIdFromUsername()", "res.GetRow(row) failed for unknown reason." );
        return false;
    }

    charInfoList.push_back( std::string(row.GetText(0)) );      // 0. Balance
    charInfoList.push_back( std::string(row.GetText(1)) );      // 1. Skill Points
    charInfoList.push_back( std::string(row.GetText(2)) );     // 2. corporationID
    charInfoList.push_back( std::string(row.GetText(3)) );     // 3. corp Role
    charInfoList.push_back( std::string(row.GetText(4)) );     // 4. roles At All
    charInfoList.push_back( std::string(row.GetText(5)) );     // 5. roles At Base
    charInfoList.push_back( std::string(row.GetText(6)) );     // 6. roles At HQ
    charInfoList.push_back( std::string(row.GetText(7)) );     // 7. roles At Other
    charInfoList.push_back( std::string(row.GetText(8)) );     // 8. birthday
    charInfoList.push_back( std::string(row.GetText(10)) );     // 9. ancestry Name
    charInfoList.push_back( std::string(row.GetText(11)) );     // 10. bloodline Name
    charInfoList.push_back( std::string(row.GetText(12)) );     // 11. race Name
    charInfoList.push_back( std::string(row.GetText(13)) );     // 12. char Name
    charInfoList.push_back( std::string(row.GetText(14)) );     // 13. corp Name
    charInfoList.push_back( std::string(row.GetText(9)) );     // 14. gender (0 = female, 1 = male)

    return true;
}

bool APICharacterDB::GetCharacterAttributes(uint32 characterID, std::map<std::string, std::string> & attribList)
{
    DBQueryResult res;

    // Get list of characters and their corporation info from the accountID:
    if( !DBcore::RunQuery(res,
        " SELECT "
        "  itemID, "
        "  attributeID, "
        "  valueInt, "
        "  valueFloat "
        " FROM srvEntity_attributes "
        " WHERE itemID = %u ", characterID ))
    {
        SysLog::Error( "APIAccountDB::GetCharacterAttributes()", "Cannot find characterID %u", characterID );
        return false;
    }

    DBResultRow row;
    bool row_found = false;
    while( res.GetRow( row ) )
    {
        row_found = true;

        if( row.GetUInt(1) == AttrCharisma )
        {
            // Charisma
            if( row.GetText(2) == NULL )
                // Get value from 'srvEntity_attributes' table 'valueFloat' column since 'valueInt' contains 'NULL'
                attribList.insert( std::pair<std::string, std::string>(std::string(itoa(AttrCharisma)), std::string((row.GetText(3) == NULL ? "0.0" : itoa((uint32)(row.GetFloat(3))))) ));
            else
                // Get value from 'srvEntity_attributes' table 'valueInt' column since it does not contain 'NULL'
                attribList.insert( std::pair<std::string, std::string>(std::string(itoa(AttrCharisma)), std::string((row.GetText(2) == NULL ? "0" : row.GetText(2))) ));
        }

        if( row.GetUInt(1) == AttrIntelligence )
        {
            // Intelligence
            if( row.GetText(2) == NULL )
                // Get value from 'srvEntity_attributes' table 'valueFloat' column since 'valueInt' contains 'NULL'
                attribList.insert( std::pair<std::string, std::string>(std::string(itoa(AttrIntelligence)), std::string((row.GetText(3) == NULL ? "0.0" : itoa((uint32)(row.GetFloat(3))))) ));
            else
                // Get value from 'srvEntity_attributes' table 'valueInt' column since it does not contain 'NULL'
                attribList.insert( std::pair<std::string, std::string>(std::string(itoa(AttrIntelligence)), std::string((row.GetText(2) == NULL ? "0" : row.GetText(2))) ));
        }

        if( row.GetUInt(1) == AttrMemory )
        {
            // Memory
            if( row.GetText(2) == NULL )
                // Get value from 'srvEntity_attributes' table 'valueFloat' column since 'valueInt' contains 'NULL'
                attribList.insert( std::pair<std::string, std::string>(std::string(itoa(AttrMemory)), std::string((row.GetText(3) == NULL ? "0.0" : itoa((uint32)(row.GetFloat(3))))) ));
            else
                // Get value from 'srvEntity_attributes' table 'valueInt' column since it does not contain 'NULL'
                attribList.insert( std::pair<std::string, std::string>(std::string(itoa(AttrMemory)), std::string((row.GetText(2) == NULL ? "0" : row.GetText(2))) ));
        }

        if( row.GetUInt(1) == AttrPerception )
        {
            // Perception
            if( row.GetText(2) == NULL )
                // Get value from 'srvEntity_attributes' table 'valueFloat' column since 'valueInt' contains 'NULL'
                attribList.insert( std::pair<std::string, std::string>(std::string(itoa(AttrPerception)), std::string((row.GetText(3) == NULL ? "0.0" : itoa((uint32)(row.GetFloat(3))))) ));
            else
                // Get value from 'srvEntity_attributes' table 'valueInt' column since it does not contain 'NULL'
                attribList.insert( std::pair<std::string, std::string>(std::string(itoa(AttrPerception)), std::string((row.GetText(2) == NULL ? "0" : row.GetText(2))) ));
        }

        if( row.GetUInt(1) == AttrWillpower )
        {
            // Will Power
            if( row.GetText(2) == NULL )
                // Get value from 'srvEntity_attributes' table 'valueFloat' column since 'valueInt' contains 'NULL'
                attribList.insert( std::pair<std::string, std::string>(std::string(itoa(AttrWillpower)), std::string((row.GetText(3) == NULL ? "0.0" : itoa((uint32)(row.GetFloat(3))))) ));
            else
                // Get value from 'srvEntity_attributes' table 'valueInt' column since it does not contain 'NULL'
                attribList.insert( std::pair<std::string, std::string>(std::string(itoa(AttrWillpower)), std::string((row.GetText(2) == NULL ? "0" : row.GetText(2))) ));
        }
    }

    if( !row_found )
    {
        SysLog::Error( "APIServiceDB::GetAccountIdFromUsername()", "res.GetRow(row) failed for unknown reason." );
        return false;
    }

    return true;
}

bool APICharacterDB::GetCharacterSkillQueue(uint32 characterID, std::vector<std::string> & orderList, std::vector<std::string> & typeIdList,
    std::vector<std::string> & levelList, std::vector<std::string> & rankList, std::vector<std::string> & skillIdList,
    std::vector<std::string> & primaryAttrList, std::vector<std::string> & secondaryAttrList, std::vector<std::string> & skillPointsTrainedList)
{
    DBQueryResult res;

    // Get list of characters and their corporation info from the accountID:
    if( !DBcore::RunQuery(res,
        " SELECT "
        "  srvChrSkillQueue.*, "
        "  dgmTypeAttributes.attributeID, "
        "  dgmTypeAttributes.valueInt, "
        "  dgmTypeAttributes.valueFloat, "
        "  srvEntity.itemID, "
        "  srvEntity_attributes.valueInt, "
        "  srvEntity_attributes.valueFloat "
        " FROM srvChrSkillQueue "
        "  LEFT JOIN dgmTypeAttributes ON dgmTypeAttributes.typeID = srvChrSkillQueue.typeID "
        "  LEFT JOIN srvEntity ON srvEntity.typeID = srvChrSkillQueue.typeID "
        "  LEFT JOIN srvEntity_attributes ON srvEntity_attributes.itemID = srvEntity.itemID "
        " WHERE srvChrSkillQueue.characterID = %u AND dgmTypeAttributes.typeID = srvChrSkillQueue.typeID AND "
        "  dgmTypeAttributes.attributeID IN (%u,%u,%u) AND srvEntity.ownerID = %u AND srvEntity_attributes.attributeID = %u ",
        characterID, AttrPrimaryAttribute, AttrSecondaryAttribute, AttrSkillTimeConstant, characterID, AttrSkillPoints ))
    {
        SysLog::Error( "APIAccountDB::GetCharacterSkillQueue()", "Cannot find characterID %u", characterID );
        return false;
    }

    DBResultRow row;
    bool row_found = false;
    uint32 prev_orderIndex = 4294967295UL;
    while( res.GetRow( row ) )
    {
        row_found = true;

        if( prev_orderIndex != row.GetUInt(1) )
        {
            prev_orderIndex = row.GetUInt(1);
            orderList.push_back( std::string(row.GetText(1)) );
            typeIdList.push_back( std::string(row.GetText(2)) );
            levelList.push_back( std::string(row.GetText(3)) );
            skillIdList.push_back( std::string(row.GetText(7)) );

            if( row.GetText(8) == NULL )
                // Get value from the query's 'valueFloat' column since 'valueInt' contains 'NULL'
                skillPointsTrainedList.push_back( std::string((row.GetText(9) == NULL ? "0.0" : itoa((uint32)(row.GetFloat(9))))) );
            else
                // Get value from the query's 'valueInt' column since it does not contain 'NULL'
                skillPointsTrainedList.push_back( std::string((row.GetText(8) == NULL ? "0" : row.GetText(8))) );
        }

        if( row.GetUInt(4) == AttrPrimaryAttribute )
        {
            if( row.GetText(5) == NULL )
                // Get value from the query's 'valueFloat' column since 'valueInt' contains 'NULL'
                primaryAttrList.push_back( std::string((row.GetText(6) == NULL ? "0.0" : itoa((uint32)(row.GetFloat(6))))) );
            else
                // Get value from the query's 'valueInt' column since it does not contain 'NULL'
                primaryAttrList.push_back( std::string((row.GetText(5) == NULL ? "0" : row.GetText(5))) );
        }
        else if( row.GetUInt(4) == AttrSecondaryAttribute )
        {
            if( row.GetText(5) == NULL )
                // Get value from the query's 'valueFloat' column since 'valueInt' contains 'NULL'
                secondaryAttrList.push_back( std::string((row.GetText(6) == NULL ? "0.0" : itoa((uint32)(row.GetFloat(6))))) );
            else
                // Get value from the query's 'valueInt' column since it does not contain 'NULL'
                secondaryAttrList.push_back( std::string((row.GetText(5) == NULL ? "0" : row.GetText(5))) );
        }
        else if( row.GetUInt(4) == AttrSkillTimeConstant )
        {
            if( row.GetText(5) == NULL )
                // Get value from the query's 'valueFloat' column since 'valueInt' contains 'NULL'
                rankList.push_back( std::string((row.GetText(6) == NULL ? "0.0" : itoa((uint32)(row.GetFloat(6))))) );
            else
                // Get value from the query's 'valueInt' column since it does not contain 'NULL'
                rankList.push_back( std::string((row.GetText(5) == NULL ? "0" : row.GetText(5))) );
        }
    }

    if( !row_found )
    {
        SysLog::Error( "APIServiceDB::GetCharacterSkillQueue()", "res.GetRow(row) failed for unknown reason." );
        return false;
    }

    return true;
}

bool APICharacterDB::GetCharacterImplants(uint32 characterID, std::map<std::string, std::string> & implantList)
{
    return false;
}

bool APICharacterDB::GetCharacterCertificates(uint32 characterID, std::vector<std::string> & certList)
{
    return false;
}

bool APICharacterDB::GetCharacterCorporationRoles(uint32 characterID, std::string roleType, std::map<std::string, std::string> & roleList)
{
    return false;
}



/*
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
        Log::Error( "APIServiceDB::GetAccountIdFromUsername()", "Cannot find accountID for username %s", username.c_str() );
        return false;
    }

    DBResultRow row;
    if( !res.GetRow(row) )
    {
        Log::Error( "APIServiceDB::GetAccountIdFromUsername()", "res.GetRow(row) failed for unknown reason." );
        return false;
    }

    *accountID = row.GetText(0);        // Grab accountID from the retrieved row from the 'account' table
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
        Log::Error( "APIServiceDB::GetApiAccountInfoUsingAccountID()", "Cannot find accountID '%s' in 'srvAccountApi' table", accountID.c_str() );
        return false;
    }

    DBResultRow row;
    if( !res.GetRow(row) )
    {
        Log::Error( "APIServiceDB::GetApiAccountInfoUsingAccountID()", "res.GetRow(row) failed for unknown reason." );
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
        Log::Error( "APIServiceDB::GetApiAccountInfoUsingUserID()", "Cannot find userID '%s' in 'srvAccountApi' table", userID.c_str() );
        return false;
    }

    DBResultRow row;
    if( !res.GetRow(row) )
    {
        Log::Error( "APIServiceDB::GetApiAccountInfoUsingUserID()", "res.GetRow(row) failed for unknown reason." );
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
        Log::Error( "APIServiceDB::UpdateUserIdApiKeyDatabaseRow()", "limitedApiKey length != 64, but rather %u", apiLimitedKey.length() );
        return false;
    }

    if( apiFullKey.length() != 64 )
    {
        Log::Error( "APIServiceDB::UpdateUserIdApiKeyDatabaseRow()", "fullApiKey length != 64, but rather %u", apiFullKey.length() );
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
        Log::Error( "", "Error in query: %s.", err.c_str());
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
        Log::Error( "APIServiceDB::UpdateUserIdApiKeyDatabaseRow()", "limitedApiKey length != 64, but rather %u", apiLimitedKey.length() );
        return false;
    }

    if( apiFullKey.length() != 64 )
    {
        Log::Error( "APIServiceDB::UpdateUserIdApiKeyDatabaseRow()", "fullApiKey length != 64, but rather %u", apiFullKey.length() );
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
        Log::Error( "", "Error in query: %s.", err.c_str());
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
        Log::Error( "", "Error in query: %s.", err.c_str());
        return false;
    }
    else
        return true;
}
*/
