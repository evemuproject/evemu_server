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
: m_Item( item ),
  m_Mod( mod ),
  m_Ship( ship ),
  m_timer(0),
  m_Effect((EVEEffect *)NULL)
{
	m_Stop = false;
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
    if(m_Mod->m_ChargeState != MOD_LOADING && m_Mod->m_ChargeState != MOD_RELOADING )
    {
        // module is ready to do it's work.
        sLog.Debug("ActiveModuleProcessingComponent", "Cycle finished, processing...");
        ProcessActiveCycle();
    }
    else {
        // end the loading cycle.
        m_Stop = true;
        // put the charge in the module.
        m_Mod->EndLoading();
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
    }

}

void ActiveModuleProcessingComponent::ActivateCycle(uint32 effectID)
{
    // cannot activate module if it's still cycling from last activation.
    if(m_timer.Enabled())
        return;
    // are we reloading?
    if(m_Mod->m_ChargeState == ChargeStates::MOD_LOADING || m_Mod->m_ChargeState == ChargeStates::MOD_RELOADING)
    {
        // loading, set cycle time to reload cycle time.
        m_CycleTime = m_Mod->m_LoadCycleTime;
        // instant load, do nothing more.
        if(m_CycleTime <= 0)
        {
            // put the charge in the module, immediately.
            m_Mod->EndLoading();
            return;
        }
        if(m_Mod->isOnline())
        {
            // this is a hack to try and get the module to flash.
            m_Item->PutOffline();
            m_Item->PutOnline();
        }
        // start the timer.
        m_timer.Start(m_CycleTime.get_int());
        return;
    }
    m_Effect = EVEEffectRef(NULL);
    // if the effectID given is -1 attempt to look up the default effect.
    if(effectID == -1)
        m_Effect = m_Item->type().GetEffects()->GetDefaultEffect();
    else
        m_Effect = m_Item->type().GetEffects()->GetEffect(effectID);
    bool autoRepeat;
    if(m_Effect.get() != NULL)
    {
        // an actual effect is being used.
        m_CycleTime = m_Mod->GetAttribute(m_Effect->GetDurationAttributeID());
        autoRepeat = !m_Effect->GetDisallowAutoRepeat();
    }
    else
    {
        // no effect specified, assume default behavior.
        EvilNumber zero(0);
        autoRepeat = m_Mod->GetAttribute(AttrDisallowRepeatingActivation, zero) == 0;
        // get the modules cycle time.
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

    if(m_CycleTime > 0)
    {
        if(!BeginCycle())
            return;
        // start the timer.
        m_timer.Start(m_CycleTime.get_int());
    }
    if(!autoRepeat)
    	m_Stop = true;
}

void ActiveModuleProcessingComponent::DeactivateCycle()
{
    m_Stop = true;
}

void ActiveModuleProcessingComponent::AbortCycle()
{
	// Immediately stop active cycle for things such as target destroyed or left bubble, or asteroid emptied and removed from space:
	m_Stop = true;
	m_timer.Disable();
    if(m_Mod->m_ChargeState == ChargeStates::MOD_LOADING || m_Mod->m_ChargeState == ChargeStates::MOD_RELOADING)
        m_Mod->EndLoading();
    else
        m_Mod->StopCycle(true);
}

bool ActiveModuleProcessingComponent::BeginCycle()
{
    // consume capacitor
    double capNeed;
    if(m_Effect.get() != NULL)
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
        // to-do: implement heat damage
    }

    // start new cycle.
    m_Mod->StartCycle();

    return true;
 }

void ActiveModuleProcessingComponent::ProcessActiveCycle()
{
    // cycle ended perform end of cycle actions.
    m_Mod->StopCycle();

    //check for stop signal
    if(m_Stop)
    {
        return; // cycle stopped.
    }

    // cycling not stopped start next cycle.
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
