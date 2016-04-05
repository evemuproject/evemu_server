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

#include "eve-server.h"

#include "inventory/AttributeEnum.h"
#include "ship/DestinyManager.h"
#include "station/Station.h"
#include "system/SolarSystem.h"

/*
 * CelestialObjectData
 */
CelestialObjectData::CelestialObjectData(
    double _radius,
    double _security,
    uint8 _celestialIndex,
    uint8 _orbitIndex)
: radius(_radius),
  security(_security),
  celestialIndex(_celestialIndex),
  orbitIndex(_orbitIndex)
{
}

/*
 * CelestialObject
 */
CelestialObject::CelestialObject(
    uint32 _celestialID,
                                 const InvTypeRef _type,
    const ItemData &_data)
: InventoryItem(_celestialID, _type, _data),
  m_radius( 0.0 ),
  m_security( 0.0 ),
  m_celestialIndex( 0 ),
  m_orbitIndex( 0 )
{
}

CelestialObject::CelestialObject(
    uint32 _celestialID,
    // InventoryItem stuff:
                                 const InvTypeRef _type,
    const ItemData &_data,
    // CelestialObject stuff:
    const CelestialObjectData &_cData)
: InventoryItem(_celestialID, _type, _data),
  m_radius(_cData.radius),
  m_security(_cData.security),
  m_celestialIndex(_cData.celestialIndex),
  m_orbitIndex(_cData.orbitIndex)
{
}

CelestialObjectRef CelestialObject::Load(uint32 celestialID)
{
    return InventoryItem::Load<CelestialObject>( celestialID );
}

template<class _Ty>
RefPtr<_Ty> CelestialObject::_LoadCelestialObject(uint32 celestialID,
    // InventoryItem stuff:
                                                  const InvTypeRef type, const ItemData &data,
    // CelestialObject stuff:
    const CelestialObjectData &cData)
{
    // Our category is celestial; what to do next:
    switch (type->groupID)
    {
        ///////////////////////////////////////
        // Solar system:
        ///////////////////////////////////////
        case EVEDB::invGroups::Solar_System: {
            return SolarSystem::_LoadCelestialObject<SolarSystem>( celestialID, type, data, cData );
        }

        ///////////////////////////////////////
        // Station:
        ///////////////////////////////////////
        case EVEDB::invGroups::Station: {
            return Station::_LoadCelestialObject<Station>( celestialID, type, data, cData );
        }
    }

    // Create a generic one:
    return CelestialObjectRef( new CelestialObject( celestialID, type, data, cData ) );
}

CelestialObjectRef CelestialObject::Spawn(
    // InventoryItem stuff:
    ItemData &data
) {
    uint32 celestialID = CelestialObject::_Spawn( data );
    if( celestialID == 0 )
        return CelestialObjectRef();
    return CelestialObject::Load( celestialID );
}

uint32 CelestialObject::_Spawn(
    // InventoryItem stuff:
    ItemData &data
) {
    // make sure it's a ship
    const InvTypeRef item = InvType::getType(data.typeID);
    if (!(item->getCategoryID() == EVEDB::invCategories::Celestial))
    {
        return 0;
    }

    // store item data
    uint32 celestialID = InventoryItem::_Spawn(data);
    if (celestialID == 0)
    {
        return 0;
    }

    // nothing additional

    return celestialID;
}

void CelestialObject::Delete() {
    InventoryItem::Delete();
}


using namespace Destiny;

CelestialEntity::CelestialEntity(
    CelestialObjectRef celestial,
    //InventoryItemRef celestial,
    SystemManager *system,
    const Vector3D &position)
: CelestialDynamicSystemEntity(new DestinyManager(this, system), celestial),
  m_system(system)
{
    _celestialRef = celestial;
    m_destiny->SetPosition(position, false);
}

void CelestialEntity::Process() {
    SystemEntity::Process();
}

void CelestialEntity::ForcedSetPosition(const Vector3D &pt) {
    m_destiny->SetPosition(pt, false);
}

/*
void CelestialEntity::EncodeDestiny( Buffer& into ) const
{
    const Vector3D& position = GetPosition();
    const std::string itemName( GetName() );

    /*if(m_orbitingID != 0) {
        #pragma pack(1)
        struct AddBall_Orbit {
            BallHeader head;
            MassSector mass;
            ShipSector ship;
            DSTBALL_ORBIT_Struct main;
            NameStruct name;
        };
        #pragma pack()

        into.resize(start
            + sizeof(AddBall_Orbit)
            + slen*sizeof(uint16) );
        uint8 *ptr = &into[start];
        AddBall_Orbit *item = (AddBall_Orbit *) ptr;
        ptr += sizeof(AddBall_Orbit);

        item->head.entityID = GetID();
        item->head.mode = Destiny::DSTBALL_ORBIT;
        item->head.radius = m_self->radius();
        item->head.x = x();
        item->head.y = y();
        item->head.z = z();
        item->head.sub_type = IsMassive | IsFree;

        item->mass.mass = m_self->mass();
        item->mass.unknown51 = 0;
        item->mass.unknown52 = 0xFFFFFFFFFFFFFFFFLL;
        item->mass.corpID = GetCorporationID();
        item->mass.unknown64 = 0xFFFFFFFF;

        item->ship.max_speed = m_self->maxVelocity();
        item->ship.velocity_x = m_self->maxVelocity();    //hacky hacky
        item->ship.velocity_y = 0.0;
        item->ship.velocity_z = 0.0;
        item->ship.agility = 1.0;    //hacky
        item->ship.speed_fraction = 0.133f;    //just strolling around. TODO: put in speed fraction!

        item->main.unknown116 = 0xFF;
        item->main.followID = m_orbitingID;
        item->main.followRange = 6000.0f;

        item->name.name_len = slen;    // in number of unicode chars
        //strcpy_fake_unicode(item->name.name, GetName());
    } else *//*{
        BallHeader head;
        head.entityID = GetID();
        head.mode = Destiny::DSTBALL_STOP;
        head.radius = GetRadius();
        head.x = position.x;
        head.y = position.y;
        head.z = position.z;
        head.sub_type = IsMassive | IsFree;
        into.Append( head );

        MassSector mass;
        mass.mass = GetMass();
        mass.cloak = 0;
        mass.unknown52 = 0xFFFFFFFFFFFFFFFFLL;
        mass.corpID = GetCorporationID();
        mass.allianceID = GetAllianceID();
        into.Append( mass );

        ShipSector ship;
        ship.max_speed = GetMaxVelocity();
        ship.velocity_x = 0.0;
        ship.velocity_y = 0.0;
        ship.velocity_z = 0.0;
        ship.unknown_x = 0.0;
        ship.unknown_y = 0.0;
        ship.unknown_z = 0.0;
        ship.agility = GetAgility();
        ship.speed_fraction = 0.0;
        into.Append( ship );

        DSTBALL_STOP_Struct main;
        main.formationID = 0xFF;
        into.Append( main );

    }
}
*/

void CelestialEntity::MakeDamageState(DoDestinyDamageState &into) const
{
    into.shield = (m_self->GetAttribute(AttrShieldCharge).get_float() / m_self->GetAttribute(AttrShieldCapacity).get_float());
    into.tau = 100000;    //no freaking clue.
    into.timestamp = Win32TimeNow();
//    armor damage isn't working...
    into.armor = 1.0 - (m_self->GetAttribute(AttrArmorDamage).get_float() / m_self->GetAttribute(AttrArmorHP).get_float());
    into.structure = 1.0 - (m_self->GetAttribute(AttrDamage).get_float() / m_self->GetAttribute(AttrHp).get_float());
}

