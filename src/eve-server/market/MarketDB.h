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

#ifndef __MARKETDB_H_INCL__
#define __MARKETDB_H_INCL__

#include "ServiceDB.h"

class PyRep;

static const uint32 HISTORY_AGGREGATION_DAYS = 5;    //how many days in the past is the cutoff between "new" and "old" price history.

typedef enum
{
    TransactionTypeSell = 0,
    TransactionTypeBuy = 1
} MktTransType;

class MarketDB
: public ServiceDB
{
public:
    static PyRep *CharGetNewTransactions(uint32 characterID);
    static PyRep *GetStationAsks(uint32 stationID);
    static PyRep *GetSystemAsks(uint32 solarSystemID);
    static PyRep *GetRegionBest(uint32 regionID);

    static PyRep *GetOrders(uint32 regionID, uint32 typeID);
    static PyRep *GetCharOrders(uint32 characterID);
    static PyRep *GetOrderRow(uint32 orderID);

    static PyRep *GetOldPriceHistory(uint32 regionID, uint32 typeID);
    static PyRep *GetNewPriceHistory(uint32 regionID, uint32 typeID);
    static PyRep *GetTransactions(uint32 characterID, uint32 typeID, uint32 quantity, double minPrice, double maxPrice, uint64 fromDate, int buySell);

    static PyRep *GetMarketGroups();
    static PyObject *GetRefTypes();
    static PyObject *GetCorporationBills(uint32 corpID, bool payable);

    static uint32 FindBuyOrder(uint32 stationID, uint32 typeID, double price, uint32 quantity, uint32 orderRange);
    static uint32 FindSellOrder(uint32 stationID, uint32 typeID, double price, uint32 quantity, uint32 orderRange);

    static bool GetOrderInfo(uint32 orderID, uint32 *orderOwnerID, uint32 *typeID, uint32 *stationID, uint32 *quantity, double *price, bool *isBuy, bool *isCorp);
    static bool AlterOrderQuantity(uint32 orderID, uint32 new_qty);
    static bool AlterOrderPrice(uint32 orderID, double new_price);
    static bool DeleteOrder(uint32 orderID);

    static bool AddCharacterBalance(uint32 char_id, double delta);

    static uint32 StoreBuyOrder(uint32 clientID, uint32 accountID, uint32 stationID, uint32 typeID, double price, uint32 quantity, uint8 orderRange, uint32 minVolume, uint8 duration, bool isCorp);
    static uint32 StoreSellOrder(uint32 clientID, uint32 accountID, uint32 stationID, uint32 typeID, double price, uint32 quantity, uint8 orderRange, uint32 minVolume, uint8 duration, bool isCorp);
    static bool RecordTransaction(uint32 typeID, uint32 quantity, double price, MktTransType ttype, uint32 charID, uint32 regionID, uint32 stationID);

    static bool BuildOldPriceHistory();

protected:
    static uint32 _StoreOrder(uint32 clientID, uint32 accountID, uint32 stationID, uint32 typeID, double price, uint32 quantity, uint8 orderRange, uint32 minVolume, uint8 duration, bool isCorp, bool isBuy);
};





#endif


