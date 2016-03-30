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

#ifndef __SHIP__H__INCL__
#define __SHIP__H__INCL__

#include "inventory/ItemType.h"
#include "inventory/Inventory.h"
#include "inventory/InventoryItem.h"
#include "system/SystemEntity.h"
#include "ship/ModuleManager.h"
#include "ship/modules/Modules.h"

class ShipOperatorInterface;

#define SHIP_PROCESS_TICK_MS	5000

/**
 * InventoryItem which represents ship.
 */
class Ship
: public InventoryItem,
  public InventoryEx
{
    friend class InventoryItem;    // to let it construct us
public:
    /**
     * Loads ship from DB.
     *
     * @param[in] factory
     * @param[in] shipID ID of ship to load.
     * @return Pointer to Ship object; NULL if failed.
     */
    static ShipRef Load(uint32 shipID);
    /**
     * Spawns new ship.
     *
     * @param[in] factory
     * @param[in] data Item data for ship.
     * @return Pointer to new Ship object; NULL if failed.
     */
    static ShipRef Spawn(ItemData &data);

    /*
     * Primary public interface:
     */
    void Delete();

    /*
     * _ExecAdd validation interface:
     */
    double GetCapacity(EVEItemFlags flag) const;
	double GetRemainingVolumeByFlag(EVEItemFlags flag) const;
    virtual bool ValidateAddItem(EVEItemFlags flag, InventoryItemRef item) const;
    /*
     * Checks for conflicts between ship and fitting
     */
    bool ValidateItemSpecifics(InventoryItemRef equip) const;

/*
     * Public fields:
     */
    /*
     * Primary public packet builders:
     */
    PyDict *ShipGetInfo();
    PyDict *ShipGetState();

    /*
     * Saves the ship state
     */
    void SaveShip();

    /*
     * Inform Ship that it is docking or undocking
     */
    void Dock();
	void Undock();

    /* begin new module manager interface */
	InventoryItemRef GetModule(EVEItemFlags flag);
	InventoryItemRef GetModule(uint32 itemID);
    uint32 FindAvailableModuleSlot( InventoryItemRef item );
    EvilNumber GetMaxTurrentHardpoints() { return GetAttribute(AttrTurretSlotsLeft); }
    EvilNumber GetMaxLauncherHardpoints() { return GetAttribute(AttrLauncherSlotsLeft); }
    uint32 AddItem( EVEItemFlags flag, InventoryItemRef item);
    void RemoveItem(InventoryItemRef item, uint32 inventoryID, EVEItemFlags flag);
    /**
     * Alter the quantity of an item in the ships cargo.
     * @param item The item to alter.
     * @param qtyChange The amount to change.
     * @return True if the change was successful.
     */
    bool AlterCargoQty(InventoryItemRef item, int qtyChange);
    void UpdateModules();
    void UnloadModule(uint32 itemID);
    void UnloadAllModules();
    void RepairModules();
	void Online(uint32 moduleID);
	void Offline(uint32 moduleID);
    int32 Activate(int32 itemID, std::string effectName, int32 targetID, int32 repeat);
    void Deactivate(int32 itemID, std::string effectName);
	void Overload();
	void CancelOverloading();
    void ReplaceCharges(EVEItemFlags flag, InventoryItemRef newCharge);
    void RemoveRig(InventoryItemRef item, uint32 inventoryID);
    void Process();
    void DeactivateAllModules();
    void OnlineAll();
    ShipOperatorInterface * GetOperator() { return m_pOperator; }
    std::vector<GenericModule *> GetStackedItems(uint32 typeID, ModulePowerLevel level);

	// Tactical Interface:
	void SetShipShields(double shieldChargeFraction);
	void SetShipArmor(double armorHealthFraction);
	void SetShipHull(double hullHealthFraction);
	void SetShipCapacitorLevel(double capacitorChargeFraction);

    // External Methods For use by hostile entities directing effects to this entity:
    int32 ApplyRemoteEffect() { assert(true); }     // DO NOT CALL THIS YET!!!  This function needs to call down to ModuleManager::RemoveRemoteEffect with the proper argument list.
    int32 RemoveRemoteEffect() { assert(true); }    // DO NOT CALL THIS YET!!!  This function needs to call down to ModuleManager::RemoveRemoteEffect with the proper argument list.

protected:
    Ship(
        uint32 _shipID,
        // InventoryItem stuff:
         const ItemType &_shipType,
        const ItemData &_data
    );

    /*
     * Member functions
     */
    using InventoryItem::_Load;

    // Template loader:
    template<class _Ty>
    static RefPtr<_Ty> _LoadItem(uint32 shipID,
        // InventoryItem stuff:
        const ItemType &type, const ItemData &data)
    {
        // check it's a ship
        if( type.categoryID() != EVEDB::invCategories::Ship )
        {
            _log(ITEM__ERROR, "Trying to load %s as Ship.", type.category()->categoryName.c_str());
            return RefPtr<_Ty>();
        }

        // no additional stuff

        return _Ty::template _LoadShip<_Ty>(shipID, type, data);
    }

    // Actual loading stuff:
    template<class _Ty>
    static RefPtr<_Ty> _LoadShip(uint32 shipID,
        // InventoryItem stuff:
                                 const ItemType &shipType, const ItemData &data
    );

    bool _Load();

    static uint32 _Spawn(
        // InventoryItem stuff:
        ItemData &data
    );

    uint32 inventoryID() const { return itemID(); }
    PyRep *GetItem() const { return GetItemRow(); }

    void AddItem(InventoryItemRef item);

	void _UpdateCargoHoldsUsedVolume();
	void _IncreaseCargoHoldsUsedVolume(EVEItemFlags flag, double volumeToConsume);	// To release cargo space, make 'volumeToConsume' negative
	void _DecreaseCargoHoldsUsedVolume(EVEItemFlags flag, double volumeToConsume);	// To release cargo space, make 'volumeToConsume' negative

	const uint32 m_processTimerTick;
    Timer m_processTimer;

    // Access to the pilot object, which could be Client, NPC, or other type,
    // so access is through an interface object.
    ShipOperatorInterface * m_pOperator;    // We own this

    //the ship's module manager.  We own this
    ModuleManager * m_ModuleManager;
};

/**
 * DynamicSystemEntity which represents ship object in space
 */
class InventoryItem;
class DestinyManager;
class SystemManager;

class ShipEntity
: public DynamicSystemEntity
{
public:
    ShipEntity(
        ShipRef ship,
        SystemManager *system,
        const GPoint &position);
    ~ShipEntity();

    /*
     * Primary public interface:
     */
    ShipRef GetShipObject() { return _shipRef; }
    DestinyManager * GetDestiny() { return m_destiny; }
    SystemManager * GetSystem() { return m_system; }

    /*
     * Public fields:
     */

    inline double x() const { return(GetPosition().x); }
    inline double y() const { return(GetPosition().y); }
    inline double z() const { return(GetPosition().z); }

    //SystemEntity interface:
    virtual EntityClass GetClass() const { return(ecShipEntity); }
    virtual bool IsShipEntity() const { return true; }
    virtual ShipEntity *CastToShipEntity() { return(this); }
    virtual const ShipEntity *CastToShipEntity() const { return(this); }
    virtual void Process();
    virtual void EncodeDestiny( Buffer& into ) const;
    virtual void QueueDestinyUpdate(PyTuple **du) {/* not required to consume */}
    virtual void QueueDestinyEvent(PyTuple **multiEvent) {/* not required to consume */}
    virtual uint32 GetCorporationID() const { return(1); }
    virtual uint32 GetAllianceID() const { return(0); }
    virtual void Killed(Damage &fatal_blow);
    virtual SystemManager *System() const { return(m_system); }

    void ForcedSetPosition(const GPoint &pt);

    virtual bool ApplyDamage(Damage &d);
    virtual void MakeDamageState(DoDestinyDamageState &into) const;

    void SendNotification(const PyAddress &dest, EVENotificationStream &noti, bool seq=true);
    void SendNotification(const char *notifyType, const char *idType, PyTuple **payload, bool seq=true);

protected:
    /*
     * Member functions
     */
    void _ReduceDamage(Damage &d);
    void ApplyDamageModifiers(Damage &d, SystemEntity *target);
    void _DropLoot(SystemEntity *owner);

    /*
     * Member fields:
     */
    SystemManager *const m_system;    //we do not own this
    ShipRef _shipRef;   // We don't own this

    /* Used to calculate the damages on NPCs
     * I don't know why, npc->Set_shieldCharge does not work
     * calling npc->shieldCharge() return the complete shield
     * So we get the values on creation and use then instead.
    */
    double m_shieldCharge;
    double m_armorDamage;
    double m_hullDamage;
};

#endif /* !__SHIP__H__INCL__ */


