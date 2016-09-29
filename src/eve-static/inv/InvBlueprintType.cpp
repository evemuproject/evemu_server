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

#include "InvBlueprintType.h"

#include "eveStatic.h"
#include "python/classes/PyDatabase.h"
#include "log/SystemLog.h"
#include "database/EVEDBUtils.h"

std::map<uint32, InvBlueprintTypeRef> InvBlueprintType::s_AllBlueprintTypes;

InvBlueprintType::InvBlueprintType(uint32 _blueprintTypeID,
                                   uint32 _parentBlueprintTypeID,
                                   uint32 _productTypeID,
                                   uint32 _productionTime,
                                   uint32 _techLevel,
                                   uint32 _researchProductivityTime,
                                   uint32 _researchMaterialTime,
                                   uint32 _researchCopyTime,
                                   uint32 _researchTechTime,
                                   uint32 _productivityModifier,
                                   uint32 _materialModifier,
                                   uint32 _wasteFactor,
                                   uint32 _maxProductionLimit,
                                   double _chanceOfReverseEngineering
                                   ) :
blueprintTypeID(_blueprintTypeID),
parentBlueprintTypeID(_parentBlueprintTypeID),
productTypeID(_productTypeID),
productionTime(_productionTime),
techLevel(_techLevel),
researchProductivityTime(_researchProductivityTime),
researchMaterialTime(_researchMaterialTime),
researchCopyTime(_researchCopyTime),
researchTechTime(_researchTechTime),
productivityModifier(_productivityModifier),
materialModifier(_materialModifier),
wasteFactor(_wasteFactor),
maxProductionLimit(_maxProductionLimit),
chanceOfReverseEngineering(_chanceOfReverseEngineering),
productType(InvType::getType(_productTypeID))
{
    s_AllBlueprintTypes[blueprintTypeID] = InvBlueprintTypeRef(this, [](InvBlueprintType * type)
    {
        delete type;
    });
}

InvBlueprintType::~InvBlueprintType() { }

bool EVEStatic::loadInvBlueprintTypes()
{
    DBQueryResult result;
    DBRowDescriptor *header;
    CRowSet *rowset;
    DBResultRow row;

    std::string columns = "blueprintTypeID, parentBlueprintTypeID, productTypeID, productionTime, techLevel,"
            " researchProductivityTime, researchMaterialTime, researchCopyTime, researchTechTime,"
            " productivityModifier, materialModifier, wasteFactor, chanceOfReverseEngineering, maxProductionLimit";
    std::string qry = "SELECT " + columns + " FROM invBlueprintTypes LEFT JOIN extInvBlueprintTypes Using(blueprintTypeID)";
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
        uint32 parentBlueprintTypeID = row.getIntNC(1);
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
        double chanceOfReverseEngineering = row.getDoubleNC(12);
        new InvBlueprintType(
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

    return true;
}
