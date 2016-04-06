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

#include "eve-server.h"

#include "Client.h"
#include "PyCallable.h"
#include "admin/CommandDB.h"
#include "mining/Asteroid.h"
#include "system/SystemManager.h"

uint32 GetAsteroidType( double p, const std::map<double, uint32>& roids );
void SpawnAsteroid( SystemManager* system, uint32 typeID, double radius, const Vector3D& position );

PyResult Command_roid( Client* who, const Seperator& args )
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

    SysLog::Log( "Command", "Roid %u of radius %f", typeID, radius );

    Vector3D position( who->GetPosition() );
    position.x += radius + 1 + who->GetRadius();    //put it raw enough away to not push us around.

    SpawnAsteroid( who->System(), typeID, radius, position );

    return new PyString( "Spawn successsfull." );
}

/*
 * SQL to remove all asteroids from space in ALL systems.
 * Important, run in this order or the attributes will not be deleted!
 * 
DELETE FROM srvEntity_default_attributes WHERE attributeID > 0 and itemID in
(SELECT itemID from srvEntity where ownerID=1 AND typeID in
(SELECT typeID from invTypes where groupID in
(select groupID FROM invGroups where categoryID=25) or groupID=711));
DELETE FROM srvEntity_attributes WHERE attributeID > 0 and itemID in
(SELECT itemID from srvEntity where ownerID=1 AND typeID in
(SELECT typeID from invTypes where groupID in
(select groupID FROM invGroups where categoryID=25) or groupID=711));
DELETE FROM srvEntity WHERE itemID>=140000000 AND ownerID=1 AND typeID in
(SELECT typeID from invTypes where groupID in
(select groupID FROM invGroups where categoryID=25) or groupID=711);
 * 
 */
PyResult Command_spawnbelt( Client* who, const Seperator& args )
{
    if (!who->IsInSpace())
    {
        throw PyException(MakeCustomError("You must be in space to spawn things."));
    }

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

    double beltradius = 25000.0; // 25 KM
    if(makeIceBelt)
    {
        beltradius = 100000.0; // 100 KM
    }
    uint32 pcs = 0;

    if (customCount > 15)
    {
        pcs = customCount + static_cast<uint32> (MakeRandomInt(-10, 10));
    }
    else
    {
        pcs = 200 + static_cast<uint32> (MakeRandomInt(-10, 10));
    }

    SystemManager* sys = who->System();
    std::map<double, uint32> roidDist;
    if (makeIceBelt)
    {
        pcs /= 8;
        std::string securityStatus = sys->GetSystemSecurity();
        if (!makeRareIce)
        {
            roidDist.insert(std::pair<double, uint32>(0.60, 16264)); // Blue Ice
            roidDist.insert(std::pair<double, uint32>(0.45, 17975)); // Thick Blue Ice
            roidDist.insert(std::pair<double, uint32>(0.30, 28627)); // Azure Ice
            roidDist.insert(std::pair<double, uint32>(0.20, 16262)); // Clear Icicle
            roidDist.insert(std::pair<double, uint32>(0.10, 16267)); // Dark Glitter
        }
        if (makeRareIce)
        {
            roidDist.insert(std::pair<double, uint32>(0.90, 16263)); // Glacial Mass
            roidDist.insert(std::pair<double, uint32>(0.80, 16265)); // White Glaze
            roidDist.insert(std::pair<double, uint32>(0.70, 16266)); // Glare Crust
            roidDist.insert(std::pair<double, uint32>(0.60, 16268)); // Gelidus
            roidDist.insert(std::pair<double, uint32>(0.50, 16269)); // Krystallos
            roidDist.insert(std::pair<double, uint32>(0.40, 17976)); // Pristine White Glaze
            roidDist.insert(std::pair<double, uint32>(0.30, 17977)); // Smooth Glacial Mass
            roidDist.insert(std::pair<double, uint32>(0.20, 17978)); // Enriched Clear Icicle
            roidDist.insert(std::pair<double, uint32>(0.10, 28628)); // Crystalline Icicle
        }
    }
    else
    {
        if (!CommandDB::GetRoidDist(sys->GetSystemSecurity(), roidDist))
        {
            SysLog::Error("Command", "Couldn't get roid list for system security %s", sys->GetSystemSecurity());

            throw PyException(MakeCustomError("Couldn't get roid list for system security %s", sys->GetSystemSecurity()));
        }
    }

    const Vector3D position(who->GetPosition());
    double phi = atan(position.x / position.z);
    if (position.z == 0)
    {
        phi = M_PI / 2;
    }
    if (position.z < 0)
    {
        phi += M_PI;
    }
    Vector3D beltOffset;
    if (makeIceBelt)
    {
        beltOffset.x = (beltradius * 0.75) * sin(phi);
        beltOffset.z = (beltradius * 0.75) * cos(phi);
    }
    double alpha;
    Vector3D mposition;
    double beltThickness = 3000;
    double height;
    double roidradius;
    const double beltangle = M_PI * 2.0 / 3.0;
    int triesLeft = pcs * 25;
    int pcsLeft = pcs;
    std::vector<std::pair<Vector3D, double>> spawned;
    while (triesLeft-- && pcsLeft)
    {
        uint32 typeID = GetAsteroidType(MakeRandomFloat(), roidDist);
        // Generate asteroid parameters.
		if( makeIceBelt)
        {
            height = MakeRandomFloat(-0.2, 1.8);
            alpha = beltangle * ((M_PI / 8) * height);
            roidradius = MakeRandomFloat(4000.0, 10000.0);
            height *= 8;
        }
        else
        {
            alpha = beltangle * MakeRandomFloat(-M_PI / 4, M_PI / 4);
			roidradius = MakeRandomFloat( 100.0, 1000.0 );
            height = MakeRandomFloat(-1, 1);
            const InvTypeRef type = InvType::getType(typeID);
            if (type->groupID == EVEDB::invGroups::Veldspar)
            {
                roidradius *= 2;
            }
        }
        // Calculate new position.
        mposition.y = beltThickness * height;
        mposition.x = beltradius * sin(phi + alpha) + beltThickness * MakeRandomFloat(-1, 1);
        mposition.z = beltradius * cos(phi + alpha) + beltThickness * MakeRandomFloat(-1, 1);
        // Check for collision.
        bool collision = false;
        for (auto pair : spawned)
        {
            Vector3D point = pair.first;
            double dist = (mposition - point).length();
            double radii = (roidradius + pair.second);
            if ((dist - radii) < 0)
            {
                collision = true;
                continue;
            }
        }
        if (collision)
        {
            // There was a collision, try again.
            continue;
        }
        // Were good, add the asteroid.
        pcsLeft--;
        SpawnAsteroid(who->System(), typeID, roidradius, mposition + position - beltOffset);
        // Save the location for collision checks.
        spawned.push_back(std::pair<Vector3D, double>(mposition, roidradius));
    }

    return new PyString( "Spawn successsfull." );
}

PyResult Command_growbelt( Client* who, const Seperator& args )
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

void SpawnAsteroid( SystemManager* system, uint32 typeID, double radius, const Vector3D& position )
{
    ItemData idata( typeID,
                    1,
                    system->GetID(),
                    flagAutoFit,
                    "",    //name
                    position );

    InventoryItemRef i = ItemFactory::SpawnItem(idata);
    if (!i)
    {
        throw PyException(MakeCustomError("Unable to spawn item of type %u.", typeID));
    }

    // Calculate 1/10000th of the volume of a sphere with radius 'radius':
    // (this should yield around 90,000 units of Veldspar in an asteroid with 1000.0m radius)
    double volume = (1.0/100000.0) * (4.0/3.0) * M_PI * pow(radius,3);
    //uint32 qty = floor((volume/(i->GetAttribute(AttrVolume).get_float())));
    uint32 qty = (radius * 10) / std::sqrt(i->getAttribute(AttrVolume).get_float());
    if (i->groupID() == EVEDB::invGroups::Veldspar)
    {
        qty *= 2;
    }
    i->setAttribute(AttrQuantity, qty);
    i->setAttribute(AttrRadius, radius);

    // Create astroid srvEntity.
    AsteroidEntity* new_roid = new AsteroidEntity(i, system, position);
    if (new_roid != nullptr)
    {
        SysLog::Debug("SpawnAsteroid()", "Spawned new asteroid of radius= %fm and volume= %f m3", radius, volume);
        // Add srvEntity to system.
        system->AddEntity(new_roid);
    }
}
