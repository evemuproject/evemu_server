/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2011 The EVEmu Team
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

#include "eve-server.h"

#include "Client.h"
#include "PyCallable.h"
#include "admin/CommandDB.h"
#include "mining/Asteroid.h"
#include "system/SystemManager.h"

uint32 GetAsteroidType( double p, const std::map<double, uint32>& roids );
void SpawnAsteroid( SystemManager* system, uint32 typeID, double radius, const GVector& position );

PyResult Command_roid( Client* who, CommandDB* db, PyServiceMgr* services, const Seperator& args )
{
    if( !args.isNumber( 1 ) )
        throw PyException( MakeCustomError( "Argument 1 should be an item type ID" ) );
    const uint32 typeID = atoi( args.arg( 1 ).c_str() );

    if( !args.isNumber( 2 ) )
        throw PyException( MakeCustomError( "Argument 2 should be a radius" ) );
    const double radius = atof( args.arg( 2 ).c_str() );

    if( 0 >= radius )
        throw PyException( MakeCustomError( "Invalid radius." ) );

    if( !who->IsInSpace() )
        throw PyException( MakeCustomError( "You must be in space to spawn things." ) );

    sLog.Log( "Command", "Roid %u of radius %f", typeID, radius );

    GPoint position( who->GetPosition() );
    position.x += radius + 1 + who->GetRadius();    //put it raw enough away to not push us around.

    SpawnAsteroid( who->System(), typeID, radius, position );

    return new PyString( "Spawn successsfull." );
}

PyResult Command_spawnbelt( Client* who, CommandDB* db, PyServiceMgr* services, const Seperator& args )
{
    if( !who->IsInSpace() )
        throw PyException( MakeCustomError( "You must be in space to spawn things." ) );

	bool makeIceBelt = false;
	bool makeRareIce = false;
	uint32 customCount = 0;
    if( args.argCount() >= 2 )
	{
        if( !args.isNumber( 1 ) )
		{
			if( args.arg( 1 ) == "ice" )
				makeIceBelt = true;
		}
		else
		{
			if( atoi(args.arg( 1 ).c_str()) > 15 )
				customCount = atoi(args.arg( 1 ).c_str());
			else
				PyException( MakeCustomError( "Argument 1 should be at least 15!" ) );
		}
	}

	if( args.argCount() >= 3 )
	{
		if( args.isNumber( 2 ) )
		{
			if( atoi(args.arg( 2 ).c_str()) > 15 )
				customCount = atoi(args.arg(2).c_str());
			else
				PyException( MakeCustomError( "Argument 2 should be at least 15!" ) );
		}
		else
			if( args.arg( 2 ) == "ice" )
				makeIceBelt = true;
			if( args.arg( 2 ) == "rareice" )
			{
				makeIceBelt = true;
				makeRareIce = true;
			}
	}

    const double beltradius = 100000.0;
    const double beltdistance = 25000.0;
    double roidradius;
    const double beltangle = M_PI * 2.0 / 3.0;
    uint32 pcs = 0;
	
	if( customCount > 15 )
		pcs = customCount + static_cast<uint32>(MakeRandomInt( -10, 10 ));
	else
		pcs = 30 + static_cast<uint32>(MakeRandomInt( -10, 10 ));

    const GPoint position( who->GetPosition() );

    const double R = sqrt( position.x * position.x + position.z * position.z );
    const GPoint r = position * ( R + beltdistance - beltradius ) / R;

    double phi = atan( position.x / position.z );
    if( position.z < 0 )
        phi += M_PI;

    SystemManager* sys = who->System();
    std::map<double, uint32> roidDist;
	if( makeIceBelt )
	{
		std::string securityStatus = sys->GetSystemSecurity();
		if( !makeRareIce )
		{
			roidDist.insert(std::pair<double,uint32>(0.60,16264));		// Blue Ice
			roidDist.insert(std::pair<double,uint32>(0.45,17975));		// Thick Blue Ice
			roidDist.insert(std::pair<double,uint32>(0.30,28627));		// Azure Ice
			roidDist.insert(std::pair<double,uint32>(0.20,16262));		// Clear Icicle
			roidDist.insert(std::pair<double,uint32>(0.10,16267));		// Dark Glitter
		}
		if( makeRareIce )
		{
			roidDist.insert(std::pair<double,uint32>(0.90,16263));		// Glacial Mass
			roidDist.insert(std::pair<double,uint32>(0.80,16265));		// White Glaze
			roidDist.insert(std::pair<double,uint32>(0.70,16266));		// Glare Crust
			roidDist.insert(std::pair<double,uint32>(0.60,16268));		// Gelidus
			roidDist.insert(std::pair<double,uint32>(0.50,16269));		// Krystallos
			roidDist.insert(std::pair<double,uint32>(0.40,17976));		// Pristine White Glaze
			roidDist.insert(std::pair<double,uint32>(0.30,17977));		// Smooth Glacial Mass
			roidDist.insert(std::pair<double,uint32>(0.20,17978));		// Enriched Clear Icicle
			roidDist.insert(std::pair<double,uint32>(0.10,28628));		// Crystalline Icicle
		}
	}
	else
	{
		if( !db->GetRoidDist( sys->GetSystemSecurity(), roidDist ) )
		{
			sLog.Error( "Command", "Couldn't get roid list for system security %s", sys->GetSystemSecurity() );

			throw PyException( MakeCustomError( "Couldn't get roid list for system security %s", sys->GetSystemSecurity() ) );
		}
	}

    double distanceToMe;
    double alpha;
    GPoint mposition;

	if( makeIceBelt )
		pcs *= 2;

    for( uint32 i = 0; i < pcs; ++i )
    {
        alpha = beltangle * MakeRandomFloat( -0.5, 0.5 );

		if( makeIceBelt )
			roidradius = MakeRandomFloat( 1000.0, 10000.0 );
		else
			roidradius = MakeRandomFloat( 100.0, 1000.0 );
        mposition.x = beltradius * sin( phi + alpha ) + roidradius * MakeRandomFloat( 0, 15 );
        mposition.z = beltradius * cos( phi + alpha ) + roidradius * MakeRandomFloat( 0, 15 );
        mposition.y = position.y - r.y + roidradius * MakeRandomFloat( 0, 15 );
        distanceToMe = (r + mposition - position).length();
        SpawnAsteroid( who->System(), GetAsteroidType( MakeRandomFloat(), roidDist ), roidradius, r + mposition );
    }

    return new PyString( "Spawn successsfull." );
}

PyResult Command_growbelt( Client* who, CommandDB* db, PyServiceMgr* services, const Seperator& args )
{
    throw PyException( MakeCustomError( "Not implemented yet." ) );
}

uint32 GetAsteroidType( double p, const std::map<double, uint32>& roids )
{
    std::map<double, uint32>::const_iterator cur, end;
    cur = roids.begin();
    end = roids.end();
    for(; cur != end; ++cur )
    {
        if( cur->first > p )
            return cur->second;
    }
	--cur;

	return cur->second;
}

void SpawnAsteroid( SystemManager* system, uint32 typeID, double radius, const GVector& position )
{
    //TODO: make item in IsUniverseAsteroid() range...
    ItemData idata( typeID,
                    1 /* who->GetCorporationID() */, //owner
                    system->GetID(),
                    flagAutoFit,
                    "",    //name
                    position );

    InventoryItemRef i = system->itemFactory().SpawnItem( idata );
    if( !i )
        throw PyException( MakeCustomError( "Unable to spawn item of type %u.", typeID ) );

    //i->Set_radius( radius );
    // Calculate 1/10000th of the volume of a sphere with radius 'radius':
    // (this should yield around 90,000 units of Veldspar in an asteroid with 1000.0m radius)
    double volume = (1.0/10000.0) * (4.0/3.0) * M_PI * pow(radius,3);

	i->SetAttribute(AttrQuantity, EvilNumber(floor(100*(volume/(i->GetAttribute(AttrVolume).get_float())))));
    i->SetAttribute(AttrRadius, EvilNumber(radius));
    //i->SetAttribute(AttrVolume, EvilNumber(volume));
    //i->SetAttribute(AttrIsOnline,EvilNumber(1));                            // Is Online
    //i->SetAttribute(AttrDamage,EvilNumber(0.0));                            // Structure Damage
    //i->SetAttribute(AttrShieldCharge,i->GetAttribute(AttrShieldCapacity));  // Shield Charge
    //i->SetAttribute(AttrArmorDamage,EvilNumber(0.0));                       // Armor Damage
    //i->SetAttribute(AttrMass,EvilNumber(i->type().attributes.mass()));      // Mass
    //i->SetAttribute(AttrRadius,EvilNumber(i->type().attributes.radius()));  // Radius
    //i->SetAttribute(AttrVolume,EvilNumber(i->type().attributes.volume()));  // Volume

    // TODO: Rework this code now that
    AsteroidEntity* new_roid = NULL;
    new_roid = new AsteroidEntity( i, system, *(system->GetServiceMgr()), position );
    if( new_roid != NULL )
        sLog.Debug( "SpawnAsteroid()", "Spawned new asteroid of radius= %fm and volume= %f m3", radius, volume );
    //TODO: check for a local asteroid belt object?
    //TODO: actually add this to the asteroid belt too...
    system->AddEntity( new_roid );
}
