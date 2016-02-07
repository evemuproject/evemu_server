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
 *     NPCMarket::CreateNPCMarketFromFile("/etc/npcMarket.xml");
 * This starts a worker thread as it can potentially take a VERY long time to complete.
 *
 * Format for the xml file as follows.
 *
 * <npcMarketOrders>
 *   <Station>
 *     <StationID>60000004</StationID>
 *     <Order>
 *       <TypeID>41</TypeID>
 *       <Qty>23572</Qty>
 *       <Price>25.52</Price>
 *       <Bid>0</Bid>
 *     </Order>
 *     <Order>
 *       <TypeID>43</TypeID>
 *       <Qty>59656</Qty>
 *       <Price>333.96</Price>
 *       <Bid>1</Bid>
 *     </Order>
 *     ....
 *   </station>
 *   <station>
 *     ....
 *   </station>
 * </npcMarketOrders>
 */

#ifndef NPCMARKET_H
#define	NPCMARKET_H

#include "MarketDB.h"

class NPCMarket
: public XMLParserEx
{
private:
    NPCMarket();
public:

    /**
     * Process an xml file to create NPC market orders.
     * @param filename the file to process, path relative to the server root directory.
     * @param verbose Should the seeder print non-error messages to the server log?
     */
    static void CreateNPCMarketFromFile(std::string filename, bool verbose = true);

    /**
     * Stop any running seeding task.
     */
    static void StopSeeding();

private:
    /**
     * Access to the market database information.
     */
    MarketDB m_db;
    /**
     * The retrieved station ID.
     */
    uint32 StationID;

    /**
     * Container for the retrieve market order data.
     */
    struct stationOrder
    {
        /**
         * The item type.
         */
        uint32 TypeID;
        /**
         * The quantity of items.
         */
        uint32 Qty;
        /**
         * The price of the item.
         */
        double Price;
        /**
         * Flag indicating a buy / sell order.
         */
        uint32 Bid;
    } order;
    /**
     * A list of orders retrieved for the current station.
     */
    std::list<stationOrder> newOrders;

    /**
     * Process the NPC Orders from the xml document.
     * @param ele the xml element to process.
     * @return true if successful, false on error.
     */
    bool ProcessNPCOrders(const TiXmlElement* ele);
    /**
     * Process the station entries from the xml document.
     * @param ele the xml element to process.
     * @return true if successful, false on error.
     */
    bool ProcessStation(const TiXmlElement* ele);
    /**
     * Process the order entries from the xml document.
     * @param ele the xml element to process.
     * @return true if successful, false on error.
     */
    bool ProcessOrder(const TiXmlElement* ele);

    /**
     * Entry point for the market seeder thread.
     * @param arg The NPCMarket object to use.
     * @return The result state of the task.
     */
#ifdef HAVE_WINDOWS_H
    static DWORD WINAPI NPCMarketTask(LPVOID arg);
#else /* !HAVE_WINDOWS_H */
    static void* NPCMarketTask(void* arg);
#endif /* !HAVE_WINDOWS_H */

    /**
     * The file to parse.
     */
    std::string marketFile;

    /**
     * Should the seeder print to the log?
     */
    bool _verbose;

    /**
     * Protect against multiple runs.
     */
    static Mutex mMarket;

    /**
     * Do the actual market seeding.
     */
    void NPCMarketTask();
};

#endif	/* NPCMARKET_H */

