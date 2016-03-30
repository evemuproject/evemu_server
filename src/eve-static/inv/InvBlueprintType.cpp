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

