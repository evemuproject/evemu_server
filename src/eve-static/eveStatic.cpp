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
#include "inv/InvType.h"
#include "inv/InvGroup.h"
#include "inv/InvCategory.h"
#include "inv/InvBlueprintType.h"

#include "python/classes/PyDatabase.h"
#include "python/PyVisitor.h"
#include "log/SystemLog.h"
#include "database/EVEDBUtils.h"

#include <mutex>

bool EVEStatic::staticLoaded = false;
PyRep *EVEStatic::m_InvTypesCache = nullptr;
PyRep *EVEStatic::m_InvGroupsCache = nullptr;
PyRep *EVEStatic::m_InvCategoriesCache = nullptr;
PyRep *EVEStatic::m_InvBlueprintTypesCache = nullptr;

/**
 * Get a database row string value with null check.
 * @param row The row.
 * @param index The column.
 * @return The string or an empty string on null.
 */
std::string getStringNC(DBResultRow &row, int index)
{
    return (row.IsNull(index) ? "" : row.GetText(index));
}

/**
 * Get a database row int value with null check.
 * @param row The row.
 * @param index The column.
 * @return The int or an zero on null.
 */
int32 getIntNC(DBResultRow &row, int index)
{
    return row.IsNull(index) ? 0 : row.GetInt(index);
}

bool EVEStatic::loadStaticData()
{
    static std::mutex sMutex;
    auto lock = std::unique_lock<std::mutex>(sMutex);
    if (staticLoaded)
    {
        return true;
    }

    std::map<uint32, std::vector < uint32>> groupTypeList;
    std::map<uint32, std::vector < uint32>> categoryGroupList;
    DBQueryResult result;
    DBRowDescriptor *header;
    CRowSet *rowset;
    DBResultRow row;
    //-------------------------------
    // Load the invTypes table
    //-------------------------------

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
        std::string description = getStringNC(row, 3);
        uint32 graphicID = getIntNC(row, 4);
        double radius = row.GetDouble(5);
        double mass = row.GetDouble(6);
        double volume = row.GetDouble(7);
        double capacity = row.GetDouble(8);
        uint32 portionSize = row.GetInt(9);
        uint32 raceID = getIntNC(row, 10);
        double basePrice = row.GetDouble(11);
        bool published = row.GetBool(12);
        uint32 marketGroupID = getIntNC(row, 13);
        double chanceOfDuplicating = row.GetDouble(14);
        uint32 iconID = getIntNC(row, 16);
        // Create the type object.
        InvType *type = new InvType(
                                    typeID, groupID, typeName, description, graphicID,
                                    radius, mass, volume, capacity, portionSize,
                                    raceID, basePrice, published, marketGroupID,
                                    chanceOfDuplicating, iconID);
        groupTypeList[type->groupID].push_back(type->typeID);
    }
    m_InvTypesCache = rowset;

    //-------------------------------
    // Load the invGroups table
    //-------------------------------

    columns = "groupID, categoryID, groupName, description, iconID,"
            " 0 as graphicID, useBasePrice, allowManufacture, allowRecycler,"
            " anchored, anchorable, fittableNonSingleton, published, 0 AS dataID";
    qry = "SELECT " + columns + " FROM invGroups";
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
        uint32 iconID = getIntNC(row, 4);
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

    //-------------------------------
    // Load the invCategories table
    //-------------------------------

    columns = "categoryID, categoryName, description, 0 as graphicID, iconID, published, 0 as dataID";
    qry = "SELECT " + columns + " FROM invCategories";
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
        uint32 iconID = getIntNC(row, 4);
        bool published = row.GetBool(5);
        std::vector<uint32> categoryGroups;
        auto itr = categoryGroupList.find(categoryID);
        if (itr != categoryGroupList.end())
        {
            categoryGroups = itr->second;
        }
        InvCategory *Category = new InvCategory(categoryID, CategoryName,
                                                description, iconID, published, categoryGroups);
    }
    m_InvCategoriesCache = rowset;

    //-------------------------------
    // Load the invBlueprintTypes table
    //-------------------------------

    columns = "blueprintTypeID, parentBlueprintTypeID, productTypeID, productionTime, techLevel,"
            " researchProductivityTime, researchMaterialTime, researchCopyTime, researchTechTime,"
            " productivityModifier, materialModifier, wasteFactor, chanceOfReverseEngineering, maxProductionLimit";
    qry = "SELECT " + columns + " FROM invBlueprintTypes LEFT JOIN extInvBlueprintTypes Using(blueprintTypeID)";
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
        uint32 blueprintTypeID = row.GetInt(0);
        uint32 parentBlueprintTypeID = getIntNC(row, 1);
        uint32 productTypeID = row.GetInt(2);
        uint32 productionTime = row.GetInt(3);
        uint32 techLevel = row.GetInt(4);
        uint32 researchProductivityTime = row.GetInt(5);
        uint32 researchMaterialTime = row.GetInt(6);
        uint32 researchCopyTime = row.GetInt(7);
        uint32 researchTechTime = row.GetInt(8);
        uint32 productivityModifier = row.GetInt(9);
        uint32 materialModifier = row.GetInt(10);
        uint32 wasteFactor = row.GetInt(11);
        uint32 maxProductionLimit = row.GetInt(13);
        // from extInvBlueprintTypes
        double chanceOfReverseEngineering = 0;
        if (!row.IsNull(12))
        {
            chanceOfReverseEngineering = row.GetDouble(12);
        }
        InvBlueprintType *bpType = new InvBlueprintType(
                                                   blueprintTypeID,
                                                   parentBlueprintTypeID,
                                                   productTypeID,
                                                   productionTime,
                                                   techLevel,
                                                   researchProductivityTime,
                                                   researchMaterialTime,
                                                   researchCopyTime,
                                                   researchTechTime,
                                                   productivityModifier,
                                                   materialModifier,
                                                   wasteFactor,
                                                   maxProductionLimit,
                                                   chanceOfReverseEngineering);
    }
    m_InvBlueprintTypesCache = rowset;

    staticLoaded = true;
    return true;
}
