/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2011 The EVEmu Team
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
#ifndef __COMMANDDB_H_INCL__
#define __COMMANDDB_H_INCL__

#include "ServiceDB.h"

class CommandDB
: public ServiceDB
{
public:
    bool ItemSearch(const char *query, std::map<uint32, std::string> &into);
    bool ItemSearch(uint32 typeID, uint32 &actualTypeID, std::string &actualTypeName,
        uint32 &actualGroupID, uint32 &actualCategoryID, double &actualRadius);
    bool GetRoidDist(const char * sec, std::map<double, uint32> &roids);
    int GetAttributeID(const char *attributeName);
    int GetAccountID(std::string name);
	bool FullSkillList(std::vector<uint32> &skillList);
};





#endif


