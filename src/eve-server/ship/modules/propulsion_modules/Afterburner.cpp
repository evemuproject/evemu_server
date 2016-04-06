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
    Author:        Luck
*/

#include "eve-server.h"

#include "ship/modules/propulsion_modules/Afterburner.h"

Afterburner::Afterburner( InventoryItemRef item, ShipRef ship)
: ActiveModule(item, ship)
{
    m_effectString = "effects.SpeedBoost";
}

bool Afterburner::endCycle(bool continuing)
{
    if(continuing)
    {
        return true;
    }
	// Tell Destiny Manager about our new speed so it properly tracks ship movement:
	m_ship->GetOperator()->GetDestiny()->SetMaxVelocity(m_ship->getDefaultAttribute(AttrMaxVelocity).get_float());
	m_ship->GetOperator()->GetDestiny()->SetSpeedFraction(1.0);

	DoDestiny_SetMaxSpeed speed;
	speed.entityID = m_ship->itemID();
	speed.speedValue = m_ship->getDefaultAttribute(AttrMaxVelocity).get_float();

	DoDestiny_SetBallMass mass;
	mass.entityID = m_ship->itemID();
	mass.mass = m_ship->getAttribute(AttrMass).get_float();

	std::vector<PyTuple *> updates;
	updates.push_back(speed.Encode());
	updates.push_back(mass.Encode());

	m_ship->GetOperator()->GetDestiny()->SendDestinyUpdate(updates, false);
    
    return true;
}

void Afterburner::startCycle(bool continuing)
{
    if(continuing)
    {
        return;
    }
	double implantBonuses = 1.0;	// TODO: gather and accumulate all implant bonuses for MWDs/Afterburners
	double accelerationControlSkillLevel = 0.0;	// TODO: Figure out how to get access to skills list of character running this ship and get this value
	double boostSpeed = m_ship->getAttribute(AttrMaxVelocity).get_float() * (1.0 + (m_item->getAttribute(AttrSpeedFactor).get_float() / 100.0 * (1 + accelerationControlSkillLevel * 0.05) * (implantBonuses) * (m_item->getAttribute(AttrSpeedBoostFactor).get_float() / (m_ship->getAttribute(AttrMass).get_float()))));

	// Tell Destiny Manager about our new speed so it properly tracks ship movement:
	m_ship->GetOperator()->GetDestiny()->SetMaxVelocity(boostSpeed);
	m_ship->GetOperator()->GetDestiny()->SetSpeedFraction(1.0);

	DoDestiny_SetBallMass mass;
	mass.entityID = m_ship->itemID();
	mass.mass = m_ship->getAttribute(AttrMass).get_float();

	DoDestiny_SetMaxSpeed speed;
	speed.entityID = m_ship->itemID();
	speed.speedValue = boostSpeed;

	std::vector<PyTuple *> updates;
	updates.push_back(mass.Encode());
	updates.push_back(speed.Encode());
}
