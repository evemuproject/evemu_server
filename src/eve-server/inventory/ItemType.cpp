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
    Author:     Bloody.Rabbit
*/

#include "eve-server.h"

#include "character/Character.h"
#include "manufacturing/Blueprint.h"
#include "ship/Ship.h"
#include "station/Station.h"

/*
 * TypeData
 */
TypeData::TypeData(
    uint32 _groupID,
    const char *_name,
    const char *_desc,
    double _radius,
    double _mass,
    double _volume,
    double _capacity,
    uint32 _portionSize,
    EVERace _race,
    double _basePrice,
    bool _published,
    uint32 _marketGroupID,
    double _chanceOfDuplicating)
: groupID(_groupID),
  name(_name),
  description(_desc),
  radius(_radius),
  mass(_mass),
  volume(_volume),
  capacity(_capacity),
  portionSize(_portionSize),
  race(_race),
  basePrice(_basePrice),
  published(_published),
  marketGroupID(_marketGroupID),
  chanceOfDuplicating(_chanceOfDuplicating)
{
}

/*
 * ItemType
 */
ItemType::ItemType(
    uint32 _id,
                   const InvGroupRef _group,
    const TypeData &_data)
: attributes(*this),
  m_id(_id),
  m_group(_group),
  m_name(_data.name),
  m_description(_data.description),
  m_portionSize(_data.portionSize),
  m_basePrice(_data.basePrice),
  m_published(_data.published),
  m_marketGroupID(_data.marketGroupID),
  m_chanceOfDuplicating(_data.chanceOfDuplicating)
{
    // assert for data consistency
    assert(_data.groupID == _group->groupID);

    // set some attributes
    attributes.Set_radius(_data.radius);
    attributes.Set_mass(_data.mass);
    attributes.Set_volume(_data.volume);
    attributes.Set_capacity(_data.capacity);
    attributes.Set_raceID(_data.race);

    _log(ITEM__TRACE, "Created object %p for type %s (%u).", this, name().c_str(), id());
}

ItemType *ItemType::Load(uint32 typeID)
{
    return ItemType::Load<ItemType>( typeID );
}

template<class _Ty>
_Ty *ItemType::_LoadType(uint32 typeID,
    // ItemType stuff:
                         const InvGroupRef group, const TypeData &data)
{
    // See what to do next:
    switch (group->categoryID)
    {
        //! TODO not handled.
        case EVEDB::invCategories::Owner:
        case EVEDB::invCategories::Celestial:
        case EVEDB::invCategories::Skill:
        case EVEDB::invCategories::_System:
        case EVEDB::invCategories::Station:
        case EVEDB::invCategories::Material:
        case EVEDB::invCategories::Accessories:
        case EVEDB::invCategories::Module:
        case EVEDB::invCategories::Charge:
        case EVEDB::invCategories::Trading:
        case EVEDB::invCategories::Entity:
        case EVEDB::invCategories::Bonus:
        case EVEDB::invCategories::Commodity:
        case EVEDB::invCategories::Drone:
        case EVEDB::invCategories::Implant:
        case EVEDB::invCategories::Deployable:
        case EVEDB::invCategories::Structure:
        case EVEDB::invCategories::Reaction:
        case EVEDB::invCategories::Asteroid:
             break;
        ///////////////////////////////////////
        // Blueprint:
        ///////////////////////////////////////
        case EVEDB::invCategories::Blueprint:
        {
            break;
        }

        ///////////////////////////////////////
        // Ship:
        ///////////////////////////////////////
        case EVEDB::invCategories::Ship:
        {
            break;
        }
    }

    // ItemCategory didn't do it, try ItemGroup:
    switch( group->groupID ) {
        ///////////////////////////////////////
        // Character:
        ///////////////////////////////////////
        case EVEDB::invGroups::Character: {
            return CharacterType::_LoadType<CharacterType>( typeID, group, data );
        }

        ///////////////////////////////////////
        // Station:
        ///////////////////////////////////////
        case EVEDB::invGroups::Station:
        {
            break;
        }
    }

    // Generic one, create it:
    return new ItemType( typeID, group, data );
}

bool ItemType::_Load() {
	// load type effects
	InventoryDB::GetTypeEffectsList( m_id, m_effects );

    // load type attributes
    return (attributes.Load());
}



