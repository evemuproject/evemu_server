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
#include "ship/modules/armor_modules/ArmorRepairer.h"

ArmorRepairer::ArmorRepairer(InventoryItemRef item, ShipRef ship)
: ActiveModule(item, ship)
{
    m_effectString  = "effects.ArmorRepair";
}

void ArmorRepairer::startCycle(bool continuing)
{
    // Apply repair amount:
    EvilNumber newDamageAmount;
    newDamageAmount = m_ship->getAttribute(AttrArmorDamage) - m_item->getAttribute(AttrArmorDamageAmount);
    if( newDamageAmount < 0.0 )
    {
        newDamageAmount = 0.0;
    }

    m_ship->setAttribute(AttrArmorDamage, newDamageAmount);
}
