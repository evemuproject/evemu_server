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
    Author:        Luck
 */

#include "eve-server.h"

#include "ship/modules/Modules.h"

GenericModule::GenericModule(InventoryItemRef item, ShipRef ship)
{
    m_Item = item;
    m_Ship = ship;
    m_Effects = new ModuleEffects(m_Item->typeID());
    m_ModuleState = MOD_UNFITTED;
    m_ChargeState = MOD_UNLOADED;

    // Set up modifier sources.
    m_ShipModifiers = AttributeModifierSourceRef(new AttributeModifierSource(item));
    m_ShipActiveModifiers = AttributeModifierSourceRef(new AttributeModifierSource(item));
    m_ShipPassiveModifiers = AttributeModifierSourceRef(new AttributeModifierSource(item));
    m_OverloadModifiers = AttributeModifierSourceRef(new AttributeModifierSource(item));

    GenerateModifiers();
    // attach overload modifiers.
    m_OverloadModifiers->SetActive(false);
    m_Item->AddAttributeModifier(m_OverloadModifiers);
    // attach ship modifiers.
    m_ShipActiveModifiers->SetActive(false);
    m_ShipPassiveModifiers->SetActive(false);
    m_Ship->AddAttributeModifier(m_ShipModifiers);
    m_Ship->AddAttributeModifier(m_ShipPassiveModifiers);
    m_Ship->AddAttributeModifier(m_ShipActiveModifiers);
}

GenericModule::~GenericModule()
{
    // remove overload modifiers.
    m_Item->RemoveAttributeModifier(m_OverloadModifiers);
    // remove ship modifiers.
    m_Ship->RemoveAttributeModifier(m_ShipModifiers);
    m_Ship->RemoveAttributeModifier(m_ShipPassiveModifiers);
    m_Ship->RemoveAttributeModifier(m_ShipActiveModifiers);

    //delete members
    delete m_Effects;
    //null ptrs
    m_Effects = NULL;
}

void GenericModule::offline()
{
    // Insure the module is inactive.
    deactivate();
    //change item state
    m_Item->PutOffline();
    m_ModuleState = MOD_OFFLINE;

    // Disable ALL modifiers.
    m_ShipModifiers->SetActive(false);
    m_ShipPassiveModifiers->SetActive(false);
    m_ShipActiveModifiers->SetActive(false); // should be false anyway.
    m_ShipModifiers->UpdateModifiers(m_Ship.get(), true);
    m_ShipPassiveModifiers->UpdateModifiers(m_Ship.get(), true);
}

void GenericModule::online()
{
    //change item state
    m_Item->PutOnline();
    m_ModuleState = MOD_ONLINE;

    // Trigger modifiers.
    m_ShipModifiers->SetActive(true);
    m_ShipPassiveModifiers->SetActive(true);
    m_ShipActiveModifiers->SetActive(false); // should be false anyway.
    m_ShipModifiers->UpdateModifiers(m_Ship.get(), true);
    m_ShipPassiveModifiers->UpdateModifiers(m_Ship.get(), true);
}

bool GenericModule::isTurretFitted()
{
    // Try to make the effect called 'turretFitted' active, if it exists, to test for module being a turret:
    return m_Effects->HasEffect(Effect_turretFitted); // Effect_turretFitted from enum EveAttrEnum::Effect_turretFitted
}

bool GenericModule::isLauncherFitted()
{
    // Try to make the effect called 'launcherFitted' active, if it exists, to test for module being a launcher:
    return m_Effects->HasEffect(Effect_launcherFitted); // Effect_launcherFitted from enum EveAttrEnum::Effect_launcherFitted
}

bool GenericModule::isMaxGroupFitLimited()
{
    return m_Item->HasAttribute(AttrMaxGroupFitted); // AttrMaxGroupFitted from enum EveAttrEnum::AttrMaxGroupFitted
}

bool GenericModule::isRig()
{
    uint32 i = m_Item->categoryID();
    return ( (i >= 773 && i <= 782) || (i == 786) || (i == 787) || (i == 896) || (i == 904)); //need to use enums, but the enum system is a huge mess
}

bool GenericModule::isSubSystem()
{
    return (m_Item->categoryID() == EVEDB::invCategories::Subsystem);
}

ModulePowerLevel GenericModule::GetModulePowerLevel()
{
    if (isSubSystem())
    {
        return MODULE_BANK_SUBSYSTEM;
    }
    if (isRig())
    {
        return MODULE_BANK_RIG;
    }
    return isHighPower() ? MODULE_BANK_HIGH_POWER : (isMediumPower() ? MODULE_BANK_MEDIUM_POWER : MODULE_BANK_LOW_POWER);
}

void GenericModule::GenerateModifiers()
{
    // load and setup ONLINE effects
    auto map = m_Effects->GetEffects();
    for (auto itr : map)
    {
        std::shared_ptr<MEffect> effect = itr.second;
        int nEffects = effect->GetSizeOfAttributeList();
        if (nEffects == 0)
            continue;
        for (int i = 0; i < nEffects; i++)
        {
            // ignore anything that affects a non attribute.
            if (effect->GetSourceAttributeID(i) == 0 || effect->GetTargetAttributeID(i) == 0)
                continue;
            bool Stack = false;
            if (effect->GetStackingPenaltyApplied(i) != 0)
                Stack = true;
            AttributeModifierRef mod = AttributeModifierRef(new AttributeModifier(m_Item, effect, i, true));
            // get the module type that causes the effect.
            uint32 affecting = effect->GetAffectingID(i);
            uint32 state = effect->GetModuleStateWhenEffectApplied(i);
            if (affecting == 0 || affecting == m_Item->groupID())
            {
                typeTargetGroupIDlist *groups = effect->GetTargetGroupIDlist(i);
                typeTargetGroupIDlist::iterator tItr = groups->begin();
                for (; tItr != groups->end(); tItr++)
                {
                    uint32 groupID = *tItr;
                    if (groupID == 6) // target ship
                    {
                        if (state == EFFECT_ONLINE)
                            m_ShipModifiers->AddModifier(mod);
                        if (state == EFFECT_ACTIVE)
                            m_ShipActiveModifiers->AddModifier(mod);
                        if (state == EFFECT_PASSIVE)
                            m_ShipPassiveModifiers->AddModifier(mod);
                    }
                    else if (groupID == 0) // target self
                    {
                        if (state == EFFECT_OVERLOAD)
                            m_OverloadModifiers->AddModifier(mod);
                    }
                    else // target module
                    {
                        // to-do: add module modifiers.
                        if (state == EFFECT_ONLINE)
                        {
                            if (m_ModuleModifiers.find(groupID) == m_ModuleModifiers.end())
                                m_ModuleModifiers[groupID] = AttributeModifierSourceRef(new AttributeModifierSource(m_Item));
                            m_ModuleModifiers[groupID]->AddModifier(mod);
                        }
                    }
                }
            }
        }
    }
}
