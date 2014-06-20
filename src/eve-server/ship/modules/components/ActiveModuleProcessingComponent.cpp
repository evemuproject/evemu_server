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

#include "ship/Ship.h"
#include "ship/modules/ActiveModules.h"
#include "ship/modules/components/ActiveModuleProcessingComponent.h"
#include "system/SystemBubble.h"

ActiveModuleProcessingComponent::ActiveModuleProcessingComponent(InventoryItemRef item, ActiveModule * mod, ShipRef ship, ModifyShipAttributesComponent * shipAttrMod)
: m_Item( item ), m_Mod( mod ), m_Ship( ship ), m_ShipAttrModComp( shipAttrMod ), m_timer(0)
{
	m_Stop = false;
    m_ButtonCycle = false;
    m_EffectName = "";
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
    if(m_Mod->m_Charge_State == ChargeStates::MOD_LOADED)
    {
        // weapon is loaded and ready to do it's work.
        sLog.Debug("ActiveModuleProcessingComponent", "Cycle finished, processing...");
        ProcessActiveCycle();
    }
    else {
        // end the loading cycle.
        m_Stop = true;
        m_Mod->EndLoading();
    }

    //check if we have a signal to stop the cycle
    if(m_Stop)
    {
        // yep stop the cycle
        m_timer.Disable();
        m_Item->SetActive(false, 1253, 0, false);
        EndButton();
    }

}

void ActiveModuleProcessingComponent::ActivateCycle(uint32 effectID, std::string effectName, uint32 chargeID)
{
    // cannot activate module if it's still cycling from last activation.
    // cannot activate module if there is insufficient capacitor.
  	if(m_ButtonCycle == true || m_Ship->GetAttribute(AttrCharge) < m_Mod->GetAttribute(AttrCapacitorNeed))
    {
        return;
    }
    EvilNumber zero(0);
    if(m_Mod->GetAttribute(AttrDisallowRepeatingActivation, zero) != 0)
    	m_Stop = true;
    else
        m_Stop = false;
    // to-do: get the effect from the database dgmTypeEffects.  Should be category 2 with default flag.
    m_EffectID = effectID;
    m_EffectName = effectName;
    m_chargeID = chargeID;
    // if the effectID given is -1 attempt to look up the default effect.
    if(m_EffectID == -1)
    {
        MEffect *effect = m_Mod->m_Effects->GetDefaultEffect();
        if(effect != NULL)
        {
            // found the default effect.
            m_EffectID = effect->GetEffectID();
            m_EffectName = effect->GetGuid();
        }
    }

    // are we reloading?
    if(m_Mod->m_Charge_State == ChargeStates::MOD_LOADING || m_Mod->m_Charge_State == ChargeStates::MOD_RELOADING)
    {
        // loading, set cycle time to reload cycle time.
        m_CycleTime = m_Mod->m_LoadCycleTime;
        // instant load, do nothing more.
        if(m_CycleTime <= 0)
            m_Mod->EndLoading();
        // set the effect to onlining.
        m_EffectID = 0;//16;
        m_EffectName = "";
    }
    else
    {
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

    if(m_Mod->m_Charge_State == ChargeStates::MOD_LOADED)
    {
        // if weapon is loaded perform weapon start action.
        m_Mod->StartCycle();	// Do initial cycle immediately while we start timer
    }
    if(m_CycleTime > 0)
    {
        // start the timer.
        m_timer.Start(m_CycleTime.get_int());
        // start the button effects.
        StartButton();
    }
}

void ActiveModuleProcessingComponent::DeactivateCycle()
{
    m_Stop = true;
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

    try{
        // Check to see if our target is still in this bubble or has left or been destroyed:
        uint32 m_targetID = m_Mod->GetTargetID();
        if (!(m_Ship->GetOperator()->GetSystemEntity()->Bubble()->GetEntity(m_targetID)))
        {
            // Target has left our bubble or been destroyed, deactivate this module:
            m_Mod->Deactivate();
            return;
        }
    }
    catch (...){
        // something has gone wrong with our target.  Shutdown!
        // may happen as a result of kill all npcs
        m_Mod->Deactivate();
        return;
    }

    // consume capacitor
	EvilNumber capCapacity = m_Ship->GetAttribute(AttrCharge);
	EvilNumber capNeed = m_Mod->GetAttribute(AttrCapacitorNeed);
	capCapacity -= capNeed;

    // check for sufficient capacitor.
    if(capCapacity < 0)
    {
        // insufficient capacitor, deactivate.
        m_Mod->Deactivate();
        return;
    }

    // sufficient capacitor begin new cycle.
	m_Ship->SetAttribute(AttrCharge, capCapacity);

    // start new cycle.
    m_Mod->StartCycle();
    // start the new button cycle.
    StartButton();
}

double ActiveModuleProcessingComponent::GetRemainingCycleTimeMS()
{
	return (double)(m_timer.GetRemainingTime());
}

void ActiveModuleProcessingComponent::StartButton()
{
    m_ButtonCycle = true;
    uint32 tID = m_Mod->GetTargetID();

    // create ship button effect
    Notify_OnGodmaShipEffect shipEff;
    shipEff.itemID = m_Item->itemID();
    shipEff.effectID = m_EffectID; // From EVEEffectID::
    shipEff.when = Win32TimeNow();
    shipEff.start = 1;
    shipEff.active = 1;

    PyList* env = new PyList;
    env->AddItem(new PyInt(shipEff.itemID));
    env->AddItem(new PyInt(m_Ship->ownerID()));
    env->AddItem(new PyInt(m_Ship->itemID()));
    if(tID > 0)
      env->AddItem(new PyInt(tID));
    else
      env->AddItem(new PyNone);
    env->AddItem(new PyNone);
    env->AddItem(new PyNone);
    env->AddItem(new PyInt(m_EffectID));

    shipEff.environment = env;
    shipEff.startTime = shipEff.when;
    shipEff.duration = m_CycleTime.get_float();
    shipEff.repeat = new PyInt(1000);
    shipEff.randomSeed = new PyNone;
    shipEff.error = new PyNone;

    PyTuple *event = shipEff.Encode();
    m_Ship->GetOperator()->GetDestiny()->SendSelfDestinyEvent(&event);

    if(tID == 0)
        tID = m_Ship->itemID();

        // Create Special Effect:
// shipRef, moduleID, moduleTypeID,
// targetID, chargeID, effectString,
// isOffensive, isActive, duration, repeat
    m_Ship->GetOperator()->GetDestiny()->SendSpecialEffect
            (
             m_Ship,
             m_Item->itemID(),
             m_Item->typeID(),
             tID,
             tID > 0 ? m_chargeID : 0,
             m_EffectName,
             1,
             1,
             m_CycleTime.get_float(),
             m_Stop ? 1 : 0
             );

}

void ActiveModuleProcessingComponent::EndButton()
{
    m_ButtonCycle = false;
    uint32 tID = m_Mod->GetTargetID();

    Notify_OnGodmaShipEffect shipEff;
    shipEff.itemID = m_Item->itemID();
    shipEff.effectID = m_EffectID;
    shipEff.when = Win32TimeNow();
    shipEff.start = 0;
    shipEff.active = 0;
    if(m_Mod->m_Charge_State != ChargeStates::MOD_LOADED)
    {
        //shipEff.start = m_Mod->isOnline() ? 1 : 0;
        //shipEff.active = m_Mod->isOnline() ? 1 : 0;
    }

    PyList* env = new PyList;
    env->AddItem(new PyInt(shipEff.itemID));
    env->AddItem(new PyInt(m_Ship->ownerID()));
    env->AddItem(new PyInt(m_Ship->itemID()));
    if(tID > 0)
      env->AddItem(new PyInt(tID));
    else
      env->AddItem(new PyNone);
    env->AddItem(new PyNone);
    env->AddItem(new PyNone);
    env->AddItem(new PyInt(m_EffectID));

    shipEff.environment = env;
    shipEff.startTime = shipEff.when;
    shipEff.duration = 0;
    shipEff.repeat = new PyInt(1000);
    shipEff.randomSeed = new PyNone;
    shipEff.error = new PyNone;

    Notify_OnMultiEvent multi;
    multi.events = new PyList;
    multi.events->AddItem(shipEff.Encode());

    PyTuple* tmp = multi.Encode();

    m_Ship->GetOperator()->SendDogmaNotification("OnMultiEvent", "clientID", &tmp);
    
    if(tID == 0)
        tID = m_Ship->itemID();

    // Cancel Special Effect:
    m_Ship->GetOperator()->GetDestiny()->SendSpecialEffect(
             m_Ship,
             m_Item->itemID(),
             m_Item->typeID(),
             tID,
             tID > 0 ? m_chargeID : 0,
             m_EffectName,
             1,
             0,
             m_Item->GetAttribute(AttrSpeed).get_float(),
             0
             );
}

