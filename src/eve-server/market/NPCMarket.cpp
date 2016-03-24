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
    if (!DBcore::RunQuery(err, "DELETE FROM srvMarket_orders WHERE duration > 90 AND regionID=%u", regionID))
    {
        _log(MARKET__ERROR, "Error in query: %s.", err.c_str());
        SysLog::Log("NPCMarket", "Failed to clear old NPC market for region %u", regionID);
        return;
    }

    // Create the new orders.
    if (!DBcore::RunQuery(err,
                             "INSERT INTO srvMarket_orders ("
                             "    typeID, charID, regionID, stationID,"
                             "    `range`, bid, price, volEntered, volRemaining, issued,"
                             "    orderState, minVolume, contraband, accountID, duration,"
                             "    isCorp, solarSystemID, escrow, jumps ) "
                          "SELECT blkMarketNPC.typeID, '0' AS charID, '%u' AS regionID,"
                             "     blkMarketNPC.stationID,"
                             "     '0' AS `range`, blkMarketNPC.bid,"
                             "     blkMarketNPC.price, blkMarketNPC.volEntered, blkMarketNPC.volEntered,"
                             "     %" PRIu64 " AS issued, '1' AS orderState, '1' AS minVolume, '0' AS contraband,"
                             "     '0' AS accountID, '365' AS duration, '0' AS isCorp,"
                             "     (SELECT staStations.solarSystemID FROM staStations "
                             "     WHERE staStations.stationID=blkMarketNPC.stationID) AS solarSystemID,"
                             " '0' AS escrow, '-1' AS jumps FROM blkMarketNPC WHERE blkMarketNPC.stationID IN "
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
    if (!DBcore::RunQuery(err, "DELETE FROM srvMarket_orders WHERE duration > 90"))
    {
        _log(MARKET__ERROR, "Error in query: %s.", err.c_str());
        SysLog::Log("NPCMarket", "Failed to clear old NPC market for ALL regions.");
        return;
    }

    // Create the new orders.
    if (!DBcore::RunQuery(err,
                          "INSERT INTO srvMarket_orders ("
                          "    typeID, charID, regionID, stationID,"
                          "    `range`, bid, price, volEntered, volRemaining, issued,"
                          "    orderState, minVolume, contraband, accountID, duration,"
                          "    isCorp, solarSystemID, escrow, jumps ) "
                          "SELECT blkMarketNPC.typeID, '0' AS charID, "
                          "    (SELECT staStations.regionID FROM staStations "
                          "    WHERE staStations.stationID=blkMarketNPC.stationID) AS regionID, "
                          "    blkMarketNPC.stationID,"
                          "    '0' AS `range`, blkMarketNPC.bid,"
                          "    blkMarketNPC.price, blkMarketNPC.volEntered, blkMarketNPC.volEntered,"
                          "    %" PRIu64 " AS issued, '1' AS orderState, '1' AS minVolume, '0' AS contraband,"
                          "    '0' AS accountID, '365' AS duration, '0' AS isCorp,"
                          "    (SELECT staStations.solarSystemID FROM staStations "
                          "    WHERE staStations.stationID=blkMarketNPC.stationID) AS solarSystemID,"
                          " '0' AS escrow, '-1' AS jumps FROM blkMarketNPC",
                          Win32TimeNow()
                          ))
    {
        codelog(MARKET__ERROR, "Error in query: %s", err.c_str());
    }

}
