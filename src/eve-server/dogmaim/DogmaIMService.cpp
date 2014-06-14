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
    Author:        Zhur
*/

#include "eve-server.h"

#include "PyBoundObject.h"
#include "PyServiceCD.h"
#include "cache/ObjCacheService.h"
#include "dogmaim/DogmaIMService.h"
#include "ship/modules/Modules.h"
#include "system/SystemManager.h"

class DogmaIMBound
: public PyBoundObject
{
public:
    PyCallable_Make_Dispatcher(DogmaIMBound)

    DogmaIMBound(PyServiceMgr *mgr)
    : PyBoundObject(mgr),
      m_dispatch(new Dispatcher(this))
    {
        _SetCallDispatcher(m_dispatch);

        m_strBoundObjectName = "DogmaIMBound";

        PyCallable_REG_CALL(DogmaIMBound, ShipGetInfo)
        PyCallable_REG_CALL(DogmaIMBound, CharGetInfo)
        PyCallable_REG_CALL(DogmaIMBound, ItemGetInfo)
		PyCallable_REG_CALL(DogmaIMBound, GetAllInfo)
		PyCallable_REG_CALL(DogmaIMBound, GetLocationInfo)
        PyCallable_REG_CALL(DogmaIMBound, GetTargets)
        PyCallable_REG_CALL(DogmaIMBound, GetTargeters)
		PyCallable_REG_CALL(DogmaIMBound, GetWeaponBankInfoForShip)
        PyCallable_REG_CALL(DogmaIMBound, GetCharacterBaseAttributes)
		PyCallable_REG_CALL(DogmaIMBound, CheckSendLocationInfo)
        PyCallable_REG_CALL(DogmaIMBound, Activate)
        PyCallable_REG_CALL(DogmaIMBound, Deactivate)
		PyCallable_REG_CALL(DogmaIMBound, Overload)
        PyCallable_REG_CALL(DogmaIMBound, CancelOverloading)
		PyCallable_REG_CALL(DogmaIMBound, SetModuleOnline)
		PyCallable_REG_CALL(DogmaIMBound, TakeModuleOffline)
		PyCallable_REG_CALL(DogmaIMBound, LoadAmmoToBank)
        PyCallable_REG_CALL(DogmaIMBound, AddTarget)
        PyCallable_REG_CALL(DogmaIMBound, RemoveTarget)
        PyCallable_REG_CALL(DogmaIMBound, ClearTargets)
    }
    virtual ~DogmaIMBound() {delete m_dispatch;}
    virtual void Release() {
        //I hate this statement
        delete this;
    }

    PyCallable_DECL_CALL(ShipGetInfo)
    PyCallable_DECL_CALL(CharGetInfo)
    PyCallable_DECL_CALL(ItemGetInfo)
	PyCallable_DECL_CALL(GetAllInfo)
	PyCallable_DECL_CALL(GetWeaponBankInfoForShip)
    PyCallable_DECL_CALL(GetLocationInfo)
    PyCallable_DECL_CALL(GetCharacterBaseAttributes)
    PyCallable_DECL_CALL(GetTargets)
    PyCallable_DECL_CALL(GetTargeters)
	PyCallable_DECL_CALL(CheckSendLocationInfo)
    PyCallable_DECL_CALL(Activate)
    PyCallable_DECL_CALL(Deactivate)
	PyCallable_DECL_CALL(Overload)
    PyCallable_DECL_CALL(CancelOverloading)
	PyCallable_DECL_CALL(SetModuleOnline)
	PyCallable_DECL_CALL(TakeModuleOffline)
	PyCallable_DECL_CALL(LoadAmmoToBank)
    PyCallable_DECL_CALL(AddTarget)
    PyCallable_DECL_CALL(RemoveTarget)
    PyCallable_DECL_CALL(ClearTargets)
    
    

protected:
    Dispatcher *const m_dispatch;
};

PyCallable_Make_InnerDispatcher(DogmaIMService)

DogmaIMService::DogmaIMService(PyServiceMgr *mgr)
: PyService(mgr, "dogmaIM"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(DogmaIMService, GetAttributeTypes)
}

DogmaIMService::~DogmaIMService() {
    delete m_dispatch;
}

PyBoundObject *DogmaIMService::_CreateBoundObject(Client *c, const PyRep *bind_args) {
    _log(CLIENT__MESSAGE, "DogmaIMService bind request for:");
    bind_args->Dump(CLIENT__MESSAGE, "    ");

    return(new DogmaIMBound(m_manager));
}

PyResult DogmaIMService::Handle_GetAttributeTypes(PyCallArgs &call) {
    PyString* str = new PyString( "dogmaIM.attributesByName" );
    PyRep* result = m_manager->cache_service->GetCacheHint( str );
    PyDecRef( str );

    return result;
}

PyResult DogmaIMBound::Handle_GetCharacterBaseAttributes(PyCallArgs &call)
{
    CharacterRef cref = call.client->GetChar();

    PyDict* result = new PyDict();
    result->SetItem(new PyInt(AttrIntelligence), new PyInt(static_cast<int32>(cref->GetAttribute(AttrIntelligence).get_int())));
    result->SetItem(new PyInt(AttrPerception), new PyInt(static_cast<int32>(cref->GetAttribute(AttrPerception).get_int())));
    result->SetItem(new PyInt(AttrCharisma), new PyInt(static_cast<int32>(cref->GetAttribute(AttrCharisma).get_int())));
    result->SetItem(new PyInt(AttrWillpower), new PyInt(static_cast<int32>(cref->GetAttribute(AttrWillpower).get_int())));
    result->SetItem(new PyInt(AttrMemory), new PyInt(static_cast<int32>(cref->GetAttribute(AttrMemory).get_int())));

    return result;
}

PyResult DogmaIMBound::Handle_GetLocationInfo(PyCallArgs &call)
{
    // no arguments

    // dummy right now, don't have any meaningful packet logs
    return new PyDict();
}

PyResult DogmaIMBound::Handle_ShipGetInfo(PyCallArgs &call) {
    //takes no arguments

    /*PyObject *result = call.client->GetShip()->ShipGetInfo();
    if(result == NULL) {
        codelog(SERVICE__ERROR, "Unable to build ship info for ship %u", call.client->GetShipID());
        return NULL;
    }

    return result;*/
    return new PyNone;
}

PyResult DogmaIMBound::Handle_ItemGetInfo(PyCallArgs &call) {
    Call_SingleIntegerArg args;
    if(!args.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Failed to decode arguments");
        return NULL;
    }

    InventoryItemRef item = m_manager->item_factory.GetItem( args.arg );
    if( !item ) {
        codelog(SERVICE__ERROR, "Unable to load item %u", args.arg);
        return NULL;
    }

    return item->ItemGetInfo();
}

PyResult DogmaIMBound::Handle_CharGetInfo(PyCallArgs &call) {
    //no arguments

    /*PyObject *result = call.client->GetChar()->CharGetInfo();
    if(result == NULL) {
        codelog(SERVICE__ERROR, "Unable to build char info for char %u", call.client->GetCharacterID());
        return NULL;
    }

    return result;
    */
    return new PyNone;
}

PyResult DogmaIMBound::Handle_CheckSendLocationInfo( PyCallArgs& call )
{
    //no arguments

    sLog.Debug( "DogmaIMBound", "Called CheckSendLocationInfo stub." );

    return new PyNone;
}

PyResult DogmaIMBound::Handle_GetTargets(PyCallArgs &call) {
    //no arguments
    return call.client->targets.GetTargets();
}

PyResult DogmaIMBound::Handle_GetTargeters(PyCallArgs &call) {
    //no arguments
    return call.client->targets.GetTargeters();
}


PyResult DogmaIMBound::Handle_SetModuleOnline( PyCallArgs& call ) {
	Call_TwoIntegerArgs args; //locationID, moduleID
	
	if( !args.Decode( &call.tuple ) )
    {
        codelog( SERVICE__ERROR, "Unable to decode arguments from '%s'", call.client->GetName() );
        return NULL;
    }

	call.client->GetShip()->Online(args.arg2);

	return NULL;
}

PyResult DogmaIMBound::Handle_TakeModuleOffline( PyCallArgs& call ) {
	Call_TwoIntegerArgs args; //locationID, moduleID
	
	if( !args.Decode( &call.tuple ) )
    {
        codelog( SERVICE__ERROR, "Unable to decode arguments from '%s'", call.client->GetName() );
        return NULL;
    }

	call.client->GetShip()->Offline(args.arg2);

	return NULL;
}

PyResult DogmaIMBound::Handle_LoadAmmoToBank( PyCallArgs& call ) {
	Call_Dogma_LoadAmmoToBank args;
	
	if( !args.Decode( &call.tuple ) )
    {
        codelog( SERVICE__ERROR, "Unable to decode arguments from '%s'", call.client->GetName() );
        return NULL;
    }

	// NOTES:
	// args.chargeList will contain one or more entries, each of which is an itemID of a charge or stack of charges
	// presumably, this list allows the player to select more than one stack of exact same ammo and drag whole selection
	// onto the module to be loaded into it; then what can be loaded is, and a single stack of the remainder quantity is
	// created and returned to the inventory the original selection of charges was pulled from.
	// -- this still must be fully confirmed by testing on hybrid or projectile turrets or missile batteries

	// WARNING!  Initial Implementation ONLY handles the FIRST entry in the args.chargeList,
	// which is basically supporting only single charge stacks applied to module!

	// Get Reference to Ship, Module, and Charge
	ShipRef shipRef = call.client->GetShip();
	InventoryItemRef moduleRef = shipRef->GetModule(args.moduleItemID);
	if( moduleRef == NULL )
	{
		sLog.Error("DogmaIMBound::Handle_LoadAmmoToBank()", "ERROR: cannot find module into which charge should be loaded!  How did we get here!?!?!" );
		return NULL;
	}
	EVEItemFlags moduleFlag = moduleRef->flag();
	InventoryItemRef chargeRef;

	if( !(args.chargeList.empty()) )
		chargeRef = m_manager->item_factory.GetItem(args.chargeList.at(0));

	// Move Charge into Ship's Inventory and change the Charge's flag to match flag of Module
	uint32 loadedChargeID = shipRef->AddItem( moduleFlag, chargeRef );
	//call.client->MoveItem(chargeRef->itemID(), call.client->GetShipID(), moduleFlag);

    //Create new item id return result
	if( loadedChargeID )
	{
		Call_SingleIntegerArg result;
		result.arg = loadedChargeID;	//chargeRef->itemID();
		//Return new item result
		return result.Encode();
	}

	return NULL;
}

PyResult DogmaIMBound::Handle_Activate( PyCallArgs& call )
{
    Call_Dogma_Activate args;
    uint32 callTupleSize = call.tuple->size();
    uint32 itemID = 0;
    uint32 effect = 0;

    if( callTupleSize == 2 )
    {
        // This call is for Anchor/Unanchor a POS structure or Cargo Container,
        // so get the new flag value and change the item referenced:
        if( call.tuple->items.at( 0 )->IsInt() )
        {
            itemID = call.tuple->items.at( 0 )->AsInt()->value();

            if( call.tuple->items.at( 1 )->IsInt() )
            {
                effect = call.tuple->items.at( 1 )->AsInt()->value();

                SystemEntity * se = call.client->System()->get( itemID );

                if( se == NULL )
                {
                    sLog.Error( "DogmaIMBound::Handle_Activate()", "Item ID = %u is not a valid SystemEntity found in this system.", itemID );
                    return NULL;
                }

                // TODO: somehow notify client with one of these effects:
                // 1) effectAnchorDrop for effect = 649
                // 2) effectAnchorDropForStructures = 1022
                // 3) effectAnchorLift = 650
                // 4) effectAnchorLiftForStructures = 1023

                // Send notification SFX appropriate effect for the value effect value supplied:
                switch( effect )
                {
                    case 649:
                        //call.client->Destiny()->SendContainerUnanchor( call.client->services().item_factory.GetCargoContainer( itemID ) );
                        break;
                    case 1022:
                        //call.client->Destiny()->SendStructureUnanchor( call.client->services().item_factory.GetStructure( itemID ) );
                        break;
                    case 650:
                        //call.client->Destiny()->SendContainerAnchor( call.client->services().item_factory.GetCargoContainer( itemID ) );
                        break;
                    case 1023:
                        //call.client->Destiny()->SendStructureAnchor( call.client->services().item_factory.GetStructure( itemID ) );
                        break;
                    default:
                        break;
                }

                return new PyInt( 1 );
            }
            else
            {
                sLog.Error( "DogmaIMBound::Handle_Activate()", "call.tuple->items.at( 1 ) was not PyInt expected type." );
                return NULL;
            }
        }
        else
        {
            sLog.Error( "DogmaIMBound::Handle_Activate()", "call.tuple->items.at( 0 ) was not PyInt expected type." );
            return NULL;
        }
    }
    else if( callTupleSize == 4 )
    {
        if( !args.Decode( &call.tuple ) )
        {
            codelog( SERVICE__ERROR, "Unable to decode arguments from '%s'", call.client->GetName() );
            return NULL;
        }

        //TODO: make sure we are allowed to do this.
        return new PyInt( call.client->GetShip()->Activate( args.itemID, args.effectName, args.target, args.repeat ) );
    }

    return NULL;
}

PyResult DogmaIMBound::Handle_Deactivate( PyCallArgs& call )
{
    Call_Dogma_Deactivate args;
    if( !args.Decode( &call.tuple ) )
    {
        codelog( SERVICE__ERROR, "Unable to decode arguments from '%s'", call.client->GetName() );
        return NULL;
    }

    //TODO: make sure we are allowed to do this.
    call.client->GetShip()->Deactivate( args.itemID, args.effectName );

    return NULL;
}

PyResult DogmaIMBound::Handle_Overload( PyCallArgs& call ) {

	sLog.Warning("Server", "Called Overload stub");
	return NULL;
}

PyResult DogmaIMBound::Handle_CancelOverloading( PyCallArgs& call ) {

	sLog.Warning("Server", "Called CancelOverloading stub");
	return NULL;
}

PyResult DogmaIMBound::Handle_AddTarget(PyCallArgs &call) {
    Call_SingleIntegerArg args;
    if(!args.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Unable to decode arguments from '%s'", call.client->GetName());
        return NULL;
    }

    SystemManager *smgr = call.client->System();
    if(smgr == NULL) {
        codelog(SERVICE__ERROR, "Unable to find system manager from '%s'", call.client->GetName());
        return NULL;
    }
    SystemEntity *target = smgr->get(args.arg);
    if(target == NULL) {
        codelog(SERVICE__ERROR, "Unable to find entity %u in system %u from '%s'", args.arg, smgr->GetID(), call.client->GetName());
        return NULL;
    }

    ShipRef ship = call.client->GetShip();

    if( !call.client->targets.StartTargeting(target, ship) )
        return NULL;

    // For Debugging purposes, put a message in the log to print out the range to the target:
    GVector vectorToTarget( call.client->GetPosition(), target->GetPosition() );
    double rangeToTarget = vectorToTarget.length();
    // TODO: calculate double distance = SQRT(x^2 + y^2 + z^), where x,y,z are to.x-from.x, etc
    sLog.Warning( "DogmaIMBound::Handle_AddTarget()", "TARGET ADDED - Range to Target = %f meters.", rangeToTarget );

    Rsp_Dogma_AddTarget rsp;
    rsp.success = true;
    rsp.targets.push_back(target->GetID());
	
    return(rsp.Encode());
}

PyResult DogmaIMBound::Handle_RemoveTarget(PyCallArgs &call) {
    Call_SingleIntegerArg args;
    if(!args.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Unable to decode arguments from '%s'", call.client->GetName());
        return NULL;
    }

    SystemManager *smgr = call.client->System();
    if(smgr == NULL) {
        codelog(SERVICE__ERROR, "Unable to find system manager from '%s'", call.client->GetName());
        return NULL;
    }
    SystemEntity *target = smgr->get(args.arg);
    if(target == NULL) {
        codelog(SERVICE__ERROR, "Unable to find entity %u in system %u from '%s'", args.arg, smgr->GetID(), call.client->GetName());
        return NULL;
    }

    // For Debugging purposes, put a message in the log to print out the range to the target:
    GVector vectorToTarget( call.client->GetPosition(), target->GetPosition() );
    double rangeToTarget = vectorToTarget.length();
    sLog.Warning( "DogmaIMBound::Handle_AddTarget()", "TARGET REMOVED - Range to Target = %f meters.", rangeToTarget );

    call.client->targets.ClearTarget(target);

    return NULL;
}

PyResult DogmaIMBound::Handle_ClearTargets(PyCallArgs &call) {
    //no arguments.

    call.client->targets.ClearTargets();

    return NULL;
}

PyResult DogmaIMBound::Handle_GetWeaponBankInfoForShip( PyCallArgs& call )
{
    sLog.Debug( "DogmaIMBound", "Called GetWeaponBankInfoForShip stub." );

    return new PyDict;
}


class BuiltinSet : public PyObjectEx_Type1
{
public:
    BuiltinSet() : PyObjectEx_Type1( new PyToken("collections.defaultdict"), new_tuple(new PyToken("__builtin__.set")) ) {}
};

PyResult DogmaIMBound::Handle_GetAllInfo( PyCallArgs& call )
{
    //arg1: getCharInfo, arg2: getShipInfo
    Call_TwoBoolArgs args;
    if(!args.Decode(&call.tuple)) {
        codelog(SERVICE__ERROR, "Unable to decode arguments from '%s'", call.client->GetName());
        return NULL;
    }

	// ========================================================================
	// Create the response dictionary:
    PyDict *rsp = new PyDict;

    rsp->SetItemString("charInfo", new PyNone);
    rsp->SetItemString("activeShipID", new PyInt(call.client->GetShipID()));
    rsp->SetItemString("locationInfo", new PyDict);
    rsp->SetItemString("shipInfo", new PyNone);
    rsp->SetItemString("shipModifiedCharAttribs", new PyNone);
    rsp->SetItemString("shipState", new PyNone);


	// ========================================================================
	// Setting "charInfo" in the Dictionary:
    if(args.arg1)
    {
        PyDict *charResult = call.client->GetChar()->CharGetInfo();
        if(charResult == NULL) {
            codelog(SERVICE__ERROR, "Unable to build char info for char %u", call.client->GetCharacterID());
            return NULL;
        }

        rsp->SetItemString("charInfo", charResult);
    }
	// ========================================================================


	// ========================================================================
	// Setting "locationInfo" in the Dictionary:
	// TODO
	// ========================================================================


	// ========================================================================
	// Setting "shipInfo" in the Dictionary:
	if(args.arg2)
    {
        PyDict *shipResult = call.client->GetShip()->ShipGetInfo();
        if(shipResult == NULL) {
            codelog(SERVICE__ERROR, "Unable to build ship info for ship %u", call.client->GetShipID());
            return NULL;
        }
        rsp->SetItemString("shipInfo", shipResult);
    }
	// ========================================================================


	// ========================================================================
	// Setting "shipModifiedCharAttribs" in the Dictionary:
	// TODO
	// ========================================================================


	// ========================================================================
	// Setting "shipState" in the Dictionary:
    //Get some attributes about the ship and its modules for shipState
    PyTuple *rspShipState = new PyTuple(3);

    //Contains a dict of the ship and its modules

    if(call.client->GetShip() == NULL) {
        codelog(SERVICE__ERROR, "Unable to build ship status for ship %u", call.client->GetShipID());
        return NULL;
    }
    PyDict *shipState = call.client->GetShip()->ShipGetState();
    rspShipState->items[0] = shipState;

    //Contains a dict with the ship and an empty dict
    PyDict *shipStateItem2 = new PyDict();
    shipStateItem2->SetItem(new PyInt(call.client->GetShipID()), new PyDict());
    rspShipState->items[1] = shipStateItem2;

    //Some PyObjectEx
    rspShipState->items[2] = new BuiltinSet();

    rsp->SetItemString("shipState", rspShipState);


	return new PyObject( "util.KeyVal", rsp );
}

