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
    Author:        AknorJaden
*/

#include "eve-server.h"

#include "EntityList.h"
#include "system/SystemBubble.h"
#include "system/Damage.h"
#include "ship/modules/weapon_modules/ProjectileTurret.h"

ProjectileTurret::ProjectileTurret( InventoryItemRef item, ShipRef ship )
{
    m_Item = item;
    m_Ship = ship;
    m_Effects = new ModuleEffects(m_Item->typeID());
    m_ShipAttrComp = new ModifyShipAttributesComponent(this, ship);
	m_ActiveModuleProc = new ActiveModuleProcessingComponent(item, this, ship, m_ShipAttrComp);

	m_chargeRef = InventoryItemRef();		// Ensure ref is NULL
	m_chargeLoaded = false;

	m_ModuleState = MOD_UNFITTED;
	m_ChargeState = MOD_UNLOADED;
}

ProjectileTurret::~ProjectileTurret()
{

}

void ProjectileTurret::Process()
{
	m_ActiveModuleProc->Process();
}

void ProjectileTurret::Load(InventoryItemRef charge)
{
	ActiveModule::Load(charge);
	m_ChargeState = MOD_LOADED;
}

void ProjectileTurret::Unload()
{
	ActiveModule::Unload();
	m_ChargeState = MOD_UNLOADED;
}

void ProjectileTurret::Repair()
{

}

void ProjectileTurret::Overload()
{

}

void ProjectileTurret::DeOverload()
{

}

void ProjectileTurret::DestroyRig()
{

}

void ProjectileTurret::Activate(SystemEntity * targetEntity)
{
	if( this->m_chargeRef != NULL )
	{
		m_targetEntity = targetEntity;
		m_targetID = targetEntity->Item()->itemID();

		// Activate active processing component timer:
		m_ActiveModuleProc->ActivateCycle();
		m_ModuleState = MOD_ACTIVATED;
		//_ShowCycle();
		m_ActiveModuleProc->ProcessActiveCycle();
	}
	else
	{
		sLog.Error( "ProjectileTurret::Activate()", "ERROR: Cannot find charge that is supposed to be loaded into this module!" );
		throw PyException( MakeCustomError( "ERROR!  Cannot find charge that is supposed to be loaded into this module!" ) );
	}
}

void ProjectileTurret::Deactivate() 
{
	m_ModuleState = MOD_DEACTIVATING;
	m_ActiveModuleProc->DeactivateCycle();
}

void ProjectileTurret::StopCycle(bool abort)
{
	Notify_OnGodmaShipEffect shipEff;
	shipEff.itemID = m_Item->itemID();
	shipEff.effectID = effectProjectileFired;
	shipEff.when = Win32TimeNow();
	shipEff.start = 0;
	shipEff.active = 0;

	PyList* env = new PyList;
	env->AddItem(new PyInt(shipEff.itemID));
	env->AddItem(new PyInt(m_Ship->ownerID()));
	env->AddItem(new PyInt(m_Ship->itemID()));
	env->AddItem(new PyInt(m_targetID));
	env->AddItem(new PyNone);
	env->AddItem(new PyNone);
	env->AddItem(new PyInt(shipEff.effectID));

	shipEff.environment = env;
	shipEff.startTime = shipEff.when;
	shipEff.duration = 1.0;		//m_ActiveModuleProc->GetRemainingCycleTimeMS();		// At least, I'm assuming this is the remaining time left in the cycle
	shipEff.repeat = new PyInt(0);
	shipEff.randomSeed = new PyNone;
	shipEff.error = new PyNone;

	PyList* events = new PyList;
	events->AddItem(shipEff.Encode());

	Notify_OnMultiEvent multi;
	multi.events = events;

	PyTuple* tmp = multi.Encode();

	m_Ship->GetOperator()->SendDogmaNotification("OnMultiEvent", "clientID", &tmp);

	m_ActiveModuleProc->DeactivateCycle();

	// Create Special Effect:
	m_Ship->GetOperator()->GetDestiny()->SendSpecialEffect
	(
		m_Ship,
		m_Item->itemID(),
		m_Item->typeID(),
		m_targetID,
		m_chargeRef->itemID(),
		"effects.ProjectileFired",
		1,
		0,
		0,
		1.0,
		0
	);
}

void ProjectileTurret::DoCycle()
{
	if( m_ActiveModuleProc->ShouldProcessActiveCycle() )
	{
		// Check to see if our target is still in this bubble or has left or been destroyed:
		if( m_Ship->GetOperator()->GetSystemEntity()->Bubble() == NULL )
		{
			// Target has left our bubble or been destroyed, deactivate this module:
			Deactivate();
			return;
		}
		else
		{
			if( !(m_Ship->GetOperator()->GetSystemEntity()->Bubble()->GetEntity(m_targetID)) )
			{
				// Target has left our bubble or been destroyed, deactivate this module:
				Deactivate();
				return;
			}
		}

		if( m_chargeRef->quantity() == 0 )
		{
			Deactivate();
			return;
		}

		_ShowCycle();

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
		if( m_chargeRef->HasAttribute(AttrKineticDamage) )
			kinetic_damage = (m_Item->GetAttribute(AttrDamageMultiplier) * m_chargeRef->GetAttribute(AttrKineticDamage)).get_float();
		if( m_chargeRef->HasAttribute(AttrThermalDamage) )
			thermal_damage = (m_Item->GetAttribute(AttrDamageMultiplier) * m_chargeRef->GetAttribute(AttrThermalDamage)).get_float();
		if( m_chargeRef->HasAttribute(AttrEmDamage) )
			em_damage = (m_Item->GetAttribute(AttrDamageMultiplier) * m_chargeRef->GetAttribute(AttrEmDamage)).get_float();
		if( m_chargeRef->HasAttribute(AttrExplosiveDamage) )
			explosive_damage = (m_Item->GetAttribute(AttrDamageMultiplier) * m_chargeRef->GetAttribute(AttrExplosiveDamage)).get_float();

		Damage damageDealt
		(
			m_Ship->GetOperator()->GetSystemEntity(),
			m_Item,
			kinetic_damage,			// kinetic damage
			thermal_damage,			// thermal damage
			em_damage,				// em damage
			explosive_damage,		// explosive damage
			effectProjectileFired		// from EVEEffectID::
		);
		
		m_targetEntity->ApplyDamage( damageDealt );

		// Reduce ammo charge by 1 unit:
		m_chargeRef->SetQuantity(m_chargeRef->quantity() - 1);
	}
}

void ProjectileTurret::_ShowCycle()
{
	// Create Destiny Updates:
	Notify_OnGodmaShipEffect shipEff;
	shipEff.itemID = m_Item->itemID();
	shipEff.effectID = effectProjectileFired;		// From EVEEffectID::
	shipEff.when = Win32TimeNow();
	shipEff.start = 1;
	shipEff.active = 1;

	PyList* env = new PyList;
	env->AddItem(new PyInt(shipEff.itemID));
	env->AddItem(new PyInt(m_Ship->ownerID()));
	env->AddItem(new PyInt(m_Ship->itemID()));
	env->AddItem(new PyInt(m_targetID));
	env->AddItem(new PyNone);
	env->AddItem(new PyNone);
	env->AddItem(new PyInt(shipEff.effectID));

	shipEff.environment = env;
	shipEff.startTime = shipEff.when;
	shipEff.duration = m_Item->GetAttribute(AttrSpeed).get_float();
	shipEff.repeat = new PyInt(1000);
	shipEff.randomSeed = new PyNone;
	shipEff.error = new PyNone;

	PyTuple* tmp = new PyTuple(3);
	//tmp->SetItem(1, dmgMsg.Encode());
	tmp->SetItem(2, shipEff.Encode());

	std::vector<PyTuple*> events;
	//events.push_back(dmgMsg.Encode());
	events.push_back(shipEff.Encode());

	std::vector<PyTuple*> updates;
	//updates.push_back(dmgChange.Encode());

	m_Ship->GetOperator()->GetDestiny()->SendDestinyUpdate(updates, events, false);

	// Create Special Effect:
	m_Ship->GetOperator()->GetDestiny()->SendSpecialEffect
	(
		m_Ship,
		m_Item->itemID(),
		m_Item->typeID(),
		m_targetID,
		0,//m_chargeRef->typeID(),
		"effects.ProjectileFired",
		1,
		1,
		1,
		1.0, //m_Item->GetAttribute(AttrSpeed).get_float(),
		50000
	);
}
