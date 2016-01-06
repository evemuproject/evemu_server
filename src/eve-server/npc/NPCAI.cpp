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
    Author:        Zhur
*/

#include "eve-server.h"

#include "Client.h"
#include "inventory/AttributeEnum.h"
#include "npc/NPC.h"
#include "npc/NPCAI.h"
#include "ship/DestinyManager.h"
#include "system/Damage.h"
#include "system/SystemBubble.h"

NPCAIMgr::NPCAIMgr(NPC *who)
: m_state(Idle),
  m_entityFlyRange2(who->Item()->GetAttribute(AttrEntityFlyRange)*who->Item()->GetAttribute(AttrEntityFlyRange)),
  m_entityChaseMaxDistance2(who->Item()->GetAttribute(AttrEntityChaseMaxDistance)*who->Item()->GetAttribute(AttrEntityChaseMaxDistance)),
  m_entityAttackRange2(who->Item()->GetAttribute(AttrEntityAttackRange)*who->Item()->GetAttribute(AttrEntityAttackRange)),
  m_npc(who),
  m_processTimer(50),    //arbitrary.
  m_mainAttackTimer(1),    //we want this to always trigger the first time through.
  m_shieldBoosterTimer(static_cast<int32>(who->Item()->GetAttribute(AttrEntityShieldBoostDuration).get_int())),
  m_armorRepairTimer(static_cast<int32>(who->Item()->GetAttribute(AttrEntityArmorRepairDuration).get_int())),
  m_beginFindTarget(20000)

{
    m_processTimer.Start();
    m_mainAttackTimer.Start();
	m_beginFindTarget.Start();

    // This NPC uses Shield Booster
    if( who->Item()->GetAttribute(AttrEntityShieldBoostDuration) > 0 )
        m_shieldBoosterTimer.Start();
    // This NPC uses armor repairer
    if( who->Item()->GetAttribute(AttrEntityArmorRepairDuration) > 0 )
        m_armorRepairTimer.Start();
}

void NPCAIMgr::Process() {
    if(!m_processTimer.Check())
        return;

    // Test to see if we have a Shield Booster
    if( m_shieldBoosterTimer.Enabled() )
    {
        // It's time to recharge?
        if( m_shieldBoosterTimer.Check() )
        {
            m_npc->UseShieldRecharge();
        }
    }
    // Test to see if we have an Armor Repair
    if( m_armorRepairTimer.Enabled() )
    {
        // It's time to recharge?
        if( m_armorRepairTimer.Check() )
        {
            m_npc->UseArmorRepairer();
        }
    }

    switch(m_state) {
    case Idle:
		{
			// Make sure we're not warping to the spawn point:
			if( !(m_npc->Destiny()->IsWarping()) )
			{
				//TODO: wander around?
				//TODO: look around for shit to shoot at?
				//         The parameter proximityRange tells us how far we "see"
				bool targetSelected = false;
				if( m_beginFindTarget.Check() )
				{
					std::set<SystemEntity *> possibleTargets;
					m_npc->Bubble()->GetEntities(possibleTargets);
					std::set<SystemEntity *>::iterator cur, end;
					cur = possibleTargets.begin();
					end = possibleTargets.end();
					for(; cur != end; cur++)
					{
						// We find a target
						// TODO: Determine the weakest target to engage
						if( (*cur)->IsClient() )
						{
							// Check to see if this player ship is not cloaked, so we can really target them:
							if( ((*cur)->CastToClient()->Destiny()) != NULL )
							{
								if( !((*cur)->CastToClient()->Destiny()->IsCloaked()) )
								{
									// TODO: Check to see if target's standings are below 0.0, if so, engage, otherwise, ignore:
									//Client * const currentClient = (*cur)->CastToClient();
									//if( currentClient->GetStandingsFrom(this->m_npc->CastToNPC()->GetCorporationID()) >= 0.0 )
									//	break;
						
									// Check to see if it's a capsule
									// Target him and begin the process of the attack.
									if( !((*cur)->Item()->groupID() == EVEDB::invGroups::Capsule) )
									{
										this->Targeted((*cur));
										targetSelected = true;
									}
								}
							}
						}

						if( targetSelected )
							break;
					}
				}
			}
			break;
		}

    case Chasing: {
        //NOTE: getting our target like this is pretty weak...
        SystemEntity *target = m_npc->targets.GetFirstTarget(false);
        if(target == NULL) {
            //no valid target...
            if(m_npc->targets.HasNoTargets()) {
                _log(NPC__AI_TRACE, "[%u] Stopped chasing, no targets remain.", m_npc->GetID());
                m_state = Idle;
                return;
            }
            //else, still locking or something.
            return;
        }

        if(m_npc->DistanceTo2(target) < m_entityAttackRange2.get_float()) {
            //we caught up... off to follow mode. Should orbit, but that
            //isnt working yet.
            _log(NPC__AI_TRACE, "[%u] Was chasing %u, but they are close enough now. Following.", m_npc->GetID(), target->GetID());
            _EnterEngaged(target);
            return;
        }

        //else, we continue chasing... should we shoot?
        CheckAttacks(target);
    } break;

    case Following: {
        //NOTE: getting our target like this is pretty weak...
        SystemEntity *target = m_npc->targets.GetFirstTarget(false);
        if(target == NULL) {
            //no valid target...
            if(m_npc->targets.HasNoTargets()) {
                _log(NPC__AI_TRACE, "[%u] Stopped chasing, no targets remain.", m_npc->GetID());
                m_state = Idle;
                return;
            }
            //else, still locking or something.
            return;
        }

        if(m_npc->DistanceTo2(target) > m_entityChaseMaxDistance2.get_float()) {
            //they are too far away now...
            _log(NPC__AI_TRACE, "[%u] Was chasing with %u, but they are too far away now. Chasing.", m_npc->GetID(), target->GetID());
            _EnterChasing(target);
            return;
        }

        //ok, we are close enough...
        CheckAttacks(target);
    } break;

    case Engaged: {
        //NOTE: getting our target like this is pretty weak...
        SystemEntity *target = m_npc->targets.GetFirstTarget(false);

        if(target == NULL) {
            //no valid target...
            if(m_npc->targets.HasNoTargets()) {
                _log(NPC__AI_TRACE, "[%u] Stopped chasing, no targets remain.", m_npc->GetID());
                _EnterIdle();
                return;
            }
            //else, still locking or something.
            return;
        }

        if(m_npc->DistanceTo2(target) > m_entityAttackRange2.get_float()) {
            //they are too far away now...
            _log(NPC__AI_TRACE, "[%u] Was engaged with %u, but they are too far away now. Following.", m_npc->GetID(), target->GetID());
            _EnterFollowing(target);
            return;
        }

        //ok, we are close enough...
        CheckAttacks(target);
    } break;
    //no default on purpose
    }
}

void NPCAIMgr::ClearAllTargets()
{
	m_npc->targets.ClearAllTargets();
}

void NPCAIMgr::_EnterChasing(SystemEntity *target) {
    //TODO: we actually use MWD if we have them...
    m_npc->Destiny()->Follow(target, m_npc->Item()->GetAttribute(AttrEntityFlyRange).get_float());
    m_state = Chasing;
}

void NPCAIMgr::_EnterFollowing(SystemEntity *target) {
    m_npc->Destiny()->Follow(target, m_npc->Item()->GetAttribute(AttrEntityFlyRange).get_float());
    m_state = Following;
}

void NPCAIMgr::_EnterIdle() {
    m_npc->Destiny()->Stop();
    m_state = Idle;
}

void NPCAIMgr::_EnterEngaged(SystemEntity *target) {
    //m_npc->Destiny()->Follow(target, m_npc->Item()->entityFlyRange());
    //not sure if we should use orbitRange or entityFlyRange...
    EvilNumber orbit_range = m_npc->Item()->GetAttribute(AttrOrbitRange);
    if( orbit_range > m_npc->Item()->GetAttribute(AttrEntityAttackRange) )
	{
        orbit_range = m_npc->Item()->GetAttribute(AttrMaxRange);
		if( orbit_range > m_npc->Item()->GetAttribute(AttrEntityAttackRange) )
			orbit_range = m_npc->Item()->GetAttribute(AttrEntityFlyRange);
    }
	if( orbit_range.get_float() == 0.0 )
	{
		GVector vectorToTarget( m_npc->GetPosition(), target->GetPosition() );
    	orbit_range = vectorToTarget.length();
	}
    m_npc->Destiny()->OrbitingCruise(target, orbit_range.get_float(),true, m_npc->Item()->GetAttribute(AttrEntityCruiseSpeed).get_float());
    m_state = Engaged;
}

void NPCAIMgr::Targeted(SystemEntity *by_who) {
    //TODO: determind lock speed.
    //TODO: obey maxLockedTargets
    //m_npc->targets.StartTargeting(by_who, 1000);
    //if( m_npc->Item()->GetAttribute(AttrMaxLockedTargets) > m_npc->targets.GetTotalTargets())
        //m_npc->targets.StartTargeting( by_who, NEED_A_SHIPREF_HERE );		// TO BE UPDATED DUE TO StartTargeting() signature change
    m_npc->targets.StartTargeting( by_who, (uint32)m_npc->Item()->GetAttribute(AttrSpeed).get_int(), (uint32)m_npc->Item()->GetAttribute(AttrMaxAttackTargets).get_int(), m_npc->Item()->GetAttribute(AttrEntityAttackRange).get_float() );

    switch(m_state) 
	{
    case Idle: 
		{
        _log(NPC__AI_TRACE, "[%u] Targeted by %u in Idle. Attacking.", m_npc->GetID(), by_who->GetID());
		
		_EnterChasing(by_who);	// HACK, doing this, somehow the NPC can orbit
		/*
        double dist = m_npc->DistanceTo2(by_who);
        if(dist < m_entityAttackRange2.get_float()) {
            _EnterEngaged(by_who);
        } else if(dist < m_entityChaseMaxDistance2.get_float()) {
            _EnterFollowing(by_who);
        } else {
            _EnterChasing(by_who);
        }*/
    } break;
    case Chasing:
        _log(NPC__AI_TRACE, "[%u] Targeted by %u while chasing.", m_npc->GetID(), by_who->GetID());
        break;
    case Following:
        _log(NPC__AI_TRACE, "[%u] Targeted by %u while following.", m_npc->GetID(), by_who->GetID());
        break;
    case Engaged:
        _log(NPC__AI_TRACE, "[%u] Targeted by %u while chasing.", m_npc->GetID(), by_who->GetID());
        break;
    //no default on purpose
    }
}

void NPCAIMgr::TargetLost(SystemEntity *by_who) {
    switch(m_state) {
    case Idle:
        //do nothing.
        break;
    case Chasing:
    case Following:
    case Engaged:
        if(m_npc->targets.HasNoTargets()) {
            _log(NPC__AI_TRACE, "[%u] Target of %u lost. No targets remain.", m_npc->GetID(), by_who->GetID());
            _EnterIdle();
        } else {
            _log(NPC__AI_TRACE, "[%u] Target of %u lost, but more targets remain.", m_npc->GetID(), by_who->GetID());
        }
        break;
    //no default on purpose
    }
}

void NPCAIMgr::CheckAttacks(SystemEntity *target) {
    if(m_mainAttackTimer.Check(false)) {
        _log(NPC__AI_TRACE, "[%u] Attack timer expired. Attacking %u.", m_npc->GetID(), target->GetID());

        InventoryItemRef self = m_npc->Item();

		// Check to see if the target is still visible, ie not cloaked:
		if( target->IsClient() )
		{
			if( target->CastToClient()->Destiny() != NULL )
			{
				if( target->CastToClient()->Destiny()->IsCloaked() )
				{
					m_npc->targets.ClearTarget(target);
					return;
				}
			}
			else
			{
				m_npc->targets.ClearTarget(target);
				return;
			}
		}

		// Check to see if the target still in the bubble (Client warped out)
		if( !m_npc->Bubble()->InBubble(target->GetPosition()) )
		{
			m_npc->targets.ClearTarget(target);
			return;
		}

        //reset the attack timer.
        //NOTE: there is probably a more intelligent way to make this descision.
        //if(self->entityAttackDelayMax() <= 0) {
            //use speed field...
            m_mainAttackTimer.Start(static_cast<uint32>(self->GetAttribute(AttrSpeed).get_int()));
        //} else {
            //I think this field is actually meant as a reaction time to the player showing up in range.
        //    m_mainAttackTimer.Start(MakeRandomInt(
        //        self->entityAttackDelayMin(),
        //        self->entityAttackDelayMax() ));
        //}
        //Do main attack...

        //check our attack range...
        if(m_npc->DistanceTo2(target) > m_entityAttackRange2.get_float()) {
            _log(NPC__AI_TRACE, "[%u] Target (%u) is too far away (%.2f > %.2f)", m_npc->GetID(), target->GetID(), m_npc->DistanceTo2(target), m_entityAttackRange2.get_float());
            _EnterFollowing(target);
            return;
        }

        //TODO: check to-hit...

        //TODO: Need to consult dgmTypeEffects to determine what kind
        // of effects to throw for this attack.
        _SendWeaponEffect("effects.Laser", target);

        Damage d(
            m_npc, (InventoryItemRef)self,
            effectTargetAttack);    //should get this from somewhere.
        m_npc->ApplyDamageModifiers(d, m_npc);

        target->ApplyDamage(d);
    }
}


//NOTE: duplicated from module manager code. They should share some day!
void NPCAIMgr::_SendWeaponEffect( const char*effect, SystemEntity *target )
{
    DoDestiny_OnSpecialFX13 sfx;
    sfx.entityID = m_npc->Item()->itemID();
    sfx.moduleID = m_npc->Item()->itemID();
    sfx.moduleTypeID = m_npc->Item()->typeID();
    sfx.targetID = target->GetID();
    sfx.otherTypeID = target->Item()->typeID();
    sfx.effect_type = effect;
    sfx.isOffensive = 1;
    sfx.start = 1;
    sfx.active = 1;

    //omit these for now, setting up the repeat might be a network optimization, but we don't need it right now.
    //sfx.duration_ms = 1960;    //no idea...
    //sfx.duration_ms = m_npc->Item()->speed();
    sfx.duration_ms = m_npc->Item()->GetAttribute(AttrSpeed).get_float();
    sfx.repeat = new PyBool(true);
    sfx.startTime = Win32TimeNow();

    PyTuple* up = sfx.Encode();
    m_npc->Destiny()->SendSingleDestinyUpdate( &up );    //consumed
    PySafeDecRef( up );
}



















