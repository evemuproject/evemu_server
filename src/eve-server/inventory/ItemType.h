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
    Author:        Bloody.Rabbit
*/

#ifndef __ITEM_TYPE__H__INCL__
#define __ITEM_TYPE__H__INCL__

#include "inv/InvCategory.h"
#include "inv/InvGroup.h"

#include "inventory/EVEAttributeMgr.h"
#include "inventory/ItemFactory.h"

/*
 * LOADING INVOKATION EXPLANATION:
 * ItemCategory, ItemGroup, ItemType and InventoryItem classes and their children have special loading. Every such type has following methods:
 *
 *  static Load(<identifier>):
 *    Merges static and virtual loading trees.
 *    First calls static _Load() to create desired object and
 *    then calls its virtual _Load() (if the type has any).
 *
 *  static _Load(<identifier>[, <data-argument>, ...]):
 *    These functions gradually, one by one, load any data needed to create desired
 *    type and in the end they create the type object.
 *
 *  virtual _Load() (optional):
 *    Performs any post-construction loading.
 */

/*
 * Simple container for raw type data.
 */
class TypeData {
public:
    TypeData(
        uint32 _groupID = 0,
        const char *_name = "",
        const char *_desc = "",
        double _radius = 0.0,
        double _mass = 0.0,
        double _volume = 0.0,
        double _capacity = 0.0,
        uint32 _portionSize = 0,
        EVERace _race = (EVERace)0,
        double _basePrice = 0.0,
        bool _published = false,
        uint32 _marketGroupID = 0,
        double _chanceOfDuplicating = 0.0
    );

    // Content:
    uint32 groupID;
    std::string name;
    std::string description;
    double radius;
    double mass;
    double volume;
    double capacity;
    uint32 portionSize;
    EVERace race;
    double basePrice;
    bool published;
    uint32 marketGroupID;
    double chanceOfDuplicating;
};

/*
 * Class which maintains type data.
 */
class ItemType {
public:
    /**
     * Loads type from DB.
     *
     * @param[in] typeID ID of type to load.
     * @return Pointer to new ItemType object; NULL if failed.
     */
    static ItemType *Load(uint32 typeID);

    /*
     * Attributes:
     */
    TypeAttributeMgr attributes;

    /*
     * Helper methods
     */
    uint32 id() const { return(m_id);
    }

    const InvGroupRef group() const
    {
        return (m_group);
    }

    uint32 groupID() const
    {
        return m_group->groupID;
    }

    const InvCategoryRef category() const
    {
        return InvCategory::getCategory(categoryID());
    }

    uint32 categoryID() const
    {
        return (m_group->categoryID);
    }

    const std::string &name() const { return(m_name); }
    const std::string &description() const  { return(m_description); }
    uint32 portionSize() const { return(m_portionSize); }
    double basePrice() const { return(m_basePrice); }
    bool published() const { return(m_published); }
    uint32 marketGroupID() const { return(m_marketGroupID); }
    double chanceOfDuplicating() const { return(m_chanceOfDuplicating); }

    double radius() const { return(attributes.radius()); }
    double mass() const { return(attributes.mass()); }
    double volume() const { return(attributes.volume()); }
    double capacity() const { return(attributes.capacity()); }
    EVERace race() const { return(static_cast<EVERace>(attributes.raceID())); }
	bool HasEffect(uint32 effectID) const
	{
		if(std::find(m_effects.begin(), m_effects.end(), effectID)!=m_effects.end())
			return true;
		else
			return false;
	}

protected:
    ItemType(
        uint32 _id,
             const InvGroupRef _group,
        const TypeData &_data
    );

	std::vector<uint32> m_effects;

	/*
     * Member functions
     */
    // Template helper:
    template<class _Ty>
    static _Ty *Load(uint32 typeID)
    {
        // static load
        _Ty *t = _Ty::template _Load<_Ty>( typeID );
        if( t == NULL )
            return NULL;

        // dynamic load
        if( !t->_Load() )
        {
            delete t;
            return NULL;
        }

        // return
        return t;
    }

    // Template loader:
    template<class _Ty>
    static _Ty *_Load(uint32 typeID)
    {
        // pull data
        TypeData data;
        if( !InventoryDB::GetType( typeID, data ) )
            return NULL;

        // obtain group
        InvGroupRef g;
        if (!InvGroup::getGroup(data.groupID, g))
        {
            return NULL;
        }

        return _Ty::template _LoadType<_Ty>( typeID, g, data );
    }

    // Actual loading stuff:
    template<class _Ty>
    static _Ty *_LoadType(uint32 typeID,
        // ItemType stuff:
                          const InvGroupRef group, const TypeData &data
    );

    virtual bool _Load();

    /*
     * Data members
     */
    const uint32 m_id;

    const InvGroupRef m_group;

    std::string m_name;
    std::string m_description;
    uint32 m_portionSize;
    double m_basePrice;
    bool m_published;
    uint32 m_marketGroupID;
    double m_chanceOfDuplicating;
};

#endif /* __ITEM_TYPE__H__INCL__ */



