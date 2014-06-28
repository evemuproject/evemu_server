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

#include "ship/modules/ActiveModules.h"

ActiveModule::ActiveModule(InventoryItemRef item, ShipRef ship)
: GenericModule(item, ship)
{
    m_ActiveModuleProc = new ActiveModuleProcessingComponent(item, this, ship);

	m_ChargeRef = InventoryItemRef();		// Ensure ref is NULL
    m_targetEntity = NULL;
    m_Charge_State = ChargeStates::MOD_UNLOADED;
    m_RequiresCharge = false;
    // load cycle for most charges is zero.
    m_LoadCycleTime = 0;
}

ActiveModule::~ActiveModule()
{
    //delete members
    delete m_ActiveModuleProc;

    //null ptrs
    m_ActiveModuleProc = NULL;
}

void ActiveModule::Process()
{
    m_ActiveModuleProc->Process();
}

void ActiveModule::Offline()
{
    Deactivate();
    GenericModule::Offline();
}

void ActiveModule::Activate(SystemEntity * targetEntity)
{
	// This may be handled by the Module class itself (eg. Afterburner.cpp)
    // but many modules may just need to run.
    m_ActiveModuleProc->ActivateCycle(-1);
}

void ActiveModule::Deactivate()
{
    m_ActiveModuleProc->DeactivateCycle();
}

void ActiveModule::Load(InventoryItemRef charge)
{
    // check if the crystal takes damage.
    if (charge->GetAttribute(AttrCrystalsGetDamaged, 0) == 1 && charge->quantity() == 1)
    {
        // make charge a singleton as it can be damaged and can no longer be stacked.
        charge->ChangeSingleton(true, true);
    }

    m_targetEntity = NULL;
    m_Charge_State = ChargeStates::MOD_LOADING;
    m_ActiveModuleProc->ActivateCycle( -1, charge);
	m_ChargeRef = InventoryItemRef();
}

void ActiveModule::Unload()
{
    m_Charge_State = ChargeStates::MOD_UNLOADED;
	m_ChargeRef = InventoryItemRef();		// Ensure ref is NULL
}

void ActiveModule::EndLoading(InventoryItemRef charge)
{
	m_ChargeRef = charge;
    m_Charge_State = ChargeStates::MOD_LOADED;
    if(m_ChargeRef.get() != NULL)
        m_ChargeRef->Move(m_Ship->itemID(), flag());
}
