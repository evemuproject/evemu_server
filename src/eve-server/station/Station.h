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

#ifndef __STATION__H__INCL__
#define __STATION__H__INCL__

#include "sta/StaStationType.h"
#include "inventory/Inventory.h"
#include "system/Celestial.h"

/**
 * Data container for station.
 */
class StationData {
public:
    StationData(
        uint32 _security = 0,
        double _dockingCostPerVolume = 0.0,
        double _maxShipVolumeDockable = 0.0,
        uint32 _officeRentalCost = 0,
        uint32 _operationID = 0,
        double _reprocessingEfficiency = 0.0,
        double _reprocessingStationsTake = 0.0,
        EVEItemFlags _reprocessingHangarFlag = (EVEItemFlags)0
    );

    // Data members:
    uint32 security;
    double dockingCostPerVolume;
    double maxShipVolumeDockable;
    uint32 officeRentalCost;
    uint32 operationID;

    double reprocessingEfficiency;
    double reprocessingStationsTake;
    EVEItemFlags reprocessingHangarFlag;
};

/**
 * CelestialObject which represents station.
 */
class Station
: public CelestialObject,
  public Inventory
{
    friend class InventoryItem; // to let it construct us
    friend class CelestialObject; // to let it construct us
public:
    /**
     * Loads station.
     *
     * @param[in] stationID ID of station to load.
     * @return Pointer to new Station object; NULL if fails.
     */
    static StationRef Load(uint32 stationID);

    /*
     * Access methods:
     */
    uint32          security() const { return m_security; }
    double          dockingCostPerVolume() const { return m_dockingCostPerVolume; }
    double          maxShipVolumeDockable() const { return m_maxShipVolumeDockable; }
    uint32          officeRentalCost() const { return m_officeRentalCost; }
    uint32          operationID() const { return m_operationID; }

    double          reprocessingEfficiency() const { return m_reprocessingEfficiency; }
    double          reprocessingStationsTake() const { return m_reprocessingStationsTake; }
    EVEItemFlags    reprocessingHangarFlag() const { return m_reprocessingHangarFlag;
    }

    StaStationTypeRef GetStationType()
    {
        return m_stationType;
    }

protected:
    Station(
        uint32 _stationID,
        // InventoryItem stuff:
            const InvTypeRef _type,
        const ItemData &_data,
        // CelestialObject stuff:
        const CelestialObjectData &_cData,
        // Station stuff:
        const StationData &_stData
    );

    /*
     * Member functions:
     */
    using CelestialObject::_Load;

    // Template loader:
    template<class _Ty>
    static RefPtr<_Ty> _LoadCelestialObject(uint32 stationID,
        // InventoryItem stuff:
                                            const InvTypeRef stType, const ItemData &data,
        // CelestialObject stuff:
        const CelestialObjectData &cData)
    {
        // check it's a station
        if (stType->groupID != EVEDB::invGroups::Station)
        {
            _log(ITEM__ERROR, "Trying to load %s as Station.", stType->getGroup()->groupName.c_str());
            return RefPtr<_Ty>();
        }

        // load station data
        StationData stData;
        if (!InventoryDB::GetStation(stationID, stData))
            return RefPtr<_Ty>();

        return _Ty::template _LoadStation<_Ty>(  stationID, stType, data, cData, stData );
    }

    // Actual loading stuff:
    template<class _Ty>
    static RefPtr<_Ty> _LoadStation(uint32 stationID,
        // InventoryItem stuff:
                                    const InvTypeRef type, const ItemData &data,
        // CelestialObject stuff:
        const CelestialObjectData &cData,
        // Station stuff:
        const StationData &stData
    );

    bool _Load();
    static uint32 _Spawn(ItemData &data);

    uint32 inventoryID() const { return itemID(); }
    PyRep *GetItem() const { return GetItemRow(); }

    /*
     * Data members:
     */
    StaStationTypeRef m_stationType;
    uint32 m_security;
    double m_dockingCostPerVolume;
    double m_maxShipVolumeDockable;
    uint32 m_officeRentalCost;
    uint32 m_operationID;

    double m_reprocessingEfficiency;
    double m_reprocessingStationsTake;
    EVEItemFlags m_reprocessingHangarFlag;
};


/**
 * DynamicSystemEntity which represents Station object in space
 */
class InventoryItem;
class DestinyManager;
class SystemManager;

class StationEntity
: public DynamicSystemEntity
{
public:
    StationEntity(
        StationRef station,
        SystemManager *system,
        const GPoint &position);

    /*
     * Primary public interface:
     */
    StationRef GetStationObject() { return _stationRef; }
    DestinyManager * GetDestiny() { return m_destiny; }
    SystemManager * GetSystem() { return m_system; }

    /*
     * Public fields:
     */

    inline double x() const { return(GetPosition().x); }
    inline double y() const { return(GetPosition().y); }
    inline double z() const { return(GetPosition().z); }

    //SystemEntity interface:
    virtual EntityClass GetClass() const { return(ecStation); }
    virtual bool IsCelestialEntity() const { return true; }
    virtual bool IsStaticEntity() const { return true; }
    virtual bool IsVisibleSystemWide() const { return true; }
    virtual StationEntity *CastToStationEntity() { return(this); }
    virtual const StationEntity *CastToStationEntity() const { return(this); }
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

    /*
     * Member fields:
     */
    SystemManager *const m_system;    //we do not own this
    StationRef _stationRef;   // We don't own this

    /* Used to calculate the damages on NPCs
     * I don't know why, npc->Set_shieldCharge does not work
     * calling npc->shieldCharge() return the complete shield
     * So we get the values on creation and use then instead.
    */
    double m_shieldCharge;
    double m_armorDamage;
    double m_hullDamage;
};

#endif /* !__STATION__H__INCL__ */


