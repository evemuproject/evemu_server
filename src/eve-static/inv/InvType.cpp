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

#include "eveStatic.h"

#include "InvType.h"
#include "log/SystemLog.h"
#include "InvGroup.h"

#include "python/classes/PyDatabase.h"
#include "python/PyVisitor.h"
#include "log/SystemLog.h"
#include "database/EVEDBUtils.h"

std::map<uint32, InvTypeRef> InvType::s_AllTypes;

InvType::InvType(uint32 _typeID,
                 uint32 _groupID,
                 std::string &_typeName,
                 std::string &_description,
                 uint32 _graphicID,
                 double _radius,
                 double _mass,
                 double _volume,
                 double _capacity,
                 uint32 _portionSize,
                 uint32 _raceID,
                 double _basePrice,
                 bool _published,
                 uint32 _marketGroupID,
                 double _chanceOfDuplicating,
                 uint32 _iconID
                 ) :
typeID(_typeID),
groupID(_groupID),
typeName(_typeName),
description(_description),
graphicID(_graphicID),
radius(_radius),
mass(_mass),
volume(_volume),
capacity(_capacity),
portionSize(_portionSize),
raceID(_raceID),
basePrice(_basePrice),
published(_published),
marketGroupID(_marketGroupID),
chanceOfDuplicating(_chanceOfDuplicating),
iconID(_iconID)
{
    s_AllTypes[typeID] = InvTypeRef(this, [](InvType * type)
    {
        delete type;
    });
}

InvType::~InvType() { }

uint32 InvType::getCategoryID()
{
    InvGroupRef group;
    if (InvGroup::getGroup(groupID, group))
    {
        return group->categoryID;
    }
    return 0;
}

bool EVEStatic::loadInvTypes(std::map<uint32, std::vector<uint32> >& groupTypeList)
{
    DBQueryResult result;
    DBRowDescriptor *header;
    CRowSet *rowset;
    DBResultRow row;
    // switch order of iconID and soundID because that's the way it was in objCacheDB.
    std::string columns = "typeID, groupID, typeName, description,"
            " graphicID, radius, mass, volume, capacity, portionSize,"
            " raceID, basePrice, published, marketGroupID, chanceOfDuplicating,"
            " soundID, iconID, dataID, typeNameID, descriptionID";
    std::string qry = "SELECT " + columns + " FROM invTypes LEFT JOIN extInvTypes USING(typeID)";
    if (!DBcore::RunQuery(result, qry.c_str()))
    {
        SysLog::Error("Static DB", "Error in query: %s", result.error.c_str());
        return false;
    }
    header = new DBRowDescriptor(result);
    rowset = new CRowSet(&header);
    while (result.GetRow(row))
    {
        PyPackedRow* into = rowset->NewRow();
        FillPackedRow(row, into);
        // Get the data for the global object.
        uint32 typeID = row.GetInt(0);
        uint32 groupID = row.GetInt(1);
        std::string typeName = row.GetText(2);
        std::string description = row.getStringNC(3);
        uint32 graphicID = row.getIntNC(4);
        double radius = row.GetDouble(5);
        double mass = row.GetDouble(6);
        double volume = row.GetDouble(7);
        double capacity = row.GetDouble(8);
        uint32 portionSize = row.GetInt(9);
        uint32 raceID = row.getIntNC(10);
        double basePrice = row.GetDouble(11);
        bool published = row.GetBool(12);
        uint32 marketGroupID = row.getIntNC(13);
        double chanceOfDuplicating = row.GetDouble(14);
        uint32 iconID = row.getIntNC(16);
        // Create the type object.
        InvType *type = new InvType(
                                    typeID, groupID, typeName, description, graphicID,
                                    radius, mass, volume, capacity, portionSize,
                                    raceID, basePrice, published, marketGroupID,
                                    chanceOfDuplicating, iconID);
        groupTypeList[type->groupID].push_back(type->typeID);
    }
    m_InvTypesCache = rowset;

    return true;
}
