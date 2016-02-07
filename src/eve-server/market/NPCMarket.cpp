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

Mutex NPCMarket::mMarket;
bool npcMarketSeederRunning = false;
bool stopNPCMarketSeeding = false;

NPCMarket::NPCMarket()
{
    AddMemberParser("npcMarketOrders", &NPCMarket::ProcessNPCOrders);
}

void NPCMarket::CreateNPCMarketFromFile(std::string filename, bool verbose)
{
    // Create a NPCMarket object to process the file.
    NPCMarket *npcMarket = new NPCMarket();
    npcMarket->marketFile = filename;
    npcMarket->_verbose = verbose;

    // Spawn new thread
#ifdef HAVE_WINDOWS_H
    CreateThread(NULL, 0, NPCMarketTask, this, 0, NULL);
#else /* !HAVE_WINDOWS_H */
    pthread_t thread;
    pthread_create(&thread, NULL, NPCMarketTask, npcMarket);
#endif /* !HAVE_WINDOWS_H */
}

void NPCMarket::StopSeeding()
{
    stopNPCMarketSeeding = true;
    uint64 count = 0;
    while (npcMarketSeederRunning && count < 100000)
    {
        count++;
        Sleep(1);
    }
}

bool NPCMarket::ProcessNPCOrders(const TiXmlElement* ele)
{
    // Add parsers for the child properties.
    AddMemberParser("Station", &NPCMarket::ProcessStation);
    AddValueParser("StationID", StationID);
    AddMemberParser("Order", &NPCMarket::ProcessOrder);
    AddValueParser("TypeID", order.TypeID);
    AddValueParser("Qty", order.Qty);
    AddValueParser("Price", order.Price);
    AddValueParser("Bid", order.Bid);
    // Parse the <npcMarketOrders> element
    const bool result = ParseElementChildren(ele);
    RemoveParser("TypeID");
    RemoveParser("Qty");
    RemoveParser("Price");
    RemoveParser("Bid");
    RemoveParser("Order");
    RemoveParser("StationID");
    RemoveParser("Station");
    return result;
}

bool NPCMarket::ProcessStation(const TiXmlElement* ele)
{
    static int nStations = 0;
    newOrders.clear();
    StationID = 0;
    // Parse the <station> element
    const bool result = ParseElementChildren(ele);
    if (result == false)
    {
        return false;
    }

    // Done if there were no orders.
    if (newOrders.size() == 0 || StationID == 0)
    {
        return true;
    }

    // Count how many stations have been found.
    nStations++;
    if (_verbose)
    {
        sLog.Log("NPCMarket", "%d: Adding %d orders to stationID= %d", nStations, newOrders.size(), StationID);
    }

    DBerror err;

    // Get the solar system and region IDs.
    uint32 solarSystemID;
    uint32 regionID;
    if (!m_db.GetStationInfo(StationID, &solarSystemID, NULL, &regionID, NULL, NULL, NULL))
    {
        newOrders.clear();
        codelog(MARKET__ERROR, "NPCMarket: Failed to find parents for station %u", StationID);
        // Adding these market orders failed but that does not mean the xml is at fault.
        // Return a successful processing of the xml.
        return true;
    }

    uint32 orderID;
    std::ostringstream values;
    uint64 trnTime = Win32TimeNow();
    bool first = true;
    // Create a single insert command to improve sql performance.
    std::list<stationOrder>::iterator itr = newOrders.begin();
    while (itr != newOrders.end())
    {
        if (!first)
            values << ", ";
        first = false;
        values << "(";
        values << (*itr).TypeID;
        values << ", 0"; // clientID
        values << ", " << regionID;
        values << ", " << StationID;
        values << ", 0"; // orderRange
        values << ", " << (*itr).Bid;
        values << ", " << (*itr).Price;
        values << ", " << (*itr).Qty;
        values << ", " << (*itr).Qty;
        values << ", " << trnTime;
        values << ", 1"; // orderState
        values << ", 1"; // minVolume
        values << ", 0"; // contraband
        values << ", 0"; // accountID
        values << ", 365"; // duration
        values << ", 0"; // isCorp
        values << ", " << solarSystemID;
        values << ", 0"; // escrow
        values << ", 1"; // jumps
        values << ")";
        itr++;
    }
    // Check to see if were being requested to stop?  Or if the database has closed!
    if (stopNPCMarketSeeding || sDatabase.GetStatus() == sDatabase.Closed)
    {
        sLog.Warning("Failed to complete NPC market seeding from file %s.", marketFile.c_str());
        return false;
    }
    // Process the sql command.
    if (!sDatabase.RunQueryLID(err, orderID,
                               "INSERT INTO market_orders ("
                               "    typeID, charID, regionID, stationID,"
                               "    `range`, bid, price, volEntered, volRemaining, issued,"
                               "    orderState, minVolume, contraband, accountID, duration,"
                               "    isCorp, solarSystemID, escrow, jumps "
                               " ) VALUES %s",
                               values.str().c_str()
                               ))
    {
        codelog(MARKET__ERROR, "Error in query: %s", err.c_str());
        return false;
    }
    newOrders.clear();

    return true;
}

bool NPCMarket::ProcessOrder(const TiXmlElement* ele)
{
    order.Price = 0;
    order.Bid = 0;
    order.TypeID = 0;
    order.Qty = 0;
    // Parse the <order> element
    const bool result = ParseElementChildren(ele);
    // If all of the order information was found add it to the list of new orders.
    if (order.Price != 0 && order.Qty != 0 && order.TypeID != 0)
    {
        newOrders.push_back(order);
    }
    return result;
}

#ifdef HAVE_WINDOWS_H
DWORD WINAPI NPCMarket::NPCMarketTask(LPVOID arg)
#else /* !HAVE_WINDOWS_H */
void* NPCMarket::NPCMarketTask(void* arg)
#endif /* !HAVE_WINDOWS_H */
{
    // Get the NPCMarket object.
    NPCMarket* npcMarket = reinterpret_cast<NPCMarket*> (arg);
    assert(npcMarket != NULL);

    // Run the seeding task.
    npcMarket->NPCMarketTask();
    npcMarketSeederRunning = false;

    // Free the market object.
    delete npcMarket;

#ifdef HAVE_WINDOWS_H
    return 0;
#else /* !HAVE_WINDOWS_H */
    return NULL;
#endif /* !HAVE_WINDOWS_H */
}

void NPCMarket::NPCMarketTask()
{
    // Lock the task.
    MutexLock lock(mMarket, false);
    if (mMarket.TryLock())
    {
        npcMarketSeederRunning = true;
        // Tried to lock the mutex and succeeded, there is not another task running.
        if (_verbose)
        {
            sLog.Log("NPCMarket", "Regenerating NPC market from file %s", marketFile.c_str());
        }
        DBerror err;

        // Delete all old market orders.
        // TO-DO: make this safe for concurrency.
        if (_verbose)
        {
            sLog.Log("NPCMarket", "Deleting old NPC orders.");
        }
        if (!sDatabase.RunQuery(err, "DELETE FROM market_orders WHERE duration > 90"))
        {
            _log(MARKET__ERROR, "Error in query: %s.", err.c_str());
            sLog.Log("NPCMarket", "Failed to clear old NPC market.");
            return;
        }

        if (_verbose)
        {
            sLog.Log("NPCMarket", "Reading NPC Market xml file %s", marketFile.c_str());
        }
        // Process the file.
        if (!ParseFile(marketFile.c_str()))
        {
            sLog.Warning("Failed to generate NPC market from %s.", marketFile.c_str());
        }
        else
        {
            sLog.Log("NPCMarket", "NPC market created from file %s", marketFile.c_str());
        }
    }
}
