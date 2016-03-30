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
    Author:        eve-moo
 */

#include "ChrBloodline.h"

#include "eveStatic.h"
#include "log/SystemLog.h"
#include "database/EVEDBUtils.h"

std::map<uint32, ChrBloodlineRef> ChrBloodline::s_AllBloodlines;

ChrBloodline::ChrBloodline(
                           uint32 _bloodlineID,
                           std::string _bloodlineName,
                           uint32 _raceID,
                           std::string _description,
                           std::string _maleDescription,
                           std::string _femaleDescription,
                           uint32 _shipTypeID,
                           uint32 _corporationID,
                           uint8 _perception,
                           uint8 _willpower,
                           uint8 _charisma,
                           uint8 _memory,
                           uint8 _intelligence,
                           uint32 _iconID,
                           std::string _shortDescription,
                           std::string _shortMaleDescription,
                           std::string _shortFemaleDescription
                           ) :
bloodlineID(_bloodlineID),
bloodlineName(_bloodlineName),
raceID(_raceID),
description(_description),
maleDescription(_maleDescription),
femaleDescription(_femaleDescription),
shipTypeID(_shipTypeID),
corporationID(_corporationID),
perception(_perception),
willpower(_willpower),
charisma(_charisma),
memory(_memory),
intelligence(_intelligence),
iconID(_iconID),
shortDescription(_shortDescription),
shortMaleDescription(_shortMaleDescription),
shortFemaleDescription(_shortFemaleDescription)
{
    s_AllBloodlines[bloodlineID] = ChrBloodlineRef(this, [](ChrBloodline * type)
    {
        delete type;
    });
}

ChrBloodline::~ChrBloodline() { }

bool EVEStatic::loadChrBloodlines()
{
    DBQueryResult result;
    DBResultRow row;
    std::string columns = "shipTypeID, weaponTypeID, miningTypeID, skillTypeID";
    std::string qry = "SELECT " + columns + " FROM chrBloodlines";
    if (!DBcore::RunQuery(result, qry.c_str()))
    {
        SysLog::Error("Static DB", "Error in query: %s", result.error.c_str());
        return false;
    }
    while (result.GetRow(row))
    {
        uint32 bloodlineID = row.GetInt(0);
        std::string bloodlineName = row.GetText(1);
        uint32 raceID = row.GetInt(2);
        std::string description = row.GetText(3);
        std::string maleDescription = row.GetText(4);
        std::string femaleDescription = row.GetText(5);
        uint32 shipTypeID = row.GetInt(6);
        uint32 corporationID = row.GetInt(7);
        uint8 perception = row.GetInt(8);
        uint8 willpower = row.GetInt(9);
        uint8 charisma = row.GetInt(10);
        uint8 memory = row.GetInt(11);
        uint8 intelligence = row.GetInt(12);
        uint32 iconID = row.getIntNC(13);
        std::string shortDescription = row.GetText(14);
        std::string shortMaleDescription = row.GetText(15);
        std::string shortFemaleDescription = row.GetText(16);
        new ChrBloodline(
                         bloodlineID,
                         bloodlineName,
                         raceID,
                         description,
                         maleDescription,
                         femaleDescription,
                         shipTypeID,
                         corporationID,
                         perception,
                         willpower,
                         charisma,
                         memory,
                         intelligence,
                         iconID,
                         shortDescription,
                         shortMaleDescription,
                         shortFemaleDescription
                         );
    }

    return true;
}
