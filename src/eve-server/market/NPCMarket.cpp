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
    Author:       EVE-Moo
 */

#include "eve-server.h"
#include "NPCMarket.h"
#include "MarketDB.h"

void NPCMarket::CreateNPCMarketForRegion(uint32 regionID)
{
    DBerror err;

    // Delete the old orders.
    if (!DBcore::RunQuery(err, "DELETE FROM market_orders WHERE duration > 90 AND regionID=%u", regionID))
    {
        _log(MARKET__ERROR, "Error in query: %s.", err.c_str());
        sLog.Log("NPCMarket", "Failed to clear old NPC market for region %u", regionID);
        return;
    }

    // Create the new orders.
    if (!DBcore::RunQuery(err,
                             "INSERT INTO market_orders ("
                             "    typeID, charID, regionID, stationID,"
                             "    `range`, bid, price, volEntered, volRemaining, issued,"
                             "    orderState, minVolume, contraband, accountID, duration,"
                             "    isCorp, solarSystemID, escrow, jumps ) "
                          "SELECT market_npc.typeID, '0' AS charID, '%u' AS regionID,"
                             "     market_npc.stationID,"
                             "     '0' AS `range`, market_npc.bid,"
                             "     market_npc.price, market_npc.volEntered, market_npc.volEntered,"
                             "     %" PRIu64 " AS issued, '1' AS orderState, '1' AS minVolume, '0' AS contraband,"
                             "     '0' AS accountID, '365' AS duration, '0' AS isCorp,"
                             "     (SELECT staStations.solarSystemID FROM staStations "
                             "     WHERE staStations.stationID=market_npc.stationID) AS solarSystemID,"
                             " '0' AS escrow, '-1' AS jumps FROM market_npc WHERE market_npc.stationID IN "
                          "(SELECT staStations.stationID FROM staStations WHERE regionID=%u);",
                             regionID,
                             Win32TimeNow(),
                             regionID
                             ))
    {
        codelog(MARKET__ERROR, "Error in query: %s", err.c_str());
    }

}

void NPCMarket::CreateNPCMarket()
{
    DBerror err;

    // Delete the old orders.
    if (!DBcore::RunQuery(err, "DELETE FROM market_orders WHERE duration > 90"))
    {
        _log(MARKET__ERROR, "Error in query: %s.", err.c_str());
        sLog.Log("NPCMarket", "Failed to clear old NPC market for ALL regions.");
        return;
    }

    // Create the new orders.
    if (!DBcore::RunQuery(err,
                          "INSERT INTO market_orders ("
                          "    typeID, charID, regionID, stationID,"
                          "    `range`, bid, price, volEntered, volRemaining, issued,"
                          "    orderState, minVolume, contraband, accountID, duration,"
                          "    isCorp, solarSystemID, escrow, jumps ) "
                          "SELECT market_npc.typeID, '0' AS charID, "
                          "    (SELECT staStations.regionID FROM staStations "
                          "    WHERE staStations.stationID=market_npc.stationID) AS regionID, "
                          "    market_npc.stationID,"
                          "    '0' AS `range`, market_npc.bid,"
                          "    market_npc.price, market_npc.volEntered, market_npc.volEntered,"
                          "    %" PRIu64 " AS issued, '1' AS orderState, '1' AS minVolume, '0' AS contraband,"
                          "    '0' AS accountID, '365' AS duration, '0' AS isCorp,"
                          "    (SELECT staStations.solarSystemID FROM staStations "
                          "    WHERE staStations.stationID=market_npc.stationID) AS solarSystemID,"
                          " '0' AS escrow, '-1' AS jumps FROM market_npc",
                          Win32TimeNow()
                          ))
    {
        codelog(MARKET__ERROR, "Error in query: %s", err.c_str());
    }

}
