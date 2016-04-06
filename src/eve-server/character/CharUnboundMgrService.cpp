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
    Author:     caytchen, Zhur
*/

#include "eve-server.h"

#include "EVEServerConfig.h"
#include "PyServiceCD.h"
#include "cache/ObjCacheService.h"
#include "character/CharUnboundMgrService.h"
#include "imageserver/ImageServer.h"
#include "PyServiceMgr.h"

#include "chr/ChrBloodline.h"

PyCallable_Make_InnerDispatcher(CharUnboundMgrService)

CharUnboundMgrService::CharUnboundMgrService()
: PyService("charUnboundMgr", new Dispatcher(this))
{
    CharacterDB::Init();

    PyCallable_REG_CALL(CharUnboundMgrService, SelectCharacterID)
    PyCallable_REG_CALL(CharUnboundMgrService, GetCharacterToSelect)
    PyCallable_REG_CALL(CharUnboundMgrService, GetCharactersToSelect)
    PyCallable_REG_CALL(CharUnboundMgrService, GetCharacterInfo)
    PyCallable_REG_CALL(CharUnboundMgrService, IsUserReceivingCharacter)
    PyCallable_REG_CALL(CharUnboundMgrService, DeleteCharacter)
    PyCallable_REG_CALL(CharUnboundMgrService, PrepareCharacterForDelete)
    PyCallable_REG_CALL(CharUnboundMgrService, CancelCharacterDeletePrepare)
    PyCallable_REG_CALL(CharUnboundMgrService, ValidateNameEx)
    PyCallable_REG_CALL(CharUnboundMgrService, GetCharCreationInfo)
    PyCallable_REG_CALL(CharUnboundMgrService, GetCharNewExtraCreationInfo)
    PyCallable_REG_CALL(CharUnboundMgrService, CreateCharacterWithDoll)
}

CharUnboundMgrService::~CharUnboundMgrService() {
}

void CharUnboundMgrService::GetCharacterData(uint32 characterID, std::map<std::string, uint32> &characterDataMap)
{
    CharacterDB::GetCharacterData(characterID, characterDataMap);
}

PyResult CharUnboundMgrService::Handle_IsUserReceivingCharacter(PyCallArgs &call) {
    return new PyBool(false);
}

PyResult CharUnboundMgrService::Handle_ValidateNameEx(PyCallArgs &call)
{
    Call_SingleWStringArg arg;
    if (!arg.Decode(&call.tuple))
    {
        codelog(CLIENT__ERROR, "Failed to decode args for ValidateNameEx call");
        return NULL;
    }

    return new PyBool(CharacterDB::ValidateCharName(arg.arg.c_str()));
}

PyResult CharUnboundMgrService::Handle_SelectCharacterID(PyCallArgs &call) {
    CallSelectCharacterID arg;
    if (!arg.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "Failed to decode args for SelectCharacterID call");
        return NULL;
    }

    call.client->SelectCharacter(arg.charID);
    return NULL;
}

PyResult CharUnboundMgrService::Handle_GetCharactersToSelect(PyCallArgs &call)
{
    return (CharacterDB::GetCharacterList(call.client->GetAccountID()));
}

PyResult CharUnboundMgrService::Handle_GetCharacterToSelect(PyCallArgs &call) {
    Call_SingleIntegerArg args;
    if(!args.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "Invalid arguments");
        return NULL;
    }

    PyRep *result = CharacterDB::GetCharSelectInfo(args.arg);
    if(result == NULL) {
        _log(CLIENT__ERROR, "Failed to load character %d", args.arg);
        return NULL;
    }

    return result;
}

PyResult CharUnboundMgrService::Handle_DeleteCharacter(PyCallArgs &call) {
    Call_SingleIntegerArg args;
    if (!args.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "Invalid arguments for DeleteCharacter call");
        return NULL;
    }

    return CharacterDB::DeleteCharacter(call.client->GetAccountID(), args.arg);
}

PyResult CharUnboundMgrService::Handle_PrepareCharacterForDelete(PyCallArgs &call) {
    Call_SingleIntegerArg args;
    if (!args.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "Invalid arguments for PrepareCharacterForDelete call");
        return NULL;
    }

    return new PyLong((int64) CharacterDB::PrepareCharacterForDelete(call.client->GetAccountID(), args.arg));
}

PyResult CharUnboundMgrService::Handle_CancelCharacterDeletePrepare(PyCallArgs &call) {
    Call_SingleIntegerArg args;
    if (!args.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "Invalid arguments for CancelCharacterDeletePrepare call");
        return NULL;
    }

    CharacterDB::CancelCharacterDeletePrepare(call.client->GetAccountID(), args.arg);

    // the client doesn't care what we return here
    return NULL;
}

PyResult CharUnboundMgrService::Handle_GetCharacterInfo(PyCallArgs &call) {
	_log(CLIENT__MESSAGE, "Called GetCharacterInfo stub");
    return NULL;
}

PyResult CharUnboundMgrService::Handle_GetCharCreationInfo(PyCallArgs &call) {
    PyDict *result = new PyDict();

    //send all the cache hints needed for char creation.
    PyServiceMgr::cache_service->InsertCacheHints(
        ObjCacheService::hCharCreateCachables,
        result);
    _log(CLIENT__MESSAGE, "Sending char creation info reply");

    return result;
}

PyResult CharUnboundMgrService::Handle_GetCharNewExtraCreationInfo(PyCallArgs &call) {
    PyDict *result = new PyDict();
    PyServiceMgr::cache_service->InsertCacheHints(ObjCacheService::hCharCreateNewExtraCachables, result);
    _log(CLIENT__MESSAGE, "Sending char new extra creation info reply");
    return result;
}

PyResult CharUnboundMgrService::Handle_CreateCharacterWithDoll(PyCallArgs &call) {
    CallCreateCharacterWithDoll arg;

    if (!arg.Decode(call.tuple))
    {
        codelog(CLIENT__ERROR, "Failed to decode args for CreateCharacterWithDoll call");
        return NULL;
    }

    _log(CLIENT__MESSAGE, "CreateCharacterWithDoll called for '%s'", arg.name.c_str());
    _log(CLIENT__MESSAGE, "  bloodlineID=%u genderID=%u ancestryID=%u",
            arg.bloodlineID, arg.genderID, arg.ancestryID);

    // obtain character type
    ItemFactory::SetUsingClient(call.client);
    ChrBloodlineRef char_type;
    if (!ChrBloodline::getBloodline(arg.bloodlineID, char_type))
    {
        return nullptr;
    }
    uint32 charTypeID;
    InventoryDB::GetCharacterTypeByBloodline(char_type->bloodlineID, charTypeID);

    // we need to fill these to successfully create character item
    ItemData idata;
    CharacterData cdata;
    CharacterAppearance capp;
    CorpMemberInfo corpData;

    idata.typeID = charTypeID;
    idata.name = arg.name;
    idata.ownerID = 1; // EVE System
    idata.quantity = 1;
    idata.singleton = true;

    cdata.accountID = call.client->GetAccountID();
    cdata.gender = arg.genderID != 0;
    cdata.ancestryID = arg.ancestryID;
    cdata.schoolID = arg.schoolID;
    cdata.bloodline = ChrBloodline::getBloodline(arg.bloodlineID);

    //Set the character's career based on the school they picked.
    if (CharacterDB::GetCareerBySchool(cdata.schoolID, cdata.careerID))
    {
        // Right now we don't know what causes the specialization switch, so just make both values the same
        cdata.careerSpecialityID = cdata.careerID;
    } else {
        codelog(SERVICE__WARNING, "Could not find default School ID %u. Using Caldari Military.", cdata.schoolID);
        cdata.careerID = 11;
        cdata.careerSpecialityID = 11;
    }

    corpData.corpRole = 0;
    corpData.rolesAtAll = 0;
    corpData.rolesAtBase = 0;
    corpData.rolesAtHQ = 0;
    corpData.rolesAtOther = 0;

    // Variables for storing attribute bonuses
    uint8 intelligence = char_type->intelligence;
    uint8 charisma = char_type->charisma;
    uint8 perception = char_type->perception;
    uint8 memory = char_type->memory;
    uint8 willpower = char_type->willpower;

    // Setting character's starting position, and getting it's location...
    // Also query attribute bonuses from ancestry
    if (!CharacterDB::GetLocationCorporationByCareer(cdata)
            || !CharacterDB::GetAttributesFromAncestry(cdata.ancestryID, intelligence, charisma, perception, memory, willpower)
    ) {
        codelog(CLIENT__ERROR, "Failed to load char create details. Bloodline %u, ancestry %u.",
            char_type->bloodlineID, cdata.ancestryID);
        return NULL;
    }

    idata.locationID = cdata.stationID; // Just so our starting items end up in the same place.

    // Change starting corperation based on value in XML file.
    if( EVEServerConfig::character.startCorporation ) { // Skip if 0
        if (CharacterDB::DoesCorporationExist(EVEServerConfig::character.startCorporation))
        {
            cdata.corporationID = EVEServerConfig::character.startCorporation;
        } else {
            codelog(SERVICE__WARNING, "Could not find default Corporation ID %u. Using Career Defaults instead.", EVEServerConfig::character.startCorporation);
        }
    }
    else
    {
        uint32 corporationID;
        if (CharacterDB::GetCorporationBySchool(cdata.schoolID, corporationID))
        {
            cdata.corporationID = corporationID;
        }
        else
        {
            codelog(SERVICE__ERROR, "Could not place character in default corporation for school.");
        }
    }

    // Added ability to set starting station in xml config by Pyrii
    if( EVEServerConfig::character.startStation ) { // Skip if 0
        if (!CharacterDB::GetLocationByStation(EVEServerConfig::character.startStation, cdata))
        {
            codelog(SERVICE__WARNING, "Could not find default station ID %u. Using Career Defaults instead.", EVEServerConfig::character.startStation);
        }
    }
    else
    {
        uint32 stationID;
        if (CharacterDB::GetCareerStationByCorporation(cdata.corporationID, stationID))
        {
            if (!CharacterDB::GetLocationByStation(stationID, cdata))
                codelog(SERVICE__WARNING, "Could not find default station ID %u.", stationID);
        }
        else
        {
            codelog(SERVICE__ERROR, "Could not place character in default station for school.");
        }
    }

    cdata.bounty = 0;
    cdata.balance = EVEServerConfig::character.startBalance;
    cdata.aurBalance = 0; // TODO Add aurBalance to the database
    cdata.securityRating = EVEServerConfig::character.startSecRating;
    cdata.logonMinutes = 0;
    cdata.title = "No Title";

    cdata.startDateTime = Win32TimeNow();
    cdata.createDateTime = cdata.startDateTime;
    cdata.corporationDateTime = cdata.startDateTime;

    typedef std::map<uint32, uint32>        CharSkillMap;
    typedef CharSkillMap::iterator          CharSkillMapItr;

    //load skills
    CharSkillMap startingSkills;
    if (!CharacterDB::GetSkillsByRace(char_type->raceID, startingSkills))
    {
        codelog(CLIENT__ERROR, "Failed to load char create skills. Bloodline %u, Ancestry %u.",
            char_type->bloodlineID, cdata.ancestryID);
        return NULL;
    }

    //now we have all the data we need, stick it in the DB
    //create char item
    CharacterRef char_item = ItemFactory::SpawnCharacter(idata, cdata, corpData);
    if( !char_item ) {
        //a return to the client of 0 seems to be the only means of marking failure
        codelog(CLIENT__ERROR, "Failed to create character '%s'", idata.name.c_str());
        return NULL;
    }

	// build character appearance (body, clothes, accessories)
	capp.Build(char_item->itemID(), arg.avatarInfo);

    // add attribute bonuses
    char_item->setAttribute(AttrIntelligence, intelligence);
    char_item->setAttribute(AttrCharisma, charisma);
    char_item->setAttribute(AttrPerception, perception);
    char_item->setAttribute(AttrMemory, memory);
    char_item->setAttribute(AttrWillpower, willpower);

    // register name
    CharacterDB::add_name_validation_set(char_item->itemName().c_str(), char_item->itemID());

    //spawn all the skills
    uint32 skillLevel;
    CharSkillMapItr cur, end;
    cur = startingSkills.begin();
    end = startingSkills.end();
    for(; cur != end; cur++)
    {
        ItemData skillItem( cur->first, char_item->itemID(), char_item->itemID(), flagSkill );
        SkillRef i = ItemFactory::SpawnSkill(skillItem);
        if( !i ) {
            _log(CLIENT__ERROR, "Failed to add skill %u to char %s (%u) during char create.", cur->first, char_item->itemName().c_str(), char_item->itemID());
            continue;
        }

        skillLevel = cur->second;
        i->setAttribute(AttrSkillLevel, skillLevel );
        i->setAttribute(AttrSkillPoints, i->GetSPForLevel(cur->second));
        i->SaveAttributes();
    }

    //now set up some initial inventory:
    InventoryItemRef initInvItem;

    // add "Damage Control I"
    ItemData itemDamageControl( 2046, char_item->itemID(), char_item->locationID(), flagHangar, 1 );
    initInvItem = ItemFactory::SpawnItem(itemDamageControl);

    if( !initInvItem )
        codelog(CLIENT__ERROR, "%s: Failed to spawn a starting item", char_item->itemName().c_str());

    // add 1 unit of "Tritanium"
    ItemData itemTritanium( 34, char_item->itemID(), char_item->locationID(), flagHangar, 1 );
    initInvItem = ItemFactory::SpawnItem(itemTritanium);

    // add 1 unit of "Clone Grade Alpha"
    ItemData itemCloneAlpha( 164, char_item->itemID(), char_item->locationID(), flagClone, 1 );
    itemCloneAlpha.customInfo="active";
    initInvItem = ItemFactory::SpawnItem(itemCloneAlpha);

    if( !initInvItem )
        codelog(CLIENT__ERROR, "%s: Failed to spawn a starting item", char_item->itemName().c_str());

    // give the player its ship.
    std::string ship_name = char_item->itemName() + "'s Ship";

    ItemData shipItem( char_type->shipTypeID, char_item->itemID(), char_item->locationID(), flagHangar, ship_name.c_str() );
    ShipRef ship_item = ItemFactory::SpawnShip(shipItem);

    char_item->SetActiveShip( ship_item->itemID() );
    char_item->SaveFullCharacter();
	ship_item->SaveItem();

    if( !ship_item ) {
        codelog(CLIENT__ERROR, "%s: Failed to spawn a starting item", char_item->itemName().c_str());
    }
    else
        //welcome on board your starting ship
        //char_item->MoveInto( *ship_item, flagPilot, false );

    _log( CLIENT__MESSAGE, "Sending char create ID %u as reply", char_item->itemID() );

    // we need to report the charID to the ImageServer so it can correctly assign a previously received image
    ImageServer::ReportNewCharacter(call.client->GetAccountID(), char_item->itemID());

    // Release the item factory now that the character is finished being accessed:
    ItemFactory::UnsetUsingClient();

    return new PyInt( char_item->itemID() );
}
