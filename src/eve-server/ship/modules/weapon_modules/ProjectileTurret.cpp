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

#include "EntityList.h"
#include "system/SystemBubble.h"
#include "system/Damage.h"
#include "ship/modules/weapon_modules/ProjectileTurret.h"

ProjectileTurret::ProjectileTurret(InventoryItemRef item, ShipRef ship)
: WeaponModule(item, ship)
{
    // charge loading time is 10 seconds.
    m_LoadCycleTime = 10000;
}

void ProjectileTurret::StartCycle()
{
    // Create Destiny Updates:
    DoDestiny_OnDamageStateChange dmgChange;
    dmgChange.entityID = m_targetEntity->GetID();

    PyList *states = new PyList;
    states->AddItem(new PyFloat(0));
    states->AddItem(new PyFloat(0));
    states->AddItem(new PyFloat(0.99));
    dmgChange.state = states;

    Notify_OnDamageMessage dmgMsg;
    dmgMsg.messageID = ""; // Can be left blank as Damage.cpp fills this in.  This can be one in this set {"AttackHit1", "AttackHit2", "AttackHit3", "AttackHit4", "AttackHit5", "AttackHit6"}
    dmgMsg.weapon = m_Item->itemID();
    dmgMsg.splash = "";
    dmgMsg.target = m_targetEntity->GetID();
    dmgMsg.damage = (m_Item->GetAttribute(AttrDamageMultiplier).get_float() * 48.0);

    std::vector<PyTuple*> events;
    events.push_back(dmgMsg.Encode());

    std::vector<PyTuple*> updates;
    updates.push_back(dmgChange.Encode());

    m_Ship->GetOperator()->GetDestiny()->SendDestinyUpdate(updates, events, true);

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
    double damageMultiplier = m_Item->GetAttribute(AttrDamageMultiplier).get_float();
    EvilNumber damage;

    // This still somehow needs skill, ship, module, and implant bonuses to be applied:
    // This still somehow needs to have optimal range and falloff attributes applied as a damage modification factor:
    if (m_ChargeRef->HasAttribute(AttrKineticDamage, damage))
        kinetic_damage = damageMultiplier * damage.get_float();
    if (m_ChargeRef->HasAttribute(AttrThermalDamage, damage))
        thermal_damage = damageMultiplier * damage.get_float();
    if (m_ChargeRef->HasAttribute(AttrEmDamage, damage))
        em_damage = damageMultiplier * damage.get_float();
    if (m_ChargeRef->HasAttribute(AttrExplosiveDamage, damage))
        explosive_damage = damageMultiplier * damage.get_float();

    Damage damageDealt
            (
             m_Ship->GetOperator()->GetSystemEntity(),
             m_Item,
             kinetic_damage, // kinetic damage
             thermal_damage, // thermal damage
             em_damage, // em damage
             explosive_damage, // explosive damage
             effectTargetAttack // from EVEEffectID::
             );

    if(m_targetEntity->ApplyDamage(damageDealt))
    {
        m_targetEntity = NULL;
        Deactivate();
    }

    // expend round.
    if (m_ChargeRef->quantity() <= 1)
    {
        // last rounds used.
        if(m_Ship.get() != NULL)
        {
            Deactivate();
            m_ChargeRef->Delete();
            Unload();
            // to-do: auto-reload
        }
    }
    else
      m_ChargeRef->AlterQuantity(-1, true);
}
