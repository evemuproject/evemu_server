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

#include "StaStationType.h"

#include "eveStatic.h"
#include "log/SystemLog.h"
#include "database/EVEDBUtils.h"

std::map<uint32, StaStationTypeRef> StaStationType::s_AllTypes;

StaStationType::StaStationType(
                               uint32 _stationTypeID,
                               double _dockEntryX,
                               double _dockEntryY,
                               double _dockEntryZ,
                               double _dockOrientationX,
                               double _dockOrientationY,
                               double _dockOrientationZ,
                               uint32 _operationID,
                               uint32 _officeSlots,
                               double _reprocessingEfficiency,
                               bool _conquerable,
                               uint32 _dockingBayGraphicID,
                               uint32 _hangarGraphicID
                               ) :
stationTypeID(_stationTypeID),
dockEntryX(_dockEntryX),
dockEntryY(_dockEntryY),
dockEntryZ(_dockEntryZ),
dockOrientationX(_dockOrientationX),
dockOrientationY(_dockOrientationY),
dockOrientationZ(_dockOrientationZ),
operationID(_operationID),
officeSlots(_officeSlots),
reprocessingEfficiency(_reprocessingEfficiency),
conquerable(_conquerable),
dockingBayGraphicID(_dockingBayGraphicID),
hangarGraphicID(_hangarGraphicID),
dockEntry(_dockEntryX, _dockEntryY, _dockEntryZ),
dockOrientation(_dockOrientationX, _dockOrientationY, _dockOrientationZ)
{
    s_AllTypes[stationTypeID] = StaStationTypeRef(this, [](StaStationType * type)
    {
        delete type;
    });
}

StaStationType::~StaStationType() { }

bool EVEStatic::loadStaStationTypes()
{
    DBQueryResult result;
    DBResultRow row;
    std::string columns = "stationTypeID, dockEntryX, dockEntryY, dockEntryZ,"
            " dockOrientationX, dockOrientationY, dockOrientationZ,"
            " operationID, officeSlots, reprocessingEfficiency, conquerable,"
            " dockingBayGraphicID, hangarGraphicID";
    std::string qry = "SELECT " + columns + " FROM staStationTypes LEFT JOIN extStaStationTypes Using(stationTypeID)";
    if (!DBcore::RunQuery(result, qry.c_str()))
    {
        SysLog::Error("Static DB", "Error in query: %s", result.error.c_str());
        return false;
    }
    while (result.GetRow(row))
    {
        uint32 stationTypeID = row.GetInt(0);
        double dockEntryX = row.GetDouble(1);
        double dockEntryY = row.GetDouble(2);
        double dockEntryZ = row.GetDouble(3);
        double dockOrientationX = row.GetDouble(4);
        double dockOrientationY = row.GetDouble(5);
        double dockOrientationZ = row.GetDouble(6);
        uint32 operationID = row.getIntNC(7);
        uint32 officeSlots = row.getIntNC(8);
        double reprocessingEfficiency = row.getDoubleNC(9);
        bool conquerable = row.GetBool(10);
        // From extStaStationTypes
        uint32 dockingBayGraphicID = row.getIntNC(11);
        uint32 hangarGraphicID = row.getIntNC(12);
        new StaStationType(
                           stationTypeID,
                           dockEntryX,
                           dockEntryY,
                           dockEntryZ,
                           dockOrientationX,
                           dockOrientationY,
                           dockOrientationZ,
                           operationID,
                           officeSlots,
                           reprocessingEfficiency,
                           conquerable,
                           dockingBayGraphicID,
                           hangarGraphicID
                           );
    }

    return true;
}
