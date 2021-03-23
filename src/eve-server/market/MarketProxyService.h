/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2021 The EVEmu Team
    For the latest information visit https://github.com/evemuproject/evemu_server
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

#ifndef __MARKETPROXY_SERVICE_H_INCL__
#define __MARKETPROXY_SERVICE_H_INCL__

#include "market/MarketDB.h"
#include "PyService.h"

class MarketProxyService
: public PyService
{
public:
    MarketProxyService(PyServiceMgr *mgr);
    virtual ~MarketProxyService();

protected:
    class Dispatcher;
    Dispatcher *const m_dispatch;

    MarketDB m_db;

    PyCallable_DECL_CALL(GetStationAsks);
    PyCallable_DECL_CALL(GetSystemAsks);
    PyCallable_DECL_CALL(GetRegionBest);
    PyCallable_DECL_CALL(GetMarketGroups);
    PyCallable_DECL_CALL(GetOrders);
    PyCallable_DECL_CALL(GetOldPriceHistory);
    PyCallable_DECL_CALL(GetNewPriceHistory);
    PyCallable_DECL_CALL(PlaceCharOrder);
    PyCallable_DECL_CALL(GetCharOrders);
    PyCallable_DECL_CALL(ModifyCharOrder);
    PyCallable_DECL_CALL(CancelCharOrder);
    PyCallable_DECL_CALL(CharGetNewTransactions);
    PyCallable_DECL_CALL(CorpGetNewTransactions);
    PyCallable_DECL_CALL(StartupCheck);
    PyCallable_DECL_CALL(GetCorporationOrders);
};

#endif
