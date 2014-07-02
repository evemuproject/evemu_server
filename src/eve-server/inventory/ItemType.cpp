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
    Author:     Bloody.Rabbit
*/

#include "eve-server.h"

#include "character/Character.h"
#include "manufacturing/Blueprint.h"
#include "ship/Ship.h"
#include "station/Station.h"

/*
 * CategoryData
 */
CategoryData::CategoryData(
    const char *_name,
    const char *_desc,
    bool _published)
: name(_name),
  description(_desc),
  published(_published)
{
}

/*
 * ItemCategory
 */
ItemCategory::ItemCategory(
    EVEItemCategories _id,
    // ItemCategory stuff:
    const CategoryData &_data)
: m_id(_id),
  m_name(_data.name),
  m_description(_data.description),
  m_published(_data.published)
{
    _log(ITEM__TRACE, "Created object %p for category %s (%u).", this, name().c_str(), (uint32)id());
}

ItemCategory *ItemCategory::Load(EVEItemCategories category) {
    // create category
    ItemCategory *c = ItemCategory::_Load(category);
    if(c == NULL)
        return NULL;

    // ItemCategory has no virtual _Load()

    return(c);
}

ItemCategory *ItemCategory::_Load(EVEItemCategories category
) {
    // pull data
    CategoryData data;
    if(!sItemFactory.db().GetCategory(category, data))
        return NULL;

    return(
        ItemCategory::_Load(category, data)
    );
}

ItemCategory *ItemCategory::_Load(EVEItemCategories category,
    // ItemCategory stuff:
    const CategoryData &data
) {
    // enough data for construction
    return(new ItemCategory(
        category, data
    ));
}

/*
 * GroupData
 */
GroupData::GroupData(
    EVEItemCategories _category,
    const char *_name,
    const char *_desc,
    bool _useBasePrice,
    bool _allowManufacture,
    bool _allowRecycler,
    bool _anchored,
    bool _anchorable,
    bool _fittableNonSingleton,
    bool _published)
: category(_category),
  name(_name),
  description(_desc),
  useBasePrice(_useBasePrice),
  allowManufacture(_allowManufacture),
  allowRecycler(_allowRecycler),
  anchored(_anchored),
  anchorable(_anchorable),
  fittableNonSingleton(_fittableNonSingleton),
  published(_published)
{
}

/*
 * ItemGroup
 */
ItemGroup::ItemGroup(
    uint32 _id,
    // ItemGroup stuff:
    const ItemCategory &_category,
    const GroupData &_data)
: m_id(_id),
  m_category(&_category),
  m_name(_data.name),
  m_description(_data.description),
  m_useBasePrice(_data.useBasePrice),
  m_allowManufacture(_data.allowManufacture),
  m_allowRecycler(_data.allowRecycler),
  m_anchored(_data.anchored),
  m_anchorable(_data.anchorable),
  m_fittableNonSingleton(_data.fittableNonSingleton),
  m_published(_data.published)
{
    // assert for data consistency
    assert(_data.category == _category.id());

    _log(ITEM__TRACE, "Created object %p for group %s (%u).", this, name().c_str(), id());
}

ItemGroup *ItemGroup::Load(uint32 groupID) {
    // create group
    ItemGroup *g = ItemGroup::_Load(groupID);
    if(g == NULL)
        return NULL;

    // ItemGroup has no virtual _Load()

    return(g);
}

ItemGroup *ItemGroup::_Load(uint32 groupID
) {
    // pull data
    GroupData data;
    if(!sItemFactory.db().GetGroup(groupID, data))
        return NULL;

    // retrieve category
    const ItemCategory *c = sItemFactory.GetCategory(data.category);
    if(c == NULL)
        return NULL;

    return(
        ItemGroup::_Load(groupID, *c, data)
    );
}

ItemGroup *ItemGroup::_Load(uint32 groupID,
    // ItemGroup stuff:
    const ItemCategory &category, const GroupData &data
) {
    // enough data for construction
    return(new ItemGroup(
        groupID, category, data
    ));
}

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
    const ItemGroup &_group,
    const TypeData &_data)
: m_id(_id),
  m_group(&_group),
  m_name(_data.name),
  m_description(_data.description),
  m_portionSize(_data.portionSize),
  m_basePrice(_data.basePrice),
  m_published(_data.published),
  m_marketGroupID(_data.marketGroupID),
  m_chanceOfDuplicating(_data.chanceOfDuplicating),
  m_Effects(new TypeEffects(_id)),
  m_AttributeMap(_id, _data)
{
    // assert for data consistency
    assert(_data.groupID == _group.id());

    _log(ITEM__TRACE, "Created object %p for type %s (%u).", this, name().c_str(), id());
}

ItemType *ItemType::Load(uint32 typeID)
{
    return ItemType::Load<ItemType>( typeID );
}

template<class _Ty>
_Ty *ItemType::_LoadType(uint32 typeID,
    // ItemType stuff:
    const ItemGroup &group, const TypeData &data)
{
    // See what to do next:
    switch( group.categoryID() ) {
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
        case EVEDB::invCategories::Blueprint: {
            return BlueprintType::_LoadType<BlueprintType>( typeID, group, data );
        }

        ///////////////////////////////////////
        // Ship:
        ///////////////////////////////////////
        case EVEDB::invCategories::Ship: {
            return ShipType::_LoadType<ShipType>( typeID, group, data );
        }
    }

    // ItemCategory didn't do it, try ItemGroup:
    switch( group.id() ) {
        ///////////////////////////////////////
        // Character:
        ///////////////////////////////////////
        case EVEDB::invGroups::Character: {
            return CharacterType::_LoadType<CharacterType>( typeID, group, data );
        }

        ///////////////////////////////////////
        // Station:
        ///////////////////////////////////////
        case EVEDB::invGroups::Station: {
            return StationType::_LoadType<StationType>( typeID, group, data );
        }
    }

    // Generic one, create it:
    return new ItemType( typeID, group, data );
}

bool ItemType::_Load() {
    // load type attributes
    return true;
}

EvilNumber ItemType::GetAttribute( const uint32 attributeID ) const
{
     return m_AttributeMap.GetAttribute(attributeID);
}

EvilNumber ItemType::GetAttribute( const uint32 attributeID , const EvilNumber &defaultValue ) const
{
     return m_AttributeMap.GetAttribute(attributeID, defaultValue);
}

bool ItemType::HasAttribute(const uint32 attributeID) const
{
     return m_AttributeMap.HasAttribute(attributeID);
}

bool ItemType::HasAttribute(const uint32 attributeID, EvilNumber &value) const
{
     return m_AttributeMap.HasAttribute(attributeID, value);
}

