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

#ifndef EVESTATIC_H
#define	EVESTATIC_H

#include "python/PyRep.h"
#include <map>
#include <vector>

class EVEStatic
{
public:
    static bool loadStaticData();

    static PyRep *getInvTypesCache()
    {

        return m_InvTypesCache;
    }

    static PyRep *getInvGroupsCache()
    {

        return m_InvGroupsCache;
    }

    static PyRep *getInvCategoriesCache()
    {

        return m_InvCategoriesCache;
    }

    static PyRep *getInvBlueprintTypesCache()
    {

        return m_InvBlueprintTypesCache;
    }

protected:
    static bool loadInvTypes(std::map<uint32, std::vector<uint32>> &groupTypeList);
    static bool loadInvGroups(std::map<uint32, std::vector<uint32>> &groupTypeList, std::map<uint32, std::vector < uint32>> &categoryGroupList);
    static bool loadInvCategories(std::map<uint32, std::vector < uint32>> &categoryGroupList);
    static bool loadInvBlueprintTypes();
    static bool loadStaStationTypes();
    static bool loadBlkShipTypes();

private:
    static bool staticLoaded;
    static PyRep *m_InvTypesCache;
    static PyRep *m_InvGroupsCache;
    static PyRep *m_InvCategoriesCache;
    static PyRep *m_InvBlueprintTypesCache;
};

#endif	/* EVESTATIC_H */

