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
    Author:        Zhur
*/
#ifndef EVE_ITEM_FACTORY_H
#define EVE_ITEM_FACTORY_H

#include "inventory/InventoryDB.h"
#include "inventory/ItemRef.h"

class ItemGroup;

class ItemType;
class CharacterType;
class ShipType;
class StationType;

class Inventory;

class ItemFactory
{
    friend class InventoryItem; //only for access to _DeleteItem
    friend class Inventory; //only for access to _DeleteItem
private:
    ItemFactory() = delete;

public:
    static void Shutdown();

    /*
     * Type stuff
     */
    static const ItemType *GetType(uint32 typeID);

    /**
     * Loads character type, caches it and returns it.
     *
     * @param[in] characterTypeID Character type to be returned.
     * @return Pointer to character type data container; NULL if fails.
     */
    static const CharacterType *GetCharacterType(uint32 characterTypeID);
    /**
     * Loads character type, caches it and returns it.
     *
     * @param[in] characterTypeID Character type to be returned.
     * @return Pointer to character type data container; NULL if fails.
     */
    static const CharacterType *GetCharacterTypeByBloodline(uint32 bloodlineID);

    /**
     * Loads ship type, caches it and returns it.
     *
     * @param[in] shipTypeID ID of ship type.
     * @return Pointer to ship type data container; NULL if fails.
     */
    static const ShipType *GetShipType(uint32 shipTypeID);

    /**
     * Loads station type, caches it and returns it.
     *
     * @param[in] stationTypeID ID of station type to load.
     * @return Pointer to StationType object; NULL if fails.
     */
    static const StationType *GetStationType(uint32 stationTypeID);

    /*
     * Item stuff
     */
    static InventoryItemRef GetItem(uint32 itemID);

    static BlueprintRef GetBlueprint(uint32 blueprintID);

    /**
     * Loads character.
     *
     * @param[in] character ID of character to load.
     * @return Pointer to Character object; NULL if load failed.
     */
    static CharacterRef GetCharacter(uint32 characterID);

    /**
     * Loads ship.
     *
     * @param[in] shipID ID of ship to load.
     * @return Pointer to Ship object; NULL if failed.
     */
    static ShipRef GetShip(uint32 shipID);

    /**
     * Loads celestial object.
     *
     * @param[in] celestialID ID of celestial object to load.
     * @return Pointer to CelestialObject; NULL if fails.
     */
    static CelestialObjectRef GetCelestialObject(uint32 celestialID);

    /**
     * Loads solar system.
     *
     * @param[in] solarSystemID ID of solar system to load.
     * @return Pointer to solar system object; NULL if failed.
     */
    static SolarSystemRef GetSolarSystem(uint32 solarSystemID);

    /**
     * Loads station.
     *
     * @param[in] stationID ID of station to load.
     * @return Pointer to Station object; NULL if fails.
     */
    static StationRef GetStation(uint32 stationID);

    /**
     * Loads skill.
     *
     * @param[in] skillID ID of skill to load.
     * @return Pointer to Skill object; NULL if fails.
     */
    static SkillRef GetSkill(uint32 skillID);

    /**
     * Loads owner.
     *
     * @param[in] ownerID ID of owner to load.
     * @return Ref to Owner object.
     */
    static OwnerRef GetOwner(uint32 ownerID);

    /**
     * Loads structure object.
     *
     * @param[in] structureID ID of structure object to load.
     * @return Pointer to Structure; NULL if fails.
     */
    static StructureRef GetStructure(uint32 structureID);

    /**
     * Loads cargo container object.
     *
     * @param[in] containerID ID of cargo container object to load.
     * @return Pointer to CargoContainer; NULL if fails.
     */
    static CargoContainerRef GetCargoContainer(uint32 containerID);

    //spawn a new item with the specified information, creating it in the DB as well.
    static InventoryItemRef SpawnItem(ItemData &data);
    static BlueprintRef SpawnBlueprint(ItemData &data, BlueprintData &bpData);
    /**
     * Spawns new character, caches it and returns it.
     *
     * @param[in] data Item data (for srvEntity table).
     * @param[in] charData Character data.
     * @param[in] appData Character's appearance.
     * @param[in] corpData Character's corporation-membership data.
     * @return Pointer to new Character object; NULL if spawn failed.
     */
    static CharacterRef SpawnCharacter(ItemData &data, CharacterData &charData, CorpMemberInfo &corpData);
    /**
     * Spawns new ship.
     *
     * @param[in] data Item data for ship.
     * @return Pointer to Ship object; NULL if failed.
     */
    static ShipRef SpawnShip(ItemData &data);
    /**
     * Spawns new skill.
     *
     * @param[in] data Item data for skill.
     * @return Pointer to new Skill object; NULL if fails.
     */
    static SkillRef SpawnSkill(ItemData &data);
    /**
     * Spawns new owner.
     *
     * @param[in] data Item data for owner.
     * @return Ref to new Owner object.
     */
    static OwnerRef SpawnOwner(ItemData &data);
    /**
     * Spawns new structure.
     *
     * @param[in] data Item data for structure.
     * @return Ref to new Structure object.
     */
    static StructureRef SpawnStructure(ItemData &data);
    /**
     * Spawns new cargo container.
     *
     * @param[in] data Item data for cargo container.
     * @return Ref to new CargoContainer object.
     */
    static CargoContainerRef SpawnCargoContainer(ItemData &data);

    /*
     * Inventory stuff
     */
    static Inventory *GetInventory(uint32 inventoryID, bool load = true);

    static void SetUsingClient(Client *pClient);

    static Client * GetUsingClient();

    static void UnsetUsingClient();

    /*
     * ID Authority Functions:
     */
    static uint32 GetNextEntityID();

protected:
    static Client * m_pClient; // pointer to client currently using the ItemFactory, we do not own this

    /*
     * Member functions and variables:
     */
    // Groups:
    static std::map<uint32, ItemGroup *> m_groups;

    // Types:
    template<class _Ty>
    static const _Ty *_GetType(uint32 typeID);

    static std::map<uint32, ItemType *> m_types;

    // Items:
    template<class _Ty>
    static RefPtr<_Ty> _GetItem(uint32 itemID);

    static void _DeleteItem(uint32 itemID);

    static std::map<uint32, InventoryItemRef> m_items;

	// ID Authority:
	static uint32 m_nextEntityID;		// holds the next valid ID for in-memory only objects of EVEDB::invCategories::Entity
};


#endif

