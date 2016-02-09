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

#ifndef EVE_ENTITY_LIST_H
#define EVE_ENTITY_LIST_H

#include "threading/Mutex.h"
#include "utils/Singleton.h"

class Client;
class PyAddress;
class EVENotificationStream;
class SystemManager;
class PyTuple;
class PyServiceMgr;

typedef enum {
    NOTIF_DEST__LOCATION,
    NOTIF_DEST__CORPORATION
} NotificationDestination;

class MulticastTarget {
public:
    //this object is a set of "or"s, matching any criteria is sufficient.
    std::set<uint32> characters;
    std::set<uint32> locations;
    std::set<uint32> corporations;
};

class EntityList
{
public:

    static void UseServices(PyServiceMgr *svc);

    typedef std::set<uint32> character_set;

    static void Add(Client **client);

    static void Process();

    static Client *FindCharacter(uint32 char_id);
    static Client *FindCharacter(const char *name);
    static Client *FindByShip(uint32 ship_id);
    static Client *FindAccount(uint32 account_id);
    static void FindByStationID(uint32 stationID, std::vector<Client *> &result);
    static void FindByRegionID(uint32 regionID, std::vector<Client *> &result);

    static uint32 GetClientCount();

    static SystemManager *FindOrBootSystem(uint32 systemID);

    static void Broadcast(const char *notifyType, const char *idType, PyTuple **payload);
    static void Broadcast(const PyAddress &dest, EVENotificationStream &noti);
    static void Multicast(const char *notifyType, const char *idType, PyTuple **payload, NotificationDestination target, uint32 target_id, bool seq = true);
    static void Multicast(const char *notifyType, const char *idType, PyTuple **payload, const MulticastTarget &mcset, bool seq = true);
    static void Multicast(const character_set &cset, const PyAddress &dest, EVENotificationStream &noti);
    static void Multicast(const character_set &cset, const char *notifyType, const char *idType, PyTuple **payload, bool seq = true);
    static void Unicast(uint32 charID, const char *notifyType, const char *idType, PyTuple **payload, bool seq = true);
    static void GetClients(const character_set &cset, std::vector<Client *> &result);

};

#endif

