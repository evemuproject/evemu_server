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
    Author:        eve-moo
 */

#include "eve-server.h"

#include "EntityList.h"
#include "inventory/ItemRef.h"
#include "system/SystemBubble.h"
#include "system/SystemManager.h"
#include "ship/modules/mining_modules/SurveyScanner.h"
#include "Client.h"

SurveyScanner::SurveyScanner(InventoryItemRef item, ShipRef ship)
: ActiveModule(item, ship)
{
    m_effectString = "effects.SurveyScan";
}

void SurveyScanner::startCycle(bool continuing)
{
    m_ship->GetOperator()->GetDestiny()->SendSpecialEffect(
                                                           m_ship, m_item->itemID(), m_item->typeID(),
                                                           0, 0, "effects.SurveyScan", false, true, true,
                                                           getCycleTime(), 0);
}

bool SurveyScanner::endCycle(bool continuing)
{
    Client *c = EntityList::FindCharacter(m_ship->ownerID());
    SystemEntity *shipEntity = m_ship->GetOperator()->GetSystemEntity();
    SystemBubble *bubble = shipEntity->Bubble();
    if (bubble == nullptr || c == nullptr)
    {
        return false;
    }
    // Construct response packet.
    PyTuple *result = new PyTuple(2);
    result->SetItem(0, new PyString("OnSurveyScanComplete"));
    PyList *roids = new PyList();
    result->SetItem(1, roids);
    // Get max scan distance.
    double maxDist = m_item->GetAttribute(AttrSurveyScanRange).get_float();
    // Search for asteroids in range.
    std::set<SystemEntity *> entities;
    bubble->GetEntities(entities);
    for (auto entity : entities)
    {
        InventoryItemRef item = entity->Item();
        // Is the item an asteroid?
        if (item->categoryID() == EVEDB::invCategories::Asteroid ||
            item->groupID() == EVEDB::invGroups::Harvestable_Cloud)
        {
            // Yes, is it in range?
            Vector3D rel = entity->GetPosition() - shipEntity->GetPosition();
            if (rel.length() - entity->GetRadius() <= maxDist)
            {
                // Yes, add it to list.
                PyTuple *roid = new PyTuple(3);
                roid->SetItem(0, new PyInt(item->itemID()));
                roid->SetItem(1, new PyInt(item->typeID()));
                roid->SetItem(2, new PyInt(item->GetAttribute(AttrQuantity).get_int()));
                roids->AddItem(roid);
            }
        }
    }
    // Send results.
    c->QueueDestinyEvent(&result);
    return false;
}
