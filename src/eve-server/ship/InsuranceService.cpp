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
#include "ship/InsuranceService.h"

class InsuranceBound
: public PyBoundObject
{
public:
    PyCallable_Make_Dispatcher(InsuranceBound)

    InsuranceBound(PyServiceMgr *mgr, ShipDB* db)
    : PyBoundObject(mgr),
      m_db(db),
      m_dispatch(new Dispatcher(this))
    {
        _SetCallDispatcher(m_dispatch);

        PyCallable_REG_CALL(InsuranceBound, GetContracts)
        PyCallable_REG_CALL(InsuranceBound, GetInsurancePrice)

        m_strBoundObjectName = "InsuranceBound";
    }

    virtual ~InsuranceBound() { delete m_dispatch; }
    virtual void Release() {
        //I hate this statement
        delete this;
    }

    PyCallable_DECL_CALL(GetContracts)
    PyCallable_DECL_CALL(GetInsurancePrice)

protected:
    ShipDB* m_db;
    Dispatcher *const m_dispatch;
};

PyCallable_Make_InnerDispatcher(InsuranceService)

InsuranceService::InsuranceService(PyServiceMgr *mgr)
: PyService(mgr, "insuranceSvc"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(InsuranceService, GetContractForShip)
    PyCallable_REG_CALL(InsuranceService, InsureShip)
    PyCallable_REG_CALL(InsuranceService, GetInsurancePrice)
}

InsuranceService::~InsuranceService() {
    delete m_dispatch;
}

PyBoundObject* InsuranceService::_CreateBoundObject( Client* c, const PyRep* bind_args )
{
    _log( CLIENT__MESSAGE, "InsuranceService bind request for:" );
    bind_args->Dump( CLIENT__MESSAGE, "    " );

    return new InsuranceBound( m_manager, &m_db );
}

PyResult InsuranceBound::Handle_GetInsurancePrice( PyCallArgs& call )
{
    //  will add this completed code at a later date  -allan 25Jul14
    return new PyFloat(0.0);
}

PyResult InsuranceBound::Handle_GetContracts( PyCallArgs& call )
{
    //  will add this completed code at a later date  -allan 25Jul14
    return NULL;
}

PyResult InsuranceService::Handle_GetInsurancePrice( PyCallArgs& call )
{
    //  will add this completed code at a later date  -allan 25Jul14
    return new PyFloat(0.0);
}

PyResult InsuranceService::Handle_GetContractForShip( PyCallArgs& call )
{
    //  will add this completed code at a later date  -allan 25Jul14
    return NULL;
}

PyResult InsuranceService::Handle_InsureShip( PyCallArgs& call )
{
    //  will add this completed code at a later date  -allan 25Jul14
    return NULL;
}
