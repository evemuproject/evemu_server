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
    Author:        Reve
*/

#include "eve-server.h"

#include "EntityList.h"
#include "system/SystemBubble.h"
#include "system/Damage.h"
#include "system/SystemManager.h"
#include "PyServiceMgr.h"
#include "ship/modules/mining_modules/MiningLaser.h"

MiningLaser::MiningLaser( InventoryItemRef item, ShipRef ship )
{
    m_Item = item;
    m_Ship = ship;
    m_Effects = new ModuleEffects(m_Item->typeID());
    m_ShipAttrComp = new ModifyShipAttributesComponent(this, ship);
	m_ActiveModuleProc = new ActiveModuleProcessingComponent(item, this, ship, m_ShipAttrComp);

	m_chargeRef = InventoryItemRef();		// Ensure ref is NULL
	m_chargeLoaded = false;

	m_ModuleState = MOD_UNFITTED;
	m_ChargeState = MOD_UNLOADED;

	//m_IsInitialCycle = true;
}

MiningLaser::~MiningLaser()
{

}

void MiningLaser::Process()
{
	m_ActiveModuleProc->Process();
}

void MiningLaser::Load(InventoryItemRef charge)
{
	ActiveModule::Load(charge);
	m_ChargeState = MOD_LOADED;
}

void MiningLaser::Unload()
{
	ActiveModule::Unload();
	m_ChargeState = MOD_UNLOADED;
}

void MiningLaser::Repair()
{

}

void MiningLaser::Overload()
{

}

void MiningLaser::DeOverload()
{

}

void MiningLaser::DestroyRig()
{

}

void MiningLaser::Activate(SystemEntity * targetEntity)
{
    InventoryItemRef miner = getItem();
    bool isIceMiner = (miner->typeID() == 16278 || miner->typeID() == 22229 || miner->typeID() == 28752);
    if (isIceMiner)
    {
        // Only allow ice harvesters to mine ice.
        if (targetEntity->Item()->groupID() != EVEDB::invGroups::Ice)
        {
            SysLog::Error("MiningLaser::Activate()", "ERROR: invalid target!");
            throw PyException(MakeCustomError("ERROR!  invalid target!"));
        }
    }
    else if (miner->groupID() == EVEDB::invGroups::Gas_Cloud_Harvester)
    {
        // Gas cloud harvesters only allowed to harvest gas.
        if (targetEntity->Item()->groupID() != EVEDB::invGroups::Harvestable_Cloud)
        {
            SysLog::Error("MiningLaser::Activate()", "ERROR: invalid target!");
            throw PyException(MakeCustomError("ERROR!  invalid target!"));
        }
    }
        // Only thing left are astroid miners.
    else if (targetEntity->Item()->categoryID() != EVEDB::invCategories::Asteroid)
    {
        // We are not targeting an asteroid.
        SysLog::Error("MiningLaser::Activate()", "ERROR: invalid target!");
        throw PyException(MakeCustomError("ERROR!  invalid target!"));
    }
    // We have a valid target, are we in range?
    double maxRange = miner->GetAttribute(AttrMaxRange).get_float();
    maxRange = maxRange * maxRange;
    double targetRange = targetEntity->DistanceTo2(m_Ship->GetOperator()->GetSystemEntity());
    if (targetRange > maxRange)
    {
        // We are not targeting a valid target.
        // TO-DO: send proper out or range response.
        SysLog::Error("MiningLaser::Activate()", "ERROR: Cannot activate mining laser target out of range!");
        throw PyException(MakeCustomError("ERROR!  Cannot activate mining laser target out of range!"));
    }
    m_targetEntity = targetEntity;
    m_targetID = targetEntity->Item()->itemID();
    // Activate active processing component timer:
    m_ActiveModuleProc->ActivateCycle();
    m_ModuleState = MOD_ACTIVATED;
    //m_IsInitialCycle = true;
    _ShowCycle();
}

void MiningLaser::Deactivate()
{
	m_ModuleState = MOD_DEACTIVATING;
	m_ActiveModuleProc->DeactivateCycle();
}

void MiningLaser::DoCycle()
{
	if( m_ActiveModuleProc->ShouldProcessActiveCycle() )
	{
		// Check to see if our target is still in this bubble or has left or been destroyed:
		if( !(m_Ship->GetOperator()->GetSystemEntity()->Bubble()->GetEntity(m_targetID)) )
		{
			// Target has left our bubble or been destroyed, deactivate this module:
			Deactivate();
			return;
		}

		_ShowCycle();

		// Actually pull in the ore
		_ProcessCycle();
	}
}

void MiningLaser::StopCycle(bool abort)
{
    if (!abort)
    {
        // On end of last cycle, make sure we pull in one more batch of ore:
        _ProcessCycle();
    }

	Notify_OnGodmaShipEffect shipEff;
	shipEff.itemID = m_Item->itemID();
	shipEff.effectID = effectMiningLaser;
	shipEff.when = Win32TimeNow();
	shipEff.start = 0;
	shipEff.active = 0;

	PyList* env = new PyList;
	env->AddItem(new PyInt(shipEff.itemID));
	env->AddItem(new PyInt(m_Ship->ownerID()));
	env->AddItem(new PyInt(m_Ship->itemID()));
	env->AddItem(new PyInt(m_targetID));
	env->AddItem(new PyNone);
	env->AddItem(new PyNone);
	env->AddItem(new PyInt(shipEff.effectID));

	shipEff.environment = env;
	shipEff.startTime = shipEff.when;
	shipEff.duration = 1.0;		//m_ActiveModuleProc->GetRemainingCycleTimeMS();		// At least, I'm assuming this is the remaining time left in the cycle
	shipEff.repeat = new PyInt(0);
	shipEff.randomSeed = new PyNone;
	shipEff.error = new PyNone;

	PyList* events = new PyList;
	events->AddItem(shipEff.Encode());

	Notify_OnMultiEvent multi;
	multi.events = events;

	PyTuple* tmp = multi.Encode();

	m_Ship->GetOperator()->SendDogmaNotification("OnMultiEvent", "clientID", &tmp);

	// Create Special Effect:
	uint32 chargeID = 0;
	if( m_chargeLoaded )
		chargeID = m_chargeRef->itemID();

	std::string effectsString;
	if (getItem()->groupID() == EVEDB::invGroups::Gas_Cloud_Harvester)
		effectsString = "effects.CloudMining";
	else
		effectsString = "effects.Mining";
	m_Ship->GetOperator()->GetDestiny()->SendSpecialEffect
	(
		m_Ship,
		m_Item->itemID(),
		m_Item->typeID(),
		m_targetID,
		chargeID,
		effectsString,
		0,
		0,
		0,
		1.0,
		0
	);

	m_ActiveModuleProc->DeactivateCycle();
}

void MiningLaser::_ProcessCycle()
{
    InventoryItemRef moduleRef = getItem();
    // Check range
    double maxRange = moduleRef->GetAttribute(AttrMaxRange).get_float();
    maxRange = maxRange * maxRange;
    double targetRange = m_targetEntity->DistanceTo2(m_Ship->GetOperator()->GetSystemEntity());
    if (targetRange > maxRange)
    {
        // We must have drifted out of range.
        m_ModuleState = MOD_DEACTIVATING;
        m_ActiveModuleProc->AbortCycle();
        // TO-DO: send proper out or range response.
        SysLog::Error("MiningLaser::Activate()", "ERROR: mining laser target moved out of range!");
        return;
    }
    // Retrieve ore from target Asteroid and put into flagCargoHold
    InventoryItemRef asteroidRef = m_targetEntity->Item();
	uint32 remainingOreUnits = asteroidRef->GetAttribute(AttrQuantity).get_int();
	double oreUnitVolume = asteroidRef->GetAttribute(AttrVolume).get_float();
	double oreUnitsToPull = 0.0;
	double remainingCargoVolume = 0.0;

    // Calculate how many units of ore to pull from the asteroid on this cycle:
    // Get base mining amount.
    oreUnitsToPull = moduleRef->GetAttribute(AttrMiningAmount).get_float() / oreUnitVolume;
    // Do we have a crystal?
	if( m_chargeRef )
    {
        // Yes, apply yield multiplier.
        if (m_chargeRef->HasAttribute(AttrSpecialisationAsteroidYieldMultiplier))
        {
            oreUnitsToPull *= m_chargeRef->GetAttribute(AttrSpecialisationAsteroidYieldMultiplier).get_float();
        }
    }
    // Get percent cycle complete.
    double cycleTime = 1; //m_ActiveModuleProc->GetTotalCycleTimeMS();
    double usedTime = 1; //m_ActiveModuleProc->GetElapsedCycleTimeMS();
    double percent = usedTime / cycleTime;
    // Limit to range 0.0 - 1.0.
    percent = std::min(1.0, std::max(0.0, percent));
    // Round down to next lowest integer value.
    oreUnitsToPull = floor(oreUnitsToPull * percent);

    // Limit to units remaining in asteroid.
    oreUnitsToPull = std::min(oreUnitsToPull, (double) remainingOreUnits);

    // Find what cargo hold to use.
    EVEItemFlags cargoFlag = flagCargoHold;
    // Check for specialized cargo hold.
    if (m_Ship->HasAttribute(AttrSpecialOreHoldCapacity))
    {
        // We have a specialized ore hold all or goes here.
        cargoFlag = flagSpecializedOreHold;
    }
    // Get cargo hold and remaining capacity.
    remainingCargoVolume = m_Ship->GetRemainingVolumeByFlag(cargoFlag);
    // Do we have enough room for the whole stack?
    if (remainingCargoVolume < (oreUnitsToPull * oreUnitVolume))
    {
        // No, reduce the stack size.
        oreUnitsToPull = floor(remainingCargoVolume / oreUnitVolume);
    }
    // Are we actually pulling anything?
    if (oreUnitsToPull <= 0.0)
    {
        // No, hmmm... thats bad!
        m_ModuleState = MOD_DEACTIVATING;
        m_ActiveModuleProc->AbortCycle();
        // TO-DO: send client miner deactivated because hold full message.
        SysLog::Warning("MiningLaser::DoCycle()", "Somehow MiningLaser could not extract ore from current target asteroid '%s' (id %u)", m_targetEntity->Item()->itemName().c_str(), m_targetEntity->GetID());
        return;
    }

    // Check for an existing ore item in the cargo.
    InventoryItemRef existing = m_Ship->GetByTypeFlag(asteroidRef->typeID(), cargoFlag);
    if (existing.get() != nullptr)
    {
        // We have an existing ore sample, add to it.
        m_Ship->AlterCargoQty(existing, oreUnitsToPull);
    }
    else
    {
        // No existing ore sample, create one.
        ItemData idata(
                       asteroidRef->typeID(),
                       m_Ship->ownerID(),
                       0, //temp location
                       cargoFlag,
                       oreUnitsToPull
                       );

        InventoryItemRef ore = ItemFactory::SpawnItem(idata);
        if (ore)
        {
            m_Ship->AddItem(cargoFlag, ore);
        }
        else
        {
            SysLog::Error("MiningLaser::DoCycle()", "ERROR: Could not create ore stack for '%s' ship (id %u)!", m_Ship->itemName().c_str(), m_Ship->itemID());
            ore->Delete();
        }
    }
    // Finally, reduce the amount of ore in the asteroid by how much we took out:
    remainingOreUnits -= oreUnitsToPull;
    asteroidRef->SetAttribute(AttrQuantity, remainingOreUnits);

    // Check to see is ship is full or asteroid depleted.
    remainingCargoVolume = m_Ship->GetRemainingVolumeByFlag(cargoFlag);
    if ((remainingCargoVolume < oreUnitVolume) || remainingOreUnits == 0)
    {
        // Asteroid is empty OR cargo hold is entirely full, either way, DEACTIVATE module immediately!
        m_ModuleState = MOD_DEACTIVATING;
        m_ActiveModuleProc->AbortCycle();
        if (remainingOreUnits == 0)
        {
            // Asteroid is empty now, so remove it
            m_targetEntity->Bubble()->Remove(m_targetEntity);
            m_targetEntity->Item()->Delete();
            // To-Do: send client asteroid depleted message.
        }
    }

}

void MiningLaser::_ShowCycle()
{
	// Create Destiny Updates:
	Notify_OnGodmaShipEffect shipEff;
	shipEff.itemID = m_Item->itemID();
	shipEff.effectID = effectMiningLaser;		// From EVEEffectID::
	shipEff.when = Win32TimeNow();
	shipEff.start = 1;
	shipEff.active = 1;

	PyList* env = new PyList;
	env->AddItem(new PyInt(shipEff.itemID));
	env->AddItem(new PyInt(m_Ship->ownerID()));
	env->AddItem(new PyInt(m_Ship->itemID()));
	env->AddItem(new PyInt(m_targetID));
	env->AddItem(new PyNone);
	env->AddItem(new PyNone);
	env->AddItem(new PyInt(shipEff.effectID));

	shipEff.environment = env;
	shipEff.startTime = shipEff.when;
	shipEff.duration = m_Item->GetAttribute(AttrDuration).get_float();
	shipEff.repeat = new PyInt(1000);
	shipEff.randomSeed = new PyNone;
	shipEff.error = new PyNone;

	PyTuple* tmp = new PyTuple(3);
	//tmp->SetItem(1, dmgMsg.Encode());
	tmp->SetItem(1, shipEff.Encode());

	std::vector<PyTuple*> events;
	//events.push_back(dmgMsg.Encode());
	events.push_back(shipEff.Encode());

	std::vector<PyTuple*> updates;
	//updates.push_back(dmgChange.Encode());

	m_Ship->GetOperator()->GetDestiny()->SendDestinyUpdate(updates, events, false);

	// Create Special Effect:
	uint32 chargeID = 0;
	if( m_chargeLoaded )
		chargeID = m_chargeRef->itemID();

	std::string effectsString;
	if (getItem()->groupID() == EVEDB::invGroups::Gas_Cloud_Harvester)
		effectsString = "effects.CloudMining";
	else
		effectsString = "effects.Mining";
	m_Ship->GetOperator()->GetDestiny()->SendSpecialEffect
	(
		m_Ship,
		m_Item->itemID(),
		m_Item->typeID(),
		m_targetID,
		chargeID,
		effectsString,
		0,
		1,
		1,
		m_Item->GetAttribute(AttrDuration).get_float(),
		1000
	);
}
