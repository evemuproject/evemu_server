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

#include "eveStatic.h"

#include <mutex>

bool EVEStatic::staticLoaded = false;
PyRep *EVEStatic::m_InvTypesCache = nullptr;
PyRep *EVEStatic::m_InvGroupsCache = nullptr;
PyRep *EVEStatic::m_InvCategoriesCache = nullptr;
PyRep *EVEStatic::m_InvBlueprintTypesCache = nullptr;

bool EVEStatic::loadStaticData()
{
    static std::mutex sMutex;
    auto lock = std::unique_lock<std::mutex>(sMutex);
    if (staticLoaded)
    {
        return true;
    }

    std::map<uint32, std::vector < uint32>> groupTypeList;
    std::map<uint32, std::vector < uint32>> categoryGroupList;
    //-------------------------------
    // Load the invTypes table
    //-------------------------------
    if (!loadInvTypes(groupTypeList))
    {
        return false;
    }

    //-------------------------------
    // Load the invGroups table
    //-------------------------------
    if (!loadInvGroups(groupTypeList, categoryGroupList))
    {
        return false;
    }

    //-------------------------------
    // Load the invCategories table
    //-------------------------------
    if (!loadInvCategories(categoryGroupList))
    {
        return false;
    }

    //-------------------------------
    // Load the invBlueprintTypes table
    //-------------------------------
    if (!loadInvBlueprintTypes())
    {
        return false;
    }

    //-------------------------------
    // Load the staStationTypes table
    //-------------------------------
    if (!loadStaStationTypes())
    {
        return false;
    }

    //-------------------------------
    // Load the blkShipTypes table
    //-------------------------------
    if (!loadBlkShipTypes())
    {
        return false;
    }

    //-------------------------------
    // Load the chrBloodlines table
    //-------------------------------
    if (!loadChrBloodlines())
    {
        return false;
    }

    staticLoaded = true;
    return true;
}
