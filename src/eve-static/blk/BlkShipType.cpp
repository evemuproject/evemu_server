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

#include "BlkShipType.h"

#include "eveStatic.h"
#include "log/SystemLog.h"
#include "database/EVEDBUtils.h"

std::map<uint32, BlkShipTypeRef> BlkShipType::s_AllTypes;

BlkShipType::BlkShipType(
                         uint32 _shipTypeID,
                         uint32 _weaponTypeID,
                         uint32 _miningTypeID,
                         uint32 _skillTypeID
                         ) :
shipTypeID(_shipTypeID),
weaponTypeID(_weaponTypeID),
miningTypeID(_miningTypeID),
skillTypeID(_skillTypeID)
{
    s_AllTypes[shipTypeID] = BlkShipTypeRef(this, [](BlkShipType * type)
    {
        delete type;
    });
}

BlkShipType::~BlkShipType() { }

bool EVEStatic::loadBlkShipTypes()
{
    DBQueryResult result;
    DBResultRow row;
    std::string columns = "shipTypeID, weaponTypeID, miningTypeID, skillTypeID";
    std::string qry = "SELECT " + columns + " FROM blkShipTypes";
    if (!DBcore::RunQuery(result, qry.c_str()))
    {
        SysLog::Error("Static DB", "Error in query: %s", result.error.c_str());
        return false;
    }
    while (result.GetRow(row))
    {
        uint32 shipTypeID = row.GetInt(0);
        uint32 weaponTypeID = row.GetInt(1);
        uint32 miningTypeID = row.GetInt(2);
        uint32 skillTypeID = row.GetInt(3);
        new BlkShipType(
                        shipTypeID,
                        weaponTypeID,
                        miningTypeID,
                        skillTypeID
                        );
    }

    return true;
}
