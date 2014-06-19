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
{
    m_Item = item;
    m_Ship = ship;
    m_Effects = new ModuleEffects(m_Item->typeID());
    m_ShipAttrComp = new ModifyShipAttributesComponent(this, ship);

	m_chargeRef = InventoryItemRef();		// Ensure ref is NULL
    m_targetEntity = NULL;
    m_Charge_State = ChargeStates::MOD_UNLOADED;
}

ActiveModule::~ActiveModule()
{
    //delete members
    delete m_Effects;
    delete m_ShipAttrComp;

    //null ptrs
    m_Effects = NULL;
    m_ShipAttrComp = NULL;
}

void ActiveModule::Offline()
{
    m_Item->PutOffline();
}

void ActiveModule::Online()
{
    m_Item->PutOnline();
}

void ActiveModule::Activate(SystemEntity * targetEntity)
{
	//This will be handled by the Module class itself (eg. Afterburner.cpp)
}

void ActiveModule::Deactivate()
{
	//This will be handled by the Module class itself (eg. Afterburner.cpp)
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
	m_chargeRef = charge;
    // check to see if the client has been registered to this ship.
    // if not then it's either not a player ship or the player hasn't finished loading.
    if(!m_Ship->GetOperator()->IsClient())
    {
        // do instant load so no errors are generated.
        m_Charge_State = ChargeStates::MOD_LOADED;
        return;
    }
    m_ActiveModuleProc->ActivateCycle( EVEEffectID::effectHiPower, "", m_chargeRef->itemID());
}

void ActiveModule::Unload()
{
    m_Charge_State = ChargeStates::MOD_UNLOADED;
	m_chargeRef = InventoryItemRef();		// Ensure ref is NULL
}

void ActiveModule::EndLoading()
{
    m_Charge_State = ChargeStates::MOD_LOADED;
}
