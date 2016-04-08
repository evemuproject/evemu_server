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
#include <algorithm>

#include "InvGroup.h"
#include "utils/EvilNumber.h"

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
            uint32 _iconID,
            std::map<uint32, EvilNumber> &_attributes,
            std::vector<uint32> _effects,
            uint32 _defaultEffect
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

    const std::map<uint32, EvilNumber> m_attributes;
    const std::vector<uint32> m_effects;
    const uint32 m_defaultEffect;

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

    /**
     * Get the types group.
     * @return The InvGroup.
     */
    InvGroupRef getGroup()
    {
        return InvGroup::getGroup(groupID);
    }

    /**
     * Get the types category.
     * @return The InvCategory.
     */
    InvCategoryRef getCategory()
    {
        return InvCategory::getCategory(getCategoryID());
    }

    bool hasEffect(uint32 effectID)
    {
        if (m_effects.empty())
        {
            return false;
        }
        return std::find(m_effects.begin(), m_effects.end(), effectID) != m_effects.end();
    }
    bool hasAttribute(uint32 attrID)
    {
        auto itr = m_attributes.find(attrID);
        return itr != m_attributes.end();
    }
    EvilNumber getAttribute(uint32 attrID)
    {
        auto itr = m_attributes.find(attrID);
        if (itr != m_attributes.end())
        {
            itr->second;
        }
        return 0;
    }

    int64 getIntAttribute(uint32 attrID)
    {
        auto itr = m_attributes.find(attrID);
        if (itr != m_attributes.end())
        {
            itr->second.get_int();
        }
        return 0;
    }

    double getDoubleAttribute(uint32 attrID)
    {
        auto itr = m_attributes.find(attrID);
        if (itr != m_attributes.end())
        {
            itr->second.get_float();
        }
        return 0;
    }

    bool fetchAttribute(const uint32 attributeID, EvilNumber &value) const
    {
        auto itr = m_attributes.find(attributeID);
        if (itr != m_attributes.end())
        {
            value = itr->second;
            return true;
        }
        return false;
    }

    bool fetchAttribute(const uint32 attributeID, double &value) const
    {
        auto itr = m_attributes.find(attributeID);
        if (itr != m_attributes.end())
        {
            value = itr->second.get_float();
            return true;
        }
        return false;
    }

    bool fetchAttribute(const uint32 attributeID, float &value) const
    {
        auto itr = m_attributes.find(attributeID);
        if (itr != m_attributes.end())
        {
            value = itr->second.get_float();
            return true;
        }
        return false;
    }

    bool fetchAttribute(const uint32 attributeID, int32 &value) const
    {
        auto itr = m_attributes.find(attributeID);
        if (itr != m_attributes.end())
        {
            value = itr->second.get_int();
            return true;
        }
        return false;
    }

    bool fetchAttribute(const uint32 attributeID, uint32 &value) const
    {
        auto itr = m_attributes.find(attributeID);
        if (itr != m_attributes.end())
        {
            value = itr->second.get_int();
            return true;
        }
        return false;
    }

    bool fetchAttribute(const uint32 attributeID, int64 &value) const
    {
        auto itr = m_attributes.find(attributeID);
        if (itr != m_attributes.end())
        {
            value = itr->second.get_int();
            return true;
        }
        return false;
    }

    bool fetchAttribute(const uint32 attributeID, uint64 &value) const
    {
        auto itr = m_attributes.find(attributeID);
        if (itr != m_attributes.end())
        {
            value = itr->second.get_int();
            return true;
        }
        return false;
    }


private:
    virtual ~InvType();
    InvType(const InvType& orig) = delete;

    static std::map<uint32, InvTypeRef> s_AllTypes;
};

#endif	/* INVTYPES_H */

