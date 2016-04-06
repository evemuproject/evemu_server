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

#include "EntityList.h"
#include "system/SystemBubble.h"
#include "ship/modules/ActiveModules.h"

ActiveModule::ActiveModule(InventoryItemRef item, ShipRef ship)
: GenericModule(item, ship),
 m_timer(0)
{
    m_stop = false;
    m_targetID = 0;
	m_chargeRef = InventoryItemRef();		// Ensure ref is NULL
	m_chargeLoaded = false;
}

void ActiveModule::process()
{
    if( m_ship->GetOperator()->GetSystemEntity()->Bubble() == nullptr )
    {
        // We have left the bubble!
        deactivate();
    }
    else
    {
        if(m_targetID != 0)
        {
            // Check to see if our target is still in this bubble or has left or been destroyed:
            if( m_ship->GetOperator()->GetSystemEntity()->Bubble()->GetEntity(m_targetID) == nullptr )
            {
                // Target has left our bubble or been destroyed, deactivate this module:
                deactivate();
            }
        }
    }
    // Check for empty ammo.
    if(m_chargeRef)
    {
        if(m_chargeRef->quantity() == 0)
        {
            deactivate();
            m_chargeRef->Delete();
        }
    }
    // Check if the timer expired.
    if (m_timer.Check())
    {
        // Check for sufficient capacitor charge.
        if (m_ship->getAttribute(AttrCharge) < m_item->getAttribute(AttrCapacitorNeed))
        {
            deactivate();
            // TO-DO: send capacitor depleted message.
            if(canAbort())
            {
                return;
            }
        }
        // Check if we have signal to stop the cycle
        if (m_stop)
        {
            doStop();
        }
        else
        {
            // Tell the module we finished a cycle and will be starting another.
            doEffect(false);
            if(!endCycle(true))
            {
                // Disable timer to prevent extra call to endCycle()
                m_timer.Disable();
                doStop();
                return;
            }
            // Drain capacitor.
            EvilNumber capCapacity = m_ship->getAttribute(AttrCharge);
            EvilNumber capNeed = m_item->getAttribute(AttrCapacitorNeed);
            capCapacity -= capNeed;
            m_ship->setAttribute(AttrCharge, capCapacity);
            // Reset the timer.
            m_timer.Start(getCycleTime());
            // Tell the module we are starting a cycle after ending another.
            startCycle(true);
            doEffect(true);
        }
    }
}

void ActiveModule::activate(SystemEntity * targetEntity)
{
    if (m_timer.Enabled())
    {
        return;
    }
    m_stop = false;
    // Check for sufficient capacitor charge.
    if (m_ship->getAttribute(AttrCharge) < m_item->getAttribute(AttrCapacitorNeed))
    {
        // TO-DO: send client insufficient power notice.
        return;
    }
    // store the target entity.
    m_targetEntity = targetEntity;
    if(!canActivate(targetEntity))
    {
        return;
    }
    m_targetID = 0;
    if(requiresTarget())
    {
        if(targetEntity == nullptr)
        {
            return;
        }
        m_targetID = targetEntity->Item()->itemID();
    }
    // Activate active processing component timer:
    m_timer.Start(getCycleTime());
    m_moduleState = MOD_ACTIVATED;
    // Drain capacitor.
    EvilNumber capCapacity = m_ship->getAttribute(AttrCharge);
    EvilNumber capNeed = m_item->getAttribute(AttrCapacitorNeed);
    capCapacity -= capNeed;
    m_ship->setAttribute(AttrCharge, capCapacity);
    // Show the module effects.
    showEffects();
    // Tell the module that we started a new cycle.
    startCycle(false);
    // Apply modifiers.
    m_shipActiveModifiers->setActive(true);
    m_shipPassiveModifiers->setActive(false);
    m_shipActiveModifiers->updateModifiers(m_ship.get(), true);
    m_shipPassiveModifiers->updateModifiers(m_ship.get(), true);
}

void ActiveModule::deactivate()
{
    m_stop = true;
    m_moduleState = MOD_DEACTIVATING;
    if(canAbort() && m_timer.Enabled())
    {
        doStop();
    }
}

void ActiveModule::load(InventoryItemRef charge)
{
	m_chargeRef = charge;
	m_chargeLoaded = true;
}

void ActiveModule::unload()
{
	m_chargeRef = InventoryItemRef();		// Ensure ref is NULL
	m_chargeLoaded = false;
}

bool ActiveModule::canActivate(SystemEntity *targetEntity)
{
    return true;
}

uint32 ActiveModule::getCycleTime()
{
    uint32 dur;
    if (m_item->fetchAttribute(AttrDuration, dur))
    {
        return dur;
    }
    else
    {
        if (m_item->fetchAttribute(AttrSpeed, dur))
        {
            return dur;
        }
        else
        {
            SysLog::Error("ActiveModule::ActivateCycle()", "ERROR! ActiveModule '%s' (id %u) has neither AttrSpeed nor AttrDuration! No way to process time-based cycle!", getItem()->itemName().c_str(), getItem()->itemID());
        }
    }
    return 0;
}

double ActiveModule::getRemainingCycleTimeMS()
{
    return (double) (m_timer.GetRemainingTime());
}

double ActiveModule::getElapsedCycleTimeMS()
{
    return (double) (m_timer.GetElapsedTime());
}

double ActiveModule::getTotalCycleTimeMS()
{
    return (double) (m_timer.GetTimerTime());
}

void ActiveModule::doStop()
{
    //m_Item->SetActive(false, 1253, 0, false);
    // Tell the module we finished a cycle and will NOT be starting another.
    if(m_timer.Enabled())
    {
        // The timer is still active, end the final cycle.
        endCycle(false);
        doEffect(false);
        // Disable timer.
        m_timer.Disable();
        m_stop = true;
    }
    if(m_moduleState != MOD_OFFLINE)
    {
        m_moduleState = MOD_ONLINE;
    }
    // Remove modifiers.
    m_shipActiveModifiers->setActive(false);
    m_shipPassiveModifiers->setActive(m_moduleState != MOD_OFFLINE);
    m_shipActiveModifiers->updateModifiers(m_ship.get(), true);
    m_shipPassiveModifiers->updateModifiers(m_ship.get(), true);
}

void ActiveModule::doEffect(bool active)
{
    doEffect(active, std::shared_ptr<MEffect>(), "");
}

void ActiveModule::doEffect(bool active, std::string effectString)
{
    doEffect(active, std::shared_ptr<MEffect>(), effectString);
}

void ActiveModule::doEffect(bool active, std::shared_ptr<MEffect> effect)
{
    doEffect(active, effect, "");
}

void ActiveModule::doEffect(bool active, std::shared_ptr<MEffect> effect, std::string effectString)
{
    if (effect == nullptr)
    {
        // Use default effect.
        effect = m_effects->GetDefaultEffect();
    }
    if (effect == nullptr)
    {
        // Unable to find an effect.
        return;
    }
    // Get the effect cycle time.
    double cycleTime = m_item->getAttribute(effect->GetDurationAttributeID()).get_float();
    // Create Destiny Updates:
    Notify_OnGodmaShipEffect shipEff;
    shipEff.itemID = m_item->itemID();
    shipEff.effectID = effect->GetEffectID();
    shipEff.when = Win32TimeNow();
    shipEff.start = active ? 1 : 0;
    shipEff.active = active ? 1 : 0;

    PyList* env = new PyList;
    env->AddItem(new PyInt(shipEff.itemID));
    env->AddItem(new PyInt(m_ship->ownerID()));
    env->AddItem(new PyInt(m_ship->itemID()));
    env->AddItem((m_targetID == 0) ? (PyRep *)new PyNone : (PyRep *)new PyInt(m_targetID));
    env->AddItem(new PyNone);
    env->AddItem(new PyNone);
    env->AddItem(new PyInt(shipEff.effectID));

    shipEff.environment = env;
    shipEff.startTime = shipEff.when;
    shipEff.duration = active ? cycleTime : 1.0;
    shipEff.repeat = new PyInt(active ? 1000 : 0);
    shipEff.randomSeed = new PyNone;
    if (m_error != nullptr)
    {
        shipEff.error = m_error;
        m_error = nullptr;
    }
    else
    {
        shipEff.error = new PyNone;
    }

    if(active)
    {
        PyTuple* tmp = new PyTuple(3);
        //tmp->SetItem(1, dmgMsg.Encode());
        tmp->SetItem(1, shipEff.Encode());

        std::vector<PyTuple*> events;
        //events.push_back(dmgMsg.Encode());
        events.push_back(shipEff.Encode());

        std::vector<PyTuple*> updates;
        //updates.push_back(dmgChange.Encode());

        m_ship->GetOperator()->GetDestiny()->SendDestinyUpdate(updates, events, false);
    }
    else
    {
        PyList* events = new PyList;
        events->AddItem(shipEff.Encode());

        Notify_OnMultiEvent multi;
        multi.events = events;

        PyTuple* tmp = multi.Encode();

        m_ship->GetOperator()->SendDogmaNotification("OnMultiEvent", "clientID", &tmp);
    }

    // Create Special Effect:
    uint32 chargeID = 0;
    if (m_chargeLoaded)
    {
        chargeID = m_chargeRef->itemID();
    }

    if (effectString.empty())
    {
        effectString = m_effectString;
    }
    if (effectString.empty())
    {
        effectString = effect->GetGuid();
    }
    m_effectString = effectString;
    m_ship->GetOperator()->GetDestiny()->SendSpecialEffect
            (
             m_ship,
             m_item->itemID(),
             m_item->typeID(),
             m_targetID,
             chargeID,
             effectString,
             effect->GetIsOffensive() ? 1 : 0,
            active ? 1 : 0,
            active ? 1 : 0,
            active ? cycleTime : 1.0,
            active ? 1 : 0 // this number vaires (1000, 50000) : (0, 1)
            );
}
