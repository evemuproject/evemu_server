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
#include "EntityList.h"

#include "ship/modules/ActiveModules.h"

ActiveModule::ActiveModule(InventoryItemRef item, ShipRef ship)
: GenericModule(item, ship)
{
    m_ActiveModuleProc = new ActiveModuleProcessingComponent(item, this, ship);

	m_ChargeRef = InventoryItemRef();		// Ensure ref is NULL
    m_targetEntity = NULL;
    m_ChargeState = ChargeStates::MOD_UNLOADED;
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
    // store the target entity.
    m_targetEntity = targetEntity;
    // activate the module.
    m_ActiveModuleProc->ActivateCycle(-1);
}

void ActiveModule::Deactivate()
{
	m_ModuleState = MOD_DEACTIVATING;
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
    m_ChargeState = ChargeStates::MOD_LOADING;
	m_ChargeRef = charge;
    m_ActiveModuleProc->ActivateCycle( -1);
}

void ActiveModule::Unload()
{
    m_ChargeState = ChargeStates::MOD_UNLOADED;
	m_ChargeRef = InventoryItemRef();		// Ensure ref is NULL
}

void ActiveModule::EndLoading()
{
    m_ChargeState = ChargeStates::MOD_LOADED;
    // finally, move the charge into the module.
    if(m_ChargeRef.get() != NULL)
        m_ChargeRef->Move(m_Ship->itemID(), flag());
}

void ActiveModule::StartCycle()
{
    m_ModuleState = MOD_ACTIVATED;
    m_ChargeID = 0;
    EvilNumber civilianCharge;
    if(m_Item->HasAttribute(AttrAmmoLoaded, civilianCharge))
        m_ChargeID = civilianCharge.get_int();
    if(m_ChargeRef.get() != NULL)
        m_ChargeID = m_ChargeRef->typeID();
    DoGraphics(true);
    m_ShipActiveModifiers->SetActive(true);
    m_ShipPassiveModifiers->SetActive(false);
    m_ShipActiveModifiers->UpdateModifiers(m_Ship.get(), true);
    m_ShipPassiveModifiers->UpdateModifiers(m_Ship.get(), true);
}

void ActiveModule::StopCycle(bool abort)
{
    // Aknor had the chargeID as the itemID instead of typeID in the graphics stop, do the same.
    if(m_ChargeRef.get() != NULL)
        m_ChargeID = m_ChargeRef->itemID();
    m_ModuleState = MOD_ONLINE;
    DoGraphics(false);
    m_ShipActiveModifiers->SetActive(false);
    m_ShipPassiveModifiers->SetActive(true);
    m_ShipActiveModifiers->UpdateModifiers(m_Ship.get(), true);
    m_ShipPassiveModifiers->UpdateModifiers(m_Ship.get(), true);
}

void ActiveModule::DoGraphics(bool active, EVEEffectRef Effect)
{
    // no effect specified try to get a default.
    if(Effect.get() == NULL)
        Effect = m_Item->type().GetEffects()->GetDefaultEffect();
    // no effect?  no graphics!
    if(Effect.get() == NULL)
        return;
    // get the cycle time.
    double CycleTime = m_Item->GetAttribute(Effect->GetDurationAttributeID()).get_float();

    uint32 effectID = Effect->GetEffectID();
    std::string effectName = Effect->GetGuid();
    uint32 targetID = 0;
    if(m_targetEntity != NULL)
        targetID = m_targetEntity->GetID();
    uint32 itemID = m_Item->itemID();
    
    // create ship button effect
    Notify_OnGodmaShipEffect shipEff;
    shipEff.itemID = itemID;
    shipEff.effectID = effectID;
    shipEff.when = Win32TimeNow();
    shipEff.start = active ? 1 : 0;
    shipEff.active = active ? 1 : 0;

    PyList* env = new PyList;
    env->AddItem(new PyInt(shipEff.itemID));
    env->AddItem(new PyInt(m_Ship->ownerID()));
    env->AddItem(new PyInt(m_Ship->itemID()));
    if(targetID != 0)
        env->AddItem(new PyInt(targetID));
    else
        env->AddItem(new PyNone);
    env->AddItem(new PyNone);
    env->AddItem(new PyNone);
    env->AddItem(new PyInt(10));

    shipEff.environment = env;
    shipEff.startTime = shipEff.when;
    shipEff.duration = active ? CycleTime : 1.0;
    shipEff.repeat = new PyInt(active ? 1000 : 0);
    shipEff.randomSeed = new PyNone;
    shipEff.error = new PyNone;

    if(active)
    {
        PyTuple* tmp = new PyTuple(3);
        tmp->SetItem(2, shipEff.Encode());

        std::vector<PyTuple*> events;
        events.push_back(shipEff.Encode());

        std::vector<PyTuple*> updates;

        m_Ship->GetOperator()->GetDestiny()->SendDestinyUpdate(updates, events, true);
    }
    else
    {
        PyList* events = new PyList;
        events->AddItem(shipEff.Encode());

        Notify_OnMultiEvent multi;
        multi.events = events;

        PyTuple* tmp = multi.Encode();

        m_Ship->GetOperator()->SendDogmaNotification("OnMultiEvent", "clientID", &tmp);
    }

    m_Ship->GetOperator()->GetDestiny()->SendSpecialEffect (
         m_Ship,
         itemID,
         m_Item->typeID(),
         targetID,
         // projectile turrets sets this to 0 on start?
         //m_ChargeRef.get() != NULL ? (active ? m_ChargeRef->typeID() : m_ChargeRef->itemID() ) : 0,
         m_ChargeID,
         effectName.c_str(),
         Effect->GetIsOffensive() ? 1 : 0,
         active ? 1 : 0,
         active ? 1 : 0,
         active ? CycleTime : 1.0,
         active ? 1000 : 0   // this number vaires (1000, 50000) : (0, 1)
         );
    if(!active)
        m_ActiveModuleProc->DeactivateCycle();
}
