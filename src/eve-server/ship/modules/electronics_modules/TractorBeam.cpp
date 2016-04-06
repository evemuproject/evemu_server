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

#include "EntityList.h"
#include "system/SystemBubble.h"
#include "system/Damage.h"
#include "ship/modules/electronics_modules/TractorBeam.h"

TractorBeam::TractorBeam( InventoryItemRef item, ShipRef ship)
: ActiveModule(item, ship)
{
    m_effectString = "effects.TractorBeam";
}

bool TractorBeam::canActivate(SystemEntity * targetEntity)
{
	// Check to make sure target is NOT a static entity:
	// TODO: Check for target = asteroid, ice, or gas cloud then only allow tractoring if ship = Orca
	// TODO: DO NOT allow tractoring of Client-connected player ships
	if (!(targetEntity->IsStaticEntity()))
	{
		if (
		     (
				(m_ship->typeID() == 28606)		// Orca is the only ship allowed to tractor asteroids and ice chunks
				&&
				(
				((getItem()->typeID() == 16278 || getItem()->typeID() == 22229) && (targetEntity->Item()->groupID() == EVEDB::invGroups::Ice))
				||
				(targetEntity->Item()->categoryID() == EVEDB::invCategories::Asteroid)
				||
				((targetEntity->Item()->groupID() == EVEDB::invGroups::Harvestable_Cloud) && (getItem()->groupID() == EVEDB::invGroups::Gas_Cloud_Harvester))
				)
				)
				||
				(targetEntity->Item()->groupID() == EVEDB::invGroups::Cargo_Container)
				||
				(targetEntity->Item()->groupID() == EVEDB::invGroups::Secure_Cargo_Container)
				||
				(targetEntity->Item()->groupID() == EVEDB::invGroups::Wreck)
			)
		{
            return true;
		}
	}
    return false;
}

void TractorBeam::startCycle(bool continuing)
{
    // Initiate continued Destiny Action to move tractored object toward ship
    DynamicSystemEntity * targetEntity = static_cast<DynamicSystemEntity *>(m_targetEntity);
    // Check for distance to target > 5000m + ship radius
    Vector3D distanceToTarget(m_ship->position() - targetEntity->GetPosition());
    if (distanceToTarget.length() > (5000.0 + m_ship->getAttribute(AttrRadius).get_float()))
    {
        // Range higher?  Then start it moving toward ship @ 200m/s
        targetEntity->Destiny()->SetMaxVelocity(1000.0);
        targetEntity->Destiny()->SetSpeedFraction(1.0);
        // Tractor objects at 1000m/s:
        targetEntity->Destiny()->TractorBeamFollow(m_ship->GetOperator()->GetSystemEntity(), 10, 1000, (5000.0 + m_ship->getAttribute(AttrRadius).get_float()));
    }
    else
    {
        targetEntity->Destiny()->TractorBeamHalt();
        deactivate();
    }
}
