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

#ifndef CHRBLOODLINE_H
#define	CHRBLOODLINE_H

#include "inv/InvType.h"
#include <map>
#include <memory>

class ChrBloodline;
typedef std::shared_ptr<ChrBloodline> ChrBloodlineRef;

class ChrBloodline
{
public:
    ChrBloodline(
                 uint32 _bloodlineID,
                 std::string _bloodlineName,
                 uint32 _raceID,
                 std::string _description,
                 std::string _maleDescription,
                 std::string _femaleDescription,
                 uint32 _shipTypeID,
                 uint32 _corporationID,
                 uint8 _perception,
                 uint8 _willpower,
                 uint8 _charisma,
                 uint8 _memory,
                 uint8 _intelligence,
                 uint32 _iconID,
                 std::string _shortDescription,
                 std::string _shortMaleDescription,
                 std::string _shortFemaleDescription
                 );

    const uint32 bloodlineID;
    const std::string bloodlineName;
    const uint32 raceID;
    const std::string description;
    const std::string maleDescription;
    const std::string femaleDescription;
    const uint32 shipTypeID;
    const uint32 corporationID;
    const uint8 perception;
    const uint8 willpower;
    const uint8 charisma;
    const uint8 memory;
    const uint8 intelligence;
    const uint32 iconID;
    const std::string shortDescription;
    const std::string shortMaleDescription;
    const std::string shortFemaleDescription;

    /**
     * Get the ChrBloodline for the specified bloodlineID
     * @param bloodlineID The bloodlineID to find.
     * @return The ChrBloodline or nullptr if not found.
     */
    static ChrBloodlineRef getBloodline(uint32 bloodlineID)
    {
        auto itr = s_AllBloodlines.find(bloodlineID);
        if (itr == s_AllBloodlines.end())
        {
            return std::shared_ptr<ChrBloodline>();
        }
        return itr->second;
    }

    /**
     * Get the ChrBloodline for the specified bloodlineID
     * @param bloodlineID The bloodlineID to find.
     * @param bloodline The location to store the found bloodline.
     * @return True if bloodline was found.
     */
    static bool getBloodline(uint32 bloodlineID, ChrBloodlineRef &bloodline)
    {
        auto itr = s_AllBloodlines.find(bloodlineID);
        if (itr == s_AllBloodlines.end())
        {
            bloodline.reset();
            return false;
        }
        bloodline = itr->second;
        return true;
    }

private:
    ChrBloodline(const ChrBloodline& orig) = delete;
    virtual ~ChrBloodline();

    static std::map<uint32, ChrBloodlineRef> s_AllBloodlines;
};

#endif	/* CHRBLOODLINE_H */

