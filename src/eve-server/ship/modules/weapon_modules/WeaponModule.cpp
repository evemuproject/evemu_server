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
#include "ship/modules/weapon_modules/WeaponModule.h"

WeaponModule::WeaponModule(InventoryItemRef item, ShipRef ship)
: ActiveModule(item, ship)
{
    m_RequiresCharge = true;
}

void WeaponModule::Activate(SystemEntity * targetEntity)
{
    // if the weapon is already busy do nothing.
    if(m_ActiveModuleProc->IsBusy())
        return;
    // make sure its a valid target and charge.
    if (m_ChargeRef.get() != NULL && targetEntity != NULL)
    {
        // check for civilian version with infinite ammo.
        if(!HasAttribute(AttrAmmoLoaded))
        {
            sLog.Error("WeaponModule::Activate()", "ERROR: Cannot find charge that is supposed to be loaded into this module!");
            throw PyException(MakeCustomError("ERROR!  Cannot find charge that is supposed to be loaded into this module!"));
        }
    }
    
    // store the target entity.
    m_targetEntity = targetEntity;
    // Activate active processing component timer:
    m_ActiveModuleProc->ActivateCycle(-1, m_ChargeRef);
}
