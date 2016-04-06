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

#include "Client.h"
#include "PyCallable.h"
#include "character/Character.h"
#include "inventory/Inventory.h"
#include "pos/Structure.h"
#include "ship/Ship.h"
#include "station/Station.h"
#include "system/Container.h"
#include "system/SolarSystem.h"

/*
 * Inventory
 */

Inventory::Inventory() : mContentsLoaded(false) {}
Inventory::~Inventory() {}

Inventory *Inventory::Cast(InventoryItemRef item)
{
    if( !item )
        return NULL;
    switch( item->categoryID() )
    {
        //! TODO: not handled.
        case EVEDB::invCategories::_System:
        case EVEDB::invCategories::Material:
        case EVEDB::invCategories::Accessories:
        case EVEDB::invCategories::Module:
        case EVEDB::invCategories::Charge:
        case EVEDB::invCategories::Blueprint:
        case EVEDB::invCategories::Trading:
        case EVEDB::invCategories::Entity:
        case EVEDB::invCategories::Bonus:
        case EVEDB::invCategories::Commodity:
        case EVEDB::invCategories::Drone:
        case EVEDB::invCategories::Implant:
        case EVEDB::invCategories::Deployable:
        case EVEDB::invCategories::Reaction:
        case EVEDB::invCategories::Asteroid:
        case EVEDB::invCategories::Apparel:
        case EVEDB::invCategories::Subsystem:
        case EVEDB::invCategories::AncientRelics:
        case EVEDB::invCategories::Decryptors:
        case EVEDB::invCategories::StructureUpgrade:
        case EVEDB::invCategories::SovereigntyStructure:
        case EVEDB::invCategories::PlanetaryInteraction:
        case EVEDB::invCategories::PlanetaryResources:
        case EVEDB::invCategories::PlanetaryCommodities:
        case EVEDB::invCategories::Orbitals:
        case EVEDB::invCategories::Placeables:
        case EVEDB::invCategories::Effects:
        case EVEDB::invCategories::Lights:
        case EVEDB::invCategories::Cells:
            SysLog::Warning("Inventory", "unhandled item categoryID used on cast");
            break;

        case EVEDB::invCategories::Owner:
            SysLog::Warning("Inventory", "Owner item categoryID used on cast");

            //return OwnerRef::StaticCast( item ).get();

            break;
        case EVEDB::invCategories::WorldSpace:
            SysLog::Warning("Inventory", "WorldSpace item categoryID used on cast");
            break;
        case EVEDB::invCategories::Skill:
            SysLog::Warning("Inventory", "Skill item categoryID used on cast");
            //return SkillRef::StaticCast( item ).get();
            break;
        case EVEDB::invCategories::Celestial:
            SysLog::Warning("Inventoy", "Celestial item categoryID used on cast");
            //don't know ho to do this but it's missing in a lot of places in the log
            //it says that the return is not of Inventory type
            //return CelestialObjectRef::StaticCast( item ).get();
            break;
        case EVEDB::invCategories::Station:
            SysLog::Warning("Inventory", "Station item categoryID used on cast");
            return StationRef::StaticCast( item ).get();
            break;
        case EVEDB::invCategories::Structure:
            SysLog::Warning("Inventory", "Structure item categoryID used on cast");
            return StructureRef::StaticCast( item ).get();
            break;
        case EVEDB::invCategories::Ship:
            SysLog::Warning("Inventory", "Ship item categoryID used on cast");
            return ShipRef::StaticCast( item ).get();
            break;
    }

    switch( item->groupID() )
    {
        case EVEDB::invGroups::Wreck:
        case EVEDB::invGroups::Secure_Cargo_Container:
        case EVEDB::invGroups::Audit_Log_Secure_Container:
        case EVEDB::invGroups::Cargo_Container:
        case EVEDB::invGroups::Freight_Container:
        case EVEDB::invGroups::Spawn_Container:
            return CargoContainerRef::StaticCast( item ).get();
        case EVEDB::invGroups::Station:
            return StationRef::StaticCast( item ).get();
        case EVEDB::invGroups::Character:
            return CharacterRef::StaticCast( item ).get();
        case EVEDB::invGroups::Solar_System:
            return SolarSystemRef::StaticCast( item ).get();
    }

    // maybe add extra debug info on what for type or item.
    SysLog::Error("Inventory::Cast()", "Item cast not supported for item typeID = %u, groupID = %u, categoryID = %u", item->typeID(), item->groupID(), item->categoryID() );
    return NULL;
}

bool Inventory::LoadContents()
{
    // check if the contents has already been loaded...
    if( !IsStation(this->inventoryID()) )
	{
		if( ContentsLoaded() )
		{
			return true;
		}
	}

    SysLog::Debug("Inventory", "Recursively loading contents of inventory %u", inventoryID() );

    //load the list of items we need
    std::vector<uint32> items;
    if( !GetItems( items ) )
    {
        SysLog::Error("Inventory", "Failed  to get items of %u", inventoryID() );
        return false;
    }

    //Now get each one from the factory (possibly recursing)
    ItemData into;
    uint32 characterID = 0;
    uint32 corporationID = 0;
    uint32 locationID = 0;
    std::vector<uint32>::iterator cur, end;
    cur = items.begin();
    end = items.end();
    for(; cur != end; cur++)
    {
        // Each "cur" item should be checked to see if they are "owned" by the character connected to this client,
        // and if not, then do not "get" the entire contents of this for() loop for that item, except in the case that
        // this item is located in space or belongs to this character's corporation:
        InventoryDB::GetItem( *cur, into );
        if (ItemFactory::GetUsingClient() != NULL)
        {
            characterID = ItemFactory::GetUsingClient()->GetCharacterID();
            corporationID = ItemFactory::GetUsingClient()->GetCorporationID();
            locationID = ItemFactory::GetUsingClient()->GetLocationID();
        }
        else
            SysLog::Error( "Inventory::LoadContents()", "Failed to resolve pointer to Client object currently using the ItemFactory." );
        if( (into.ownerID == characterID) || (characterID == 0) || (into.ownerID == corporationID) )// || (into.locationID == locationID) )
            //    || (ItemFactory::GetUsingClient() == NULL) )
        {
            // Continue to GetItem() if the client calling this is owned by the character that owns this item
            // --OR--
            // The characterID == 0, which means this is attempting to load the character of this client for the first time.
            // --OR--
            // The pointer to the client object currently "using" the ItemFactory is NULL, meaning no client is using it at the moment.
            if (ItemFactory::GetUsingClient() == NULL)
                SysLog::Error( "Inventory::LoadContents()", "WARNING! Loading Contents while ItemFactory::GetUsingClient() returned NULL!" );

            InventoryItemRef i = ItemFactory::GetItem(*cur);
            if( !i )
            {
                SysLog::Error("Inventory::LoadContents()", "Failed to load item %u contained in %u. Skipping.", *cur, inventoryID() );
                continue;
            }

            AddItem( i );
        }
    }

    mContentsLoaded = true;
    return true;
}

void Inventory::DeleteContents()
{
    LoadContents(  );

    std::map<uint32, InventoryItemRef>::iterator cur, end;
    cur = mContents.begin();
    end = mContents.end();
    for(; cur != end; )
    {
        // Our "cur" iterator becomes invalid once RemoveItem
        // for its item is called, so we need to increment it
        // before calling Delete().
        InventoryItemRef i = cur->second;
        cur++;

        i->Delete();
    }

    mContents.clear();
}

CRowSet* Inventory::List( EVEItemFlags _flag, uint32 forOwner ) const
{
    PyList *keywords = new PyList();
    keywords->AddItem(new_tuple(new PyString("stacksize"), new PyToken("util.StackSize")));
    keywords->AddItem(new_tuple(new PyString("singleton"), new PyToken("util.Singleton")));

    DBRowDescriptor* header = new DBRowDescriptor(keywords);
    header->AddColumn( "itemID",     DBTYPE_I8 );
    header->AddColumn( "typeID",     DBTYPE_I4 );
    header->AddColumn( "ownerID",    DBTYPE_I4 );
    header->AddColumn( "locationID", DBTYPE_I8 );
    header->AddColumn( "flagID",     DBTYPE_I2 );
    header->AddColumn( "quantity",   DBTYPE_I4 );
    header->AddColumn( "groupID",    DBTYPE_I2 );
    header->AddColumn( "categoryID", DBTYPE_I4 );
    header->AddColumn( "customInfo", DBTYPE_STR );

    //header->AddColumn( "singleton",  DBTYPE_BOOL );
    //header->AddColumn( "stacksize" , DBTYPE_I4 );

    CRowSet* rowset = new CRowSet( &header );
    List( rowset, _flag, forOwner );
    return rowset;
}

void Inventory::List( CRowSet* into, EVEItemFlags _flag, uint32 forOwner ) const
{
    //there has to be a better way to build this...
    std::map<uint32, InventoryItemRef>::const_iterator cur, end;
    cur = mContents.begin();
    end = mContents.end();
    for(; cur != end; cur++)
    {
        InventoryItemRef i = cur->second;

        if(    ( i->flag() == _flag       || _flag == flagAnywhere )
            && ( i->ownerID() == forOwner || forOwner == 0 ) )
        {
            PyPackedRow* row = into->NewRow();
            i->GetItemRow( row );
        }
    }
}

InventoryItemRef Inventory::FindFirstByFlag(EVEItemFlags _flag) const
{
    std::map<uint32, InventoryItemRef>::const_iterator cur, end;
    cur = mContents.begin();
    end = mContents.end();
    for(; cur != end; cur++)
    {
        if( cur->second->flag() == _flag )
            return cur->second;
    }

    SysLog::Error("Inventory", "unable to find first by flag");
    return InventoryItemRef();
}

InventoryItemRef Inventory::GetByID(uint32 id) const
{
    std::map<uint32, InventoryItemRef>::const_iterator res = mContents.find( id );
    if( res != mContents.end() )
        return res->second;
    else
        return InventoryItemRef();
}

InventoryItemRef Inventory::GetByTypeFlag(uint32 typeID, EVEItemFlags flag) const
{
    std::map<uint32, InventoryItemRef>::const_iterator cur, end;
    cur = mContents.begin();
    end = mContents.end();
    for(; cur != end; cur++)
    {
        if( cur->second->typeID() == typeID
            && cur->second->flag() == flag )
        {
            return cur->second;
        }
    }

    return InventoryItemRef();
}

void Inventory::GetInventoryList(std::map<uint32, InventoryItemRef> &inventory)
{
    std::map<uint32, InventoryItemRef>::const_iterator cur, end;
    cur = mContents.begin();
    end = mContents.end();
    for(; cur != end; cur++)
		inventory.insert(std::pair<uint32, InventoryItemRef>(cur->first,cur->second));
}

uint32 Inventory::FindByFlag(EVEItemFlags _flag, std::vector<InventoryItemRef> &items) const
{
    std::map<uint32, InventoryItemRef>::const_iterator cur, end;
    cur = mContents.begin();
    end = mContents.end();
    for(; cur != end; cur++)
    {
        if (cur->second)
        {
            if(cur->second->flag() == _flag)
            {
                items.push_back( cur->second );
            }
        }
    }
    return items.size();
}

bool Inventory::FindSingleByFlag( EVEItemFlags flag, InventoryItemRef &item ) const
{
    std::map<uint32, InventoryItemRef>::const_iterator cur, end;
    cur = mContents.begin();
    end = mContents.end();
    for(; cur != end; cur++)
    {
        if (cur->second)
        {
            if(cur->second->flag() == flag)
            {
                item = cur->second;
                return true;
            }
        }
    }
    return false;
}

bool Inventory::IsEmptyByFlag( EVEItemFlags flag )
{
    std::map<uint32, InventoryItemRef>::const_iterator cur, end;
    cur = mContents.begin();
    end = mContents.end();
    for(; cur != end; cur++)
    {
        if (cur->second)
        {
            if(cur->second->flag() == flag)
            {
                return false;
            }
        }
    }
    return true;
}

uint32 Inventory::FindByFlagRange(EVEItemFlags low_flag, EVEItemFlags high_flag, std::vector<InventoryItemRef> &items) const
{
    uint32 count = 0;

    std::map<uint32, InventoryItemRef>::const_iterator cur, end;
    cur = mContents.begin();
    end = mContents.end();
    for(; cur != end; cur++)
    {
        if( cur->second->flag() >= low_flag
            && cur->second->flag() <= high_flag )
        {
            items.push_back( cur->second );
            count++;
        }
    }

    return count;
}

uint32 Inventory::FindByFlagSet(std::set<EVEItemFlags> flags, std::vector<InventoryItemRef> &items) const
{
    uint32 count = 0;

    std::map<uint32, InventoryItemRef>::const_iterator cur, end;
    cur = mContents.begin();
    end = mContents.end();
    for(; cur != end; cur++)
    {
        if( flags.find( cur->second->flag() ) != flags.end() )
        {
            items.push_back( cur->second );
            count++;
        }
    }

    return count;
}

void Inventory::AddItem(InventoryItemRef item)
{
    std::map<uint32, InventoryItemRef>::iterator res = mContents.find( item->itemID() );
    if( res == mContents.end() )
    {
        mContents.insert( std::make_pair( item->itemID(), item ) );

        SysLog::Debug("Inventory", "Updated location %u to contain item %u with flag %d.", inventoryID(), item->itemID(), (int)item->flag() );
    }
	else
	{
		//else already here
		SysLog::Debug("Inventory", "unable to updated location %u to contain item %u with flag %d, because it already happend.", inventoryID(), item->itemID(), (int)item->flag() );
	}
}

void Inventory::RemoveItem(InventoryItemRef item)
{
    std::map<uint32, InventoryItemRef>::iterator res = mContents.find( item->itemID() );
    if( res != mContents.end() )
    {
        mContents.erase( res );

        SysLog::Debug("Inventory", "Updated location %u to no longer contain item %u.", inventoryID(), item->itemID() );
    }
	else
	{
		SysLog::Debug("Inventory", "unable to remove %u from %u.", item->itemID(), inventoryID() );
	}
}

void Inventory::StackAll(EVEItemFlags locFlag, uint32 forOwner)
{
    std::vector<InventoryItemRef> toStack;
    for (auto entry : mContents)
    {
        InventoryItemRef item = entry.second;
        // Ignore all singletons and non owned items.
        if (!item->singleton() && (forOwner == 0 || forOwner == item->ownerID()))
        {
            // Not a singleton and belongs to our owner. List it for stacking.
            toStack.push_back(item);
        }
    }
    if (toStack.empty())
    {
        // No stackable items.
        return;
    }

    std::vector<InventoryItemRef>::iterator cur;
    while ((cur = toStack.begin()) != toStack.end())
    {
        InventoryItemRef item = *cur;
        // Remove from waiting to stack list.
        toStack.erase(cur);

        uint32 typeID = item->typeID();
        std::vector<InventoryItemRef> toMerge;
        cur = toStack.begin();
        // Stack this type.
        while (cur != toStack.end())
        {
            InventoryItemRef merge = *cur;
            if (merge->typeID() == typeID)
            {
                // Same type save it to list.
                toMerge.push_back(merge);
                // Remove it from to stack list as it will already be stacked.
                cur = toStack.erase(cur);
            }
            else
            {
                // Not same type, continue searching.
                cur++;
            }
        }
        if (!toMerge.empty())
        {
            // We found other instances of this type.
            std::string itemIDs;
            std::string nItem = " itemID=";
            uint32 stackAmount = 0;
            for (auto merge : toMerge)
            {
                // Add itemID to database condition list.
                itemIDs += nItem + std::string(itoa(merge->itemID()));
                nItem = " OR itemID=";
                // Remove item from container.
                mContents.erase(merge->itemID());
                // Remove item from factory.
                ItemFactory::_DeleteItem(merge->itemID());
                // Get quantity to merge.
                stackAmount += merge->quantity();
                // Issue changes notice to client.
                uint32 ownerID = merge->ownerID();
                std::map<int32, PyRep *> changes;
                changes[ixLocationID] = new PyInt(merge->locationID());
                changes[ixOwnerID] = new PyInt(ownerID);
                // Set new owner and location.
                merge->m_ownerID = 2;
                merge->m_locationID = 6;
                merge->SendItemChange(ownerID, changes); //changes is consumed
            }
            // Alter amount.
            item->AlterQuantity(stackAmount);
            // Remove all entries from database.
            DBerror err;
            if (!DBcore::RunQueryMulti(err, "DELETE FROM srvEntity WHERE %s;"
                                  "DELETE FROM srvEntity_default_attributes WHERE %s;"
                                  "DELETE FROM srvEntity_attributes WHERE %s;",
                                  itemIDs.c_str(), itemIDs.c_str(), itemIDs.c_str()))
            {
                codelog(DATABASE__ERROR, "Failed to delete stacked items %s: %s", itemIDs.c_str(), err.c_str());
            }
        }
    }
}

double Inventory::GetStoredVolume(EVEItemFlags locationFlag) const
{
    //TODO: And implement Sizes for packaged ships

	std::vector<InventoryItemRef> items;
	std::vector<InventoryItemRef>::iterator cur, end;
	items.clear();
	FindByFlag(locationFlag,items);
	cur = items.begin();
	end = items.end();
    EvilNumber totalVolume(0.0);
	for(; cur != end; cur++)
        totalVolume += ((*cur)->getAttribute(AttrVolume) * (*cur)->quantity());

    // this is crap... bleh... as it should return a EvilNumber
    return totalVolume.get_float();
}

/*
 * InventoryEx
 */
bool InventoryEx::ValidateAddItem(EVEItemFlags flag, InventoryItemRef item) const
{
    //double volume = item->quantity() * item->volume();
    double volume = item->quantity() * item->getAttribute(AttrVolume).get_float();
    double capacity = GetRemainingCapacity( flag );
    if( volume > capacity )
    {
        std::map<std::string, PyRep *> args;

        args["available"] = new PyFloat( capacity );
        args["volume"] = new PyFloat(volume);

        throw PyException(MakeUserError("NotEnoughCargoSpace", args));
        return false;
    }
    return true;
}
