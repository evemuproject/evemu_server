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

#include "PyBoundObject.h"
#include "PyServiceCD.h"
#include "cache/ObjCacheService.h"
#include "ship/BeyonceService.h"
#include "ship/DestinyManager.h"
#include "ship/ShipDB.h"
#include "system/BookmarkService.h"
#include "system/SystemEntities.h"
#include "system/SystemManager.h"
#include "PyServiceMgr.h"

class BeyonceBound
: public PyBoundObject
{
public:
    PyCallable_Make_Dispatcher(BeyonceBound)

    BeyonceBound(Client *c)
    : PyBoundObject(new Dispatcher(this))
    {
        m_strBoundObjectName = "BeyonceBound";

        PyCallable_REG_CALL(BeyonceBound, CmdFollowBall)
        PyCallable_REG_CALL(BeyonceBound, CmdOrbit)
        PyCallable_REG_CALL(BeyonceBound, CmdAlignTo)
        PyCallable_REG_CALL(BeyonceBound, CmdGotoDirection)
        PyCallable_REG_CALL(BeyonceBound, CmdGotoBookmark)
        PyCallable_REG_CALL(BeyonceBound, CmdSetSpeedFraction)
        PyCallable_REG_CALL(BeyonceBound, CmdStop)
        PyCallable_REG_CALL(BeyonceBound, CmdWarpToStuff)
        PyCallable_REG_CALL(BeyonceBound, CmdDock)
        PyCallable_REG_CALL(BeyonceBound, CmdStargateJump)
        PyCallable_REG_CALL(BeyonceBound, UpdateStateRequest)
        PyCallable_REG_CALL(BeyonceBound, CmdWarpToStuffAutopilot)

        if(c->Destiny() != NULL)
            c->Destiny()->SendSetState(c->Bubble());
    }
    virtual ~BeyonceBound() {}
    virtual void Release() {
        //I hate this statement
        delete this;
    }

    PyCallable_DECL_CALL(CmdFollowBall)
    PyCallable_DECL_CALL(CmdOrbit)
    PyCallable_DECL_CALL(CmdAlignTo)
    PyCallable_DECL_CALL(CmdGotoDirection)
    PyCallable_DECL_CALL(CmdGotoBookmark)
    PyCallable_DECL_CALL(CmdSetSpeedFraction)
    PyCallable_DECL_CALL(CmdStop)
    PyCallable_DECL_CALL(CmdWarpToStuff)
    PyCallable_DECL_CALL(CmdDock)
    PyCallable_DECL_CALL(CmdStargateJump)
    PyCallable_DECL_CALL(UpdateStateRequest)
    PyCallable_DECL_CALL(CmdWarpToStuffAutopilot)

protected:

};

PyCallable_Make_InnerDispatcher(BeyonceService)

BeyonceService::BeyonceService()
: PyService("beyonce", new Dispatcher(this))
{
    //PyCallable_REG_CALL(BeyonceService, )
    PyCallable_REG_CALL(BeyonceService, GetFormations)
}

BeyonceService::~BeyonceService() {
}


PyBoundObject* BeyonceService::_CreateBoundObject( Client* c, const PyRep* bind_args )
{
    _log( CLIENT__MESSAGE, "BeyonceService bind request for:" );
    bind_args->Dump( CLIENT__MESSAGE, "    " );

    return new BeyonceBound( c );
}


PyResult BeyonceService::Handle_GetFormations(PyCallArgs &call) {
    ObjectCachedMethodID method_id(GetName(), "GetFormations");

    //check to see if this method is in the cache already.
    if (!PyServiceMgr::cache_service->IsCacheLoaded(method_id))
    {
        //this method is not in cache yet, load up the contents and cache it.
        PyRep *res = ShipDB::GetFormations();
        if(res == NULL) {
            codelog(SERVICE__ERROR, "Failed to load cache, generating empty contents.");
            res = new PyNone();
        }

        PyServiceMgr::cache_service->GiveCache(method_id, &res);
    }

    //now we know its in the cache one way or the other, so build a
    //cached object cached method call result.
    //return(PyServiceMgr::cache_service->MakeObjectCachedMethodCallResult(method_id));
    return new PyTuple(0);
}

/*
PyResult BeyonceService::Handle_(PyCallArgs &call) {
    PyRep *result = NULL;

    return result;
}
*/

PyResult BeyonceBound::Handle_CmdFollowBall(PyCallArgs &call) {
    Call_FollowBall args;
    if(!args.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "%s: Failed to decode arguments.", call.client->GetName());
        return NULL;
    }

    double distance;
    if( pyIs(Int, args.distance) )
    {
        distance = pyAs(Int, args.distance)->value();
    }
    else if( pyIs(Float, args.distance) )
    {
        distance = pyAs(Float, args.distance)->value();
    }
    else
    {
        codelog(CLIENT__ERROR, "%s: Invalid type %s for distance argument received.", call.client->GetName(), args.distance->TypeString());
        return NULL;
    }

    DestinyManager *destiny = call.client->Destiny();
    if(destiny == NULL) {
        codelog(CLIENT__ERROR, "%s: Client has no destiny manager!", call.client->GetName());
        return NULL;
    }

    SystemManager *system = call.client->System();
    if(system == NULL) {
        codelog(CLIENT__ERROR, "%s: Client has no system manager!", call.client->GetName());
        return NULL;
    }
    SystemEntity *entity = system->get(args.ballID);
    if(entity == NULL) {
        _log(CLIENT__ERROR, "%s: Unable to find entity %u to Orbit.", call.client->GetName(), args.ballID);
        return NULL;
    }

    destiny->Follow(entity, distance);

    return NULL;
}

PyResult BeyonceBound::Handle_CmdSetSpeedFraction(PyCallArgs &call) {
    Call_SingleRealArg arg;
    if(!arg.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "%s: failed to decode args", call.client->GetName());
        return NULL;
    }

    DestinyManager *destiny = call.client->Destiny();
    if(destiny == NULL) {
        codelog(CLIENT__ERROR, "%s: Client has no destiny manager!", call.client->GetName());
        return NULL;
    }

    destiny->SetSpeedFraction(arg.arg);

    return NULL;
}

/* AlignTo
 * This will look up the entityID to get it's position in space, then call
 * AlignTo to have it respond with gotopoint.
 * @author Xanarox
*/
PyResult BeyonceBound::Handle_CmdAlignTo(PyCallArgs &call) {
    CallAlignTo arg;
    if(!arg.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "%s: failed to decode args", call.client->GetName());
        return NULL;
    }

    DestinyManager *destiny = call.client->Destiny();
    if(destiny == NULL) {
        codelog(CLIENT__ERROR, "%s: Client has no destiny manager!", call.client->GetName());
        return NULL;
    }

    SystemManager *system = call.client->System();
    if(system == NULL) {
        codelog(CLIENT__ERROR, "%s: Client has no system manager!", call.client->GetName());
        return NULL;
    }

    SystemEntity *entity = system->get(arg.entityID);
    if(entity == NULL) {
        _log(CLIENT__ERROR, "%s: Unable to find entity %u to AlignTo.", call.client->GetName(), arg.entityID);
        return NULL;
    }

    const Vector3D &position = entity->GetPosition();
    destiny->AlignTo( position );

    return NULL;
}

PyResult BeyonceBound::Handle_CmdGotoDirection(PyCallArgs &call) {
    Call_PointArg arg;
    if(!arg.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "%s: failed to decode args", call.client->GetName());
        return NULL;
    }

    DestinyManager *destiny = call.client->Destiny();
    if(destiny == NULL) {
        codelog(CLIENT__ERROR, "%s: Client has no destiny manager!", call.client->GetName());
        return NULL;
    }

    destiny->GotoDirection( Vector3D( arg.x, arg.y, arg.z ) );

    return NULL;
}

PyResult BeyonceBound::Handle_CmdGotoBookmark(PyCallArgs &call) {

    if( !(pyIs(Int, call.tuple->GetItem( 0 ))) )
    {
        SysLog::Error( "BeyonceService::Handle_GotoBookmark()", "%s: Invalid type %s for bookmarkID received.", call.client->GetName(), call.tuple->GetItem( 0 )->TypeString() );
        return NULL;
    }
    uint32 bookmarkID = pyAs(Int, call.tuple->GetItem( 0 ))->value();

    DestinyManager *destiny = call.client->Destiny();
    if( destiny == NULL )
    {
        SysLog::Error( "%s: Client has no destiny manager!", call.client->GetName() );
        return NULL;
    }

    double x,y,z;
    uint32 itemID;
    uint32 typeID;
    Vector3D bookmarkPosition;

    BookmarkService *bkSrvc = (BookmarkService *) (PyServiceMgr::LookupService("bookmark"));

    if( bkSrvc == NULL )
    {
        SysLog::Error( "BeyonceService::Handle_GotoBookmark()", "Attempt to access BookmarkService via (BookmarkService *)(LookupService(\"bookmark\")) returned NULL pointer." );
        return NULL;
    }
    else
    {
        bkSrvc->LookupBookmark( call.client->GetCharacterID(),bookmarkID,itemID,typeID,x,y,z );

        if( typeID == 5 )
        {
            // Bookmark type is coordinate, so use these directly from the bookmark system call:
            bookmarkPosition.x = x;     // From bookmark x
            bookmarkPosition.y = y;     // From bookmark y
            bookmarkPosition.z = z;     // From bookmark z

            destiny->GotoDirection( bookmarkPosition );
        }
        else
        {
            // Bookmark type is of a static system entity, so search for it and obtain its coordinates:
            SystemManager *sm = call.client->System();
            if(sm == NULL) {
                SysLog::Error( "BeyonceService::Handle_GotoBookmark()", "%s: no system manager found", call.client->GetName() );
                return NULL;
            }
            SystemEntity *se = sm->get( itemID );
            if(se ==  NULL) {
                SysLog::Error( "BeyonceService::Handle_GotoBookmark()", "%s: unable to find location %d", call.client->GetName(), itemID );
                return NULL;
            }

            destiny->GotoDirection( se->GetPosition() );
        }
    }

    return NULL;
}

PyResult BeyonceBound::Handle_CmdOrbit(PyCallArgs &call) {
    Call_Orbit arg;
    if(!arg.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "%s: failed to decode args", call.client->GetName());
        return NULL;
    }

    double distance;
    if( pyIs(Int, arg.distance) )
    {
        distance = pyAs(Int, arg.distance)->value();
    }
    else if( pyIs(Float, arg.distance) )
    {
        distance = pyAs(Float, arg.distance)->value();
    }
    else
    {
        codelog(CLIENT__ERROR, "%s: Invalid type %s for distance argument received.", call.client->GetName(), arg.distance->TypeString());
        return NULL;
    }

    DestinyManager *destiny = call.client->Destiny();
    if(destiny == NULL)
    {
        codelog(CLIENT__ERROR, "%s: Client has no destiny manager!", call.client->GetName());
        return NULL;
    }

    SystemManager *system = call.client->System();
    if(system == NULL)
    {
        codelog(CLIENT__ERROR, "%s: Client has no system manager!", call.client->GetName());
        return NULL;
    }
    SystemEntity *entity = system->get(arg.entityID);
    if(entity == NULL)
    {
        _log(CLIENT__ERROR, "%s: Unable to find entity %u to Orbit.", call.client->GetName(), arg.entityID);
        return NULL;
    }

    destiny->Orbit(entity, distance);
    return NULL;
}

PyResult BeyonceBound::Handle_CmdWarpToStuff(PyCallArgs &call) {
    CallWarpToStuff arg;
    if(!arg.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "%s: failed to decode args", call.client->GetName());
        return NULL;
    }

    if( arg.type == "item" )
    {
        // This section handles Warping to any object in the Overview
        double distance;
        std::map<std::string, PyRep *>::const_iterator res = call.byname.find("minRange");
        if(res == call.byname.end()) {
            //Not needed, this is the correct behavior
            //codelog(CLIENT__ERROR, "%s: range not found, using 15 km.", call.client->GetName());
            distance = 0.0;
        } else if(!pyIs(Int, res->second) && !pyIs(Float, res->second)) {
            codelog(CLIENT__ERROR, "%s: range of invalid type %s, expected Integer or Real; using 15 km.", call.client->GetName(), res->second->TypeString());
            distance = 0.0;
        }
        else
        {
            distance = pyIs(Int, res->second) ? pyAs(Int, res->second)->value() : pyAs(Float, res->second)->value();
        }

        //we need to delay the destiny updates until after we return

        SystemManager *sm = call.client->System();
        if(sm == NULL) {
            codelog(CLIENT__ERROR, "%s: no system manager found", call.client->GetName());
            return NULL;
        }
        SystemEntity *se = sm->get(arg.ID);
        if(se ==  NULL) {
            codelog(CLIENT__ERROR, "%s: unable to find location %d", call.client->GetName(), arg.ID);
            return NULL;
        }

        // Make a warp-in point variable
        Vector3D warpToPoint(se->GetPosition());
        double distanceFromBodyOrigin = 0.0;
        Vector3D vectorToWarpPoint(1, 1, 1);
        if (IsStaticMapItem(se->GetID()))
        {
            // Calculate final distance out from origin of celestial body along common warp-to vector:
            switch (((SimpleSystemEntity *) (se))->data.groupID)
            {
                    // This should calculate a common warp in point around a celestial body.
                case EVEDB::invGroups::Sun:
                    // 20,000km
                    distanceFromBodyOrigin = 20000000;
                    break;
                case EVEDB::invGroups::Moon:
                    // 50 km
                    distanceFromBodyOrigin = 50000;
                    break;
                case EVEDB::invGroups::Planet:
                    // 500 km
                    distanceFromBodyOrigin = 500000;
                    break;
            }
        }
        if (distanceFromBodyOrigin > 0)
        {
            distanceFromBodyOrigin += se->GetRadius();
            warpToPoint += vectorToWarpPoint * distanceFromBodyOrigin;
            // Randomize warp-in point:
            warpToPoint.MakeRandomPointOnSphereLayer(1000.0, (1000.0 + call.client->GetRadius()));
        }
        else
        {
            distance += call.client->GetRadius() + se->GetRadius();
        }

        call.client->WarpTo( warpToPoint, distance );
    }
    else if( arg.type == "bookmark" )
    {
        // This section handles Warping to any Bookmark:
        double distance = 0.0;
        double x,y,z;
        uint32 itemID;
        uint32 typeID;
        Vector3D bookmarkPosition;

        BookmarkService *bkSrvc = (BookmarkService *) (PyServiceMgr::LookupService("bookmark"));

        if( bkSrvc == NULL )
        {
            SysLog::Error( "BeyonceService::Handle_WarpToStuff()", "Attempt to access BookmarkService via (BookmarkService *)(LookupService(\"bookmark\")) returned NULL pointer." );
            return NULL;
        }
        else
        {
            bkSrvc->LookupBookmark( call.client->GetCharacterID(),arg.ID,itemID,typeID,x,y,z );

            // Calculate the warp-to distance specified by the client and add this to the final warp-to distance
            std::map<std::string, PyRep *>::const_iterator res = call.byname.find("minRange");
            distance += pyIs(Int, res->second) ? pyAs(Int, res->second)->value() : pyAs(Float, res->second)->value();

            if( typeID == 5 )
            {
                // Bookmark type is coordinate, so use these directly from the bookmark system call:
                bookmarkPosition.x = x;     // From bookmark x
                bookmarkPosition.y = y;     // From bookmark y
                bookmarkPosition.z = z;     // From bookmark z

                call.client->WarpTo( bookmarkPosition, distance );
            }
            else
            {
                DBQueryResult result;
                   DBResultRow row;
                uint32 groupID = 0;

                // Query database 'invTypes' table for the supplied typeID and retrieve the groupID for this type:
                if (!DBcore::RunQuery(result,
                    " SELECT "
                    "    groupID "
                    " FROM invTypes "
                    " WHERE typeID = %u ", typeID))
                {
                    SysLog::Error( "BeyonceService::Handle_WarpToStuff()", "Error in query: %s", result.error.c_str() );
                    return NULL;
                }

                // Query went through, but check to see if there were zero rows, ie typeID was invalid,
                // and if not, then get the groupID from the row:
                if ( !(result.GetRow(row)) )
                {
                    SysLog::Error( "BeyonceService::Handle_WarpToStuff()", "Invalid typeID: %u, no rows returned in db query.", typeID );
                    return NULL;
                }
                groupID = row.GetUInt( 0 );

                // Calculate distance from target warpable object that the ship will warp to, using minimum safe distance
                // based upon groupID of the target object:
                switch( groupID )
                {
                    case 6: // target object is a SUN
                    case 7: // target object is a PLANET
                    case 8: // target object is a MOON
                        //distance += 200000;
                        break;
                    default:
                        break;
                }

                // Bookmark type is of a static system entity, so search for it and obtain its coordinates:
                SystemManager *sm = call.client->System();
                if(sm == NULL) {
                    SysLog::Error( "BeyonceService::Handle_WarpToStuff()", "%s: no system manager found", call.client->GetName() );
                    return NULL;
                }
                SystemEntity *se = sm->get( itemID );
                if(se ==  NULL) {
                    SysLog::Error( "BeyonceService::Handle_WarpToStuff()", "%s: unable to find location %d", call.client->GetName(), itemID );
                    return NULL;
                }

                // Add radiuses for ship and destination object:
                distance += call.client->GetRadius() + se->GetRadius();

                call.client->WarpTo( se->GetPosition(), distance );
            }
        }
    }
    else if( arg.type == "launch" )
    {
        DBQueryResult res;
        if(!DBcore::RunQuery(res, "SELECT `x`, `y`, `z` FROM `planetlaunches` WHERE `launchID` = %u", arg.ID)) {
            codelog(SERVICE__ERROR, "Error in BeyonceService::CmdWarpToStuff:launch Query: %s", res.error.c_str());
            return NULL;
        }
        DBResultRow row;
        if(!res.GetRow(row)) {
            codelog(SERVICE__ERROR, "Error in BeyonceService::CmdWarpToStuff:launch Query returned no rows");
            return NULL;
        }
        Vector3D warpToPoint;
        warpToPoint.x = row.GetDouble(1);
        warpToPoint.y = row.GetDouble(2);
        warpToPoint.z = row.GetDouble(3);
        call.client->WarpTo(warpToPoint, 0.0);
    }
    else
    {
        SysLog::Error( "BeyonceService::Handle_WarpToStuff()", "Unexpected arg.type value: '%s'.", arg.type.c_str() );
        return NULL;
    }

    return NULL;
}

PyResult BeyonceBound::Handle_CmdWarpToStuffAutopilot(PyCallArgs &call) {
    CallWarpToStuffAutopilot arg;

    if(!arg.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "%s: failed to decode args", call.client->GetName());
        return NULL;
    }
    //Change this to change the default autopilot distance (Faster Autopilot FTW)
    double distance = 15000.0;

    //Don't update destiny until done with warp
    SystemManager *sm = call.client->System();
    if(sm == NULL) {
        codelog(CLIENT__ERROR, "%s: no system manager found", call.client->GetName());
        return NULL;
    }
    SystemEntity *se = sm->get(arg.item);
    if(se ==  NULL) {
        codelog(CLIENT__ERROR, "%s: unable to find location %d", call.client->GetName(), arg.item);
        return NULL;
    }
    //Adding in object radius
    distance += call.client->GetRadius() + se->GetRadius();
    call.client->WarpTo(se->GetPosition(), distance);

    return NULL;
}

PyResult BeyonceBound::Handle_UpdateStateRequest(PyCallArgs &call) {
    codelog(CLIENT__ERROR, "%s: Client sent UpdateStateRequest! that means we messed up pretty bad.", call.client->GetName());

    //no arguments.

    DestinyManager *destiny = call.client->Destiny();
    if(destiny == NULL) {
        codelog(CLIENT__ERROR, "%s: Client has no destiny manager!", call.client->GetName());
        return NULL;
    }

    destiny->SendSetState(call.client->Bubble());

    return NULL;
}

PyResult BeyonceBound::Handle_CmdStop(PyCallArgs &call) {
    DestinyManager *destiny = call.client->Destiny();
    if(destiny == NULL) {
        codelog(CLIENT__ERROR, "%s: Client has no destiny manager!", call.client->GetName());
        return NULL;
    }

    // Only disallow Stopping ship when in warp state AND ship speed is greater than 0.75 times ship's maxVelocity
    if( (destiny->GetState() == Destiny::DSTBALL_WARP)
        && (destiny->GetVelocity().length() >= (0.75*call.client->GetShip()->getAttribute(AttrMaxVelocity).get_float())) ) {
            call.client->SendNotifyMsg( "You can't do this while warping");
            return NULL;
    }


    destiny->Stop();

    return NULL;
}

PyResult BeyonceBound::Handle_CmdDock(PyCallArgs &call) {
    Call_TwoIntegerArgs arg;
    if(!arg.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "%s: failed to decode args", call.client->GetName());
        return NULL;
    }

    DestinyManager *destiny = call.client->Destiny();
    if(destiny == NULL) {
        codelog(CLIENT__ERROR, "%s: Client has no destiny manager!", call.client->GetName());
        return NULL;
    }
    SystemManager *sm = call.client->System();
    if(sm == NULL) {
        codelog(CLIENT__ERROR, "%s: Client has no system manager.", call.client->GetName());
        return NULL;
    }

    // Attempt to Dock:
    call.client->SetDockStationID( arg.arg1 );   // Set client to know what station it's trying to dock into just in case docking is delayed
    return destiny->AttemptDockOperation();
}

PyResult BeyonceBound::Handle_CmdStargateJump(PyCallArgs &call) {
    //Call_TwoIntegerArgs arg;
    Call_StargateJump arg;
    if(!arg.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "%s: failed to decode args", call.client->GetName());
        return NULL;
    }

    call.client->StargateJump(arg.fromStargateID, arg.toStargateID);

    return NULL;
}
