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
    Author:        AknorJaden
*/

#include "eve-server.h"

#include "system/Damage.h"
#include "ship/modules/weapon_modules/SuperWeapon.h"

SuperWeapon::SuperWeapon( InventoryItemRef item, ShipRef ship)
: ActiveModule(item, ship),
	m_buildUpTimer(0), m_effectDurationTimer(0)
{
	m_effectID = 0;
	switch (m_item->typeID())
	{
		case 24550:
			m_effectString = "effects.SuperWeaponAmarr";
			m_effectID = effectSuperWeaponAmarr;
			break;

		case 24552:
			m_effectString = "effects.SuperWeaponCaldari";
			m_effectID = effectSuperWeaponCaldari;
			break;

		case 24554:
			m_effectString = "effects.SuperWeaponGallente";
			m_effectID = effectSuperWeaponGallente;
			break;

		case 23674:
			m_effectString = "effects.SuperWeaponMinmatar";
			m_effectID = effectSuperWeaponMinmatar;
			break;

		default:
			m_effectString = "";
			m_effectID = 0;
			break;
    }
}

bool SuperWeapon::canActivate(SystemEntity * targetEntity)
{
	// TODO:
	// 1. Prevent activation on certain targets: asteroids, NPC stations, ice, clouds...  Perhaps restrict to ships and structures.
	// 2. Check for minimum qty of consumable materials needed according to the 'consumptionType' attribute value in appropriate cargo bay on board the ship

    return true;
}

void SuperWeapon::startCycle(bool continuing)
{
		// Do massive, crazy damage to targets within a sphere of damage, screw CCP and their 'this can only target capital ships' junk ;)
		// NOTE: due to the small bit of time to "build up" the weapon firing action, we need a timer to delay application of damage to the target(s)
		// Avatar:  5 seconds to build after activation,  5 seconds duration, instant reach to target
		// Erebus:  6 seconds to build after activation,  6 seconds duration, instant reach to target
		// Leviathan:  range to target 124km,  6 seconds to launch after activation, 9 seconds flight time
		// Ragnarok:  range to target 125km,  6 seconds to build after activation, 4 seconds duration, instant reach to target
		//
		// TODO:
		// 0. Somehow disable warping and jump drive until deactivated
		// 1. Set 'm_buildUpTimer' to the "build up time"
		// 2. Set 'm_effectDurationTimer' to the "duration/flight time" of the super weapon effect
		// 3. Move Damage action to SuperWeapon::Process() function and check for timer expirations before applying damage
		// 4. Consider applying damage in increments, such as 5 stages of the 2 million hp (400,000 hp per stage, once per second)
		// 5. Loop through all entities in the bubble, filtering on dynamic entities that are ships, drones, structures, cans
		//    and calculate distance from target to calculate area-of-effect damage using some 1/x formula, where damage sustained
		//    drops off the further away from the primary target.

		// Create Damage action:
		//Damage( SystemEntity *_source,
		//    InventoryItemRef _weapon,
		//    double _kinetic,
		//    double _thermal,
		//    double _em,
		//    double _explosive,
		//    EVEEffectID _effect );
		double kinetic_damage = 0.0;
		double thermal_damage = 0.0;
		double em_damage = 0.0;
		double explosive_damage = 0.0;

    // This still somehow needs skill, ship, module, and implant bonuses to be applied:
    // This still somehow needs to have optimal range and falloff attributes applied as a damage modification factor:
    double multiplyer = m_item->getAttribute(AttrDamageMultiplier).get_float();
    m_chargeRef->fetchAttribute(AttrKineticDamage, kinetic_damage);
    m_chargeRef->fetchAttribute(AttrThermalDamage, thermal_damage);
    m_chargeRef->fetchAttribute(AttrEmDamage, em_damage);
    m_chargeRef->fetchAttribute(AttrExplosiveDamage, explosive_damage);
    kinetic_damage *= multiplyer;
    thermal_damage *= multiplyer;
    em_damage *= multiplyer;
    explosive_damage *= multiplyer;

		Damage damageDealt
			(
			m_ship->GetOperator()->GetSystemEntity(),
			m_item,
			kinetic_damage,			// kinetic damage
			thermal_damage,			// thermal damage
			em_damage,				// em damage
			explosive_damage,		// explosive damage
			(EVEEffectID)(m_effectID)	// from EVEEffectID::
			);

		m_targetEntity->ApplyDamage(damageDealt);

		// Reduce consumable in cargo:
		// TODO
}
