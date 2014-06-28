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
    Author:        avianrr
*/

#include "eve-server.h"
#include "inventory/AttributeEnum.h"
#include "ship/Ship.h"
#include "ship/modules/logistics_modules/RepairModule.h"

RepairModule::RepairModule(InventoryItemRef item, ShipRef ship)
: ActiveModule(item, ship)
{
}

void RepairModule::EndCycle()
{
    // check for shield repair.
    EvilNumber boost;
    if(HasAttribute(AttrShieldBonus, boost))
    {
        double Shield = m_Ship->GetAttribute(AttrShieldCharge).get_float();
        EvilNumber bonus;
        if(_isOverload)
        {
            if(HasAttribute(AttrOverloadShieldBonus, bonus))
            {
                boost *= bonus / 100.0;
            }
        }
        // adjust for the effects of other modules on shield boosters.
        if(HasAttribute(AttrShieldBonus, bonus))
        {
            boost *= 1.0 + (bonus / 100.0);
        }
        double newShield = Shield + boost.get_float();
        double capacity = m_Ship->GetAttribute(AttrShieldCapacity).get_float();
        if(newShield > capacity)
            newShield = capacity;
        if(newShield != Shield)
          m_Ship->SetAttribute(AttrShieldCharge, newShield);
    }
    // check for armor repair.
    if(HasAttribute(AttrArmorDamageAmount, boost))
    {
        double Armor = m_Ship->GetAttribute(AttrArmorDamage).get_float();
        // if were already at full health no need to continue.
        if(Armor > 0)
        {
            if(_isOverload)
            {
                EvilNumber bonus;
                if(HasAttribute(AttrOverloadArmorDamageAmount, bonus))
                {
                    boost *= bonus / 100.0;
                }
            }
            double newArmor = Armor - boost.get_float();
            if(newArmor < 0)
                newArmor = 0;
            if(newArmor != Armor)
                m_Ship->SetAttribute(AttrArmorDamage, newArmor);
        }
    }
    // check for structure repair.
    if(HasAttribute(AttrStructureDamageAmount, boost))
    {
        double Hull = m_Ship->GetAttribute(AttrDamage).get_float();
        if(Hull > 0)
        {
            double newHull = Hull - boost.get_float();
            if(newHull < 0)
                newHull = 0;
            if(newHull != Hull)
                m_Ship->SetAttribute(AttrDamage, newHull);
        }
    }
}
