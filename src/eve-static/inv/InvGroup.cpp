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

#include "InvGroup.h"
#include "InvType.h"

#include "eveStatic.h"
#include "python/classes/PyDatabase.h"
#include "python/PyVisitor.h"
#include "log/SystemLog.h"
#include "database/EVEDBUtils.h"

std::map<uint32, InvGroupRef> InvGroup::s_AllGroups;

InvGroup::InvGroup(uint32 _groupID,
                   uint32 _categoryID,
                   std::string &_groupName,
                   std::string &_description,
                   uint32 _iconID,
                   bool _useBasePrice,
                   bool _allowManufacture,
                   bool _allowRecycler,
                   bool _anchored,
                   bool _anchorable,
                   bool _fittableNonSingleton,
                   bool _published,
                   std::vector<uint32> &_types
                   ) :
groupID(_groupID),
categoryID(_categoryID),
groupName(_groupName),
description(_description),
iconID(_iconID),
useBasePrice(_useBasePrice),
allowManufacture(_allowManufacture),
allowRecycler(_allowRecycler),
anchored(_anchored),
anchorable(_anchorable),
fittableNonSingleton(_fittableNonSingleton),
published(_published)
{
    std::string sep;
    std::string pubSep;
    for (uint32 typeID : _types)
    {
        types.push_back(typeID);
        typesIN += sep + std::to_string(typeID);
        sep = ", ";
        InvTypeRef type;
        if (InvType::getType(typeID, type))
        {
            if (type->published)
            {
                typesPublished.push_back(typeID);
                typesINPublished += pubSep + std::to_string(typeID);
                pubSep = ", ";
            }
        }
    }
    s_AllGroups[groupID] = InvGroupRef(this, [](InvGroup * type)
    {
        delete type;
    });
}

InvGroup::~InvGroup() { }

bool EVEStatic::loadInvGroups(std::map<uint32, std::vector<uint32>> &groupTypeList, std::map<uint32, std::vector < uint32>> &categoryGroupList)
{
    DBQueryResult result;
    DBRowDescriptor *header;
    CRowSet *rowset;
    DBResultRow row;
    std::string columns = "groupID, categoryID, groupName, description, iconID,"
            " 0 as graphicID, useBasePrice, allowManufacture, allowRecycler,"
            " anchored, anchorable, fittableNonSingleton, published, 0 AS dataID";
    std::string qry = "SELECT " + columns + " FROM invGroups";
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
        uint32 groupID = row.GetInt(0);
        uint32 categoryID = row.GetInt(1);
        std::string groupName = row.GetText(2);
        std::string description = row.GetText(3);
        uint32 iconID = row.getIntNC(4);
        bool useBasePrice = row.GetBool(6);
        bool allowManufacture = row.GetBool(7);
        bool allowRecycler = row.GetBool(8);
        bool anchored = row.GetBool(9);
        bool anchorable = row.GetBool(10);
        bool fittableNonSingleton = row.GetBool(11);
        bool published = row.GetBool(12);
        std::vector<uint32> groupTypes;
        auto itr = groupTypeList.find(groupID);
        if (itr != groupTypeList.end())
        {
            groupTypes = itr->second;
        }
        InvGroup *group = new InvGroup(groupID, categoryID, groupName,
                                       description, iconID, useBasePrice,
                                       allowManufacture, allowRecycler, anchored,
                                       anchorable, fittableNonSingleton,
                                       published, groupTypes);
        categoryGroupList[group->categoryID].push_back(group->groupID);
    }
    m_InvGroupsCache = rowset;

    return true;
}
