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

#ifndef fleetProxy_h__
#define fleetProxy_h__

#include "PyService.h"

class FleetProxyService: public PyService
{
public:
    FleetProxyService(PyServiceMgr *mgr);
    ~FleetProxyService();

protected:
    class Dispatcher;
    Dispatcher *const m_dispatch;

    PyCallable_DECL_CALL(GetAvailableFleets);
    PyCallable_DECL_CALL(ApplyToJoinFleet);
    PyCallable_DECL_CALL(AddFleetFinderAdvert);
    PyCallable_DECL_CALL(RemoveFleetFinderAdvert);
    PyCallable_DECL_CALL(GetMyFleetFinderAdvert);
    PyCallable_DECL_CALL(UpdateAdvertInfo);
};

#endif
