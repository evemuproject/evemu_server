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

#include "cache/ObjCacheDB.h"

#include "eveStatic.h"

//register all the generators
std::map<std::string, ObjCacheDB::genFunc> ObjCacheDB::m_generators = {
    { "charNewExtraCreationInfo.raceskills", &ObjCacheDB::Generate_CharNewExtraRaceSkills},
    { "charNewExtraCreationInfo.careerskills", &ObjCacheDB::Generate_CharNewExtraCareerSkills},
    { "charNewExtraCreationInfo.specialityskills", &ObjCacheDB::Generate_CharNewExtraSpecialitySkills},
    { "charNewExtraCreationInfo.careers", &ObjCacheDB::Generate_CharNewExtraCareers},
    { "charNewExtraCreationInfo.specialities", &ObjCacheDB::Generate_CharNewExtraSpecialities},

    { "config.BulkData.paperdollResources", &ObjCacheDB::Generate_PaperdollResources},
    { "config.BulkData.paperdollColors", &ObjCacheDB::Generate_PaperdollColors},
    { "config.BulkData.paperdollModifierLocations", &ObjCacheDB::Generate_PaperdollModifierLocations},
    { "config.BulkData.paperdollSculptingLocations", &ObjCacheDB::Generate_PaperdollSculptingLocations},
    { "config.BulkData.paperdollColorNames", &ObjCacheDB::Generate_PaperdollColorNames},
    { "config.BulkData.paperdollColorRestrictions", &ObjCacheDB::Generate_PaperdollColorRestrictions},

    { "config.BulkData.bloodlineNames", &ObjCacheDB::Generate_BloodlineNames},
    { "config.BulkData.locationscenes", &ObjCacheDB::Generate_Locationscenes},
    { "config.BulkData.overviewDefaults", &ObjCacheDB::Generate_OverviewDefaults},
    { "config.BulkData.schematicspinmap", &ObjCacheDB::Generate_Schematicspinmap},
    { "config.BulkData.overviewDefaultGroups", &ObjCacheDB::Generate_OverviewDefaultGroups},
    { "config.BulkData.schematics", &ObjCacheDB::Generate_Schematics},
    { "config.BulkData.schematicstypemap", &ObjCacheDB::Generate_Schematicstypemap},
    { "config.BulkData.sounds", &ObjCacheDB::Generate_Sounds},
    { "config.BulkData.invtypematerials", &ObjCacheDB::Generate_Invtypematerials},
    { "config.BulkData.ownericons", &ObjCacheDB::Generate_Ownericons},
    { "config.BulkData.icons", &ObjCacheDB::Generate_Icons},

    { "config.BulkData.billtypes", &ObjCacheDB::Generate_BillTypes},
    { "config.BulkData.allianceshortnames", &ObjCacheDB::Generate_AllianceShortnames},
    { "config.BulkData.categories", &ObjCacheDB::Generate_invCategories},
    { "config.BulkData.invtypereactions", &ObjCacheDB::Generate_invTypeReactions},

    { "config.BulkData.dgmtypeattribs", &ObjCacheDB::Generate_dgmTypeAttribs},
    { "config.BulkData.dgmtypeeffects", &ObjCacheDB::Generate_dgmTypeEffects},
    { "config.BulkData.dgmeffects", &ObjCacheDB::Generate_dgmEffects},
    { "config.BulkData.dgmattribs", &ObjCacheDB::Generate_dgmAttribs},
    { "config.BulkData.metagroups", &ObjCacheDB::Generate_invMetaGroups},
    { "config.BulkData.ramactivities", &ObjCacheDB::Generate_ramActivities},
    { "config.BulkData.ramaltypesdetailpergroup", &ObjCacheDB::Generate_ramALTypeGroup},
    { "config.BulkData.ramaltypesdetailpercategory", &ObjCacheDB::Generate_ramALTypeCategory},
    { "config.BulkData.ramaltypes", &ObjCacheDB::Generate_ramALTypes},
    { "config.BulkData.ramcompletedstatuses", &ObjCacheDB::Generate_ramCompletedStatuses},
    { "config.BulkData.ramtyperequirements", &ObjCacheDB::Generate_ramTypeRequirements},

    { "config.BulkData.mapcelestialdescriptions", &ObjCacheDB::Generate_mapCelestialDescriptions},
    { "config.BulkData.tickernames", &ObjCacheDB::Generate_tickerNames},
    { "config.BulkData.groups", &ObjCacheDB::Generate_invGroups},
    { "config.BulkData.certificates", &ObjCacheDB::Generate_certificates},
    { "config.BulkData.certificaterelationships", &ObjCacheDB::Generate_certificateRelationships},
    { "config.BulkData.shiptypes", &ObjCacheDB::Generate_invShipTypes},
    { "config.BulkData.locations", &ObjCacheDB::Generate_cacheLocations},
    { "config.BulkData.locationwormholeclasses", &ObjCacheDB::Generate_locationWormholeClasses},
    { "config.BulkData.bptypes", &ObjCacheDB::Generate_invBlueprintTypes},
    { "config.BulkData.graphics", &ObjCacheDB::Generate_eveGraphics},
    { "config.BulkData.types", &ObjCacheDB::Generate_invTypes},
    { "config.BulkData.invmetatypes", &ObjCacheDB::Generate_invMetaTypes},
    { "config.Bloodlines", &ObjCacheDB::Generate_chrBloodlines},
    { "config.Units", &ObjCacheDB::Generate_eveUnits},
    { "config.BulkData.units", &ObjCacheDB::Generate_eveBulkDataUnits},
    { "config.BulkData.owners", &ObjCacheDB::Generate_cacheOwners},
    { "config.StaticOwners", &ObjCacheDB::Generate_eveStaticOwners},
    { "config.Races", &ObjCacheDB::Generate_chrRaces},
    { "config.Attributes", &ObjCacheDB::Generate_chrAttributes},
    { "config.Flags", &ObjCacheDB::Generate_invFlags},
    { "config.StaticLocations", &ObjCacheDB::Generate_eveStaticLocations},
    { "config.InvContrabandTypes", &ObjCacheDB::Generate_invContrabandTypes},

    { "charCreationInfo.bloodlines", &ObjCacheDB::Generate_c_chrBloodlines},
    { "charCreationInfo.races", &ObjCacheDB::Generate_c_chrRaces},
    { "charCreationInfo.ancestries", &ObjCacheDB::Generate_c_chrAncestries},
    { "charCreationInfo.schools", &ObjCacheDB::Generate_c_chrSchools},
    { "charCreationInfo.attributes", &ObjCacheDB::Generate_c_chrAttributes},
    { "charCreationInfo.bl_accessories", &ObjCacheDB::Generate_bl_accessories},
    { "charCreationInfo.bl_lights", &ObjCacheDB::Generate_bl_lights},
    { "charCreationInfo.bl_skins", &ObjCacheDB::Generate_bl_skins},
    { "charCreationInfo.bl_beards", &ObjCacheDB::Generate_bl_beards},
    { "charCreationInfo.bl_eyes", &ObjCacheDB::Generate_bl_eyes},
    { "charCreationInfo.bl_lipsticks", &ObjCacheDB::Generate_bl_lipsticks},
    { "charCreationInfo.bl_makeups", &ObjCacheDB::Generate_bl_makeups},
    { "charCreationInfo.bl_hairs", &ObjCacheDB::Generate_bl_hairs},
    { "charCreationInfo.bl_backgrounds", &ObjCacheDB::Generate_bl_backgrounds},
    { "charCreationInfo.bl_decos", &ObjCacheDB::Generate_bl_decos},
    { "charCreationInfo.bl_eyebrows", &ObjCacheDB::Generate_bl_eyebrows},
    { "charCreationInfo.bl_costumes", &ObjCacheDB::Generate_bl_costumes},

    { "charCreationInfo.eyebrows", &ObjCacheDB::Generate_a_eyebrows},
    { "charCreationInfo.eyes", &ObjCacheDB::Generate_a_eyes},
    { "charCreationInfo.decos", &ObjCacheDB::Generate_a_decos},
    { "charCreationInfo.hairs", &ObjCacheDB::Generate_a_hairs},
    { "charCreationInfo.backgrounds", &ObjCacheDB::Generate_a_backgrounds},
    { "charCreationInfo.accessories", &ObjCacheDB::Generate_a_accessories},
    { "charCreationInfo.lights", &ObjCacheDB::Generate_a_lights},
    { "charCreationInfo.costumes", &ObjCacheDB::Generate_a_costumes},
    { "charCreationInfo.makeups", &ObjCacheDB::Generate_a_makeups},
    { "charCreationInfo.beards", &ObjCacheDB::Generate_a_beards},
    { "charCreationInfo.skins", &ObjCacheDB::Generate_a_skins},
    { "charCreationInfo.lipsticks", &ObjCacheDB::Generate_a_lipsticks}
};

PyRep *ObjCacheDB::GetCachableObject(const std::string &type)
{
    std::map<std::string, genFunc>::const_iterator res;
    res = m_generators.find(type);

    if(res == m_generators.end())
    {
        _log(SERVICE__ERROR, "Unable to find cachable object generator for type '%s'", type.c_str());
        return NULL;
    }

    genFunc f = res->second;
    return (*f)();
}

//implement all the generators:
PyRep *ObjCacheDB::Generate_CharNewExtraSpecialities()
{
    DBQueryResult res;
    const char *q = "SELECT careerID, specialityID, specialityName, description, shortDescription, graphicID, iconID, dataID FROM blkChrSpecialities";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charNewExtraCreationInfo.specialities': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_CharNewExtraCareers()
{
    DBQueryResult res;
    const char *q = "SELECT raceID, careerID, careerName, description, shortDescription, graphicID, schoolID, iconID, dataID FROM blkChrCareers";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charNewExtraCreationInfo.careers': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_CharNewExtraSpecialitySkills()
{
    DBQueryResult res;
    const char *q = "SELECT specialityID, skillTypeID, levels FROM blkChrSpecialitySkills";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charNewExtraCreationInfo.specialityskills': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_CharNewExtraCareerSkills()
{
    DBQueryResult res;
    const char *q = "SELECT careerID, skillTypeID, levels FROM blkChrCareerSkills";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charNewExtraCreationInfo.careerskills': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_CharNewExtraRaceSkills()
{
    DBQueryResult res;
    const char *q = "SELECT raceID, skillTypeID, levels FROM blkChrRaceSkills";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charNewExtraCreationInfo.raceSkills': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_Icons()
{
    DBQueryResult res;
    const char *q = "SELECT iconID, iconFile, description, obsolete, iconType FROM blkIcons";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.icons': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_Ownericons()
{
    DBQueryResult res;
    const char *q = "SELECT ownerID, iconID FROM blkOwnerIcons";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.ownerIcons': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_Invtypematerials()
{
    DBQueryResult res;
    const char *q = "SELECT typeID, materialTypeID, quantity FROM invTypeMaterials";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.invTypeMaterials': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_Sounds()
{
    DBQueryResult res;
    const char *q = "SELECT soundID, soundFile, description, obsolete FROM blkSounds";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.sounds': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_Schematicstypemap()
{
    DBQueryResult res;
    const char *q = "SELECT schematicID, typeID, quantity, isInput FROM blkSchematicsTypeMap";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.schematicsTypeMap': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_Schematics()
{
    DBQueryResult res;
    const char *q = "SELECT schematicID, schematicName, cycleTime, dataID FROM blkSchematics";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.schematics': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_OverviewDefaultGroups()
{
    DBQueryResult res;
    const char *q = "SELECT overviewID, groupID FROM blkDefaultOverviewGroups";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.overviewDefaultGroups': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_Schematicspinmap()
{
    DBQueryResult res;
    const char *q = "SELECT schematicID, pinTypeID FROM blkSchematicsPinMap";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.schematicsPinMap': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_OverviewDefaults()
{
    DBQueryResult res;
    const char *q = "SELECT dataID, overviewID, overviewName, overviewShortName FROM blkChrDefaultOverviews";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.overviewDefaults': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_Locationscenes()
{
    DBQueryResult res;
    const char *q = "SELECT locationID, sceneID FROM blkLocationScenes";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.locationScenes': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_BloodlineNames()
{
    DBQueryResult res;
    const char *q = "SELECT nameID, bloodlineID, lastName FROM blkBloodlineNames";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.bloodlineNames': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_PaperdollColors()
{
    DBQueryResult res;
    const char *q = "SELECT colorID, colorKey, hasSecondary, hasWeight, hasGloss FROM blkPaperdollColors";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.paperdollColors': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_PaperdollColorRestrictions()
{
    DBQueryResult res;
    const char *q = "SELECT colorNameID, gender, restrictions FROM blkPaperdollColorRestrictions";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.paperdollColorRestrictions': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_PaperdollColorNames()
{
    DBQueryResult res;
    const char *q = "SELECT colorNameID, colorName FROM blkPaperdollColorNames";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.paperdollColorNames': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_PaperdollSculptingLocations()
{
    DBQueryResult res;
    const char *q = "SELECT sculptLocationID, weightKeyCategory, weightKeyPrefix FROM blkPaperdollSculptingLocations";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.paperdollSculptingLocations': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_PaperdollModifierLocations()
{
    DBQueryResult res;
    const char *q = "SELECT modifierLocationID, modifierKey, variationKey FROM blkPaperdollModifierLocations";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.paperdollModifierLocations': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_PaperdollResources()
{
    DBQueryResult res;
    const char *q = "SELECT paperdollResourceID, resGender, resPath, restrictions FROM blkPaperdollResources";
    if (DBcore::RunQuery(res, q) == false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.paperdollResources': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_BillTypes()
{
    DBQueryResult res;
    const char *q = "SELECT billTypeID,billTypeName,description FROM blkBillTypes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.billtypes': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_AllianceShortnames()
{
    DBQueryResult res;
    const char *q = "SELECT allianceID,shortName FROM srvAlliance_ShortNames";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.srvAlliance_ShortNames': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_invCategories()
{
    return EVEStatic::getInvCategoriesCache();
}

PyRep *ObjCacheDB::Generate_invTypeReactions()
{
    DBQueryResult res;
    const char *q = "SELECT reactionTypeID,input,typeID,quantity FROM invTypeReactions";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.invtypereactions': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_dgmTypeAttribs()
{
    DBQueryResult res;
    const char *q = "SELECT    dgmTypeAttributes.typeID,    dgmTypeAttributes.attributeID,    IF(valueInt IS NULL, valueFloat, valueInt) AS value FROM dgmTypeAttributes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.dgmtypeattribs': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_dgmTypeEffects()
{
    DBQueryResult res;
    const char *q = "SELECT typeID,effectID,isDefault FROM dgmTypeEffects";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.dgmtypeeffects': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_dgmEffects()
{
    DBQueryResult res;
    const char *q = "SELECT effectID, effectName, effectCategory, preExpression, postExpression, description, guid, iconID, isOffensive, isAssistance, durationAttributeID, trackingSpeedAttributeID, dischargeAttributeID, rangeAttributeID, falloffAttributeID, published, displayName, isWarpSafe, rangeChance, electronicChance, propulsionChance, distribution, sfxName, npcUsageChanceAttributeID, npcActivationChanceAttributeID, 0 as graphicID, fittingUsageChanceAttributeID, 0 AS dataID FROM dgmEffects";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.dgmeffects': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_dgmAttribs()
{
    DBQueryResult res;
    const char *q = "SELECT attributeID, attributeName, attributeCategory, description, maxAttributeID, attributeIdx, graphicID, chargeRechargeTimeID, defaultValue, published, unitID, displayName, stackable, highIsGood, iconID, dataID FROM blkDgmAttribs";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.dgmattribs': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_invMetaGroups()
{
    DBQueryResult res;
    const char *q = "SELECT metaGroupID, metaGroupName, description, iconID, 0 as graphicID, 0 AS dataID FROM invMetaGroups";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.metagroups': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_ramActivities()
{
    DBQueryResult res;
    const char *q = "SELECT activityID, activityName, iconNo, description, published FROM ramActivities";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.ramactivities': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_ramALTypeGroup()
{
    DBQueryResult res;
    const char *q = "SELECT a.assemblyLineTypeID, b.activityID, a.groupID, a.timeMultiplier, a.materialMultiplier FROM ramAssemblyLineTypeDetailPerGroup AS a LEFT JOIN ramAssemblyLineTypes AS b ON a.assemblyLineTypeID = b.assemblyLineTypeID";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.ramaltypesdetailpergroup': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_ramALTypeCategory()
{
    DBQueryResult res;
    const char *q = "SELECT a.assemblyLineTypeID, b.activityID, a.categoryID, a.timeMultiplier, a.materialMultiplier FROM ramAssemblyLineTypeDetailPerCategory AS a LEFT JOIN ramAssemblyLineTypes AS b ON a.assemblyLineTypeID = b.assemblyLineTypeID";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.ramaltypesdetailpercategory': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_ramALTypes()
{
    DBQueryResult res;
    const char *q = "SELECT assemblyLineTypeID, assemblyLineTypeName, assemblyLineTypeName AS typeName, description, activityID, baseTimeMultiplier, baseMaterialMultiplier, volume FROM ramAssemblyLineTypes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.ramaltypes': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_ramCompletedStatuses()
{
    DBQueryResult res;
    const char *q = "SELECT completedStatusID, completedStatusName FROM blkRamCompletedStatuses";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.ramcompletedstatuses': %s",res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_ramTypeRequirements()
{
    DBQueryResult res;
    const char *q = "SELECT typeID, activityID, requiredTypeID, quantity, damagePerJob, recycle FROM ramTypeRequirements";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.ramtyperequirements': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_mapCelestialDescriptions()
{
    DBQueryResult res;
    const char *q = "SELECT celestialID, description FROM blkMapCelestialDescriptions";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.mapcelestialdescriptions': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_tickerNames()
{
    DBQueryResult res;
    const char *q = "SELECT corporationID,tickerName,shape1,shape2,shape3,color1,color2,color3 FROM srvCorporation WHERE hasPlayerPersonnelManager=0";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.tickernames': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_invGroups()
{
    return EVEStatic::getInvGroupsCache();
}

PyRep *ObjCacheDB::Generate_certificates()
{
    DBQueryResult res;
    const char *q = "SELECT certificateID, categoryID, classID, grade, iconID, corpID, description, 0 AS dataID FROM crtCertificates";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.certificates': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_certificateRelationships()
{
    DBQueryResult res;
    const char *q = "SELECT relationshipID, parentID, parentTypeID, parentLevel, childID, childTypeID FROM blkCertificateRelationShips";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.certificaterelationships': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_invShipTypes()
{
    DBQueryResult res;
    const char *q = "SELECT shipTypeID, weaponTypeID, miningTypeID, skillTypeID FROM blkShipTypes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.shiptypes': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_cacheLocations()
{
    DBQueryResult res;
    const char *q = "SELECT locationID, locationName, x, y, z FROM srvCacheLocations";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.locations': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_locationWormholeClasses()
{
    DBQueryResult res;
    const char *q = "SELECT locationID, wormholeClassID FROM mapLocationWormholeClasses";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.locationwormholeclasses': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_invBlueprintTypes()
{
    return EVEStatic::getInvBlueprintTypesCache();
}

PyRep *ObjCacheDB::Generate_eveGraphics()
{
    DBQueryResult res;
    const char *q = "SELECT eveGraphics.graphicID, graphicFile, graphicName, description, obsolete, "
            "graphicType, collisionFile, paperdollFile, animationTemplate, collidable, explosionID, "
            "directoryID, graphicMinX, graphicMinY, graphicMinZ, graphicMaxX, graphicMaxY, graphicMaxZ "
            "FROM eveGraphics LEFT JOIN extEveGraphics USING(graphicID)";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.graphics': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_invTypes()
{
    return EVEStatic::getInvTypesCache();
}

PyRep *ObjCacheDB::Generate_invMetaTypes()
{
    DBQueryResult res;
    const char *q = "SELECT typeID, parentTypeID, metaGroupID FROM invMetaTypes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.invmetatypes': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_chrBloodlines()
{
    DBQueryResult res;
    const char *q = "SELECT chrBloodlines.*, extChrBloodlines.bloodlineNameID, extChrBloodlines.descriptionID, extChrBloodlines.dataID FROM chrBloodlines LEFT JOIN extChrBloodlines on extChrBloodlines.bloodlineID = chrBloodlines.bloodlineID";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.Bloodlines': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToPackedRowList(res);
}

PyRep *ObjCacheDB::Generate_eveUnits()
{
    DBQueryResult res;
    const char *q = "SELECT unitID, unitName, displayName FROM eveUnits";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.Units': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToPackedRowList(res);
}

PyRep *ObjCacheDB::Generate_eveBulkDataUnits()
{
    DBQueryResult res;
    const char *q = "SELECT unitID, unitName, displayName FROM eveUnits";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.units': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_cacheOwners()
{
    DBQueryResult res;
    const char *q = "SELECT ownerID, ownerName, typeID FROM srvCacheOwners";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.BulkData.owners': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_eveStaticOwners()
{
    DBQueryResult res;
    const char *q = "SELECT ownerID, ownerName, typeID FROM blkEveStaticOwners";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.StaticOwners': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_chrRaces()
{
    DBQueryResult res;
    const char *q = "SELECT raceID, raceName, description, iconID as graphicID, shortDescription, iconID, 0 AS dataID FROM chrRaces";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.Races': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToPackedRowList(res);
}

PyRep *ObjCacheDB::Generate_chrAttributes()
{
    DBQueryResult res;
    const char *q = "SELECT attributeID, attributeName, description, iconID, shortDescription, notes, iconID as graphicID FROM chrAttributes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.Attributes': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToPackedRowList(res);
}

PyRep *ObjCacheDB::Generate_invFlags()
{
    DBQueryResult res;
    const char *q = "SELECT flagID, flagName, flagName as flagLabel, flagName as flagGroup, flagName as description, orderID FROM invFlags";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.Flags': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToPackedRowList(res);
}

PyRep *ObjCacheDB::Generate_eveStaticLocations()
{
    DBQueryResult res;
    const char *q = "SELECT locationID, locationName, x, y, z FROM blkEveStaticLocations";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.StaticLocations': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_invContrabandTypes()
{
    DBQueryResult res;
    const char *q = "SELECT factionID, typeID, standingLoss, confiscateMinSec, fineByValue, attackMinSec FROM invContrabandTypes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'config.InvContrabandTypes': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_c_chrBloodlines()
{
    DBQueryResult res;
    const char *q = "SELECT chrBloodlines.*, extChrBloodlines.bloodlineNameID, extChrBloodlines.descriptionID, extChrBloodlines.dataID FROM chrBloodlines LEFT JOIN extChrBloodlines on extChrBloodlines.bloodlineID = chrBloodlines.bloodlineID";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bloodlines': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_c_chrRaces()
{
    DBQueryResult res;
    const char *q = "SELECT raceID, raceName, description, iconID, iconID AS graphicID, shortDescription, 0 AS dataID FROM chrRaces";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.races': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_c_chrAncestries()
{
    DBQueryResult res;
    const char *q = "SELECT chrAncestries.ancestryID, ancestryName, bloodlineID, description,"
            " perception, willpower, charisma, memory, intelligence, iconID, iconID AS graphicID,"
            " shortDescription, ancestryNameID, descriptionID, dataID"
            " FROM chrAncestries LEFT JOIN extChrAncestries USING(ancestryID)";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.ancestries': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_c_chrSchools()
{
    DBQueryResult res;
    const char *q = "SELECT "
    " raceID, schoolID, schoolName, description, graphicID, blkChrSchools.corporationID,"
    " blkChrSchools.agentID, newAgentID, iconID, schoolNameID, descriptionID FROM blkChrSchools"
    " LEFT JOIN agtAgents USING (corporationID)"
    " GROUP BY schoolID, raceID, schoolName, description, graphicID, blkChrSchools.corporationID,"
    " blkChrSchools.agentID, newAgentID, iconID, schoolNameID, descriptionID";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.schools': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_c_chrAttributes()
{
    DBQueryResult res;
    const char *q = "SELECT attributeID, attributeName, description, iconID, iconID as graphicID, shortDescription, notes FROM chrAttributes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.attributes': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_accessories()
{
    DBQueryResult res;
    const char *q = "SELECT bloodlineID, gender, accessoryID FROM blkChrBLAccessories";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_accessories': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_lights()
{
    DBQueryResult res;
    const char *q = "SELECT lightID, lightName FROM blkChrBLLights";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_lights': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_skins()
{
    DBQueryResult res;
    const char *q = "SELECT bloodlineID, gender, skinID FROM blkChrBLSkins";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_skins': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_beards()
{
    DBQueryResult res;
    const char *q = "SELECT bloodlineID, gender, beardID FROM blkChrBLBeards";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_beards': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_eyes()
{
    DBQueryResult res;
    const char *q = "SELECT bloodlineID, gender, eyesID FROM blkChrBLEyes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_eyes': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_lipsticks()
{
    DBQueryResult res;
    const char *q = "SELECT bloodlineID, gender, lipstickID FROM blkChrBLLipsticks";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_lipsticks': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_makeups()
{
    DBQueryResult res;
    const char *q = "SELECT bloodlineID, gender, makeupID FROM blkChrBLMakeups";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_makeups': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_hairs()
{
    DBQueryResult res;
    const char *q = "SELECT bloodlineID, gender, hairID FROM blkChrBLHairs";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_hairs': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_backgrounds()
{
    DBQueryResult res;
    const char *q = "SELECT backgroundID, backgroundName FROM blkChrBLBackgrounds";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_backgrounds': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_decos()
{
    DBQueryResult res;
    const char *q = "SELECT bloodlineID, gender, decoID FROM blkChrBLDecos";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_decos': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_eyebrows()
{
    DBQueryResult res;
    const char *q = "SELECT bloodlineID, gender, eyebrowsID FROM blkChrBLEyebrows";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_eyebrows': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_bl_costumes()
{
    DBQueryResult res;
    const char *q = "SELECT bloodlineID, gender, costumeID FROM blkChrBLCostumes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.bl_costumes': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_eyebrows()
{
    DBQueryResult res;
    const char *q = "SELECT eyebrowsID, eyebrowsName FROM blkChrEyebrows";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.eyebrows': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_eyes()
{
    DBQueryResult res;
    const char *q = "SELECT eyesID, eyesName FROM blkChrEyes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.eyes': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_decos()
{
    DBQueryResult res;
    const char *q = "SELECT decoID, decoName FROM blkChrDecos";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.decos': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_hairs()
{
    DBQueryResult res;
    const char *q = "SELECT hairID, hairName FROM blkChrHairs";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.hairs': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_backgrounds()
{
    DBQueryResult res;
    const char *q = "SELECT backgroundID, backgroundName FROM blkChrBackgrounds";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.backgrounds': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_accessories()
{
    DBQueryResult res;
    const char *q = "SELECT accessoryID, accessoryName FROM blkChrAccessories";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.accessories': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_lights()
{
    DBQueryResult res;
    const char *q = "SELECT lightID, lightName FROM blkChrLights";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.lights': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_costumes()
{
    DBQueryResult res;
    const char *q = "SELECT costumeID, costumeName FROM blkChrCostumes";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.costumes': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_makeups()
{
    DBQueryResult res;
    const char *q = "SELECT makeupID, makeupName FROM blkChrMakeups";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.makeups': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_beards()
{
    DBQueryResult res;
    const char *q = "SELECT beardID, beardName FROM blkChrBeards";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.beards': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_skins()
{
    DBQueryResult res;
    const char *q = "SELECT skinID, skinName FROM blkChrSkins";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.skins': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}

PyRep *ObjCacheDB::Generate_a_lipsticks()
{
    DBQueryResult res;
    const char *q = "SELECT lipstickID, lipstickName FROM blkChrLipsticks";
    if(DBcore::RunQuery(res, q)==false)
    {
        _log(SERVICE__ERROR, "Error in query for cached object 'charCreationInfo.lipsticks': %s", res.error.c_str());
        return NULL;
    }
    return DBResultToCRowset(res);
}
