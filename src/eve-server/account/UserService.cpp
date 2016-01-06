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

#include "PyServiceCD.h"
#include "account/UserService.h"

PyCallable_Make_InnerDispatcher(UserService)

UserService::UserService(PyServiceMgr *mgr)
: PyService(mgr, "userSvc"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(UserService, GetRedeemTokens)
    PyCallable_REG_CALL(UserService, GetCreateDate)
    PyCallable_REG_CALL(UserService, ReportISKSpammer)
}

UserService::~UserService() {
    delete m_dispatch;
}

PyResult UserService::Handle_GetRedeemTokens( PyCallArgs& call )
{
    // takes no args

    sLog.Debug( "UserService", "Called GetRedeemTokens stub." );

    return new PyList;
}

PyResult UserService::Handle_GetCreateDate( PyCallArgs& call )
{
    sLog.Debug( "UserService", "Called GetCreateDate stub." );

    return new PyLong((long)Win32TimeNow());
}

PyResult UserService::Handle_ReportISKSpammer( PyCallArgs& call )
{
    //  will add this completed code at a later date  -allan 25Jul14
    return NULL;
}
