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

ActiveModuleProcessingComponent::ActiveModuleProcessingComponent(InventoryItemRef item, ActiveModule * mod, ShipRef ship, ModifyShipAttributesComponent * shipAttrMod)
: m_Item( item ), m_Mod( mod ), m_Ship( ship ), m_ShipAttrModComp( shipAttrMod ), m_timer(0)
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
    if(m_timer.Check())
    {
        // nope still waiting.
        return;
    }

    //time passed and we can drain cap and make/maintain changes to the attributes
    sLog.Debug("ActiveModuleProcessingComponent", "Cycle finished, processing...");
    ProcessActiveCycle();

    //check if we have a signal to stop the cycle
    if(m_Stop)
    {
        // yep stop the cycle
        m_timer.Disable();
        m_Item->SetActive(false, 1253, 0, false);
    }

}

void ActiveModuleProcessingComponent::ActivateCycle()
{
  	if(m_Ship->GetAttribute(AttrCharge) > m_Mod->GetAttribute(AttrCapacitorNeed))
    {
        m_Mod->Deactivate();
        return;
    }
	m_Stop = false;

    EvilNumber time;
    // we can do this because HasAttribute will not modify time if the attibute does not exist.
	if( m_Mod->HasAttribute(AttrDuration, time) || m_Mod->HasAttribute(AttrSpeed, time))
	{
		m_timer.Start(time.get_int());
		m_Mod->StartCycle();	// Do initial cycle immediately while we start timer
	}
	else
        sLog.Error( "ActiveModuleProcessingComponent::ActivateCycle()", "ERROR! ActiveModule '%s' (id %u) has neither AttrSpeed nor AttrDuration! No way to process time-based cycle!", m_Mod->getItem()->itemName().c_str(), m_Mod->getItem()->itemID() );
}

void ActiveModuleProcessingComponent::DeactivateCycle()
{
    m_Stop = true;
}

void ActiveModuleProcessingComponent::ProcessActiveCycle()
{
    // cycle ended perform end of cycle actions.
    m_Mod->EndCycle();

    //check for stop signal
    if(m_Stop)
        return;

    //else consume capacitor
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

    //then check if we are targeting another ship or not and apply attribute changes
	//maybe we can have a check for modules that repeat the same attributes so we
	//send the changes just once at activation and at deactivation

	//--pseudocode--
	//if(target != self)
	//	m_ShipAttrComp->ModifyTargetShipAttribute();
	//else
	//	m_ShipAttrComp->ModifyShipAttribute();
}

double ActiveModuleProcessingComponent::GetRemainingCycleTimeMS()
{
	return (double)(m_timer.GetRemainingTime());
}