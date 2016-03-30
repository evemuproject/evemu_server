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

#ifndef STASTATIONTYPE_H
#define	STASTATIONTYPE_H

#include "inv/InvType.h"
#include "utils/gpoint.h"
#include <map>
#include <memory>

class StaStationType;
typedef std::shared_ptr<StaStationType> StaStationTypeRef;

class StaStationType
{
public:
    StaStationType(
                   uint32 _stationTypeID,
                   double _dockEntryX,
                   double _dockEntryY,
                   double _dockEntryZ,
                   double _dockOrientationX,
                   double _dockOrientationY,
                   double _dockOrientationZ,
                   uint32 _operationID,
                   uint32 _officeSlots,
                   double _reprocessingEfficiency,
                   bool _conquerable,
                   uint32 _dockingBayGraphicID,
                   uint32 _hangarGraphicID
                   );

    const uint32 stationTypeID;
    const double dockEntryX;
    const double dockEntryY;
    const double dockEntryZ;
    const double dockOrientationX;
    const double dockOrientationY;
    const double dockOrientationZ;
    const uint32 operationID;
    const uint32 officeSlots;
    const double reprocessingEfficiency;
    const bool conquerable;
    // From extStaStationTypes
    const uint32 dockingBayGraphicID;
    const uint32 hangarGraphicID;

    // Convenience values.
    const GPoint dockEntry;
    const GVector dockOrientation;

    /**
     * Get the StaStationType for the specified typeID
     * @param typeID The typeID to find.
     * @return The StaStationType or nullptr if not found.
     */
    static StaStationTypeRef getType(uint32 typeID)
    {
        auto itr = s_AllTypes.find(typeID);
        if (itr == s_AllTypes.end())
        {
            return std::shared_ptr<StaStationType>();
        }
        return itr->second;
    }

    /**
     * Get the StaStationType for the specified typeID
     * @param typeID The typeID to find.
     * @param type The location to store the found type.
     * @return True if type was found.
     */
    static bool getType(uint32 typeID, StaStationTypeRef &type)
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
     * Get the InvType for the stationType.
     * @return The InvType or nullptr if not found.
     */
    InvTypeRef getType()
    {
        return InvType::getType(stationTypeID);
    }

private:
    StaStationType(const StaStationType& orig) = delete;
    virtual ~StaStationType();

    static std::map<uint32, StaStationTypeRef> s_AllTypes;
};

#endif	/* STASTATIONTYPE_H */

