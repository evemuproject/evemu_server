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

#include "InvCategory.h"
#include "InvGroup.h"

#include "eveStatic.h"
#include "python/classes/PyDatabase.h"
#include "python/PyVisitor.h"
#include "log/SystemLog.h"
#include "database/EVEDBUtils.h"

std::map<uint32, std::shared_ptr<InvCategory>> InvCategory::s_AllCategories;

InvCategory::InvCategory(uint32 _categoryID,
                         std::string _categoryName,
                         std::string _description,
                         uint32 _iconID,
                         bool _published,
                         std::vector<uint32> &_groups
                         ) :
categoryID(_categoryID),
categoryName(_categoryName),
description(_description),
iconID(_iconID),
published(_published)
{
    std::string sep;
    std::string pubSep;
    for (uint32 groupID : _groups)
    {
        InvGroupRef group;
        if (!InvGroup::getGroup(groupID, group))
        {
            continue;
        }
        // Get the types from the group and add them to the list.
        auto groupTypes = group->getTypeIDs();
        types.insert(types.end(), groupTypes.begin(), groupTypes.end());
        // Get the published types from the group and add them to the list.
        groupTypes = group->getTypeIDs(true);
        typesPublished.insert(typesPublished.end(), groupTypes.begin(), groupTypes.end());
        // Get the typesIN string and append it if not empty.
        std::string tIN = group->getTypesIN();
        if (!tIN.empty())
        {
            typesIN += sep + tIN;
            sep = ", ";
        }
        // Get the published typesIN string and append it if not empty.
        tIN = group->getTypesIN(true);
        if (!tIN.empty())
        {
            typesINPublished += pubSep + tIN;
            pubSep = ", ";
        }
    }
    s_AllCategories[categoryID] = std::shared_ptr<InvCategory>(this, [](InvCategory * type)
    {
        delete type;
    });
}

InvCategory::~InvCategory() { }

bool EVEStatic::loadInvCategories(std::map<uint32, std::vector < uint32>> &categoryGroupList)
{
    DBQueryResult result;
    DBRowDescriptor *header;
    CRowSet *rowset;
    DBResultRow row;
    std::string columns = "categoryID, categoryName, description, 0 as graphicID, iconID, published, 0 as dataID";
    std::string qry = "SELECT " + columns + " FROM invCategories";
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
        uint32 categoryID = row.GetInt(0);
        std::string CategoryName = row.GetText(1);
        std::string description = row.GetText(2);
        uint32 iconID = row.getIntNC(4);
        bool published = row.GetBool(5);
        std::vector<uint32> categoryGroups;
        auto itr = categoryGroupList.find(categoryID);
        if (itr != categoryGroupList.end())
        {
            categoryGroups = itr->second;
        }
        new InvCategory(categoryID, CategoryName,
                        description, iconID, published, categoryGroups);
    }
    m_InvCategoriesCache = rowset;

    return true;
}
