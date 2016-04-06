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
    Author:     Bloody.Rabbit
*/

#include "eve-server.h"

#include "character/Character.h"
#include "ship/DestinyManager.h"
#include "ship/Ship.h"
#include "ship/ShipOperatorInterface.h"
#include "system/BubbleManager.h"

/*
 * Ship
 */
Ship::Ship(
   uint32 _shipID,
    // InventoryItem stuff:
           const InvTypeRef _shipType,
    const ItemData &_data)
: InventoryItem(_shipID, _shipType, _data),
  m_processTimerTick(SHIP_PROCESS_TICK_MS),
  m_processTimer(SHIP_PROCESS_TICK_MS)
{
    m_ModuleManager = NULL;
    m_pOperator = new ShipOperatorInterface();

	m_processTimer.Start();

    // Activate Save Info Timer with somewhat randomized timer value:
    //SetSaveTimerExpiry( MakeRandomInt( (10 * 60), (15 * 60) ) );        // Randomize save timer expiry to between 10 and 15 minutes
    //DisableSaveTimer();
}

ShipRef Ship::Load(uint32 shipID)
{
    return InventoryItem::Load<Ship>( shipID );
}

template<class _Ty>
RefPtr<_Ty> Ship::_LoadShip(uint32 shipID,
    // InventoryItem stuff:
                            const InvTypeRef shipType, const ItemData &data)
{
    // we don't need any additional stuff
    return ShipRef( new Ship(shipID, shipType, data ) );
}

ShipRef Ship::Spawn(ItemData &data) {
    uint32 shipID = Ship::_Spawn( data );
    if( shipID == 0 )
        return ShipRef();

    ShipRef sShipRef = Ship::Load( shipID );

    // Create default dynamic attributes in the AttributeMap:
    sShipRef->setAttribute(AttrIsOnline, 1, true); // Is Online
    sShipRef->setAttribute(AttrShieldCharge, sShipRef->getAttribute(AttrShieldCapacity), true); // Shield Charge
    sShipRef->setAttribute(AttrArmorDamage, 0.0, true); // Armor Damage
    sShipRef->setAttribute(AttrMass, sShipRef->type()->getAttr(AttrMass), true); // Mass
    sShipRef->setAttribute(AttrRadius, sShipRef->type()->getAttr(AttrRadius), true); // Radius
    sShipRef->setAttribute(AttrVolume, sShipRef->type()->getAttr(AttrVolume), true); // Volume
    sShipRef->setAttribute(AttrCapacity, sShipRef->type()->getAttr(AttrCapacity), true); // Capacity
    sShipRef->setAttribute(AttrInertia, 1, true); // Inertia
    sShipRef->setAttribute(AttrCharge, sShipRef->getAttribute(AttrCapacitorCapacity), true); // Set Capacitor Charge to the Capacitor Capacity

    // Check for existence of some attributes that may or may not have already been loaded and set them
    // to default values:
	// Hull Damage
    if (!(sShipRef->hasAttribute(AttrDamage)))
        sShipRef->setAttribute(AttrDamage, 0, true);
    // Theoretical Maximum Targeting Range
    if (!(sShipRef->hasAttribute(AttrMaximumRangeCap)))
        sShipRef->setAttribute(AttrMaximumRangeCap, ((double) BUBBLE_RADIUS_METERS), true);
    // Maximum Armor Damage Resonance
    if (!(sShipRef->hasAttribute(AttrArmorMaxDamageResonance)))
        sShipRef->setAttribute(AttrArmorMaxDamageResonance, 1.0f, true);
    // Maximum Shield Damage Resonance
    if (!(sShipRef->hasAttribute(AttrShieldMaxDamageResonance)))
        sShipRef->setAttribute(AttrShieldMaxDamageResonance, 1.0f, true);
    // Warp Speed Multiplier
    if (!(sShipRef.get()->hasAttribute(AttrWarpSpeedMultiplier)))
        sShipRef.get()->setAttribute(AttrWarpSpeedMultiplier, 1.0f, true);
    // CPU Load of the ship (new ships have zero load with no modules fitted, of course):
    if (!(sShipRef.get()->hasAttribute(AttrCpuLoad)))
        sShipRef.get()->setAttribute(AttrCpuLoad, 0, true);
    // Power Load of the ship (new ships have zero load with no modules fitted, of course):
    if (!(sShipRef.get()->hasAttribute(AttrPowerLoad)))
        sShipRef.get()->setAttribute(AttrPowerLoad, 0, true);
	// Warp Scramble Status of the ship (most ships have zero warp scramble status, but some already have it defined):
    if (!(sShipRef.get()->hasAttribute(AttrWarpScrambleStatus)))
        sShipRef.get()->setAttribute(AttrWarpScrambleStatus, 0.0, true);

	// Shield Resonance
	// AttrShieldEmDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrShieldEmDamageResonance)))
        sShipRef.get()->setAttribute(AttrShieldEmDamageResonance, 1.0, true);
	// AttrShieldExplosiveDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrShieldExplosiveDamageResonance)))
        sShipRef.get()->setAttribute(AttrShieldExplosiveDamageResonance, 1.0, true);
	// AttrShieldKineticDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrShieldKineticDamageResonance)))
        sShipRef.get()->setAttribute(AttrShieldKineticDamageResonance, 1.0, true);
	// AttrShieldThermalDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrShieldThermalDamageResonance)))
        sShipRef.get()->setAttribute(AttrShieldThermalDamageResonance, 1.0, true);

	// Armor Resonance
	// AttrArmorEmDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrArmorEmDamageResonance)))
        sShipRef.get()->setAttribute(AttrArmorEmDamageResonance, 1.0, true);
	// AttrArmorExplosiveDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrArmorExplosiveDamageResonance)))
        sShipRef.get()->setAttribute(AttrArmorExplosiveDamageResonance, 1.0, true);
	// AttrArmorKineticDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrArmorKineticDamageResonance)))
        sShipRef.get()->setAttribute(AttrArmorKineticDamageResonance, 1.0, true);
	// AttrArmorThermalDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrArmorThermalDamageResonance)))
        sShipRef.get()->setAttribute(AttrArmorThermalDamageResonance, 1.0, true);

	// Hull Resonance
	// AttrHullEmDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrHullEmDamageResonance)))
        sShipRef.get()->setAttribute(AttrHullEmDamageResonance, 1.0, true);
	// AttrHullExplosiveDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrHullExplosiveDamageResonance)))
        sShipRef.get()->setAttribute(AttrHullExplosiveDamageResonance, 1.0, true);
	// AttrHullKineticDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrHullKineticDamageResonance)))
        sShipRef.get()->setAttribute(AttrHullKineticDamageResonance, 1.0, true);
	// AttrHullThermalDamageResonance
    if (!(sShipRef.get()->hasAttribute(AttrHullThermalDamageResonance)))
        sShipRef.get()->setAttribute(AttrHullThermalDamageResonance, 1.0, true);

	// AttrTurretSlotsLeft
    if (!(sShipRef.get()->hasAttribute(AttrTurretSlotsLeft)))
        sShipRef.get()->setAttribute(AttrTurretSlotsLeft, 0, true);
	// AttrLauncherSlotsLeft
    if (!(sShipRef.get()->hasAttribute(AttrLauncherSlotsLeft)))
        sShipRef.get()->setAttribute(AttrLauncherSlotsLeft, 0, true);

    return sShipRef;
}

uint32 Ship::_Spawn(ItemData &data) {
    // make sure it's a ship
    const InvTypeRef st = InvType::getType(data.typeID);
    if (st.get() == nullptr)
    {
        return 0;
    }

    // store item data
    uint32 shipID = InventoryItem::_Spawn(data);
    if (shipID == 0)
    {
        return 0;
    }

    // nothing additional

    return shipID;
}

bool Ship::_Load()
{
    // load contents
    if( !LoadContents() )
        return false;

    bool loadSuccess = InventoryItem::_Load();      // Attributes are loaded here!

    double capacity;
	// fill cargo holds data here:
	// NOTE: These all still need to have skill and ship bonuses applied when creating the capacities!
    if (fetchAttribute(AttrCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagCargoHold, capacity));
    }
    if (fetchAttribute(AttrDroneCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagDroneBay, capacity));
    }
    if (fetchAttribute(AttrSpecialFuelBayCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagSpecializedFuelBay, capacity));
    }
    if (fetchAttribute(AttrSpecialOreHoldCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagSpecializedOreHold, capacity));
    }
    if (fetchAttribute(AttrSpecialGasHoldCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagSpecializedGasHold, capacity));
    }
    if (fetchAttribute(AttrSpecialMineralHoldCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagSpecializedMineralHold, capacity));
    }
    if (fetchAttribute(AttrSpecialSalvageHoldCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagSpecializedSalvageHold, capacity));
    }
    if (fetchAttribute(AttrSpecialShipHoldCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagSpecializedShipHold, capacity));
    }
    if (fetchAttribute(AttrSpecialSmallShipHoldCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagSpecializedSmallShipHold, capacity));
    }
    if (fetchAttribute(AttrSpecialLargeShipHoldCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagSpecializedLargeShipHold, capacity));
    }
    if (fetchAttribute(AttrSpecialIndustrialShipHoldCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagSpecializedIndustrialShipHold, capacity));
    }
    if (fetchAttribute(AttrSpecialAmmoHoldCapacity, capacity))
    {
        m_cargoHoldsUsedVolumeByFlag.insert(std::pair<EVEItemFlags, double>(flagSpecializedAmmoHold, capacity));
    }

	_UpdateCargoHoldsUsedVolume();

    // allocate the module manager, only the first time:
    if( m_ModuleManager == NULL )
        m_ModuleManager = new ModuleManager(this);

    // check for module manager load success
    if( m_ModuleManager == NULL )
        loadSuccess = false;

    return loadSuccess;
}

void Ship::_UpdateCargoHoldsUsedVolume()
{
    if (hasAttribute(AttrCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagCargoHold)->second = GetStoredVolume(flagCargoHold);
    if (hasAttribute(AttrDroneCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagDroneBay)->second = GetStoredVolume(flagDroneBay);
    if (hasAttribute(AttrSpecialFuelBayCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedFuelBay)->second = GetStoredVolume(flagSpecializedFuelBay);
    if (hasAttribute(AttrSpecialOreHoldCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedOreHold)->second = GetStoredVolume(flagSpecializedOreHold);
    if (hasAttribute(AttrSpecialGasHoldCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedGasHold)->second = GetStoredVolume(flagSpecializedGasHold);
    if (hasAttribute(AttrSpecialMineralHoldCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedMineralHold)->second = GetStoredVolume(flagSpecializedMineralHold);
    if (hasAttribute(AttrSpecialSalvageHoldCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedSalvageHold)->second = GetStoredVolume(flagSpecializedSalvageHold);
    if (hasAttribute(AttrSpecialShipHoldCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedShipHold)->second = GetStoredVolume(flagSpecializedShipHold);
    if (hasAttribute(AttrSpecialSmallShipHoldCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedSmallShipHold)->second = GetStoredVolume(flagSpecializedSmallShipHold);
    if (hasAttribute(AttrSpecialLargeShipHoldCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedLargeShipHold)->second = GetStoredVolume(flagSpecializedLargeShipHold);
    if (hasAttribute(AttrSpecialIndustrialShipHoldCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedIndustrialShipHold)->second = GetStoredVolume(flagSpecializedIndustrialShipHold);
    if (hasAttribute(AttrSpecialAmmoHoldCapacity))
		m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedAmmoHold)->second = GetStoredVolume(flagSpecializedAmmoHold);
}

void Ship::_IncreaseCargoHoldsUsedVolume(EVEItemFlags flag, double volumeToConsume)
{
	if( m_cargoHoldsUsedVolumeByFlag.find(flag) != m_cargoHoldsUsedVolumeByFlag.end() )
		m_cargoHoldsUsedVolumeByFlag.find(flag)->second += volumeToConsume;
	else
		throw PyException( MakeCustomError( "ERROR!  Illegal flag '%u' specified!", flag ) );
}

void Ship::_DecreaseCargoHoldsUsedVolume(EVEItemFlags flag, double volumeToConsume)
{
	if( m_cargoHoldsUsedVolumeByFlag.find(flag) != m_cargoHoldsUsedVolumeByFlag.end() )
		m_cargoHoldsUsedVolumeByFlag.find(flag)->second -= volumeToConsume;
	else
		throw PyException( MakeCustomError( "ERROR!  Illegal flag '%u' specified!", flag ) );
}

void Ship::Delete()
{
    // delete contents first
    DeleteContents();

    InventoryItem::Delete();
}

double Ship::GetCapacity(EVEItemFlags flag) const
{
    switch( flag ) {
		case flagAutoFit:
		case flagCargoHold:
            if (hasAttribute(AttrCapacity))
                return getAttribute(AttrCapacity).get_float();
			break;

		case flagDroneBay:
            if (hasAttribute(AttrDroneCapacity))
                return getAttribute(AttrDroneCapacity).get_float();
			break;

		case flagSpecializedFuelBay:
            if (hasAttribute(AttrSpecialFuelBayCapacity))
                return getAttribute(AttrSpecialFuelBayCapacity).get_float();
			break;

		case flagSpecializedOreHold:
            if (hasAttribute(AttrSpecialOreHoldCapacity))
                return getAttribute(AttrSpecialOreHoldCapacity).get_float();
			break;

		case flagSpecializedGasHold:
            if (hasAttribute(AttrSpecialGasHoldCapacity))
                return getAttribute(AttrSpecialGasHoldCapacity).get_float();
			break;

		case flagSpecializedMineralHold:
            if (hasAttribute(AttrSpecialMineralHoldCapacity))
                return getAttribute(AttrSpecialMineralHoldCapacity).get_float();
			break;

		case flagSpecializedSalvageHold:
            if (hasAttribute(AttrSpecialSalvageHoldCapacity))
                return getAttribute(AttrSpecialSalvageHoldCapacity).get_float();
			break;

		case flagSpecializedShipHold:
            if (hasAttribute(AttrSpecialShipHoldCapacity))
                return getAttribute(AttrSpecialShipHoldCapacity).get_float();
			break;

		case flagSpecializedSmallShipHold:
            if (hasAttribute(AttrSpecialSmallShipHoldCapacity))
                return getAttribute(AttrSpecialSmallShipHoldCapacity).get_float();
			break;

		case flagSpecializedLargeShipHold:
            if (hasAttribute(AttrSpecialLargeShipHoldCapacity))
                return getAttribute(AttrSpecialLargeShipHoldCapacity).get_float();
			break;

		case flagSpecializedIndustrialShipHold:
            if (hasAttribute(AttrSpecialIndustrialShipHoldCapacity))
                return getAttribute(AttrSpecialIndustrialShipHoldCapacity).get_float();
			break;

		case flagSpecializedAmmoHold:
            if (hasAttribute(AttrSpecialAmmoHoldCapacity))
                return getAttribute(AttrSpecialAmmoHoldCapacity).get_float();
			break;

        case flagShipHangar:
            if (hasAttribute(AttrShipMaintenanceBayCapacity))
                return getAttribute(AttrShipMaintenanceBayCapacity).get_float();
			break;

        case flagHangar:
            if (hasAttribute(AttrCorporateHangarCapacity))
                return getAttribute(AttrCorporateHangarCapacity).get_float();
			break;

		default:
			return 0.0;
			break;
	}

	// Handle all missing/unsupported/illegal flag by reporting available capacity of 0.0:
	return 0.0;
}

double Ship::GetRemainingVolumeByFlag(EVEItemFlags flag) const
{
	switch( flag ) {
		case flagAutoFit:
		case flagCargoHold:
            return (getAttribute(AttrCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagCargoHold)->second);
			break;

		case flagDroneBay:
            return (getAttribute(AttrDroneCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagDroneBay)->second);
			break;

		case flagSpecializedFuelBay:
            return (getAttribute(AttrSpecialFuelBayCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedFuelBay)->second);
			break;

		case flagSpecializedOreHold:
            return (getAttribute(AttrSpecialOreHoldCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedOreHold)->second);
			break;

		case flagSpecializedGasHold:
            return (getAttribute(AttrSpecialGasHoldCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedGasHold)->second);
			break;

		case flagSpecializedMineralHold:
            return (getAttribute(AttrSpecialMineralHoldCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedMineralHold)->second);
			break;

		case flagSpecializedSalvageHold:
            return (getAttribute(AttrSpecialSalvageHoldCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedSalvageHold)->second);
			break;

		case flagSpecializedShipHold:
            return (getAttribute(AttrSpecialShipHoldCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedShipHold)->second);
			break;

		case flagSpecializedSmallShipHold:
            return (getAttribute(AttrSpecialSmallShipHoldCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedSmallShipHold)->second);
			break;

		case flagSpecializedLargeShipHold:
            return (getAttribute(AttrSpecialLargeShipHoldCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedLargeShipHold)->second);
			break;

		case flagSpecializedIndustrialShipHold:
            return (getAttribute(AttrSpecialIndustrialShipHoldCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedIndustrialShipHold)->second);
			break;

		case flagSpecializedAmmoHold:
            return (getAttribute(AttrSpecialAmmoHoldCapacity).get_float() - m_cargoHoldsUsedVolumeByFlag.find(flagSpecializedAmmoHold)->second);
			break;

		default:
			return 0.0;
			break;
	}
}

bool Ship::ValidateAddItem(EVEItemFlags flag, InventoryItemRef item) const
{
    CharacterRef character = m_pOperator->GetChar();

    if( flag == flagDroneBay )
    {
        if (item->categoryID() != EVEDB::invCategories::Drone)
        {
            //Can only put drones in drone bay
            throw PyException(MakeUserError("ItemCannotBeInDroneBay"));
        }
    }
    else if( flag == flagShipHangar )
    {
        if (m_pOperator->GetShip()->getAttribute(AttrHasShipMaintenanceBay) != 0)
        {
            // We have no ship maintenance bay
            throw PyException(MakeCustomError("%s has no ship maintenance bay.", item->itemName().c_str()));
        }
        if (item->categoryID() != EVEDB::invCategories::Ship)
        {
            // Only ships may be put here
            throw PyException(MakeCustomError("Only ships may be placed into ship maintenance bay."));
        }
    }
    else if( flag == flagHangar )
    {
        if (m_pOperator->GetShip()->getAttribute(AttrHasCorporateHangars) != 0)
        {
            // We have no corporate hangars
            throw PyException(MakeCustomError("%s has no corporate hangars.", item->itemName().c_str()));
        }
    }
    else if( (flag >= flagLowSlot0)  &&  (flag <= flagHiSlot7) )
    {
        if (m_pOperator->IsClient())
        {
            // SKIP THIS SKILL CHECK if Operator is NOT Client *
            if (!character->canUse(item))
            {
                throw PyException(MakeCustomError("You do not have the required skills to fit this \n%s", item->itemName().c_str()));
            }
        }
        if (!ValidateItemSpecifics(item))
        {
            throw PyException(MakeCustomError("Your ship cannot equip this module"));
        }
        if(item->categoryID() == EVEDB::invCategories::Charge)
		{
			if( m_ModuleManager->GetModule(flag) != NULL )
			{
				InventoryItemRef module;
				module = m_ModuleManager->GetModule(flag)->getItem();
                if (module->getAttribute(AttrChargeSize) != item->getAttribute(AttrChargeSize))
					throw PyException( MakeCustomError( "The charge is not the correct size for this module." ) );
                if (module->getAttribute(AttrChargeGroup1) != item->groupID())
					throw PyException( MakeCustomError( "Incorrect charge type for this module.") );

				// NOTE: Module Manager will check for actual room to load charges and make stack splits, or reject loading altogether
            }
            else
            {
                throw PyException(MakeCustomError("Module at flag '%u' does not exist!", flag));
            }
        }
		else
        {
            if (m_ModuleManager->IsSlotOccupied(flag))
            {
                throw PyException(MakeUserError("SlotAlreadyOccupied"));
            }
        }
        return true;
    }
    else if( (flag >= flagRigSlot0)  &&  (flag <= flagRigSlot7) )
    {
        if (m_pOperator->IsClient())
        {
            // SKIP THIS SKILL CHECK if Operator is NOT Client *
            if (!character->canUse(item))
            {
                throw PyException(MakeCustomError("You do not have the required skills to fit this \n%s", item->itemName().c_str()));
            }
        }
        if (m_pOperator->GetShip()->getAttribute(AttrRigSize) != item->getAttribute(AttrRigSize))
        {
            throw PyException(MakeCustomError("Your ship cannot fit this size module"));
        }
        if (m_pOperator->GetShip()->getAttribute(AttrUpgradeLoad) + item->getAttribute(AttrUpgradeCost) > m_pOperator->GetShip()->getAttribute(AttrUpgradeCapacity))
        {
            throw PyException(MakeCustomError("Your ship cannot handle the extra calibration"));
        }
        return true;
    }
    else if( (flag >= flagSubSystem0)  &&  (flag <= flagSubSystem7) )
    {
        if (m_pOperator->IsClient())
        {
            // SKIP THIS SKILL CHECK if Operator is NOT Client *
            if (!character->canUse(item))
            {
                throw PyException(MakeCustomError("You do not have the required skills to fit this \n%s", item->itemName().c_str()));
            }
        }
        return true;
    }
    // Handle any other flag, legal or not by virtue of GetRemainingVolumeByFlag() and GetCapacity() that handle supported capacity types:
    // (unsupported or illegal flags report capacity of 0.0, so are automatically rejected)
    double capacityRemaining(0.0);
    capacityRemaining = GetRemainingVolumeByFlag(flag);

    // Check for sufficient capacity.
    if ((capacityRemaining < (item->getAttribute(AttrVolume).get_float() * (double) item->quantity())))
    {
        throw PyException(MakeCustomError("Not enough cargo space!<br><br>flag = %u", (uint32) flag));
        return false;
    }

	return true;
}

PyDict *Ship::ShipGetInfo()
{
    if( !LoadContents() )
    {
        codelog( ITEM__ERROR, "%s (%u): Failed to load contents for ShipGetInfo", itemName().c_str(), itemID() );
        return NULL;
    }

    PyDict *result = new PyDict;
    Rsp_CommonGetInfo_Entry entry;

    //first populate the ship.
    if( !Populate( entry ) )
        return NULL;    //print already done.

    result->SetItem(new PyInt( itemID()), new PyObject("util.KeyVal", entry.Encode()));

    //now encode contents...
    std::vector<InventoryItemRef> equipped;
    std::vector<InventoryItemRef> integrated;
    //find all the equipped items and rigs
    FindByFlagRange( flagLowSlot0, flagFixedSlot, equipped );
    FindByFlagRange( flagRigSlot0, flagRigSlot7, integrated );
    //append them into one list
    equipped.insert(equipped.end(), integrated.begin(), integrated.end() );
    //encode an entry for each one.
    std::vector<InventoryItemRef>::iterator cur, end;
    cur = equipped.begin();
    end = equipped.end();
    for(; cur != end; cur++)
    {
        if( !(*cur)->Populate( entry ) )
        {
            codelog( ITEM__ERROR, "%s (%u): Failed to load item %u for ShipGetInfo", itemName().c_str(), itemID(), (*cur)->itemID() );
        }
        else
            result->SetItem(new PyInt((*cur)->itemID()), new PyObject("util.KeyVal", entry.Encode()));
    }

    return result;
}

PyDict *Ship::ShipGetState()
{
    if( !LoadContents() )
    {
        codelog( ITEM__ERROR, "%s (%u): Failed to load contents for ShipGetInfo", itemName().c_str(), itemID() );
        return NULL;
    }

	// Create new dictionary for "shipState":
    PyDict *result = new PyDict;

	// Create entry in "shipState" dictionary for Ship itself:
    result->SetItem(new PyInt(itemID()), GetItemStatusRow());

	// Create entries in "shipState" dictionary for ALL modules, rigs, and subsystems present on ship:
	std::vector<InventoryItemRef> moduleList;
	m_ModuleManager->GetModuleListOfRefs( &moduleList );

	for(int i=0; i<moduleList.size(); i++)
		result->SetItem(new PyInt(moduleList.at(i)->itemID()), moduleList.at(i)->GetItemStatusRow());

	return result;
}

void Ship::AddItem(InventoryItemRef item)
{
    InventoryEx::AddItem( item );

    if( item->flag() >= flagSlotFirst &&
        item->flag() <= flagSlotLast &&
        item->categoryID() != EVEDB::invCategories::Charge)
    {
        // make singleton
        item->ChangeSingleton( true );
    }
}

void Ship::SaveShip()
{
    SysLog::Debug( "Ship::SaveShip()", "Saving all 'entity' info and attribute info to DB for ship %s (%u)...", itemName().c_str(), itemID() );

    SaveItem();                         // Save all attributes and item info
    m_ModuleManager->SaveModules();     // Save all attributes and item info for all modules fitted to this ship
}

bool Ship::ValidateItemSpecifics(InventoryItemRef equip) const
{
    //declaring explicitly as int...not sure if this is needed or not
    int groupID = m_pOperator->GetShip()->groupID();
    int typeID = m_pOperator->GetShip()->typeID();
    EvilNumber canFitShipGroup1 = equip->getAttribute(AttrCanFitShipGroup1);
    EvilNumber canFitShipGroup2 = equip->getAttribute(AttrCanFitShipGroup2);
    EvilNumber canFitShipGroup3 = equip->getAttribute(AttrCanFitShipGroup3);
    EvilNumber canFitShipGroup4 = equip->getAttribute(AttrCanFitShipGroup4);
    EvilNumber canFitShipType1 = equip->getAttribute(AttrCanFitShipType1);
    EvilNumber canFitShipType2 = equip->getAttribute(AttrCanFitShipType2);
    EvilNumber canFitShipType3 = equip->getAttribute(AttrCanFitShipType3);
    EvilNumber canFitShipType4 = equip->getAttribute(AttrCanFitShipType4);

	if( canFitShipGroup1 != 0 || canFitShipGroup2 != 0 || canFitShipGroup3 != 0 || canFitShipGroup4 != 0 )
		if( canFitShipGroup1 != groupID && canFitShipGroup2 != groupID && canFitShipGroup3 != groupID && canFitShipGroup4 != groupID )
			return false;
	/*
    if( canFitShipGroup1 != 0 )
        if( canFitShipGroup1 != groupID )
            return false;

    if( canFitShipGroup2 != 0 )
        if( canFitShipGroup2 != groupID )
            return false;

    if( canFitShipGroup3 != 0 )
        if( canFitShipGroup3 != groupID )
            return false;

    if( canFitShipGroup4 != 0 )
        if( canFitShipGroup4 != groupID )
            return false;
	*/

    if( canFitShipType1 != 0 || canFitShipType2 != 0 || canFitShipType3 != 0 || canFitShipType4 != 0 )
        if( canFitShipType1 != typeID && canFitShipType2 != typeID && canFitShipType3 != typeID && canFitShipType4 != typeID )
            return false;
	/*
    if( canFitShipType1 != 0 )
        if( canFitShipType1 != typeID )
            return false;

    if( canFitShipType2 != 0 )
        if( canFitShipType2 != typeID )
            return false;

    if( canFitShipType3 != 0 )
        if( canFitShipType3 != typeID )
            return false;

    if( canFitShipType4 != 0 )
        if( canFitShipType4 != typeID )
            return false;
	*/
    return true;

}

void Ship::Dock()
{
	// Heal Shields and Fully Recharge Capacitor:
	SetShipShields(1.0);
	SetShipCapacitorLevel(1.0);

	DeactivateAllModules();
}

void Ship::Undock()
{
}

/* Begin new Module Manager Interface */
InventoryItemRef Ship::GetModule(EVEItemFlags flag)
{
	if( m_ModuleManager->GetModule(flag) != NULL )
		return (m_ModuleManager->GetModule(flag))->getItem();
	else
		return InventoryItemRef();
}

InventoryItemRef Ship::GetModule(uint32 itemID)
{
	if( m_ModuleManager->GetModule(itemID) != NULL )
		return (m_ModuleManager->GetModule(itemID))->getItem();
	else
		return InventoryItemRef();
}

uint32 Ship::FindAvailableModuleSlot( InventoryItemRef item )
{
	uint32 slotFound = flagIllegal;

    // 1) get slot bank (low, med, high, rig, subsystem) from dgmTypeEffects using item->itemID()
    // 2) query this ship's ModuleManager to determine if there are any free slots in that bank,
    //    it should return a slot flag number for the next available slot starting at the lowest number
    //    for that bank
    // 3) return that slot flag number

    if (item->type()->hasEffect(Effect_loPower))
	{
		slotFound = m_ModuleManager->GetAvailableSlotInBank(Effect_loPower);
    }
    else if (item->type()->hasEffect(Effect_medPower))
	{
		slotFound = m_ModuleManager->GetAvailableSlotInBank(Effect_medPower);
    }
    else if (item->type()->hasEffect(Effect_hiPower))
	{
		slotFound = m_ModuleManager->GetAvailableSlotInBank(Effect_hiPower);
    }
    else if (item->type()->hasEffect(Effect_subSystem))
	{
		slotFound = m_ModuleManager->GetAvailableSlotInBank(Effect_subSystem);
    }
    else if (item->type()->hasEffect(Effect_rigSlot))
	{
		slotFound = m_ModuleManager->GetAvailableSlotInBank(Effect_rigSlot);
	}
	else
	{
		// ERROR: This is not a module that fits in any of the slot banks
	}

    return slotFound;
}

uint32 Ship::AddItem(EVEItemFlags flag, InventoryItemRef item)
{
    ValidateAddItem( flag, item );

    //it's a new module, make sure it's state starts at offline so that it is added correctly
    if( item->categoryID() == EVEDB::invCategories::Module )
        item->PutOffline();

	switch( item->categoryID() )
	{
		case EVEDB::invCategories::Charge:
			{
				m_ModuleManager->LoadCharge(item, flag);
				InventoryItemRef loadedChargeOnModule = m_ModuleManager->GetLoadedChargeOnModule(flag);
				if( loadedChargeOnModule )
				{
					return loadedChargeOnModule->itemID();
				}
				else
					return 0;
			}
			break;

		case EVEDB::invCategories::Module:
			if( m_ModuleManager->FitModule(item, flag) )
				item->Move(itemID(), flag);
			break;

		// The default case handles ANY other items added to ship and assumes they go into one of the valid cargo holds on this ship:
		default:
			//Log::Error( "Ship::AddItem(flag,item)", "ERROR! Function called with item '%s' (id: %u) of category neither Charge nor Module!", item->itemName().c_str(), item->itemID() );
            _IncreaseCargoHoldsUsedVolume(item->flag(), (item->getAttribute(AttrVolume).get_float() * item->quantity()));
			item->Move(itemID(), flag);
			break;
	}

	return 0;
}

void Ship::RemoveItem(InventoryItemRef item, uint32 inventoryID, EVEItemFlags flag)
{
    // If item IS a module and it's being removed from a slot:
	if( (item->categoryID() == EVEDB::invCategories::Module) && ((item->flag() >= flagLowSlot0)  &&  (item->flag() <= flagHiSlot7)) )
	{
        m_pOperator->GetShip()->Deactivate( item->itemID(), "online" );
        // m_pOperator->GetShip()->Set_mass( m_pOperator->GetShip()->mass() - item->massAddition() );
        //m_pOperator->GetShip()->SetAttribute(AttrMass,  m_pOperator->GetShip()->GetAttribute(AttrMass) - item->GetAttribute(AttrMassAddition) );
        m_pOperator->GetShip()->UnloadModule( item->itemID() );
    }

	// If item IS a rig and it's being removed from a slot:
	if( (item->categoryID() == EVEDB::invCategories::Module) && ((item->flag() >= flagRigSlot0)  &&  (item->flag() <= flagRigSlot7)) )
	{
		// Don't know what to do when removing a Rig... yet ;)
	}

	// If item IS a rig and it's being removed from a slot:
	if( (item->categoryID() == EVEDB::invCategories::Subsystem) && ((item->flag() >= flagSubSystem0)  &&  (item->flag() <= flagSubSystem7)) )
	{
		// Don't know what to do when removing a Subsystem... yet ;)
	}

	// if item being removed IS a charge, it needs to be removed via Module Manager so modules know charge is removed,
	// BUT, only if it is loaded into a module in one of the 3 slot banks, so we also check its flag value:
	if( (item->categoryID() == EVEDB::invCategories::Charge) && ((item->flag() >= flagLowSlot0)  &&  (item->flag() <= flagHiSlot7)) )
	{
		m_ModuleManager->UnloadCharge(item->flag());
	}

	if( item->flag() == flag )
		// Item's already been moved, let's return
		return;

    // Move New item to its new location:
	if( !( ((item->flag() >= flagLowSlot0)  &&  (item->flag() <= flagHiSlot7)) || ((item->flag() >= flagRigSlot0)  &&  (item->flag() <= flagRigSlot7))
		|| ((item->flag() >= flagSubSystem0)  &&  (item->flag() <= flagSubSystem7)) ) )
    {
        _DecreaseCargoHoldsUsedVolume(item->flag(), (item->getAttribute(AttrVolume).get_float() * item->quantity()));
		m_pOperator->MoveItem(item->itemID(), inventoryID, flag);
	}
	else
	{
		m_pOperator->MoveItem(item->itemID(), inventoryID, flag);
	}
}

bool Ship::AlterCargoQty(InventoryItemRef item, int qtyChange)
{
    // Make sure we actually contain this item!
    if (!Contains(item->itemID()))
    {
        // We don't contain it, sorry!
        return false;
    }
    // Calculate total volume needed.
    double volumeNeed = item->getAttribute(AttrVolume).get_float() * qtyChange;
    // Get remaining volume.
    double remain = GetRemainingCapacity(item->flag());
    if (remain >= volumeNeed)
    {
        // We have enough space remaining, add the items.
        item->AlterQuantity(qtyChange);
        // Adjust the remaining volume.
        _IncreaseCargoHoldsUsedVolume(item->flag(), volumeNeed);
        return true;
    }
    return false;
}

void Ship::UpdateModules()
{
	// List of callees to put this function into context as to what it should be doing:
	// Client::BoardShip()				- put modules online that are recorded with attributeID 2 as being online / skill check all modules and if any fail, keep those OFFLINE
	// InventoryBound::_ExecAdd()		- things have been added or removed, recheck all modules for... some reason
	// Client::MoveItem()				- something has been moved into or out of the ship, recheck all modules for... some reason

	SysLog::Error( "Ship::UpdateModules()", "We are currently not checking for modules that need to go online, or skill checking character for any modules of a newly boarded ship, or updating module states based on things being moved into or off the ship!" );
	SysLog::Error( "Ship::UpdateModules()", "This should really be a simple call to a function ModuleManager::UpdateModules() and the code put inside there." );
}

void Ship::UnloadModule(uint32 itemID)
{
    m_ModuleManager->UnfitModule(itemID);
}

void Ship::UnloadAllModules()
{

}

void Ship::RepairModules()
{

}

void Ship::Online (uint32 moduleID)
{
	m_ModuleManager->Online(moduleID);
}

void Ship::Offline (uint32 moduleID)
{
	m_ModuleManager->Offline(moduleID);
}

int32 Ship::Activate(int32 itemID, std::string effectName, int32 targetID, int32 repeat)
{
    return m_ModuleManager->Activate( itemID, effectName, targetID, repeat );
}

void Ship::Deactivate(int32 itemID, std::string effectName)
{
    m_ModuleManager->Deactivate(itemID, effectName);
}

void Ship::Overload()
{

}

void Ship::CancelOverloading()
{

}

void Ship::RemoveRig( InventoryItemRef item, uint32 inventoryID )
{
    m_ModuleManager->UnfitModule(item->itemID());

    //delete the item
    item->Delete();
}

void Ship::Process()
{
    m_ModuleManager->Process();

	// Do Automatic Shield and Capacitor Recharge:
	if( !IsStation(locationID()) )
	{
		if( m_processTimer.Check() )
		{
			// shield
            if (getAttribute(AttrShieldCharge) < getAttribute(AttrShieldCapacity))
                {
                EvilNumber newCharge = getAttribute(AttrShieldCharge) + ((EvilNumber(m_processTimerTick / 1000.0)) * getAttribute(AttrShieldCapacity) / (getAttribute(AttrShieldRechargeRate) / 1000.0));
                if (newCharge > getAttribute(AttrShieldCapacity))
                    newCharge = getAttribute(AttrShieldCapacity);
                setAttribute(AttrShieldCharge, newCharge);
			}

			// capacitor
            if (getAttribute(AttrCharge) < getAttribute(AttrCapacitorCapacity))
                {
                EvilNumber newCharge = getAttribute(AttrCharge) + ((EvilNumber(m_processTimerTick / 1000.0)) * getAttribute(AttrCapacitorCapacity) / (getAttribute(AttrRechargeRate) / 1000.0));
                if (newCharge > getAttribute(AttrCapacitorCapacity))
                    newCharge = getAttribute(AttrCapacitorCapacity);
                setAttribute(AttrCharge, newCharge);
			}
		}
	}
}

void Ship::OnlineAll()
{
    m_ModuleManager->OnlineAll();
}

void Ship::ReplaceCharges(EVEItemFlags flag, InventoryItemRef newCharge)
{

}

void Ship::DeactivateAllModules()
{
    m_ModuleManager->DeactivateAllModules();
}

std::vector<GenericModule *> Ship::GetStackedItems(uint32 typeID, ModulePowerLevel level)
{
    return m_ModuleManager->GetStackedItems(typeID, level);
}

/* End new Module Manager Interface */

void Ship::SetShipShields(double shieldChargeFraction)
{
	EvilNumber newShieldCharge = 0.0;

	if( shieldChargeFraction > 1.0 )
		shieldChargeFraction = 1.0;
	if( shieldChargeFraction < 0.0 )
		shieldChargeFraction = 0.0;

    newShieldCharge = getAttribute(AttrShieldCapacity) * shieldChargeFraction;
    if ((newShieldCharge + 0.5) > getAttribute(AttrShieldCapacity))
        newShieldCharge = getAttribute(AttrShieldCapacity);

    setAttribute(AttrShieldCharge, newShieldCharge);
}

void Ship::SetShipArmor(double armorHealthFraction)
{
	EvilNumber newArmorDamage = 0.0;

	if( armorHealthFraction > 1.0 )
		armorHealthFraction = 1.0;
	if( armorHealthFraction < 0.0 )
		armorHealthFraction = 0.0;

    newArmorDamage = getAttribute(AttrArmorHP) * (1.0 - armorHealthFraction);
	if( (newArmorDamage - 0.5) < 0.0 )
		newArmorDamage = 0.0;

    setAttribute(AttrArmorDamage, newArmorDamage);
}

void Ship::SetShipHull(double hullHealthFraction)
{
	EvilNumber newHullDamage = 0.0;

	if( hullHealthFraction > 1.0 )
		hullHealthFraction = 1.0;
	if( hullHealthFraction < 0.0 )
		hullHealthFraction = 0.0;

    newHullDamage = getAttribute(AttrHp) * (1.0 - hullHealthFraction);
	if( (newHullDamage - 0.5) > 0.0 )
		newHullDamage = 0.0;

    setAttribute(AttrDamage, newHullDamage);
}

void Ship::SetShipCapacitorLevel(double capacitorChargeFraction)
{
	EvilNumber newCapacitorCharge = 0.0;

	if( capacitorChargeFraction > 1.0 )
		capacitorChargeFraction = 1.0;
	if( capacitorChargeFraction < 0.0 )
		capacitorChargeFraction = 0.0;

    newCapacitorCharge = getAttribute(AttrCapacitorCapacity) * capacitorChargeFraction;
    if ((newCapacitorCharge + 0.5) > getAttribute(AttrCapacitorCapacity))
        newCapacitorCharge = getAttribute(AttrCapacitorCapacity);

    setAttribute(AttrCharge, newCapacitorCharge);
}


using namespace Destiny;

ShipEntity::ShipEntity(
    ShipRef ship,
    SystemManager *system,
    const Vector3D &position)
: DynamicSystemEntity(new DestinyManager(this, system), ship),
  m_system(system)
{
    _shipRef = ship;
    m_destiny->SetPosition(position, false);
}

ShipEntity::~ShipEntity()
{

}

void ShipEntity::Process()
{
    SystemEntity::Process();
}

void ShipEntity::ForcedSetPosition( const Vector3D &pt ) {
    m_destiny->SetPosition(pt, false);
}

void ShipEntity::EncodeDestiny( Buffer& into ) const
{
    const Vector3D& position = GetPosition();
    const std::string itemName( GetName() );

    /*if(m_orbitingID != 0) {
        #pragma pack(1)
        struct AddBall_Orbit {
            BallHeader head;
            MassSector mass;
            ShipSector ship;
            DSTBALL_ORBIT_Struct main;
            NameStruct name;
        };
        #pragma pack()

        into.resize(start
            + sizeof(AddBall_Orbit)
            + slen*sizeof(uint16) );
        uint8 *ptr = &into[start];
        AddBall_Orbit *item = (AddBall_Orbit *) ptr;
        ptr += sizeof(AddBall_Orbit);

        item->head.entityID = GetID();
        item->head.mode = Destiny::DSTBALL_ORBIT;
        item->head.radius = m_self->radius();
        item->head.x = x();
        item->head.y = y();
        item->head.z = z();
        item->head.sub_type = IsMassive | IsFree;

        item->mass.mass = m_self->mass();
        item->mass.unknown51 = 0;
        item->mass.unknown52 = 0xFFFFFFFFFFFFFFFFLL;
        item->mass.corpID = GetCorporationID();
        item->mass.unknown64 = 0xFFFFFFFF;

        item->ship.max_speed = m_self->maxVelocity();
        item->ship.velocity_x = m_self->maxVelocity();    //hacky hacky
        item->ship.velocity_y = 0.0;
        item->ship.velocity_z = 0.0;
        item->ship.agility = 1.0;    //hacky
        item->ship.speed_fraction = 0.133f;    //just strolling around. TODO: put in speed fraction!

        item->main.unknown116 = 0xFF;
        item->main.followID = m_orbitingID;
        item->main.followRange = 6000.0f;

        item->name.name_len = slen;    // in number of unicode chars
        //strcpy_fake_unicode(item->name.name, GetName());
    } else */{
        BallHeader head;
        head.entityID = GetID();
        head.mode = Destiny::DSTBALL_STOP;
        head.radius = GetRadius();
        head.x = position.x;
        head.y = position.y;
        head.z = position.z;
        head.sub_type = IsMassive | IsFree;
        into.Append( head );

        MassSector mass;
        mass.mass = GetMass();
        mass.cloak = 0;
        mass.Harmonic = -1.0f;
        mass.corpID = GetCorporationID();
        mass.allianceID = GetAllianceID();
        into.Append( mass );

        ShipSector ship;
        ship.max_speed = static_cast<float>(GetMaxVelocity());
        ship.velocity_x = 0.0;
        ship.velocity_y = 0.0;
        ship.velocity_z = 0.0;
        ship.agility = static_cast<float>(GetAgility());
        ship.speed_fraction = 0.0;
        into.Append( ship );

        DSTBALL_STOP_Struct main;
        main.formationID = 0xFF;
        into.Append( main );
    }
}

void ShipEntity::MakeDamageState(DoDestinyDamageState &into) const
{
    into.shield = (m_self->getAttribute(AttrShieldCharge).get_float() / m_self->getAttribute(AttrShieldCapacity).get_float());
    into.tau = 100000;    //no freaking clue.
    into.timestamp = Win32TimeNow();
//    armor damage isn't working...
    into.armor = 1.0 - (m_self->getAttribute(AttrArmorDamage).get_float() / m_self->getAttribute(AttrArmorHP).get_float());
    into.structure = 1.0 - (m_self->getAttribute(AttrDamage).get_float() / m_self->getAttribute(AttrHp).get_float());
}

