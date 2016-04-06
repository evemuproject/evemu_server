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
    m_item = item;
    m_ship = ship;
    m_effects = new ModuleEffects(m_item->typeID());
    m_moduleState = MOD_UNFITTED;
    m_chargeState = MOD_UNLOADED;

    // Set up modifier sources.
    m_shipModifiers = AttributeModifierSourceRef(new AttributeModifierSource(item));
    m_shipActiveModifiers = AttributeModifierSourceRef(new AttributeModifierSource(item));
    m_shipPassiveModifiers = AttributeModifierSourceRef(new AttributeModifierSource(item));
    m_overloadModifiers = AttributeModifierSourceRef(new AttributeModifierSource(item));

    generateModifiers();
    // attach overload modifiers.
    m_overloadModifiers->setActive(false);
    m_item->AddAttributeModifier(m_overloadModifiers);
    // attach ship modifiers.
    m_shipActiveModifiers->setActive(false);
    m_shipPassiveModifiers->setActive(false);
    m_ship->AddAttributeModifier(m_shipModifiers);
    m_ship->AddAttributeModifier(m_shipPassiveModifiers);
    m_ship->AddAttributeModifier(m_shipActiveModifiers);
}

GenericModule::~GenericModule()
{
    // remove overload modifiers.
    m_item->RemoveAttributeModifier(m_overloadModifiers);
    // remove ship modifiers.
    m_ship->RemoveAttributeModifier(m_shipModifiers);
    m_ship->RemoveAttributeModifier(m_shipPassiveModifiers);
    m_ship->RemoveAttributeModifier(m_shipActiveModifiers);

    //delete members
    delete m_effects;
    //null ptrs
    m_effects = NULL;
}

void GenericModule::offline()
{
    // Insure the module is inactive.
    deactivate();
    //change item state
    m_item->PutOffline();
    m_moduleState = MOD_OFFLINE;

    // Disable ALL modifiers.
    m_shipModifiers->setActive(false);
    m_shipPassiveModifiers->setActive(false);
    m_shipActiveModifiers->setActive(false); // should be false anyway.
    m_shipModifiers->updateModifiers(m_ship.get(), true);
    m_shipPassiveModifiers->updateModifiers(m_ship.get(), true);
}

void GenericModule::online()
{
    //change item state
    m_item->PutOnline();
    m_moduleState = MOD_ONLINE;

    // Trigger modifiers.
    m_shipModifiers->setActive(true);
    m_shipPassiveModifiers->setActive(true);
    m_shipActiveModifiers->setActive(false); // should be false anyway.
    m_shipModifiers->updateModifiers(m_ship.get(), true);
    m_shipPassiveModifiers->updateModifiers(m_ship.get(), true);
}

bool GenericModule::isTurretFitted()
{
    // Try to make the effect called 'turretFitted' active, if it exists, to test for module being a turret:
    return m_effects->HasEffect(Effect_turretFitted); // Effect_turretFitted from enum EveAttrEnum::Effect_turretFitted
}

bool GenericModule::isLauncherFitted()
{
    // Try to make the effect called 'launcherFitted' active, if it exists, to test for module being a launcher:
    return m_effects->HasEffect(Effect_launcherFitted); // Effect_launcherFitted from enum EveAttrEnum::Effect_launcherFitted
}

bool GenericModule::isMaxGroupFitLimited()
{
    return m_item->hasAttribute(AttrMaxGroupFitted); // AttrMaxGroupFitted from enum EveAttrEnum::AttrMaxGroupFitted
}

bool GenericModule::isRig()
{
    uint32 i = m_item->categoryID();
    return ( (i >= 773 && i <= 782) || (i == 786) || (i == 787) || (i == 896) || (i == 904)); //need to use enums, but the enum system is a huge mess
}

bool GenericModule::isSubSystem()
{
    return (m_item->categoryID() == EVEDB::invCategories::Subsystem);
}

ModulePowerLevel GenericModule::getModulePowerLevel()
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

void GenericModule::generateModifiers()
{
    // load and setup ONLINE effects
    auto map = m_effects->GetEffects();
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
            AttributeModifierRef mod = AttributeModifierRef(new AttributeModifier(m_item, effect, i, true));
            // get the module type that causes the effect.
            uint32 affecting = effect->GetAffectingID(i);
            uint32 state = effect->GetModuleStateWhenEffectApplied(i);
            if (affecting == 0 || affecting == m_item->groupID())
            {
                typeTargetGroupIDlist *groups = effect->GetTargetGroupIDlist(i);
                typeTargetGroupIDlist::iterator tItr = groups->begin();
                for (; tItr != groups->end(); tItr++)
                {
                    uint32 groupID = *tItr;
                    if (groupID == 6) // target ship
                    {
                        if (state == EFFECT_ONLINE)
                            m_shipModifiers->addModifier(mod);
                        if (state == EFFECT_ACTIVE)
                            m_shipActiveModifiers->addModifier(mod);
                        if (state == EFFECT_PASSIVE)
                            m_shipPassiveModifiers->addModifier(mod);
                    }
                    else if (groupID == 0) // target self
                    {
                        if (state == EFFECT_OVERLOAD)
                            m_overloadModifiers->addModifier(mod);
                    }
                    else // target module
                    {
                        // to-do: add module modifiers.
                        if (state == EFFECT_ONLINE)
                        {
                            if (m_moduleModifiers.find(groupID) == m_moduleModifiers.end())
                                m_moduleModifiers[groupID] = AttributeModifierSourceRef(new AttributeModifierSource(m_item));
                            m_moduleModifiers[groupID]->addModifier(mod);
                        }
                    }
                }
            }
        }
    }
}
