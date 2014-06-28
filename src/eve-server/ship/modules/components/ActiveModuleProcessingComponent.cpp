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

#include "Client.h"
#include "EntityList.h"
#include "ship/Ship.h"
#include "ship/modules/ActiveModules.h"
#include "ship/modules/components/ActiveModuleProcessingComponent.h"
#include "system/SystemBubble.h"

ActiveModuleProcessingComponent::ActiveModuleProcessingComponent(InventoryItemRef item, ActiveModule * mod, ShipRef ship)
: m_Item( item ), m_Mod( mod ), m_Ship( ship ), m_timer(0)
{
	m_Stop = false;
    m_ButtonCycle = false;
    m_Effect = NULL;
}

ActiveModuleProcessingComponent::~ActiveModuleProcessingComponent()
{
    //nothing to do yet
}

/****************************************************
	A little note about the timer:
		Timer.Check() has two functions:
			1. It checks if the timer has expired out 
			2. It subtracts from the start time
	Don't be fooled by it's name because if you don't
	call it in a loop, you won't get the time moving.
*****************************************************/


void ActiveModuleProcessingComponent::Process()
{
    //check if the timer expired & subtract time.  will always fail if disabled. (stopped))
    if(!m_timer.Check())
        return;  // nope still waiting.

    //time passed and we can drain cap and make/maintain changes to the attributes
    if(m_Mod->m_Charge_State == MOD_LOADED || (m_Mod->m_RequiresCharge == false && m_Mod->m_Charge_State == MOD_UNLOADED) )
    {
        // module is ready to do it's work.
        sLog.Debug("ActiveModuleProcessingComponent", "Cycle finished, processing...");
        ProcessActiveCycle();
    }
    else {
        // end the loading cycle.
        m_Stop = true;
        m_ButtonCycle = false;
        // put the charge in the module.
        m_Mod->EndLoading(m_Charge);
        // disable and stop the timer.
        m_timer.Disable();
        //m_Item->SetActive(false, 1253, 0, false);
        return;
    }
    // if were not stopping try to start another cycle.
    if(!m_Stop)
        BeginCycle();
    //check if we have a signal to stop the cycle
    if(m_Stop)
    {
        // yep stop the cycle
        m_timer.Disable();
        //m_Item->SetActive(false, 1253, 0, false);
        EndButton();
    }

}

void ActiveModuleProcessingComponent::ActivateCycle(uint32 effectID, InventoryItemRef charge)
{
    // cannot activate module if it's still cycling from last activation.
  	if(m_ButtonCycle == true)
        return;
    // are we reloading?
    if(m_Mod->m_Charge_State == ChargeStates::MOD_LOADING || m_Mod->m_Charge_State == ChargeStates::MOD_RELOADING)
    {
        // store the charge for loading.
        m_Charge = charge;
        // loading, set cycle time to reload cycle time.
        m_CycleTime = m_Mod->m_LoadCycleTime;
        // instant load, do nothing more.
        if(m_CycleTime <= 0)
        {
            // put the charge in the module.
            m_Mod->EndLoading(m_Charge);
            return;
        }
        if(m_Mod->isOnline())
        {
            m_Item->PutOffline();
            m_Item->PutOnline();
        }
        m_ButtonCycle = true;
        // start the timer.
        m_timer.Start(m_CycleTime.get_int());
        return;
    }
    m_Effect = NULL;
    // if the effectID given is -1 attempt to look up the default effect.
    if(effectID == -1)
        m_Effect = m_Mod->m_Effects->GetDefaultEffect();
    bool autoRepeat;
    if(m_Effect != NULL)
    {
        m_CycleTime = m_Mod->GetAttribute(m_Effect->GetDurationAttributeID());
        autoRepeat = !m_Effect->GetDisallowAutoRepeat();
    }
    else
    {
        EvilNumber zero(0);
        autoRepeat = m_Mod->GetAttribute(AttrDisallowRepeatingActivation, zero) == 0;
        // to-do: move this to module so that the module can factor in skill effects on time.
        // create function bool GetCycleTime(m_CycleTime); ?? returns false if no time found.
        if(!m_Mod->HasAttribute(AttrDuration, m_CycleTime))
        {
            if(!m_Mod->HasAttribute(AttrSpeed, m_CycleTime))
            {
                sLog.Error( "ActiveModuleProcessingComponent::ActivateCycle()", "ERROR! ActiveModule '%s' (id %u) has neither AttrSpeed nor AttrDuration! No way to process time-based cycle!", m_Mod->getItem()->itemName().c_str(), m_Mod->getItem()->itemID() );
                return;
            }
        }
    }
    
    m_Stop = false;
    if(!autoRepeat)
    	m_Stop = true;
    m_Charge = charge;

    if(m_CycleTime > 0)
    {
        if(!BeginCycle())
            return;
        // start the timer.
        m_timer.Start(m_CycleTime.get_int());
    }
}

void ActiveModuleProcessingComponent::DeactivateCycle()
{
    m_Stop = true;
}

bool ActiveModuleProcessingComponent::BeginCycle()
{
    // consume capacitor
    double capNeed;
    if(m_Effect != NULL)
        capNeed = m_Mod->GetAttribute(m_Effect->GetDischargeAttributeID()).get_float();
    else
        capNeed = m_Mod->GetAttribute(AttrCapacitorNeed).get_float();
	double capCapacity = m_Ship->GetAttribute(AttrCharge).get_float();
	capCapacity -= capNeed;

    // check for sufficient capacitor.
    if(capCapacity < 0)
    {
        // insufficient capacitor, deactivate.
        m_Mod->Deactivate();
        return false;
    }

    // sufficient capacitor begin new cycle.
	m_Ship->SetAttribute(AttrCharge, capCapacity);

   // check for overloading.
    if(m_Mod->_isOverload)
    {
        // check for time modifier.
        EvilNumber time;
        if(m_Mod->HasAttribute(::EveAttrEnum::AttrOverloadSelfDurationBonus, time))
        {
            double mult = 1 - (time.get_float() / 100.0);
            m_CycleTime *= mult;
        }
//        EvilNumber heat;
//        if(m_Mod->HasAttribute(AttrHeatDamage, heat))
//        {
//            // to-do: this needs work.
//            EvilNumber hp = m_Mod->GetAttribute(AttrHp);
//            hp -= heat;
//            m_Mod->SetAttribute(AttrHp, hp);
//            if(hp.get_float() <= 0)
//                DeactivateCycle();
//        }
    }

    // start new cycle.
    m_Mod->StartCycle();
    // start the new button cycle.
    StartButton();
    
    return true;
 }

void ActiveModuleProcessingComponent::ProcessActiveCycle()
{
    // cycle ended perform end of cycle actions.
    m_Mod->EndCycle();

    // to-do: check to make sure target still valid.
    // stop if it's disapeared.  or errors may occure.
    
    //check for stop signal
    if(m_Stop)
    {
        return; // cycle stopped.
    }

    // cycle not stopped start next cycle.

    try
    {
        // Check to see if our target is still in this bubble or has left or been destroyed:
        uint32 m_targetID = m_Mod->GetTargetID();
        if(m_targetID > 0)
        {
            if (!(m_Ship->GetOperator()->GetSystemEntity()->Bubble()->GetEntity(m_targetID)))
            {
                // Target has left our bubble or been destroyed, deactivate this module:
                m_Mod->Deactivate();
                return;
            }
        }
    }
    catch (...)
    {
        // something has gone wrong with our target.  Shutdown!
        // may happen as a result of kill all npcs
        m_Mod->Deactivate();
        return;
    }

}

double ActiveModuleProcessingComponent::GetRemainingCycleTimeMS()
{
	return (double)(m_timer.GetRemainingTime());
}

void DoButton(ShipRef Ship, InventoryItemRef Item, MEffect *Effect, float CycleTime, uint32 targetID, bool start, bool active, uint32 chargeID)
{
    // if we have no ship or module to affect do nothing.
    if(Item.get() == NULL || Ship.get() == NULL || Effect == NULL)
        return;

    Client *c = sEntityList.FindCharacter(Ship->ownerID());
    if(c == NULL)
        return;

    uint32 effectID = Effect->GetEffectID();
    std::string effectName = Effect->GetGuid();

    uint32 itemID = Item->itemID();
    // create ship button effect
    Notify_OnGodmaShipEffect shipEff;
    shipEff.itemID = itemID;
    shipEff.effectID = effectID;
    shipEff.when = Win32TimeNow();
    shipEff.start = start ? 1 : 0;
    shipEff.active = active ? 1 : 0;

    PyList* env = new PyList;
    env->AddItem(new PyInt(shipEff.itemID));
    env->AddItem(new PyInt(Item->ownerID()));
    if(targetID > 0)
    {
      env->AddItem(new PyInt(Ship->itemID()));
      env->AddItem(new PyInt(targetID));
    }
    else
    {
      env->AddItem(new PyInt(Item->locationID()));
      env->AddItem(new PyNone);
    }
    env->AddItem(new PyNone);
    env->AddItem(new PyNone);
    env->AddItem(new PyInt(effectID));

    shipEff.environment = env;
    shipEff.startTime = shipEff.when;
    shipEff.duration = CycleTime;
    shipEff.repeat = new PyInt(1000);
    shipEff.randomSeed = new PyNone;
    shipEff.error = new PyNone;

    PyTuple *event = shipEff.Encode();
    Ship->GetOperator()->GetDestiny()->SendSelfDestinyEvent(&event);

        // Create Special Effect:
// shipRef, moduleID, moduleTypeID,
// targetID, chargeID, effectString,
// isOffensive, isActive, duration, repeat
    if( !Effect->GetGuid().empty() && (Effect->GetIsOffensive() == (targetID > 0 ) ) )
    {
        Ship->GetOperator()->GetDestiny()->SendSpecialEffect
            (
             Ship,
             itemID,
             Item->typeID(),
             targetID,
             targetID > 0 ? chargeID : 0,
             effectName.c_str(),
             Effect->GetIsOffensive() ? 1 : 0,
             active ? 1 : 0,
             CycleTime,
             start ? 1 : 0
             );
    }
}

void ActiveModuleProcessingComponent::StartButton()
{
    m_ButtonCycle = true;
    uint32 tID = m_Mod->GetTargetID();
    uint32 chargeID = 0;
    if(m_Charge.get() != NULL)
        chargeID = m_Charge->itemID();
    else
    {
        // no charge loaded, check to see if this is a civilian module.
        EvilNumber civilianCharge;
        if(m_Mod->HasAttribute(AttrAmmoLoaded, civilianCharge))
        {
            chargeID = civilianCharge.get_int();
        }
    }

    DoButton(m_Ship, m_Item, m_Effect, m_CycleTime.get_float(), tID, true, true, chargeID);
}

void ActiveModuleProcessingComponent::EndButton()
{
    m_ButtonCycle = false;
    uint32 tID = m_Mod->GetTargetID();
    uint32 chargeID = 0;
    if(m_Charge.get() != NULL)
        chargeID = m_Charge->itemID();

    DoButton(m_Ship, m_Item, m_Effect, m_CycleTime.get_float(), tID, false, false, chargeID);    
}

