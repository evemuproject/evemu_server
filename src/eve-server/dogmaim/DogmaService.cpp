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
    Author:        ozatomic
*/

#include "eve-server.h"

#include "PyServiceCD.h"
#include "cache/ObjCacheService.h"
#include "dogmaim/DogmaService.h"

PyCallable_Make_InnerDispatcher(DogmaService)

DogmaService::DogmaService(  )
: PyService("dogma"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);

    PyCallable_REG_CALL(DogmaService, GetOperandsForChar);
}

DogmaService::~DogmaService() {
    delete m_dispatch;
}

PyResult DogmaService::Handle_GetOperandsForChar(PyCallArgs &call)
{
    ObjectCachedMethodID method_id(GetName(), "GetOperandsForChar");

    if( !sManager.cache_service->IsCacheLoaded( method_id ) )
    {
        PyRep* res = m_db.GetOperand();
        if( res == NULL )
            return NULL;

        sManager.cache_service->GiveCache( method_id, &res );
    }

    return sManager.cache_service->MakeObjectCachedMethodCallResult( method_id );
}
