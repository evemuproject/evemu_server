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
    Author:     Zhur, Captnoord
*/

#include "eve-server.h"

#include "PyServiceCD.h"
#include "inventory/InventoryBound.h"

PyCallable_Make_InnerDispatcher(InventoryBound)

InventoryBound::InventoryBound( PyServiceMgr *mgr, Inventory &inventory, EVEItemFlags flag)
: PyBoundObject(mgr),
  m_dispatch(new Dispatcher(this)),
  mInventory(inventory),
  mFlag(flag)
{
    _SetCallDispatcher(m_dispatch);

    m_strBoundObjectName = "InventoryBound";

    PyCallable_REG_CALL(InventoryBound, List)
    PyCallable_REG_CALL(InventoryBound, Add)
    PyCallable_REG_CALL(InventoryBound, MultiAdd)
    PyCallable_REG_CALL(InventoryBound, GetItem)
    PyCallable_REG_CALL(InventoryBound, ListStations)
    PyCallable_REG_CALL(InventoryBound, ReplaceCharges)
    PyCallable_REG_CALL(InventoryBound, MultiMerge)
    PyCallable_REG_CALL(InventoryBound, StackAll)
    PyCallable_REG_CALL(InventoryBound, StripFitting)
    PyCallable_REG_CALL(InventoryBound, DestroyFitting)
    PyCallable_REG_CALL(InventoryBound, SetPassword)
    PyCallable_REG_CALL(InventoryBound, CreateBookmarkVouchers)
    PyCallable_REG_CALL(InventoryBound, Voucher)
}

InventoryBound::~InventoryBound()
{
    delete m_dispatch;
}

PyResult InventoryBound::Handle_List(PyCallArgs &call) {
    //TODO: check to make sure we are allowed to list this inventory
    return mInventory.List( mFlag, call.client->GetCharacterID() );
}

PyResult InventoryBound::Handle_ReplaceCharges(PyCallArgs &call) {
    Inventory_CallReplaceCharges args;
    if(!args.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Unable to decode arguments");
        return NULL;
    }

    //validate flag.
    if(args.flag < flagSlotFirst || args.flag > flagSlotLast) {
        codelog(SERVICE__ERROR, "%s: Invalid flag %d", call.client->GetName(), args.flag);
        return NULL;
    }

    // returns new ref
    InventoryItemRef new_charge = mInventory.GetByID( args.itemID );
    if( !new_charge ) {
        codelog(SERVICE__ERROR, "%s: Unable to find charge %d", call.client->GetName(), args.itemID);
        return NULL;
    }

    if(new_charge->ownerID() != call.client->GetCharacterID()) {
        codelog(SERVICE__ERROR, "Character %u tried to load charge %u of character %u.", call.client->GetCharacterID(), new_charge->itemID(), new_charge->ownerID());
        return NULL;
    }

    if(new_charge->quantity() < (uint32)args.quantity) {
        codelog(SERVICE__ERROR, "%s: Item %u: Requested quantity (%d) exceeds actual quantity (%d), using actual.", call.client->GetName(), args.itemID, args.quantity, new_charge->quantity());
    } else if(new_charge->quantity() > (uint32)args.quantity) {
        new_charge = new_charge->Split(args.quantity);  // split item
        if( !new_charge ) {
            codelog(SERVICE__ERROR, "%s: Unable to split charge %d into %d", call.client->GetName(), args.itemID, args.quantity);
            return NULL;
        }
    }

    // new ref is consumed, we don't release it
    call.client->GetShip()->ReplaceCharges( (EVEItemFlags) args.flag, (InventoryItemRef)new_charge );

    return(new PyInt(1));
}


PyResult InventoryBound::Handle_ListStations( PyCallArgs& call )
{
    sLog.Debug( "InventoryBound", "Called ListStations stub." );

    util_Rowset rowset;

    rowset.header.push_back( "stationID" );
    rowset.header.push_back( "itemCount" );

    return rowset.Encode();
}

PyResult InventoryBound::Handle_GetItem(PyCallArgs &call) {
    return mInventory.GetItem();
}

PyResult InventoryBound::Handle_Add(PyCallArgs &call) {
    if( call.tuple->items.size() == 3 )
    {
        // TODO: Add comments here to describe what kind of client action results in having
        // to use the 'Call_Add_3' packet structure
		sLog.Debug( "InventoryBound::Handle_Add()", "Action decoded as Call_Add_3 occurred." );
        Call_Add_3 args;
        if(!args.Decode(&call.tuple)) {
            codelog(SERVICE__ERROR, "Unable to decode arguments from '%s'", call.client->GetName());
            return NULL;
        }

        std::vector<int32> items;
        items.push_back(args.itemID);

        return _ExecAdd( call.client, items, args.quantity, (EVEItemFlags)args.flag );
    }
    else if( call.tuple->items.size() == 2 )
    {
        // TODO: Add comments here to describe what kind of client action results in having
        // to use the 'Call_Add_2' packet structure
        // * Moving cargo items from ship cargo bay to a container in space goes here
        // * Qty missing, so query it from the itemRef
		sLog.Debug( "InventoryBound::Handle_Add()", "Action decoded as Call_Add_2 occurred." );
        Call_Add_2 args;
        //chances are its trying to transfer into a cargo container
        if(!args.Decode(&call.tuple))
        {
            codelog(SERVICE__ERROR, "Unable to decode arguments from '%s'", call.client->GetName());
            return NULL;
        }

        uint32 flag = 0;
        if( call.byname.find("flag") == call.byname.end() )
        {
            sLog.Debug( "InventoryBound::Handle_Add()", "Cannot find key 'flag' from call.byname dictionary." );
			if( IsStation(call.client->GetLocationID()) )
				flag = flagHangar;
			else
				flag = flagCargoHold;    // hard-code this since ship cargo to cargo container move flag since key 'flag' in client.byname does not exist
        }
        else
            flag = call.byname.find("flag")->second->AsInt()->value();

        uint32 quantity = 0;
        if( call.byname.find("qty") == call.byname.end() )
        {
            quantity = 0;   // Auto quantity - force _ExecAdd() to use quantity of the item
        }
        else
        {
            if( call.byname.find("qty")->second->IsNone() )
                quantity = 0;
            else
                quantity = call.byname.find("qty")->second->AsInt()->value();
        }

        std::vector<int32> items;
        items.push_back(args.itemID);

        return _ExecAdd( call.client, items, quantity, (EVEItemFlags)flag );
    }
    else if( call.tuple->items.size() == 1 )
    {
        // TODO: Add comments here to describe what kind of client action results in having
        // to use the 'Call_SingleIntegerArg' packet structure
		sLog.Debug( "InventoryBound::Handle_Add()", "Action decoded as Call_SingleIntegerArg occurred." );
        Call_SingleIntegerArg arg;
        if( !arg.Decode( &call.tuple ) )
        {
            codelog( SERVICE__ERROR, "Failed to decode arguments from '%s'.", call.client->GetName() );
            return NULL;
        }

        std::vector<int32> items;
        items.push_back( arg.arg );

        // no quantity given, pass 0 quantity so it assumes all.
        return _ExecAdd( call.client, items, 0, mFlag );
    }
    else
    {
        codelog( SERVICE__ERROR, "[Add] Unknown number of elements in a tuple: %lu.", call.tuple->items.size() );
        return NULL;
    }
}

PyResult InventoryBound::Handle_MultiAdd(PyCallArgs &call) {

    ShipRef ship = call.client->GetShip();
    uint32 typeID;
    uint32 powerSlot;
    uint32 useableSlot;

    if( call.tuple->items.size() == 3 )
    {
        // TODO: Add comments here to describe what kind of client action results in having
        // to use the 'Call_MultiAdd_3' packet structure
		sLog.Debug( "InventoryBound::Handle_MultiAdd()", "Action decoded as Call_MultiAdd_3 occurred." );
        Call_MultiAdd_3 args;
        if(!args.Decode(&call.tuple)) {
            codelog(SERVICE__ERROR, "Unable to decode arguments");
            return NULL;
        }

        if((EVEItemFlags)args.flag == 0 )
        {

            //Get Item TypeID - this is bad
            InventoryDB::GetTypeID(args.itemIDs[0], typeID);

            //Get Range of slots for item
            InventoryDB::GetModulePowerSlotByTypeID(typeID, powerSlot);

            //Get open slots available on ship
            InventoryDB::GetOpenPowerSlots(powerSlot,ship , useableSlot);

            //Set item flag to first useable open slot found
            args.flag = useableSlot;

        }

        //NOTE: They can specify "None" in the quantity field to indicate
        //their intention to move all... we turn this into a 0 for simplicity.

        return _ExecAdd( call.client, args.itemIDs, args.quantity, (EVEItemFlags)args.flag );
    }
    else if( call.tuple->items.size() == 2 )
    {
        // TODO: Add comments here to describe what kind of client action results in having
        // to use the 'Call_MultiAdd_2' packet structure
		sLog.Debug( "InventoryBound::Handle_MultiAdd()", "Action decoded as Call_MultiAdd_2 occurred" );
        Call_MultiAdd_2 args;
        if(!args.Decode(&call.tuple)) {
            codelog(SERVICE__ERROR, "Unable to decode arguments");
            return NULL;
        }

		uint32 flag = 0;
		if( call.byname.find("flag") == call.byname.end() )
		{
			sLog.Debug( "InventoryBound::Handle_MultiAdd()", "Cannot find key 'flag' from call.byname dictionary." );
			flag = flagCargoHold;    // hard-code this since ship cargo to cargo container move flag since key 'flag' in client.byname does not exist
		}
		else
			flag = call.byname.find("flag")->second->AsInt()->value();

        // no quantity given, set to zero so _ExecAdd() checks quantity:
        return _ExecAdd( call.client, args.itemIDs, 0, (EVEItemFlags)flag );
    }
    else if( call.tuple->items.size() == 1 )
    {
        // TODO: Add comments here to describe what kind of client action results in having
        // to use the 'Call_SingleIntList' packet structure
		sLog.Debug( "InventoryBound::Handle_MultiAdd()", "Action decoded as Call_SingleIntList occurred." );
        Call_SingleIntList args;
        if(!args.Decode(&call.tuple)) {
            codelog(SERVICE__ERROR, "Unable to decode arguments");
            return NULL;
        }

        // no quantity given, assume 1
        return _ExecAdd( call.client, args.ints, 1, mFlag );
    }
    else
    {
        codelog( SERVICE__ERROR, "[MultiAdd] Unknown number of elements in a tuple: %lu.", call.tuple->items.size() );
        return NULL;
    }
}

PyResult InventoryBound::Handle_MultiMerge(PyCallArgs &call) {
    //Decode Args
    Inventory_CallMultiMerge elements;

    if(!elements.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Unable to decode elements");
        return NULL;
    }

    Inventory_CallMultiMergeElement element;

    std::vector<PyRep *>::const_iterator cur, end;
    cur = elements.MMElements->begin();
    end = elements.MMElements->end();
    for (; cur != end; cur++) {
        if(!element.Decode( *cur )) {
            codelog(SERVICE__ERROR, "Unable to decode element. Skipping.");
            continue;
        }

        InventoryItemRef stationaryItem = m_manager->item_factory.GetItem( element.stationaryItemID );
        if( !stationaryItem ) {
            _log(SERVICE__ERROR, "Failed to load stationary item %u. Skipping.", element.stationaryItemID);
            continue;
        }

        InventoryItemRef draggedItem = m_manager->item_factory.GetItem( element.draggedItemID );
        if( !draggedItem ) {
            _log(SERVICE__ERROR, "Failed to load dragged item %u. Skipping.", element.draggedItemID);
            continue;
        }

		draggedItem->SetFlag(stationaryItem->flag());	// Set dragged item's flag to the stationary item's flag so merge can complete
        stationaryItem->Merge( (InventoryItemRef)draggedItem, element.draggedQty );
    }

    return NULL;
}

PyResult InventoryBound::Handle_StackAll(PyCallArgs &call) {
    EVEItemFlags stackFlag = mFlag;

    if(call.tuple->items.size() != 0) {
        Call_SingleIntegerArg arg;
        if(!arg.Decode(&call.tuple)) {
            _log(SERVICE__ERROR, "Failed to decode args.");
            return NULL;
        }

        stackFlag = (EVEItemFlags)arg.arg;
    }

    //Stack Items contained in this inventory
    mInventory.StackAll(stackFlag, call.client->GetCharacterID());

    return NULL;
}

PyResult InventoryBound::Handle_StripFitting(PyCallArgs &call) {
    sLog.Debug("Server", "Called StripFitting Stub.");

    return NULL;
}

PyResult InventoryBound::Handle_DestroyFitting(PyCallArgs &call) {

    sLog.Debug("InventoryBound","Called DestroyFittings stub");

    Call_SingleIntegerArg args;
    if(!args.Decode(&call.tuple)){
        sLog.Error("Destroy Fittings","Failed to decode args.");
    }

    //get the actual item
    InventoryItemRef item = m_manager->item_factory.GetItem(args.arg);

    //remove the rig effects from the ship
    call.client->GetShip()->RemoveRig(item, mInventory.inventoryID());

    //move the item to the void or w/e
    call.client->MoveItem(item->itemID(), mInventory.inventoryID(), flagAutoFit);

    //delete the item
    item->Delete();

    return NULL;
}

PyResult InventoryBound::Handle_SetPassword(PyCallArgs &call) {
    // TODO
    uint32 item = 0;
    item++;

    return NULL;
}

PyResult InventoryBound::Handle_CreateBookmarkVouchers(PyCallArgs &call)
{
    PyList *list = call.tuple->GetItem( 0 )->AsList();
    uint8 i;
    uint32 bookmarkID;
    char ci[3];

    DBQueryResult res;
    DBResultRow row;

    if( list->size() > 0 ) {
        for(i=0; i<(list->size()); i++) {
            bookmarkID = call.tuple->GetItem( 0 )->AsList()->GetItem(i)->AsInt()->value();
                            //ItemData ( typeID, ownerID, locationID, flag, quantity, customInfo, contraband)
            ItemData itemBookmarkVoucher( 51, call.client->GetCharacterID(), call.client->GetLocationID(), flagHangar, 1 );
            InventoryItemRef i = m_manager->item_factory.SpawnItem( itemBookmarkVoucher );

            if( !i ) {
                codelog(CLIENT__ERROR, "%s: Failed to spawn bookmark voucher for %u", call.client->GetName(), bookmarkID);
                break;
            }
            sDatabase.RunQuery(res, "SELECT memo FROM bookmarks WHERE bookmarkID = %u", bookmarkID);
            res.GetRow(row);
            i->Rename(row.GetText(0));
            snprintf(ci, sizeof(ci), "%u", bookmarkID);
            i->SetCustomInfo(ci);  //<- use this to set bookmarkID to DB.entity.customInfo
        }
        sLog.Log( "InventoryBound::Handle_CreateBookmarkVouchers()", "%u Vouchers created", list->size() );
        //  when bm is copied to another players places tab, copy data from db using bookmarkID stored in ItemData.customInfo
     } else {
        sLog.Error( "InventoryBound::Handle_CreateBookmarkVouchers()", "%s: call.tuple->GetItem( 0 )->AsList()->size() == 0.  Expected size > 0.", call.client->GetName() );
        return NULL;
     }

     //  NOTE: need to put check in here for isMove bool.  true=remove from PnP->bookmarks tab....false = leave

     //  NOTE: need to reload hangar to show newly created BM item.

     return new PyInt( 0 );
}

PyResult InventoryBound::Handle_Voucher(PyCallArgs &call){
    return NULL;
}

PyRep *InventoryBound::_ExecAdd(Client *c, const std::vector<int32> &items, uint32 quantity, EVEItemFlags flag) {
    //If were here, we can try move all the items (validated)

    std::vector<int32>::const_iterator cur, end;
    cur = items.begin();
    end = items.end();
    for(; cur != end; cur++) {
        InventoryItemRef sourceItem = m_manager->item_factory.GetItem( *cur );
        if( !sourceItem ) {
            sLog.Error("_ExecAdd","Failed to load item %u. Skipping.", *cur);
            continue;
        }

        //Get old position
        EVEItemFlags old_flag = sourceItem->flag();

        //NOTE: a multi add can come in with quantity 0 to indicate "all"
        if( quantity == 0 )
            quantity = sourceItem->quantity();

        /*Check if its a simple item move or an item split qty is diff if its a
        split also multiple items cannot be split so the size() should be 1*/
        if( quantity != sourceItem->quantity() && items.size() == 1 )
        {
            InventoryItemRef newItem = sourceItem->Split(quantity);
            if( !newItem ) {
                sLog.Error("_ExecAdd", "Error splitting item %u. Skipping.", sourceItem->itemID() );
            }
            else
            {
                // Unlike the other validate item requests, fitting an item requires a skill check, which means passing the character
                // (This also allows for flagAutoFit when someone drags a module or a stack of modules onto the middle of the fitting
                // window and NOT onto a specific slot.  'flagAutoFit' means "put this module into which ever slot makes sense")
                if( (flag == flagAutoFit) )
                {
					sLog.Error( "InventoryBound::_ExecAdd()", "ERROR: handling adding modules where flag = flagAutoFit not yet supported!!!" );
					EVEItemFlags newFlag = (EVEItemFlags)(c->GetShip()->FindAvailableModuleSlot( newItem ));
					if( newFlag == flagIllegal )
					{
						sLog.Error( "InventoryBound::_ExecAdd()", "ERROR: Attempt to auto-fit module failed!  'flagIllegal' returned from FindAvailableModuleSlot()" );
						return NULL;
					}
					else
					{
						c->GetShip()->AddItem( newFlag, newItem );
						flag = newFlag;
					}
                }
                else if( (flag >= flagLowSlot0 && flag <= flagHiSlot7) || (flag >= flagRigSlot0 && flag <= flagRigSlot7) )
                {
                    c->GetShip()->AddItem( flag, newItem );
                }
				else if(
							flag == flagCargoHold
							|| flag == flagDroneBay
							|| flag == flagSpecializedFuelBay
							|| flag == flagSpecializedOreHold
							|| flag == flagSpecializedGasHold
							|| flag == flagSpecializedMineralHold
							|| flag == flagSpecializedSalvageHold
							|| flag == flagSpecializedShipHold
							|| flag == flagSpecializedSmallShipHold
							|| flag == flagSpecializedLargeShipHold
							|| flag == flagSpecializedIndustrialShipHold
							|| flag == flagSpecializedAmmoHold )
				{
					c->GetShip()->ValidateAddItem( flag, newItem );
				}
                else
                {
                    mInventory.ValidateAddItem( flag, newItem );
                }

                if(old_flag >= flagLowSlot0 && old_flag <= flagHiSlot7)
                {

                    c->GetShip()->RemoveItem( newItem, mInventory.inventoryID(), flag );

                    //Create new item id return result
                    Call_SingleIntegerArg result;
                    result.arg = newItem->itemID();

                    //Return new item result
                    return result.Encode();

                }
				else if(old_flag >= flagRigSlot0 && old_flag <= flagRigSlot7) {

                    c->GetShip()->RemoveRig( newItem, mInventory.inventoryID() );

                }
				else
				{

                    //Move New item to its new location
                    c->MoveItem(newItem->itemID(), mInventory.inventoryID(), flag); // properly refresh mModulesMgr

                    //Create new item id return result
                    Call_SingleIntegerArg result;
                    result.arg = newItem->itemID();

                    //Return new item result
                    return result.Encode();
                }
            }
        }
        else
        {
			// If item being added is a module going into flag slot flagAutoFit or a specified slot, check to see if it's a stack being dragged
			// into the fitting window and split the stack to only take out and fit one from the stack:
			if ((flag == flagAutoFit) || ((flag >= flagLowSlot0 && flag <= flagHiSlot7) || (flag >= flagRigSlot0 && flag <= flagRigSlot7)))
				if (sourceItem->quantity() > 1)
					InventoryItemRef newItem = sourceItem->Split(sourceItem->quantity()-1);

			// Unlike the other validate item requests, fitting an item requires a skill check
			// (This handles modules being moved from one slot to another slot within the same bank on the same ship)
            // (This also allows for flagAutoFit when someone drags a module or a stack of modules onto the middle of the fitting
            // window and NOT onto a specific slot.  'flagAutoFit' means "put this module into which ever slot makes sense")
            if( (flag == flagAutoFit) )
            {
                sLog.Error( "InventoryBound::_ExecAdd()", "ERROR: handling adding modules where flag = flagAutoFit not yet supported!!!" );
                EVEItemFlags newFlag = (EVEItemFlags)(c->GetShip()->FindAvailableModuleSlot( sourceItem ));
                if( newFlag == flagIllegal )
				{
					sLog.Error( "InventoryBound::_ExecAdd()", "ERROR: Attempt to auto-fit module failed!  'flagIllegal' returned from FindAvailableModuleSlot()" );
					return NULL;
				}
				else
				{
					c->GetShip()->AddItem( newFlag, sourceItem );
					flag = newFlag;
				}
            }
            else if( (flag >= flagLowSlot0 && flag <= flagHiSlot7) || (flag >= flagRigSlot0 && flag <= flagRigSlot7) )
            {
				// Check to see if old_flag is from this ship:
				if ( (old_flag >= flagLowSlot0 && old_flag <= flagHiSlot7) || (old_flag >= flagRigSlot0 && old_flag <= flagRigSlot7) )
					// old_flag IS from this ship, so first remove module to current bound inventory before adding it to a different slot:
					// (warning! this may have problems with item inventories other than station items, but only if bound inventory is not being updated)
					c->GetShip()->RemoveItem( sourceItem, mInventory.inventoryID(), flag );

				c->GetShip()->AddItem( flag, sourceItem );
            }
			else if(
						flag == flagCargoHold
						|| flag == flagDroneBay
						|| flag == flagSpecializedFuelBay
						|| flag == flagSpecializedOreHold
						|| flag == flagSpecializedGasHold
						|| flag == flagSpecializedMineralHold
						|| flag == flagSpecializedSalvageHold
						|| flag == flagSpecializedShipHold
						|| flag == flagSpecializedSmallShipHold
						|| flag == flagSpecializedLargeShipHold
						|| flag == flagSpecializedIndustrialShipHold
						|| flag == flagSpecializedAmmoHold )
			{
				c->GetShip()->ValidateAddItem( flag, sourceItem );
			}
			else
            {
                mInventory.ValidateAddItem( flag, sourceItem );
            }

            if(old_flag >= flagLowSlot0 && old_flag <= flagHiSlot7)
            {
				if( !((flag >= flagLowSlot0 && flag <= flagHiSlot7) || (flag >= flagRigSlot0 && flag <= flagRigSlot7)) )
	                c->GetShip()->RemoveItem( sourceItem, mInventory.inventoryID(), flag );
            }
            else if(old_flag >= flagRigSlot0 && old_flag <= flagRigSlot7)
            {
				if( !((flag >= flagLowSlot0 && flag <= flagHiSlot7) || (flag >= flagRigSlot0 && flag <= flagRigSlot7)) )
	                //remove the rig
		            c->GetShip()->RemoveRig(sourceItem, mInventory.inventoryID());
            }
			else if( old_flag == flagCargoHold
						|| old_flag == flagDroneBay
						|| old_flag == flagSpecializedFuelBay
						|| old_flag == flagSpecializedOreHold
						|| old_flag == flagSpecializedGasHold
						|| old_flag == flagSpecializedMineralHold
						|| old_flag == flagSpecializedSalvageHold
						|| old_flag == flagSpecializedShipHold
						|| old_flag == flagSpecializedSmallShipHold
						|| old_flag == flagSpecializedLargeShipHold
						|| old_flag == flagSpecializedIndustrialShipHold
						|| old_flag == flagSpecializedAmmoHold )
			{
				if( !((flag >= flagLowSlot0 && flag <= flagHiSlot7) || (flag >= flagRigSlot0 && flag <= flagRigSlot7)) )
	                c->GetShip()->RemoveItem( sourceItem, mInventory.inventoryID(), flag );
			}
            else
            {
                c->MoveItem(sourceItem->itemID(), mInventory.inventoryID(), flag);
            }
        }

        //update modules
        c->GetShip()->UpdateModules();
    }

    //Return Null if no item was created
    return NULL;
}
