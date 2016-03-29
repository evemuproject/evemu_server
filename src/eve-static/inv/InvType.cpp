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

#include <map>

#include "InvType.h"
#include "log/SystemLog.h"
#include "InvGroup.h"

std::map<uint32, InvTypeRef> InvType::s_AllTypes;

InvType::InvType(uint32 _typeID,
                 uint32 _groupID,
                 std::string &_typeName,
                 std::string &_description,
                 uint32 _graphicID,
                 double _radius,
                 double _mass,
                 double _volume,
                 double _capacity,
                 uint32 _portionSize,
                 uint32 _raceID,
                 double _basePrice,
                 bool _published,
                 uint32 _marketGroupID,
                 double _chanceOfDuplicating,
                 uint32 _iconID
                 ) :
typeID(_typeID),
groupID(_groupID),
typeName(_typeName),
description(_description),
graphicID(_graphicID),
radius(_radius),
mass(_mass),
volume(_volume),
capacity(_capacity),
portionSize(_portionSize),
raceID(_raceID),
basePrice(_basePrice),
published(_published),
marketGroupID(_marketGroupID),
chanceOfDuplicating(_chanceOfDuplicating),
iconID(_iconID)
{
    s_AllTypes[typeID] = InvTypeRef(this, [](InvType * type)
    {
        delete type;
    });
}

InvType::~InvType() { }

uint32 InvType::getCategoryID()
{
    InvGroupRef group;
    if (InvGroup::getGroup(groupID, group))
    {
        return group->categoryID;
    }
    return 0;
}
