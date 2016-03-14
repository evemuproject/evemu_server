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

/*
 * example usage:
 *     // Seed NPC market.
 *     Log::Log("Server Init", "NPC market seeding started.");
 *     NPCMarket::CreateNPCMarket();
 *     Log::Log("Server Init", "NPC market seeding finished.");
 *
 *     // Seed NPC market in a region.
 *     NPCMarket::CreateNPCMarketForRegion(regionID);
 *
 * Manually seeding the market.
 * DELETE FROM srvMarket_orders WHERE duration > 90;
 * INSERT INTO srvMarket_orders
 *  (typeID, charID, regionID, stationID, `range`, bid, price, volEntered, volRemaining, issued, orderState, minVolume, contraband, accountID, duration, isCorp, solarSystemID, escrow, jumps )
 *  SELECT market_npc.typeID, '0' AS charID,
 *  (SELECT staStations.regionID FROM staStations WHERE staStations.stationID=market_npc.stationID) AS regionID,
 *  market_npc.stationID, '0' AS `range`, market_npc.bid, market_npc.price, market_npc.volEntered,
 *  market_npc.volEntered,
 *  '123456789' AS issued, '1' AS orderState, '1' AS minVolume, '0' AS contraband,
 *  '0' AS accountID, '365' AS duration, '0' AS isCorp,
 *  (SELECT staStations.solarSystemID FROM staStations WHERE staStations.stationID=market_npc.stationID) AS solarSystemID,
 *  '0' AS escrow, '-1' AS jumps FROM market_npc;
 *
 * replacing '123456789' with the current time.
 */

#ifndef NPCMARKET_H
#define NPCMARKET_H

class NPCMarket
{
public:

    /**
     * Create the NPC market orders for the specified region.
     * @param regionID The region to generate orders for.
     */
    static void CreateNPCMarketForRegion(uint32 regionID);

    /**
     * Create the NPC market orders for the ALL regions.
     */
    static void CreateNPCMarket();

};

#endif	/* NPCMARKET_H */

