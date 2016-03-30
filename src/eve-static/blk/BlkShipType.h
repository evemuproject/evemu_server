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

#ifndef BLKSHIPTYPE_H
#define	BLKSHIPTYPE_H

#include "inv/InvType.h"
#include <map>
#include <memory>

class BlkShipType;
typedef std::shared_ptr<BlkShipType> BlkShipTypeRef;

class BlkShipType
{
public:
    BlkShipType(
                uint32 _shipTypeID,
                uint32 _weaponTypeID,
                uint32 _miningTypeID,
                uint32 _skillTypeID
                );

    const uint32 shipTypeID;
    const uint32 weaponTypeID;
    const uint32 miningTypeID;
    const uint32 skillTypeID;

    /**
     * Get the BlkShipType for the specified typeID
     * @param typeID The typeID to find.
     * @return The BlkShipType or nullptr if not found.
     */
    static BlkShipTypeRef getType(uint32 typeID)
    {
        auto itr = s_AllTypes.find(typeID);
        if (itr == s_AllTypes.end())
        {
            return std::shared_ptr<BlkShipType>();
        }
        return itr->second;
    }

    /**
     * Get the BlkShipType for the specified typeID
     * @param typeID The typeID to find.
     * @param type The location to store the found type.
     * @return True if type was found.
     */
    static bool getType(uint32 typeID, BlkShipTypeRef &type)
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

    /**
     * Get the InvType for the shipType.
     * @return The InvType or nullptr if not found.
     */
    InvTypeRef getType()
    {
        return InvType::getType(shipTypeID);
    }

private:
    BlkShipType(const BlkShipType& orig) = delete;
    virtual ~BlkShipType();

    static std::map<uint32, BlkShipTypeRef> s_AllTypes;
};

#endif	/* BLKSHIPTYPE_H */

