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


#ifndef __CORPORATIONDB_H_INCL__
#define __CORPORATIONDB_H_INCL__

#include "corporation/CorporationCarrier.h"
#include "ServiceDB.h"

class PyRep;
class OfficeInfo;

class CorporationDB
: public ServiceDB
{
public:
    static PyObject *GetCorporation(uint32 corpID);
    static PyObject *GetStations(uint32 corpID);
    static PyObject *GetEveOwners(uint32 corpID);

    static PyRep *GetMyApplications(uint32 charID);
    static PyRep *GetApplications(uint32 corpID);
    static PyRep *GetMyShares(uint32 charID);
    static PyObject *GetEmploymentRecord(uint32 charID);
    static PyObject *GetMedalsReceived(uint32 charID);

    static PyObject *ListCorpStations(uint32 corp_id);

    static PyObject *ListStationOffices(uint32 station_id);
    static PyObject *ListStationCorps(uint32 station_id);
    static PyObject *ListStationOwners(uint32 station_id);

    static PyDict *ListAllCorpInfo();
    static PyObject *ListNPCDivisions();
    static bool ListAllCorpFactions(std::map<uint32, uint32> &into);
    static bool ListAllFactionStationCounts(std::map<uint32, uint32> &into);
    static bool ListAllFactionSystemCounts(std::map<uint32, uint32> &into);
    static bool ListAllFactionRegions(std::map<int32, PyRep *> &into);
    static bool ListAllFactionConstellations(std::map<int32, PyRep *> &into);
    static bool ListAllFactionSolarSystems(std::map<int32, PyRep *> &into);
    static bool ListAllFactionRaces(std::map<int32, PyRep *> &into);

    static bool AddCorporation(Call_AddCorporation & corpInfo, Client *client, uint32 & corpID);
    static bool JoinCorporation(uint32 charID, uint32 corpID, uint32 oldCorpID, const CorpMemberInfo &roles);
    static bool CreateCorporationChangePacket(Notify_OnCorporaionChanged & cc, uint32 oldCorpID, uint32 newCorpID);
    static bool CreateCorporationCreatePacket(Notify_OnCorporaionChanged & cc, uint32 oldCorpID, uint32 newCorpID);
    static uint32 GetOffices(uint32 corpID);
    static PyRep *Fetch(uint32 corpID, uint32 from, uint32 count);

    static uint32 GetQuoteForRentingAnOffice(uint32 corpID);
    static uint32 ReserveOffice(const OfficeInfo & oInfo);

    static uint32 GetStationOwner(uint32 stationID);
    static uint32 GetStationCorporationCEO(uint32 stationID);
    static uint32 GetCorporationCEO(uint32 corpID);

    static uint32 GetCloneTypeCostByID(uint32 cloneTypeID);

    static bool GetCurrentApplicationInfo(uint32 charID, uint32 corpID, ApplicationInfo &app);
    static bool InsertApplication(const ApplicationInfo & aInfo);
    static bool UpdateApplication(const ApplicationInfo &app);
    static bool DeleteApplication(const ApplicationInfo &app);
    static bool CreateMemberAttributeUpdate(MemberAttributeUpdate & attrib, uint32 newCorpID, uint32 charID);

    static bool UpdateDivisionNames(uint32 corpID, const Call_UpdateDivisionNames & divs, PyDict * notif);
    static bool UpdateCorporation(uint32 corpID, const Call_UpdateCorporation & upd, PyDict * notif);
    static bool UpdateLogo(uint32 corpID, const Call_UpdateLogo & upd, PyDict * notif);

    static bool ChangeCloneType(uint32 characterID, uint32 typeID);

    static PyDict* GetBookmarks(uint32 corporationID);

protected:
};





#endif


