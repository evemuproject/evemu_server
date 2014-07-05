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
:ActiveModule(item, ship)
{
}

void MiningLaser::Activate(SystemEntity * targetEntity)
{
	// Test if module is Ice Harvester I (typeID 16728) or Ice Harvester II (typeID 22229) AND the target is in groupID 465 'Ice',
	// otherwise, just test if target is in the categoryID 25 'Asteroid'
	if( ((getItem()->typeID() == 16278 || getItem()->typeID() == 22229) && (targetEntity->Item()->groupID() == EVEDB::invGroups::Ice))
		|| (targetEntity->Item()->categoryID() == EVEDB::invCategories::Asteroid) )
	{
		// We either have a chargeless mining laser OR our charged mining laser has no charge, check groupID for charged laser types:
		uint32 typeID = getItem()->typeID();
		if( typeID == 24305 || typeID == 17912 )
		{
			// Charged mining laser:
			// + Modulated Strip Miner II
			// + Modulated Deep Core Strip Miner II
			if( m_ChargeRef != NULL )
			{
                ActiveModule::Activate(targetEntity);
			}
			else
			{
				sLog.Error( "MiningLaser::Activate()", "ERROR: Cannot find charge that is supposed to be loaded into this module!" );
				throw PyException( MakeCustomError( "ERROR!  Cannot find charge that is supposed to be loaded into this module!" ) );
			}
		}
		else
		{
            ActiveModule::Activate(targetEntity);
		}
	}
	else
	{
		sLog.Error( "MiningLaser::Activate()", "ERROR: Cannot activate mining laser on non-asteroid target!" );
		throw PyException( MakeCustomError( "ERROR!  Cannot activate mining laser on non-asteroid target!" ) );
	}
}

void MiningLaser::StopCycle(bool abort)
{
    ActiveModule::StopCycle(abort);

	// Retrieve ore from target Asteroid and put into flagCargoHold
	InventoryItemRef asteroidRef = m_targetEntity->Item();
	InventoryItemRef moduleRef = this->getItem();
	uint32 remainingOreUnits = asteroidRef->GetAttribute(AttrQuantity).get_int();
	double oreUnitVolume = asteroidRef->GetAttribute(AttrVolume).get_float();
	double oreUnitsToPull = 0.0;
	double remainingCargoVolume = 0.0;

	// Calculate how many units of ore to pull from the asteroid on this cycle:
	//oreUnitsToPull = asteroidRef->GetAttribute(AttrMiningAmount).get_float() / oreUnitVolume;
	oreUnitsToPull = moduleRef->GetAttribute(AttrMiningAmount).get_float() / oreUnitVolume;
	if( m_ChargeRef != NULL )
	{
		// Use mining crystal charge to multiply ore amount taken:
		if( moduleRef->HasAttribute(AttrSpecialisationAsteroidYieldMultiplier) )
			oreUnitsToPull *= moduleRef->GetAttribute(AttrSpecialisationAsteroidYieldMultiplier).get_float();
		else
		{
			sLog.Error( "MiningLaser::DoCycle()", "" );
			oreUnitsToPull = 0.0;
		}
	}
	oreUnitsToPull = floor(oreUnitsToPull);

	if( oreUnitsToPull > remainingOreUnits )
		oreUnitsToPull = remainingOreUnits;

	if( oreUnitsToPull > 0.0 )
	{
		if( remainingOreUnits > 0 )
		{
			// Verify room left in flagCargoHold
			remainingCargoVolume = m_Ship->GetRemainingVolumeByFlag(flagCargoHold);

			if( remainingCargoVolume >= oreUnitVolume )
			{
				// There's room for at least one unit of ore, let's find out how many we can put into cargo hold,
				// then make a stack for them:
				if( remainingCargoVolume < (oreUnitsToPull * oreUnitVolume) )
				{
					oreUnitsToPull =  floor(remainingCargoVolume / oreUnitVolume);
				}

				ItemData idata(
					asteroidRef->typeID(),
					m_Ship->ownerID(),
					0, //temp location
					flagCargoHold,
					oreUnitsToPull
				);

				InventoryItemRef ore = sItemFactory.SpawnItem( idata );
				if( ore )
				{
					//ore->Move(m_Ship->itemID(), flagCargoHold);
					m_Ship->AddItem(flagCargoHold, ore);
					// Finally, reduce the amount of ore in the asteroid by how much we took out:
					asteroidRef->SetAttribute( AttrQuantity, (remainingOreUnits - oreUnitsToPull) );
					remainingOreUnits -= oreUnitsToPull;
				}
				else
				{
					sLog.Error( "MiningLaser::DoCycle()", "ERROR: Could not create ore stack for '%s' ship (id %u)!", m_Ship->itemName().c_str(), m_Ship->itemID() );
					ore->Delete();
				}
			}
			else
				throw PyException( MakeCustomError( "Not enough cargo space!") );
		}

		remainingCargoVolume = m_Ship->GetRemainingVolumeByFlag(flagCargoHold);
		if( (remainingCargoVolume < oreUnitVolume) || (remainingOreUnits == 0) )
		{
			// Asteroid is empty OR cargo hold is entirely full, either way, DEACTIVATE module immediately!
			m_ModuleState = MOD_DEACTIVATING;
			m_ActiveModuleProc->AbortCycle();
		}

		if( remainingOreUnits == 0 )
		{
			// Asteroid is empty now, so remove it
			m_targetEntity->Bubble()->Remove(m_targetEntity);
			m_targetEntity->Item()->Delete();
		}
	}
	else
		sLog.Warning( "MiningLaser::DoCycle()", "Somehow MiningLaser could not extract ore from current target asteroid '%s' (id %u)", m_targetEntity->Item()->itemName().c_str(), m_targetEntity->GetID() );
}
