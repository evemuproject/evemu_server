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
    Author:        Reve, AknorJaden
*/

#include "eve-server.h"

#include "system/Damage.h"
#include "ship/modules/weapon_modules/EnergyTurret.h"

EnergyTurret::EnergyTurret( InventoryItemRef item, ShipRef ship)
: ActiveModule(item, ship)
{
    m_effectString = "effects.Laser";
}

bool EnergyTurret::canActivate(SystemEntity * targetEntity)
{
	if( !m_chargeRef )
	{
		SysLog::Error( "EnergyTurret::Activate()", "ERROR: Cannot find charge that is supposed to be loaded into this module!" );
		throw PyException( MakeCustomError( "ERROR!  Cannot find charge that is supposed to be loaded into this module!" ) );
	}
    return true;
}

void EnergyTurret::startCycle(bool continuing)
{
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
        effectTargetAttack		// from EVEEffectID::
    );

    m_targetEntity->ApplyDamage( damageDealt );
}
