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
    Author:        Reve
*/

//work in progress

#include "eve-server.h"

#include "PyBoundObject.h"
#include "PyServiceCD.h"
#include "pos/PlanetMgr.h"

class PlanetMgrBound
: public PyBoundObject
{
public:
    PyCallable_Make_Dispatcher(PlanetMgrBound)

    PlanetMgrBound()
    : PyBoundObject(),
      m_dispatch(new Dispatcher(this))
    {
        _SetCallDispatcher(m_dispatch);

        m_strBoundObjectName = "PlanetMgrBound";

        PyCallable_REG_CALL(PlanetMgrBound, GetPlanetInfo)
        PyCallable_REG_CALL(PlanetMgrBound, GetPlanetResourceInfo)
    }
    virtual ~PlanetMgrBound() { delete m_dispatch; }
    virtual void Release() {
        //He hates this statement
        delete this;
    }

        PyCallable_DECL_CALL(GetPlanetInfo)
        PyCallable_DECL_CALL(GetPlanetResourceInfo)

protected:
    Dispatcher *const m_dispatch;
};

PyCallable_Make_InnerDispatcher(PlanetMgrService)

PlanetMgrService::PlanetMgrService()
: PyService("planetMgr"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(PlanetMgrService, GetPlanetsForChar)
    PyCallable_REG_CALL(PlanetMgrService, GetMyLaunchesDetails)
}

PlanetMgrService::~PlanetMgrService() {
    delete m_dispatch;
}

PyBoundObject *PlanetMgrService::_CreateBoundObject(Client *c, const PyRep *bind_args) {
    if(!bind_args->IsInt()) {
        codelog(SERVICE__ERROR, "%s Service: invalid bind argument type %s", GetName(), bind_args->TypeString());
        return NULL;
    }
    return new PlanetMgrBound;
}

PyResult PlanetMgrBound::Handle_GetPlanetInfo(PyCallArgs &call) {
    sLog.Debug("Server", "Called GetPlanetInfo Stub.");

    return NULL;
}

PyResult PlanetMgrBound::Handle_GetPlanetResourceInfo(PyCallArgs &call) {
    sLog.Debug("Server", "Called GetPlanetResourceInfo Stub.");

    return NULL;
}

PyResult PlanetMgrService::Handle_GetPlanetsForChar(PyCallArgs &call) {
    sLog.Debug("Server", "Called GetPlanetsForChar Stub.");

    return NULL;
}

PyResult PlanetMgrService::Handle_GetMyLaunchesDetails(PyCallArgs &call) {

    sLog.Debug("Server", "Called GetMyLaunchesDetails Stub.");

    return NULL;
}
