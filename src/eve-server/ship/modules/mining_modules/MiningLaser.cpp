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

MiningLaser::MiningLaser( InventoryItemRef item, ShipRef ship)
: ActiveModule(item, ship)
{
    if (item->groupID() == EVEDB::invGroups::Gas_Cloud_Harvester)
    {
        m_effectString = "effects.CloudMining";
    }
    else
    {
        m_effectString = "effects.Mining";
    }
}

bool MiningLaser::canActivate(SystemEntity *targetEntity)
{
    if(targetEntity == nullptr)
    {
        return false;
    }
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
    double maxRange = miner->getAttribute(AttrMaxRange).get_float();
    double targetRange = targetEntity->DistanceTo2(m_ship->GetOperator()->GetSystemEntity());
    targetRange = std::sqrt(targetRange);
    targetRange -= targetEntity->GetRadius();
    if (targetRange > maxRange)
    {
        // We are not targeting a valid target.
        // TO-DO: send proper out or range response.
        SysLog::Error("MiningLaser::Activate()", "ERROR: Cannot activate mining laser target out of range! (%f/%f)", targetRange, maxRange);
        throw PyException(MakeCustomError("ERROR!  Cannot activate mining laser target out of range! (%f/%f)", targetRange, maxRange));
    }
    return true;
}

bool MiningLaser::endCycle(bool continuing)
{
    // Check to see if our target is still in this bubble or has left or been destroyed:
    if( m_ship->GetOperator()->GetSystemEntity()->Bubble()->GetEntity(m_targetID) == nullptr )
    {
        // Target has left our bubble or been destroyed, deactivate this module:
        return false;
    }
    if (m_ship->GetOperator()->GetSystemEntity()->targets.getTarget(m_targetID, true) == nullptr)
    {
        // Target no longer targeted.
        return false;
    }
    // Check range
    double maxRange = m_item->getAttribute(AttrMaxRange).get_float();
    double targetRange = m_targetEntity->DistanceTo2(m_ship->GetOperator()->GetSystemEntity());
    targetRange = std::sqrt(targetRange);
    targetRange -= m_targetEntity->GetRadius();
    if (targetRange > maxRange)
    {
        // We must have drifted out of range.
        // TO-DO: send proper out or range response.
        SysLog::Error("MiningLaser::Activate()", "ERROR: mining laser target moved out of range!");
        return false;
    }
    // Retrieve ore from target Asteroid and put into flagCargoHold
    InventoryItemRef asteroidRef = m_targetEntity->Item();
	uint32 remainingOreUnits = asteroidRef->getAttribute(AttrQuantity).get_int();
	double oreUnitVolume = asteroidRef->getAttribute(AttrVolume).get_float();

    // Calculate how many units of ore to pull from the asteroid on this cycle:
    // Get base mining amount.
    double oreUnitsToPull = m_item->getAttribute(AttrMiningAmount).get_float() / oreUnitVolume;
    // Do we have a crystal?
	if( m_chargeRef)
    {
        double mult;
        // Yes, apply yield multiplier.
        if (m_chargeRef->fetchAttribute(AttrSpecialisationAsteroidYieldMultiplier, mult))
        {
            // TO-DO: check for correct type of crystal.
            oreUnitsToPull *= mult;
        }
        // TO-DO: do crystal damage.
    }
    // Get percent cycle complete.
    double cycleTime = getTotalCycleTimeMS();
    double percent = 1.0; // Assume full cycle if timer disabled.
    if(cycleTime != -1)
    {
        double usedTime = getElapsedCycleTimeMS();
        percent = usedTime / cycleTime;
        // Limit to range 0.0 - 1.0.
        percent = std::min(1.0, std::max(0.0, percent));
        if(percent == 0.0)
        {
            percent = 1.0;
        }
    }
    // Round down to next lowest integer value.
    oreUnitsToPull = floor(oreUnitsToPull * percent);

    // Limit to units remaining in asteroid.
    oreUnitsToPull = std::min(oreUnitsToPull, (double) remainingOreUnits);

    // Find what cargo hold to use.
    EVEItemFlags cargoFlag = flagCargoHold;
    // Check for specialized cargo hold.
    if (m_ship->hasAttribute(AttrSpecialOreHoldCapacity))
    {
        // We have a specialized ore hold all or goes here.
        cargoFlag = flagSpecializedOreHold;
    }
    // Get cargo hold and remaining capacity.
    double remainingCargoVolume = m_ship->GetRemainingVolumeByFlag(cargoFlag);
    // Do we have enough room for the whole stack?
    if (remainingCargoVolume < (floor((oreUnitsToPull * oreUnitVolume) * 100.0)/100.0))
    {
        // No, Do we have room for at least one unit?
        if (remainingCargoVolume < oreUnitVolume)
        {
            // No, Send cargo full message.
            PyDict *dict = new PyDict();
            PyTuple *tuple = new PyTuple(2);
            tuple->SetItem(0, new PyInt(MOD_ACTIVATED)); //???? what is this really?
            tuple->SetItem(1, new PyInt(m_item->typeID()));
            dict->SetItem(new PyString("modulename"), tuple);
            PyTuple *error = new PyTuple(2);
            error->SetItem(0, new PyString("MiningDronesDeactivatedCargoHoldNowFull"));
            error->SetItem(1, dict);
            m_error = error;
            return false;
        }
        // Yes, reduce the stack size.
        oreUnitsToPull = floor(remainingCargoVolume / oreUnitVolume);
    }
    // Are we actually pulling anything?
    if (oreUnitsToPull <= 0.0)
    {
        // No, hmmm... thats bad!
        // TO-DO: send client miner deactivated because hold full message.
        SysLog::Warning("MiningLaser::DoCycle()", "Somehow MiningLaser could not extract ore from current target asteroid '%s' (id %u)", m_targetEntity->Item()->itemName().c_str(), m_targetEntity->GetID());
        checkAsteroidDepleted(remainingOreUnits);
        return false;
    }

    // Check for an existing ore item in the cargo.
    InventoryItemRef existing = m_ship->GetByTypeFlag(asteroidRef->typeID(), cargoFlag);
    if (existing.get() != nullptr)
    {
        // We have an existing ore sample, add to it.
        m_ship->AlterCargoQty(existing, oreUnitsToPull);
    }
    else
    {
        // No existing ore sample, create one.
        ItemData idata(
                       asteroidRef->typeID(),
                       m_ship->ownerID(),
                       0, //temp location
                       cargoFlag,
                       oreUnitsToPull
                       );

        InventoryItemRef ore = ItemFactory::SpawnItem(idata);
        if (ore)
        {
            m_ship->AddItem(cargoFlag, ore);
        }
        else
        {
            SysLog::Error("MiningLaser::DoCycle()", "ERROR: Could not create ore stack for '%s' ship (id %u)!", m_ship->itemName().c_str(), m_ship->itemID());
            return false;
        }
    }
    // Finally, reduce the amount of ore in the asteroid by how much we took out:
    remainingOreUnits -= oreUnitsToPull;
    asteroidRef->setAttribute(AttrQuantity, remainingOreUnits);

    // Check to see is ship is full or asteroid depleted.
    remainingCargoVolume = m_ship->GetRemainingVolumeByFlag(cargoFlag);
    if ((remainingCargoVolume < oreUnitVolume) || remainingOreUnits == 0)
    {
        // Asteroid is empty OR cargo hold is entirely full, either way, DEACTIVATE module immediately!
        checkAsteroidDepleted(remainingOreUnits);
        return false;
    }
    return true;
}

void MiningLaser::checkAsteroidDepleted(uint32 remainingOreUnits)
{
    if (remainingOreUnits == 0)
    {
        // Asteroid is empty now, so remove it
        m_targetEntity->Bubble()->Remove(m_targetEntity);
        m_targetEntity->Item()->Delete();
        // Send client asteroid depleted message.
        PyDict *dict = new PyDict();
        dict->SetItem(new PyString("asteroidname"), new PyString(""));
        PyTuple *tuple = new PyTuple(2);
        tuple->SetItem(0, new PyInt(MOD_ACTIVATED)); //???? what is this really?
        tuple->SetItem(1, new PyInt(m_item->typeID()));
        dict->SetItem(new PyString("modulename"), tuple);
        PyTuple *error = new PyTuple(2);
        error->SetItem(0, new PyString("MiningDronesDeactivatedAsteroidEmpty"));
        error->SetItem(1, dict);
        m_error = error;
    }
}
