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

#ifndef INVBLUEPRINTTYPE_H
#define	INVBLUEPRINTTYPE_H

#include "InvType.h"

class InvBlueprintType;
typedef std::shared_ptr<InvBlueprintType> InvBlueprintTypeRef;

class InvBlueprintType
{
public:
    InvBlueprintType(uint32 _blueprintTypeID,
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
                     );

    const uint32 blueprintTypeID;
    const uint32 parentBlueprintTypeID;
    const uint32 productTypeID;
    const uint32 productionTime;
    const uint32 techLevel;
    const uint32 researchProductivityTime;
    const uint32 researchMaterialTime;
    const uint32 researchCopyTime;
    const uint32 researchTechTime;
    const uint32 productivityModifier;
    const uint32 materialModifier;
    const uint32 wasteFactor;
    const uint32 maxProductionLimit;
    // from extInvBlueprintTypes
    const double chanceOfReverseEngineering;

    // Extra.
    const InvTypeRef productType;

    /**
     * Get the InvBlueprintType for the specified typeID
     * @param typeID The typeID to find.
     * @return The InvBlueprintType or nullptr if not found.
     */
    static InvBlueprintTypeRef getBlueprintType(uint32 typeID)
    {
        auto itr = s_AllBlueprintTypes.find(typeID);
        if (itr == s_AllBlueprintTypes.end())
        {
            return std::shared_ptr<InvBlueprintType>();
        }
        return itr->second;
    }

    /**
     * Get the InvBlueprintType for the specified typeID
     * @param typeID The typeID to find.
     * @param type The location to store the found type.
     * @return True if type was found.
     */
    static bool getBlueprintType(uint32 typeID, InvBlueprintTypeRef &type)
    {
        auto itr = s_AllBlueprintTypes.find(typeID);
        if (itr == s_AllBlueprintTypes.end())
        {
            type.reset();
            return false;
        }
        type = itr->second;
        return true;
    }

    /**
     * Find the blueprintType for the product.
     * @param productID The typeID of the product.
     * @return The blueprint.
     */
    static InvBlueprintTypeRef getProductBlueprint(uint32 productID)
    {
        for (auto bp : s_AllBlueprintTypes)
        {
            if (bp.second->productTypeID == productID)
            {
                return bp.second;
            }
        }
    }

    /**
     * Get the InvType for the blueprint.
     * @return The InvType or nullptr if not found.
     */
    InvTypeRef getType()
    {
        return InvType::getType(blueprintTypeID);
    }

private:
    InvBlueprintType(const InvBlueprintType& orig) = delete;
    virtual ~InvBlueprintType();

    static std::map<uint32, InvBlueprintTypeRef> s_AllBlueprintTypes;
};

#endif	/* INVBLUEPRINTTYPE_H */

