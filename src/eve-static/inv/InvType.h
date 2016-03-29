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

#ifndef INVTYPES_H
#define	INVTYPES_H

#include "eve-compat.h"
#include <string>
#include <memory>
#include <map>

class InvType;
typedef std::shared_ptr<InvType> InvTypeRef;

class InvType
{
public:
    InvType(uint32 _typeID,
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
             );

    // From invTypes.
    const uint32 typeID;
    const uint32 groupID;
    const std::string typeName;
    const std::string description;
    const uint32 graphicID;
    const double radius;
    const double mass;
    const double volume;
    const double capacity;
    const uint32 portionSize;
    const uint32 raceID;
    const double basePrice;
    const bool published;
    const uint32 marketGroupID;
    const double chanceOfDuplicating;
    const uint32 iconID;

    uint32 getCategoryID();

    /**
     * Get the InvType for the specified typeID
     * @param typeID The typeID to find.
     * @return The InvType or nullptr if not found.
     */
    static InvTypeRef getType(uint32 typeID)
    {
        auto itr = s_AllTypes.find(typeID);
        if (itr == s_AllTypes.end())
        {
            return std::shared_ptr<InvType>();
        }
        return itr->second;
    }

    /**
     * Get the InvType for the specified typeID
     * @param typeID The typeID to find.
     * @param type The location to store the found type.
     * @return True if type was found.
     */
    static bool getType(uint32 typeID, InvTypeRef &type)
    {
        auto itr = s_AllTypes.find(typeID);
        if (itr == s_AllTypes.end())
        {
            type.reset();
            return false;
        }
        type = itr->second;
        return true;
    }

private:
    virtual ~InvType();
    InvType(const InvType& orig) = delete;

    static std::map<uint32, InvTypeRef> s_AllTypes;
};

#endif	/* INVTYPES_H */

