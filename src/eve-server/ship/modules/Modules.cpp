/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2011 The EVEmu Team
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
: m_ShipModifiers(item), m_ShipActiveModifiers(item), m_ShipPassiveModifiers(item), m_OverloadModifiers(item)
{
    m_Module_State = MOD_UNFITTED;
    m_Charge_State = MOD_UNLOADED;
    _isOverload = false;

    m_Item = item;
    m_Ship = ship;
    m_Effects = new ModuleEffects(m_Item->typeID());

    GenerateModifiers();
    // attach overload modifiers.
    m_Item->AddAttributeModifier(&m_OverloadModifiers);
    m_OverloadModifiers.SetActive(false);
    // attach ship modifiers.
    m_Ship->AddAttributeModifier(&m_ShipModifiers);
    m_Ship->AddAttributeModifier(&m_ShipPassiveModifiers);
    m_Ship->AddAttributeModifier(&m_ShipActiveModifiers);
    // update attributes.
    m_ShipActiveModifiers.SetActive(false);
    m_ShipModifiers.UpdateModifiers(m_Ship.get(), true);
    m_ShipPassiveModifiers.UpdateModifiers(m_Ship.get(), true);
    m_ShipActiveModifiers.UpdateModifiers(m_Ship.get(), true);
}

GenericModule::~GenericModule()
{
    // remove overload modifiers.
    m_Item->RemoveAttributeModifier(&m_OverloadModifiers);
    m_OverloadModifiers.UpdateModifiers(m_Item.get(), true);
    // remove ship modifiers.
    m_Ship->RemoveAttributeModifier(&m_ShipModifiers);
    m_Ship->RemoveAttributeModifier(&m_ShipPassiveModifiers);
    m_Ship->RemoveAttributeModifier(&m_ShipActiveModifiers);
    m_ShipModifiers.UpdateModifiers(m_Ship.get(), true);
    m_ShipActiveModifiers.UpdateModifiers(m_Ship.get(), true);
    m_ShipPassiveModifiers.UpdateModifiers(m_Ship.get(), true);

    //delete members
    delete m_Effects;

    //null ptrs
    m_Effects = NULL;
}

void GenericModule::Offline()
{
    //change item state
    m_Item->PutOffline();
    m_Module_State = MOD_OFFLINE;
    m_ShipModifiers.SetActive(false);
    m_ShipModifiers.UpdateModifiers(m_Ship.get(), true);
}

void GenericModule::Online()
{
    //change item state
    m_Item->PutOnline();
    m_Module_State = MOD_ONLINE;
    m_ShipModifiers.SetActive(true);
    m_ShipPassiveModifiers.SetActive(true);
    m_ShipModifiers.UpdateModifiers(m_Ship.get(), true);
}

void GenericModule::GenerateModifiers()
{
    // load and setup ONLINE effects
    ModuleEffects::EffectMap online = m_Effects->GetOnlineEffects();
    ModuleEffects::EffectMap::iterator itr = online.begin();
    for (; itr != online.end(); itr++)
    {
        MEffect *effect = itr->second;
        if (effect == NULL)
            continue;
        int nEffects = effect->GetSizeOfAttributeList();
        if (nEffects == 0)
            continue;
        for (int i = 0; i < nEffects; i++)
        {
            bool Stack = false;
            if (effect->GetStackingPenaltyApplied(i) != 0)
                Stack = true;
            typeTargetGroupIDlist *types = effect->GetTargetGroupIDlist(i);
            typeTargetGroupIDlist::iterator tItr = types->begin();
            for (; tItr != types->end(); tItr++)
            {
                uint32 affecting = effect->GetAffectingID(i);
                if (*tItr == 6 && (affecting == 0 || affecting == m_Item->groupID()))
                {
                    AttributeModifier *mod =
                            new AttributeModifier(
                                                  m_Item,
                                                  effect->GetSourceAttributeID(i),
                                                  effect->GetTargetAttributeID(i),
                                                  effect->GetCalculationType(i),
                                                  Stack, true
                                                  );
                    m_ShipModifiers.AddModifier(mod);
                }
            }
        }
    }
    // get and set up ACTIVE effects
    ModuleEffects::EffectMap active = m_Effects->GetActiveEffects();
    itr = active.begin();
    for (; itr != active.end(); itr++)
    {
        MEffect *effect = itr->second;
        if (effect == NULL)
            continue;
        int nEffects = effect->GetSizeOfAttributeList();
        if (nEffects == 0)
            continue;
        for (int i = 0; i < nEffects; i++)
        {
            bool Stack = false;
            if (effect->GetStackingPenaltyApplied(i) != 0)
                Stack = true;
            typeTargetGroupIDlist *types = effect->GetTargetGroupIDlist(i);
            typeTargetGroupIDlist::iterator tItr = types->begin();
            for (; tItr != types->end(); tItr++)
            {
                uint32 affecting = effect->GetAffectingID(i);
                if (*tItr == 6 && (affecting == 0 || affecting == m_Item->groupID()))
                {
                    AttributeModifier *mod =
                            new AttributeModifier(
                                                  m_Item,
                                                  effect->GetSourceAttributeID(i),
                                                  effect->GetTargetAttributeID(i),
                                                  effect->GetCalculationType(i),
                                                  Stack, true
                                                  );
                    m_ShipActiveModifiers.AddModifier(mod);
                }
            }
        }
    }
    // get and set up PASSIVE effects
    ModuleEffects::EffectMap passive = m_Effects->GetPassiveEffects();
    itr = passive.begin();
    for (; itr != passive.end(); itr++)
    {
        MEffect *effect = itr->second;
        if (effect == NULL)
            continue;
        int nEffects = effect->GetSizeOfAttributeList();
        if (nEffects == 0)
            continue;
        for (int i = 0; i < nEffects; i++)
        {
            bool Stack = false;
            if (effect->GetStackingPenaltyApplied(i) != 0)
                Stack = true;
            AttributeModifier *mod =
                    new AttributeModifier(
                                          m_Item,
                                          effect->GetSourceAttributeID(i),
                                          effect->GetTargetAttributeID(i),
                                          effect->GetCalculationType(i),
                                          Stack, true
                                          );
            m_ShipPassiveModifiers.AddModifier(mod);
        }
    }
    // get and set up Overload effects
    ModuleEffects::EffectMap overload = m_Effects->GetOverloadEffects();
    itr = overload.begin();
    for (; itr != overload.end(); itr++)
    {
        MEffect *effect = itr->second;
        if (effect == NULL)
            continue;
        int nEffects = effect->GetSizeOfAttributeList();
        if (nEffects == 0)
            continue;
        for (int i = 0; i < nEffects; i++)
        {
            bool Stack = false;
            if (effect->GetStackingPenaltyApplied(i) != 0)
                Stack = true;
            AttributeModifier *mod =
                    new AttributeModifier(
                                          m_Item,
                                          effect->GetSourceAttributeID(i),
                                          effect->GetTargetAttributeID(i),
                                          effect->GetCalculationType(i),
                                          Stack, true
                                          );
            m_OverloadModifiers.AddModifier(mod);
        }
    }
}
