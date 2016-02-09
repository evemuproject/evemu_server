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

#ifndef __OBJCACHEDB_H_INCL__
#define __OBJCACHEDB_H_INCL__

#include "ServiceDB.h"

class PyRep;
class DBQueryResult;

class ObjCacheDB
: public ServiceDB
{
public:

    static PyRep *GetCachableObject(const std::string &type);

protected:
    typedef PyRep *(* genFunc)();
    static std::map<std::string, genFunc> m_generators;

    //hack:
    static PyRep *DBResultToRowsetTuple(DBQueryResult &result);

    //declare all the generators
    static PyRep *Generate_PaperdollResources();
    static PyRep *Generate_PaperdollColors();
    static PyRep *Generate_PaperdollModifierLocations();
    static PyRep *Generate_PaperdollSculptingLocations();
    static PyRep *Generate_PaperdollColorNames();
    static PyRep *Generate_PaperdollColorRestrictions();
    static PyRep *Generate_BloodlineNames();
    static PyRep *Generate_Locationscenes();
    static PyRep *Generate_OverviewDefaults();
    static PyRep *Generate_Schematicspinmap();
    static PyRep *Generate_OverviewDefaultGroups();
    static PyRep *Generate_Schematics();
    static PyRep *Generate_Schematicstypemap();
    static PyRep *Generate_Sounds();
    static PyRep *Generate_Invtypematerials();
    static PyRep *Generate_Ownericons();
    static PyRep *Generate_Icons();
    static PyRep *Generate_CharNewExtraRaceSkills();
    static PyRep *Generate_CharNewExtraCareerSkills();
    static PyRep *Generate_CharNewExtraSpecialitySkills();
    static PyRep *Generate_CharNewExtraCareers();
    static PyRep *Generate_CharNewExtraSpecialities();

    static PyRep *Generate_BillTypes();
    static PyRep *Generate_AllianceShortnames();
    static PyRep *Generate_invCategories();
    static PyRep *Generate_invTypeReactions();

    static PyRep *Generate_dgmTypeAttribs();
    static PyRep *Generate_dgmTypeEffects();
    static PyRep *Generate_dgmEffects();
    static PyRep *Generate_dgmAttribs();

    static PyRep *Generate_invMetaGroups();

    static PyRep *Generate_ramActivities();
    static PyRep *Generate_ramALTypeGroup();
    static PyRep *Generate_ramALTypeCategory();
    static PyRep *Generate_ramALTypes();
    static PyRep *Generate_ramCompletedStatuses();
    static PyRep *Generate_ramTypeRequirements();

    static PyRep *Generate_mapCelestialDescriptions();
    static PyRep *Generate_tickerNames();
    static PyRep *Generate_invGroups();
    static PyRep *Generate_certificates();
    static PyRep *Generate_certificateRelationships();
    static PyRep *Generate_invShipTypes();
    static PyRep *Generate_cacheLocations();
    static PyRep *Generate_locationWormholeClasses();
    static PyRep *Generate_invBlueprintTypes();
    static PyRep *Generate_eveGraphics();
    static PyRep *Generate_invTypes();
    static PyRep *Generate_invMetaTypes();
    static PyRep *Generate_chrBloodlines();
    static PyRep *Generate_eveUnits();
    static PyRep *Generate_eveBulkDataUnits();
    static PyRep *Generate_cacheOwners();
    static PyRep *Generate_eveStaticOwners();
    static PyRep *Generate_chrRaces();
    static PyRep *Generate_chrAttributes();
    static PyRep *Generate_invFlags();
    static PyRep *Generate_eveStaticLocations();
    static PyRep *Generate_invContrabandTypes();

    static PyRep *Generate_c_chrBloodlines();
    static PyRep *Generate_c_chrRaces();
    static PyRep *Generate_c_chrAncestries();
    static PyRep *Generate_c_chrSchools();
    static PyRep *Generate_c_chrAttributes();
    static PyRep *Generate_bl_accessories();
    static PyRep *Generate_bl_lights();
    static PyRep *Generate_bl_skins();
    static PyRep *Generate_bl_beards();
    static PyRep *Generate_bl_eyes();
    static PyRep *Generate_bl_lipsticks();
    static PyRep *Generate_bl_makeups();
    static PyRep *Generate_bl_hairs();
    static PyRep *Generate_bl_backgrounds();
    static PyRep *Generate_bl_decos();
    static PyRep *Generate_bl_eyebrows();
    static PyRep *Generate_bl_costumes();

    static PyRep *Generate_a_eyebrows();
    static PyRep *Generate_a_eyes();
    static PyRep *Generate_a_decos();
    static PyRep *Generate_a_hairs();
    static PyRep *Generate_a_backgrounds();
    static PyRep *Generate_a_accessories();
    static PyRep *Generate_a_lights();
    static PyRep *Generate_a_costumes();
    static PyRep *Generate_a_makeups();
    static PyRep *Generate_a_beards();
    static PyRep *Generate_a_skins();
    static PyRep *Generate_a_lipsticks();
};

#endif
