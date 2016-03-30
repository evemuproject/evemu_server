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
    Author:        Bloody.Rabbit
*/

#include "eve-server.h"

#include "character/Character.h"
#include "inventory/Owner.h"

Owner::Owner(
    uint32 _ownerID,
    // InventoryItem stuff:
             const InvTypeRef _type,
    const ItemData &_data)
: InventoryItem( _ownerID, _type, _data )
{
}

OwnerRef Owner::Load(uint32 ownerID)
{
    return InventoryItem::Load<Owner>( ownerID );
}

template<class _Ty>
RefPtr<_Ty> Owner::_LoadOwner(uint32 ownerID,
    // InventoryItem stuff:
                              const InvTypeRef type, const ItemData &data)
{
    // decide what to do next:
    switch (type->groupID)
    {
        ///////////////////////////////////////
        // Character:
        ///////////////////////////////////////
        case EVEDB::invGroups::Character: {
            // create character
            return Character::_LoadOwner<Character>( ownerID, type, data );
        }
    }

    // fallback to default:
    return OwnerRef( new Owner( ownerID, type, data ) );
}

OwnerRef Owner::Spawn(ItemData &data)
{
    // obtain type of new item
    const InvTypeRef t = InvType::getType(data.typeID);
    if (t.get() == nullptr)
    {
        return OwnerRef();
    }

    switch( t->groupID )
    {
        ///////////////////////////////////////
        // Character:
        ///////////////////////////////////////
        case EVEDB::invGroups::Character: {
            // we're not gonna create character from default attributes ...
            _log( ITEM__ERROR, "Refusing to create character '%s' from default attributes.", data.name.c_str() );

            return OwnerRef();
        }
    }

    // fallback to default:
    uint32 ownerID = Owner::_Spawn( data );
    if( ownerID == 0 )
        return OwnerRef();
    return Owner::Load( ownerID );
}

uint32 Owner::_Spawn(
    // InventoryItem stuff:
    ItemData &data )
{
    // no additional stuff
    return InventoryItem::_Spawn( data );
}

