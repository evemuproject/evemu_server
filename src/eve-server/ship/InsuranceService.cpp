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
#include "ship/InsuranceService.h"

class InsuranceBound
: public PyBoundObject
{
public:
    PyCallable_Make_Dispatcher(InsuranceBound)

    InsuranceBound(ShipDB* db)
    : PyBoundObject(),
      m_db(db),
      m_dispatch(new Dispatcher(this))
    {
        _SetCallDispatcher(m_dispatch);

        PyCallable_REG_CALL(InsuranceBound, GetInsurancePrice)

        m_strBoundObjectName = "InsuranceBound";
    }

    virtual ~InsuranceBound() { delete m_dispatch; }
    virtual void Release() {
        //I hate this statement
        delete this;
    }

    PyCallable_DECL_CALL(GetInsurancePrice)

protected:
    ShipDB* m_db;
    Dispatcher *const m_dispatch;
};

PyCallable_Make_InnerDispatcher(InsuranceService)

InsuranceService::InsuranceService()
: PyService("insuranceSvc"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(InsuranceService, GetContractForShip)
}

InsuranceService::~InsuranceService() {
    delete m_dispatch;
}

PyBoundObject* InsuranceService::_CreateBoundObject( Client* c, const PyRep* bind_args )
{
    _log( CLIENT__MESSAGE, "InsuranceService bind request for:" );
    bind_args->Dump( CLIENT__MESSAGE, "    " );

    return new InsuranceBound( &m_db );
}

PyResult InsuranceService::Handle_GetInsurancePrice( PyCallArgs& call )
{
    sLog.Debug("InsuranceService", "Called GetInsurancePrice stub" );
    return new PyFloat(0.0);
}

PyResult InsuranceBound::Handle_GetInsurancePrice( PyCallArgs& call )
{
    sLog.Debug("InsuranceBound", "Called GetInsurancePrice stub" );
    return new PyFloat(0.0);
}

PyResult InsuranceService::Handle_GetContractForShip( PyCallArgs& call )
{
    sLog.Debug( "InsuranceService", "Called GetContractForShip stub." );

    return new PyNone;
}


























