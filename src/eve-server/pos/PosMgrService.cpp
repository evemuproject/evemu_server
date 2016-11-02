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
    Author:        Zhur, Cometo
*/

#include "eve-server.h"

#include "PyServiceCD.h"
#include "pos/PosMgrService.h"
#include "pos/PosMgrDB.h"
#include "PyBoundObject.h"

class PosMgrServiceBound
        : public PyBoundObject
{
public:
    PyCallable_Make_Dispatcher(PosMgrServiceBound)

    PosMgrServiceBound()
    : PyBoundObject(new Dispatcher(this))
    {
        m_strBoundObjectName = "PosMgrServiceBound";

        PyCallable_REG_CALL(PosMgrServiceBound, SetShipPassword)
        /* //TODO, Verify that these are all bound calls.
         * AnchorOrbital
         * AnchorStructure
         * AssumeStructureControl
         * ChangeStructureProvisionType
         * CompleteOrbitalStateChange
         * GetMoonForTower
         * GetMoonProcessInfoForTower
         * GMUpgradeOrbital
         * LinkResourcesForTower
         * OnlineOrbital
         * RelinquishStructureControl
         * RunMoonProcessCycleforTower
         * SetShipPassword
         * SetStarbasePermissions
         * SetTowerPassword
         * SetTowerNotifications
         * SetTowerSentrySettings
         * UnanchorOrbital
         */

    }
    virtual ~PosMgrServiceBound() { }
    virtual void Release() {
        delete this;
    }

    PyCallable_DECL_CALL(SetShipPassword)

protected:

};

PyCallable_Make_InnerDispatcher(PosMgrService)

PosMgrService::PosMgrService()
: PyService("posMgr", new Dispatcher(this))
{
    PyCallable_REG_CALL(PosMgrService, GetControlTowerFuelRequirements)
    /* //TODO, Verify that these are all unbound calls.
     * GetControlTowerFuelRequirements
     * GetControlTowers
     * GetJumpArrays
     * GetSiloCapacityByItemID
     */
}

PosMgrService::~PosMgrService() {
}

PyBoundObject *PosMgrService::_CreateBoundObject(Client *c, const PyRep *bind_args) {
    if(!pyIs(Int, bind_args)) {
        codelog(SERVICE__ERROR, "%s Service: invalid bind argument type %s", GetName(), bind_args->TypeString());
        return NULL;
    }
    bind_args->Dump(DEBUG__DEBUG, "PosMgrService:CBO:    ");
    return new PosMgrServiceBound();
}

PyResult PosMgrService::Handle_GetControlTowerFuelRequirements(PyCallArgs &args)
{
    return PosMgrDB::GetControlTowerFuelRequirements();
}

PyResult PosMgrServiceBound::Handle_SetShipPassword(PyCallArgs &call) {
    SysLog::Debug("PosMgrServiceBound","Called SetShipPassword Stub.");
    call.tuple->Dump(DEBUG__DEBUG, "PMSB:SSP:    ");

    return  NULL;
}
