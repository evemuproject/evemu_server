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
    Author:     Zhur
*/

#ifndef __SERVICEDB_H_INCL__
#define __SERVICEDB_H_INCL__

/*
 * This object is the home for common DB operations which may be needed by many
 * different service objects. It should be inherited by each service DB
 * implementation.
 *
 */

class EntityList;
class Client;
class CharacterData;
class CorpMemberInfo;

struct AccountInfo
{
    std::string name;
    std::string password;
    std::string hash;
    uint32 id;
    uint64 role;
    uint32 visits;
    std::string last_login;
    bool online;
    bool banned;
};

class ServiceDB
{
protected:
    ServiceDB() = delete;

public:
    static bool GetAccountInformation(const char* username, const char* password, AccountInfo & account_info);
    static bool UpdateAccountHash(const char* username, std::string & hash);
    static bool UpdateAccountInformation(const char* username, bool isOnline);


    //entity/item stuff:
    static PyObject *GetSolRow(uint32 systemID);
    static PyObject *GetSolDroneState(uint32 systemID);

    static bool GetSystemInfo(uint32 systemID, uint32 *constellationID, uint32 *regionID, std::string *name, std::string *securityClass); // mapSolarSystems
    static bool GetStaticItemInfo(uint32 itemID, uint32 *systemID, uint32 *constellationID, uint32 *regionID, Vector3D *position); // mapDenormalize
    static bool GetStationInfo(uint32 stationID, uint32 *systemID, uint32 *constellationID, uint32 *regionID, Vector3D *position, Vector3D *dockPosition, Vector3D *dockOrientation); // staStations

    static uint32 GetDestinationStargateID(uint32 fromSystem, uint32 toSystem);

    static bool GetConstant(const char *name, uint32 &into);

    //these really want to move back into AccountDB
    static bool GiveCash(uint32 characterID, JournalRefType refTypeID, uint32 ownerFromID, uint32 ownerToID, const char *argID1, uint32 accountID, EVEAccountKeys accountKey, double amount, double balance, const char *reason);
    static double GetCorpBalance(uint32 corpID);
    static bool AddBalanceToCorp(uint32 corpID, double amount);

    //johnsus - serverOnline mod
    static void SetServerOnlineStatus(bool onoff_status);
    //johnsus - characterOnline mod
    static void SetCharacterOnlineStatus(uint32 char_id, bool onoff_status);

    static void SetAccountOnlineStatus(uint32 accountID, bool onoff_status);
    static void SetAccountBanStatus(uint32 accountID, bool onoff_status);

protected:
    static void ProcessStringChange(const char * key, const std::string & oldValue, const std::string & newValue, PyDict * notif, std::vector<std::string> & dbQ);
    static void ProcessRealChange(const char * key, double oldValue, double newValue, PyDict * notif, std::vector<std::string> & dbQ);
    static void ProcessIntChange(const char * key, uint32 oldValue, uint32 newValue, PyDict * notif, std::vector<std::string> & dbQ);

    /**
     * CreateNewAccount
     *
     * This method is part of the "autoAccount" creation patch by firefoxpdm. This
     * will insert a new account row into the database if the account name doesn't
     * exist at login.
     *
     * @param login is a const char string containing the name.
     * @param pass is a const char string containing the password.
     * @param role is the users role in the game.
     * @author firefoxpdm, xanarox
     */
    static uint32 CreateNewAccount(const char* login, const char* pass, uint64 role);
};

#endif


