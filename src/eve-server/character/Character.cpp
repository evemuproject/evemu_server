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
    Author:     Zhur, Bloody.Rabbit
*/

#include "eve-server.h"

#include "Client.h"
#include "EntityList.h"
#include "character/Character.h"
#include "character/CharacterDB.h"
#include "inventory/AttributeEnum.h"
#include "chr/ChrBloodline.h"

/*
 * CharacterData
 */
CharacterData::CharacterData(
    uint32 _accountID,
    const char *_title,
    const char *_desc,
    bool _gender,
    double _bounty,
    double _balance,
    double _aurBalance,
    double _securityRating,
    uint32 _logonMinutes,
    double _skillPoints,
    uint32 _corporationID,
    uint32 _allianceID,
    uint32 _warFactionID,
    uint32 _stationID,
    uint32 _solarSystemID,
    uint32 _constellationID,
                             uint32 _regionID,
                             ChrBloodlineRef _bloodline,
    uint32 _ancestryID,
    uint32 _careerID,
    uint32 _schoolID,
    uint32 _careerSpecialityID,
    uint64 _startDateTime,
    uint64 _createDateTime,
    uint64 _corporationDateTime,
    uint32 _shipID)
: accountID(_accountID),
  title(_title),
  description(_desc),
  gender(_gender),
  bounty(_bounty),
  balance(_balance),
  aurBalance(_aurBalance),
  securityRating(_securityRating),
  logonMinutes(_logonMinutes),
  skillPoints(_skillPoints),
  corporationID(_corporationID),
  allianceID(_allianceID),
  warFactionID(_warFactionID),
  stationID(_stationID),
  solarSystemID(_solarSystemID),
  constellationID(_constellationID),
regionID(_regionID),
bloodline(_bloodline),
  ancestryID(_ancestryID),
  careerID(_careerID),
  schoolID(_schoolID),
  careerSpecialityID(_careerSpecialityID),
  startDateTime(_startDateTime),
  createDateTime(_createDateTime),
  corporationDateTime(_corporationDateTime),
  shipID(_shipID)
{
}

/*
 * CharacterAppearance
 */

void CharacterAppearance::Build(uint32 ownerID, PyDict* data)
{
	PyList* colors = new PyList();
	PyList* modifiers = new PyList();
	PyObjectEx* appearance;
	PyList* sculpts = new PyList();

	colors = data->GetItemString("colors")->AsList();
	modifiers = data->GetItemString("modifiers")->AsList();
	appearance = data->GetItemString("appearance")->AsObjectEx();
	sculpts = data->GetItemString("sculpts")->AsList();

	PyList::const_iterator color_cur, color_end;
	color_cur = colors->begin();
	color_end = colors->end();

	for(; color_cur != color_end; color_cur++)
	{
		if((*color_cur)->IsObjectEx())
		{
			PyObjectEx_Type2* color_obj = (PyObjectEx_Type2*)(*color_cur)->AsObjectEx();
			PyTuple* color_tuple = color_obj->GetArgs()->AsTuple();

			//color tuple data structure
			//[0] PyToken
			//[1] colorID
			//[2] colorNameA
			//[3] colorNameBC
			//[4] weight
			//[5] gloss

            CharacterDB::SetAvatarColors(ownerID,
								color_tuple->GetItem(1)->AsInt()->value(),
								color_tuple->GetItem(2)->AsInt()->value(),
								color_tuple->GetItem(3)->AsInt()->value(),
								color_tuple->GetItem(4)->AsFloat()->value(),
								color_tuple->GetItem(5)->AsFloat()->value());

		}
	}

	PyObjectEx_Type2* app_obj = (PyObjectEx_Type2*)appearance;
	PyTuple* app_tuple = app_obj->GetArgs()->AsTuple();

    CharacterDB::SetAvatar(ownerID, app_tuple->GetItem(1));

	PyList::const_iterator modif_cur, modif_end;
	modif_cur = modifiers->begin();
	modif_end = modifiers->end();

	for(; modif_cur != modif_end; modif_cur++)
	{
		if((*modif_cur)->IsObjectEx())
		{
			PyObjectEx_Type2* modif_obj = (PyObjectEx_Type2*)(*modif_cur)->AsObjectEx();
			PyTuple* modif_tuple = modif_obj->GetArgs()->AsTuple();

			//color tuple data structure
			//[0] PyToken
			//[1] modifierLocationID
			//[2] paperdollResourceID
			//[3] paperdollResourceVariation
            CharacterDB::SetAvatarModifiers(ownerID,
										modif_tuple->GetItem(1),
										modif_tuple->GetItem(2),
										modif_tuple->GetItem(3));
		}
	}

	PyList::const_iterator sculpt_cur, sculpt_end;
	sculpt_cur = sculpts->begin();
	sculpt_end = sculpts->end();

	for(; sculpt_cur != sculpt_end; sculpt_cur++)
	{
		if((*sculpt_cur)->IsObjectEx())
		{
			PyObjectEx_Type2* sculpt_obj = (PyObjectEx_Type2*)(*sculpt_cur)->AsObjectEx();
			PyTuple* sculpt_tuple = sculpt_obj->GetArgs()->AsTuple();

			//sculpts tuple data structure
			//[0] PyToken
			//[1] sculptLocationID
			//[2] weightUpDown
			//[3] weightLeftRight
			//[4] weightForwardBack

            CharacterDB::SetAvatarSculpts(ownerID,
									sculpt_tuple->GetItem(1),
									sculpt_tuple->GetItem(2),
									sculpt_tuple->GetItem(3),
									sculpt_tuple->GetItem(4));

		}
	}
}


/*
 * CorpMemberInfo
 */
CorpMemberInfo::CorpMemberInfo(
    uint32 _corpHQ,
    uint64 _corpRole,
    uint64 _rolesAtAll,
    uint64 _rolesAtBase,
    uint64 _rolesAtHQ,
    uint64 _rolesAtOther)
: corpHQ(_corpHQ),
  corpRole(_corpRole),
  rolesAtAll(_rolesAtAll),
  rolesAtBase(_rolesAtBase),
  rolesAtHQ(_rolesAtHQ),
  rolesAtOther(_rolesAtOther)
{
}

/*
 * FleetMember Info
 */
FleetMemberInfo::FleetMemberInfo(
    uint32 _fleetID,
    uint32 _wingID,
    uint32 _squadID,
    uint8 _fleetRole,
    uint8 _fleetBooster,
    uint8 _fleetJob)
: fleetID(_fleetID),
wingID(_wingID),
squadID(_squadID),
fleetRole(_fleetRole),
fleetBooster(_fleetBooster),
fleetJob(_fleetJob)
{
}

/*
 * Character
 */
Character::Character(
    uint32 _characterID,
    // InventoryItem stuff:
                     const InvTypeRef _charType,
    const ItemData &_data,
    // Character stuff:
    const CharacterData &_charData,
    const CorpMemberInfo &_corpData)
: Owner(_characterID, _charType, _data),
  m_accountID(_charData.accountID),
  m_title(_charData.title),
  m_description(_charData.description),
  m_gender(_charData.gender),
  m_bounty(_charData.bounty),
  m_balance(_charData.balance),
  m_aurBalance(_charData.aurBalance),
  m_securityRating(_charData.securityRating),
  m_logonMinutes(_charData.logonMinutes),
  m_totalSPtrained(((double)(_charData.skillPoints))),
  m_corporationID(_charData.corporationID),
  m_corpHQ(_corpData.corpHQ),
  m_allianceID(_charData.allianceID),
  m_warFactionID(_charData.warFactionID),
  m_corpRole(_corpData.corpRole),
  m_rolesAtAll(_corpData.rolesAtAll),
  m_rolesAtBase(_corpData.rolesAtBase),
  m_rolesAtHQ(_corpData.rolesAtHQ),
  m_rolesAtOther(_corpData.rolesAtOther),
  m_stationID(_charData.stationID),
  m_solarSystemID(_charData.solarSystemID),
  m_constellationID(_charData.constellationID),
m_regionID(_charData.regionID),
m_bloodline(_charData.bloodline),
  m_ancestryID(_charData.ancestryID),
  m_careerID(_charData.careerID),
  m_schoolID(_charData.schoolID),
  m_careerSpecialityID(_charData.careerSpecialityID),
  m_startDateTime(_charData.startDateTime),
  m_createDateTime(_charData.createDateTime),
  m_corporationDateTime(_charData.corporationDateTime),
  m_shipID(_charData.shipID)
{
    // allow characters to be only singletons
    //assert(singleton() && quantity() == -1);
    assert(singleton());

    // Activate Save Info Timer with somewhat randomized timer value:
    //SetSaveTimerExpiry( MakeRandomInt( (10 * 60), (15 * 60) ) );        // Randomize save timer expiry to between 10 and 15 minutes
    //EnableSaveTimer();
}

CharacterRef Character::Load(uint32 characterID)
{
    return InventoryItem::Load<Character>( characterID );
}

template<class _Ty>
RefPtr<_Ty> Character::_LoadCharacter(uint32 characterID,
    // InventoryItem stuff:
                                      const InvTypeRef charType, const ItemData &data,
    // Character stuff:
    const CharacterData &charData, const CorpMemberInfo &corpData)
{
    // construct the item
    return CharacterRef( new Character( characterID, charType, data, charData, corpData ) );
}

CharacterRef Character::Spawn(
    // InventoryItem stuff:
    ItemData &data,
    // Character stuff:
    CharacterData &charData, CorpMemberInfo &corpData)
{
    uint32 characterID = Character::_Spawn( data, charData, corpData );
    if( characterID == 0 )
        return CharacterRef();

    CharacterRef charRef = Character::Load( characterID );

    // Create default dynamic attributes in the AttributeMap:
    charRef.get()->setAttribute(AttrIsOnline, 1); // Is Online

    return charRef;
}

uint32 Character::_Spawn(
    // InventoryItem stuff:
    ItemData &data,
    // Character stuff:
    CharacterData &charData, CorpMemberInfo &corpData)
{
    // make sure it's a character
    if (charData.bloodline.get() == nullptr)
    {
        return 0;
    }

    // make sure it's a singleton with qty 1
    if(!data.singleton || data.quantity != 1) {
        _log(ITEM__ERROR, "Tried to create non-singleton character %s.", data.name.c_str());
        return 0;
    }

    // first the item
    uint32 characterID = Owner::_Spawn(data);
    if(characterID == 0)
        return 0;

    // then character
    if(!InventoryDB::NewCharacter(characterID, charData, corpData)) {
        // delete the item
        InventoryDB::DeleteItem(characterID);

        return 0;
    }

    return characterID;
}

bool Character::_Load()
{
	bool bLoadSuccessful = false;

    if( !LoadContents( ) )
        return false;

    if( !InventoryDB::LoadSkillQueue( itemID(), m_skillQueue ) )
        return false;

    bLoadSuccessful = Owner::_Load();

	// Update Skill Queue and Total Skill Points Trained:
	if( bLoadSuccessful )
		UpdateSkillQueue();
    // OLD //// Calculate total SP trained and store in internal variable:
    // OLD //_CalculateTotalSPTrained();

    if( !InventoryDB::LoadCertificates( itemID(), m_certificates ) )
        return false;

	return bLoadSuccessful;
}

void Character::Delete() {
    // delete contents
    DeleteContents( );

    // delete character record
    InventoryDB::DeleteCharacter(itemID());

    // let the parent care about the rest
    Owner::Delete();
}

bool Character::AlterBalance(double balanceChange) {
    if(balanceChange == 0)
        return true;

    double result = balance() + balanceChange;

    //remember, this can take a negative amount...
    if(result < 0)
        return false;

    m_balance = result;

    //TODO: save some info to journal.
    SaveCharacter();

    return true;
}

void Character::SetLocation(uint32 stationID, uint32 solarSystemID, uint32 constellationID, uint32 regionID) {
    m_stationID = stationID;
    m_solarSystemID = solarSystemID;
    m_constellationID = constellationID;
    m_regionID = regionID;

    SaveCharacter();
}

//TODO: Delete this method as I dont think we ever going to use it.
void Character::JoinCorporation(uint32 corporationID) {
    m_corporationID = corporationID;

    //TODO: load new roles
    m_corpRole = 0;
    m_rolesAtAll = 0;
    m_rolesAtBase = 0;
    m_rolesAtHQ = 0;
    m_rolesAtOther = 0;

    //TODO: recursively change corp on all our items.

    SaveCharacter();
}

void Character::JoinCorporation(uint32 corporationID, const CorpMemberInfo &roles) {
	m_corporationID = corporationID;

	m_corpRole = roles.corpRole;
    m_rolesAtAll = roles.rolesAtAll;
    m_rolesAtBase = roles.rolesAtBase;
    m_rolesAtHQ = roles.rolesAtHQ;
	m_rolesAtOther = roles.rolesAtOther;

	SaveCharacter();
}

void Character::SetAccountKey(int32 accountKey)
{
    m_corpAccountKey = accountKey;
    Client* pClient = EntityList::FindCharacter( itemID() );
    pClient->UpdateCorpSession(pClient->GetChar());

    SaveCharacter();
}

void Character::SetFleetData(FleetMemberInfo &fleet)
{
    m_fleetID = fleet.fleetID;
    m_wingID = fleet.wingID;
    m_squadID = fleet.squadID;
    m_fleetRole = fleet.fleetRole;
    m_fleetBooster = fleet.fleetBooster;
    m_fleetJob = fleet.fleetJob;

    Client* pClient = EntityList::FindCharacter( itemID() );
    pClient->UpdateFleetSession(pClient->GetChar());
}

void Character::SetDescription(const char *newDescription) {
    m_description = newDescription;

    SaveCharacter();
}

bool Character::HasSkill(uint32 skillTypeID) const
{
    return GetSkill(skillTypeID);
}

bool Character::HasSkillTrainedToLevel(uint32 skillTypeID, uint32 skillLevel) const
{
    SkillRef requiredSkill;

    // First, check for existence of skill trained or in training:
    requiredSkill = GetSkill( skillTypeID );
    if( !requiredSkill )
        return false;

    // Second, check for required minimum level of skill, note it must already be trained to this level:
    if (requiredSkill->getAttribute(AttrSkillLevel) < skillLevel)
        return false;

    return true;
}

bool Character::HasCertificate( uint32 certificateID ) const
{
    uint32 i = 0;
    for( i = 0; i < m_certificates.size(); i++ )
    {
        if( m_certificates.at( i ).certificateID == certificateID )
            return true;
    }

    return false;
}

uint8 Character::GetSkillLevel(uint32 skillTypeID, bool zeroForNotInjected /*true*/) const {
    SkillRef requiredSkill = GetSkill( skillTypeID );
    // First, check for existence of skill trained or in training:
    if (!requiredSkill) return (zeroForNotInjected ? 0 : -1);
    return requiredSkill->getAttribute(AttrSkillLevel).get_int();
}

SkillRef Character::GetSkill(uint32 skillTypeID) const
{
    InventoryItemRef skill = GetByTypeFlag( skillTypeID, flagSkill );
    if( !skill )
        skill = GetByTypeFlag( skillTypeID, flagSkillInTraining );

    return SkillRef::StaticCast( skill );
}

SkillRef Character::GetSkillInTraining() const
{
    InventoryItemRef item;
    if (!FindSingleByFlag(flagSkillInTraining, item))
    {
        //Log::Debug("Character","unable to find skill in training");
    }

    return SkillRef::StaticCast( item );
}

void Character::GetSkillsList(std::vector<InventoryItemRef> &skills) const
{
    //find all the skills contained within ourself.
    FindByFlag( flagSkill, skills );
    FindByFlag( flagSkillInTraining, skills );
}

double Character::GetSPPerMin(SkillRef skill)
{
    EvilNumber primarySkillTrainingAttr = skill->getAttribute(AttrPrimaryAttribute);
    EvilNumber secondarySkillTrainingAttr = skill->getAttribute(AttrSecondaryAttribute);
    uint32 primarySkill = primarySkillTrainingAttr.get_int();
    uint32 secondarySkill = secondarySkillTrainingAttr.get_int();

    double primarySPperMin = getAttribute(primarySkill).get_float();
    double secondarySPperMin = getAttribute(secondarySkill).get_float();
    primarySkill -= AttrCharisma;
    secondarySkill -= AttrCharisma;
    // Get custom bonus.
    uint32 customAttr[] = {170, 174, 173, 172, 171};
    primarySPperMin += getAttribute(customAttr[primarySkill]).get_int();
    secondarySPperMin += getAttribute(customAttr[secondarySkill]).get_int();
    // Get implant bonus.
    primarySPperMin += getAttribute(primarySkill + AttrCharismaBonus).get_int();
    secondarySPperMin += getAttribute(secondarySkill + AttrCharismaBonus).get_int();

    return primarySPperMin + secondarySPperMin / 2.0f;
}

EvilNumber Character::GetEndOfTraining() const
{
    SkillRef skill = GetSkillInTraining();
    if( !skill )
        return 0;

    return skill->getAttribute(AttrExpiryTime);
}

bool Character::InjectSkillIntoBrain(SkillRef skill)
{
    Client *c = EntityList::FindCharacter( itemID() );

    SkillRef oldSkill = GetSkill( skill->typeID() );
    if( oldSkill )
    {
        //TODO: build and send proper UserError for CharacterAlreadyKnowsSkill.
        if (c != NULL)
        {
            c->SendNotifyMsg("You already know this skill.");
        }
        return false;
    }

    // TODO: based on config options later, check to see if another character, owned by this characters account,
    // is training a skill.  If so, return. (flagID=61).
    if (!canUse(skill))
    {
        // TODO: need to send back a response to the client.  need packet specs.
        _log( ITEM__TRACE, "%s (%u): Requested to train skill %u item %u but prereq not complete.", itemName().c_str(), itemID(), skill->typeID(), skill->itemID() );

        if (c != NULL)
        {
            c->SendNotifyMsg("Injection failed!  Skill prerequisites incomplete.");
        }
        return false;
    }

    // Are we injecting from a stack of skills?
    if( skill->quantity() > 1)
    {
        uint32 iID = skill->itemID();
        std::string iName = skill->itemName();

        // Split the stack to obtain single item
        skill = SkillRef::StaticCast(skill->Split(1));
        if( !skill )
        {
            _log(ITEM__ERROR, "%s (%u): Unable to split stack of %s (%u).", itemName().c_str(), itemID(), iName.c_str(), iID);
            return false;
        }
    }
    // Inject the skill.
    // Set level in defaults to integer as client does not like floats!
    skill->setAttribute(AttrSkillLevel, (uint8) 0, true, true);
    skill->MoveInto(*this, flagSkill);
    skill->SaveItem();

    if (c != NULL)
    {
        c->SendNotifyMsg("Injection of skill complete.");
    }
    return true;
}

void Character::AddToSkillQueue(uint32 typeID, uint8 level)
{
    QueuedSkill qs;
    qs.typeID = typeID;
    qs.level = level;

    m_skillQueue.push_back( qs );
}

bool Character::GrantCertificate( uint32 certificateID )
{
    cCertificates i;
    i.certificateID = certificateID;
    i.grantDate = Win32TimeNow();
    i.visibilityFlags = true;
    m_certificates.push_back( i );

    return true;
}


void Character::UpdateCertificate( uint32 certificateID, bool pub )
{
    uint32 i;
    for( i = 0; i < m_certificates.size(); i ++ )
    {
        if( m_certificates.at( i ).certificateID == certificateID )
        {
            m_certificates.at( i ).visibilityFlags = pub ;
        }
    }
}

void Character::GetCertificates( Certificates &crt )
{
    crt = m_certificates;
}

void Character::ClearSkillQueue()
{
    m_skillQueue.clear();
}

void Character::StopTraining()
{
    SkillRef stopTraining = GetSkillInTraining();
    if (stopTraining.get() == nullptr)
    {
        return;
    }
    _log(ITEM__ERROR, "%s (%u): Stopping training of skill %s (%u).", itemName().c_str(), itemID(), stopTraining->itemName().c_str(), stopTraining->itemID());

    // Get new skill Level.
    int skillLevel = stopTraining->getAttribute(AttrSkillLevel).get_int() + 1;
    // Limit skill to level 5
    skillLevel = std::min(skillLevel, 5);
    // Get skill points for next level.
    double nextLevelPoints = stopTraining->GetSPForLevel(skillLevel);
    // Get current skill points.
    double currentPoints = stopTraining->getAttribute(AttrSkillPoints).get_float();
    // Get SP to finish level.
    double SPToNextLevel = nextLevelPoints - currentPoints;
    // Get SP rate.
    double SPPerMinute = GetSPPerMin(stopTraining);
    // Get stop time.
    uint64 stopTime = Win32TimeNow();
    // Get planed end time.
    uint64 timeEndTrain = stopTraining->getAttribute(AttrExpiryTime).get_int();
    // Find minutes remaining in training.
    double minRemaining = (timeEndTrain - stopTime) / (double) Win32Time_Minute;
    // Calculate total points trained.
    double totalPointsTrained = nextLevelPoints - (minRemaining * SPPerMinute);
    if (timeEndTrain == 0)
    {
        // If training end time was improperly calculated, then no training occurred.
        totalPointsTrained = currentPoints;
    }
    // Cannot be less than points already trained.
    totalPointsTrained = std::max(totalPointsTrained, currentPoints);
    // Cannot be more than max points
    totalPointsTrained = std::min(totalPointsTrained, stopTraining->GetSPForLevel(5));
    // Check for full level training.
    bool levelUp = false;
    while (totalPointsTrained >= nextLevelPoints && skillLevel < 5)
    {
        // We completed a level...
        levelUp = true;
        // Can we gain more levels?
        skillLevel++;
        nextLevelPoints = stopTraining->GetSPForLevel(skillLevel);
    }
    // Set skill points trained.
    stopTraining->setAttribute(AttrSkillPoints, totalPointsTrained);
    SysLog::Debug("", "Skill %s (%u) trained %f skill points before termination from training queue", stopTraining->itemName().c_str(), stopTraining->itemID(), totalPointsTrained);

    // Set flag to just be a skill.
    stopTraining->SetFlag(flagSkill);
    // Set completion time to 0;
    stopTraining->setAttribute(AttrExpiryTime, 0);

    // Add event to database.
    uint32 method = 38; // 38 - SkillTrainingCanceled
    DBerror err;
    if (!DBcore::RunQuery(err,
                          "INSERT INTO srvChrSkillHistory "
                          "(characterID, typeID, level, points, spPerMin, eventID, eventTime)"
                          " VALUES (%u, %u, %u, %f, %f, %u, %" PRId64 ")",
                          itemID(), stopTraining->typeID(), skillLevel,
                          nextLevelPoints, SPPerMinute, method, stopTime))
    {
        _log(DATABASE__ERROR, "Failed to save skill history for character %u: %s", itemID(), err.c_str());
    }

    Client *c = EntityList::FindCharacter(itemID());
    if (levelUp)
    {
        // We completed a level...
        stopTraining->setAttribute(AttrSkillLevel, skillLevel);
        // Remove it from the queue and send updates.
        auto cur = m_skillQueue.begin();
        while (cur != m_skillQueue.end())
        {
            auto skill = *cur;
            if (skill.typeID == stopTraining->typeID() && skill.level <= skillLevel)
            {
                // Completed entry.
                cur = m_skillQueue.erase(cur);
            }
        }
        if (c != NULL)
        {
            // Send complete message to client.
            OnSkillTrained ost;
            ost.itemID = stopTraining->itemID();

            PyTuple* tmp = ost.Encode();
            c->QueueDestinyEvent(&tmp);
            PySafeDecRef(tmp);
        }
    }
    else
    {
        if (c != NULL)
        {
            OnSkillTrainingStopped osst;
            osst.itemID = stopTraining->itemID();
            osst.endOfTraining = 0;

            PyTuple* tmp = osst.Encode();
            c->QueueDestinyEvent(&tmp);
            PySafeDecRef(tmp);
        }
    }
    if (c != NULL)
    {
        c->UpdateSkillTraining();
    }

    // Save changes to this skill before removing it from training:
    stopTraining->SaveItem();

    // Re-Calculate total SP trained and store in internal variable:
    _CalculateTotalSPTrained();

    // Save skill queue:
    SaveSkillQueue();

    // update queue end time:
    UpdateSkillQueueEndTime(m_skillQueue);
}

SkillRef Character::StartTraining(uint32 skillID, uint64 nextStartTime)
{
    // Get start time.
    if (nextStartTime == 0)
    {
        // Default start time.  Get now!
        nextStartTime = Win32TimeNow();
    }
    SkillRef startTraining = GetSkillInTraining();
    if (startTraining && startTraining->typeID() == skillID)
    {
        // Already training the skill.
        return startTraining;
    }
    if (startTraining)
    {
        // A different skill is training, stop it!
        StopTraining();
    }
    // Look for skill in queue.
    if (m_skillQueue.empty())
    {
        // Skill queue empty.
        return SkillRef();
    }
    // Get first skill.
    QueuedSkill skill = *m_skillQueue.begin();
    if (skill.typeID != skillID)
    {
        // Skill does not match first in queue.
        return SkillRef();
    }

    // Get the characters skill entry.
    startTraining = GetSkill(skillID);
    if (startTraining.get() == nullptr || startTraining->getAttribute(AttrSkillLevel).get_int() >= 5)
    {
        // Remove un-trainable skill from list.
        m_skillQueue.erase(m_skillQueue.begin());
        // Save skill queue:
        SaveSkillQueue();
        // update queue end time:
        UpdateSkillQueueEndTime(m_skillQueue);
        // Skill not available or skill fully trained, were done here!
        return SkillRef();
    }

    // Get training rate.
    double SPPerMinute = GetSPPerMin(startTraining);
    // Get new skill Level.
    int skillLevel = startTraining->getAttribute(AttrSkillLevel).get_int() + 1;
    // Get skill points for level.
    double skillPoints = startTraining->GetSPForLevel(skillLevel);
    // Get SP to finish level.
    double SPToNextLevel = skillPoints - startTraining->getAttribute(AttrSkillPoints).get_float();
    // Calculate the time training will finish.
    uint64 timeTraining = nextStartTime + (EvilTime_Minute.get_float() * (SPToNextLevel / SPPerMinute));

    // Minimum of 10 seconds training time,
    timeTraining = std::max(timeTraining, Win32Time_Second * 10);
    // Set training time end.
    startTraining->setAttribute(AttrExpiryTime, (double) timeTraining);
    // Set training flag.
    startTraining->SetFlag(flagSkillInTraining);
    // Save changes to this skill before removing it from training:
    startTraining->SaveItem();

    SysLog::Debug("Character::UpdateSkillQueue()", "  Training skill at %f SP/min with %f SP to next Level of %d", SPPerMinute, SPToNextLevel, skillLevel);
    SysLog::Debug("    ", "Calculated time to complete training = %s", Win32TimeToString((uint64) timeTraining).c_str());

    // Add event to database.
    uint32 method = 36; // 36 - SkillTrainingStarted
    DBerror err;
    if (!DBcore::RunQuery(err,
                          "INSERT INTO srvChrSkillHistory "
                          "(characterID, typeID, level, points, spPerMin, eventID, eventTime)"
                          " VALUES (%u, %u, %u, %f, %f, %u, %" PRId64 ")",
                          itemID(), startTraining->typeID(), skillLevel,
                          skillPoints, SPPerMinute, method, nextStartTime))
    {
        _log(DATABASE__ERROR, "Failed to save skill history for character %u: %s", itemID(), err.c_str());
    }

    // Update queue end time:
    UpdateSkillQueueEndTime(m_skillQueue);

    Client *c = EntityList::FindCharacter(itemID());
    if (c != NULL)
    {
        // Sent start training notice to client.
        OnSkillStartTraining osst;
        osst.itemID = startTraining->itemID();
        osst.endOfTraining = timeTraining;

        PyTuple* tmp = osst.Encode();
        c->QueueDestinyEvent(&tmp);
        PySafeDecRef(tmp);

        c->UpdateSkillTraining();
    }

    return startTraining;
}

void Character::UpdateSkillQueue()
{
    Client *c = EntityList::FindCharacter(itemID());

    SkillRef currentTraining = GetSkillInTraining();
    if (currentTraining)
    {
        if (m_skillQueue.empty() || currentTraining->typeID() != m_skillQueue.front().typeID)
        {
            // Either queue is empty or skill with different typeID is in training ...
            StopTraining();
            return;
        }
        if (currentTraining->getAttribute(AttrExpiryTime).get_float() == 0)
        {
            // Start training next skill.
            StartTraining(currentTraining->typeID());
            return;
        }
    }
    else
    {
        // Nothing training, were done here.
        return;
    }

    uint64 nextStartTime = Win32TimeNow();
    uint64 expiry;
    while ((expiry = currentTraining->getAttribute(AttrExpiryTime).get_float()) <= Win32TimeNow())
    {
        if (expiry == 0)
        {
            // Skill was flagged for training but not started, start it.
            currentTraining = StartTraining(currentTraining->typeID());
            if (currentTraining.get() == nullptr)
            {
                break;
            }
            continue;
        }
        // Training has been finished:
        SysLog::Debug("Character::UpdateSkillQueue()", "%s (%u): Finishing training of skill %s (%u).", itemName().c_str(), itemID(), currentTraining->itemName().c_str(), currentTraining->itemID());

        // Get new skill Level.
        int skillLevel = currentTraining->getAttribute(AttrSkillLevel).get_int() + 1;
        // Limit skill to level 5
        skillLevel = std::min(skillLevel, 5);
        // Get skill points for level.
        double skillPoints = currentTraining->GetSPForLevel(skillLevel);
        // Set new attributes.
        currentTraining->setAttribute(AttrSkillLevel, skillLevel);
        currentTraining->setAttribute(AttrSkillPoints, skillPoints, true);

        // Get completion time as new start time.
        nextStartTime = expiry;
        // Clear completion time.
        currentTraining->setAttribute(AttrExpiryTime, 0);
        // Set skill flag to not training.
        currentTraining->SetFlag(flagSkill);
        // Save changes to this skill now that it has finished training:
        currentTraining->SaveItem();
        // Erase first element in skill queue
        m_skillQueue.erase(m_skillQueue.begin());

        // Add completion to database.
        uint32 method = 37; // 37 - SkillTrainingComplete
        DBerror err;
        if (!DBcore::RunQuery(err,
                              "INSERT INTO srvChrSkillHistory "
                              "(characterID, typeID, level, points, eventID, eventTime)"
                              " VALUES (%u, %u, %u, %f, %u, %" PRId64 ")",
                              itemID(), currentTraining->typeID(), skillLevel, skillPoints, method, nextStartTime))
        {
            _log(DATABASE__ERROR, "Failed to save skill history for character %u: %s", itemID(), err.c_str());
        }

        if (c != NULL)
        {
            // Send complete message to client.
            OnSkillTrained ost;
            ost.itemID = currentTraining->itemID();

            PyTuple* tmp = ost.Encode();
            c->QueueDestinyEvent(&tmp);
            PySafeDecRef( tmp );

            c->UpdateSkillTraining();
        }
        // We are now not training anything.
        currentTraining = SkillRef();
        // Is skill queue empty?
        if (!m_skillQueue.empty())
        {
            // No, start next skill.
            QueuedSkill skill = *m_skillQueue.begin();
            currentTraining = StartTraining(skill.typeID, nextStartTime);
        }
        if (currentTraining.get() == nullptr)
        {
            break;
        }
    }

    // Re-Calculate total SP trained and store in internal variable:
    _CalculateTotalSPTrained();

    // Save skill queue:
    SaveSkillQueue();

    // update queue end time:
    UpdateSkillQueueEndTime(m_skillQueue);
}

//  this still needs work...have to check for multiple levels of same skill.
//  right now, check is current level to trained level...so, l2, l3, l4 checks for l1->l2, l1->l3, l1->l4 then combines them.
//  it wont check for previous level to level in queue....need to make check for that so it will only check l1->l4.
void Character::UpdateSkillQueueEndTime(const SkillQueue &queue)
{
    double chrMinRemaining = 0; // explicit init to 0

    for(size_t i = 0; i < queue.size(); i++)    // loop thru skills currently in queue
    {
        const QueuedSkill &qs = queue[ i ];     // get skill id from queue
        SkillRef skill = Character::GetSkill( qs.typeID );   //make ref for current skill

        chrMinRemaining += (skill->GetSPForLevel(qs.level) - skill->getAttribute(AttrSkillPoints).get_float()) / GetSPPerMin(skill);
    }
    chrMinRemaining = chrMinRemaining * Win32Time_Minute + Win32TimeNow();

    DBerror err;
    if (!DBcore::RunQuery(err, "UPDATE srvCharacter SET skillQueueEndTime = %f WHERE characterID = %u ", chrMinRemaining, itemID()))
    {
        _log(DATABASE__ERROR, "Failed to set skillQueueEndTime for character %u: %s", itemID(), err.c_str());
        return;
    }
    return;
}

PyDict *Character::CharGetInfo() {
    //TODO: verify that we are a char?

    if( !LoadContents( ) ) {
        codelog(ITEM__ERROR, "%s (%u): Failed to load contents for CharGetInfo", m_itemName.c_str(), m_itemID);
        return NULL;
    }

    PyDict *result = new PyDict;
    Rsp_CommonGetInfo_Entry entry;

    if(!Populate(entry))
        return NULL;
    result->SetItem(new PyInt(m_itemID), new PyObject("util.KeyVal", entry.Encode()));

    //now encode skills...
    std::vector<InventoryItemRef> skills;
    //find all the skills contained within ourself.
    FindByFlag( flagSkill, skills );
    FindByFlag( flagSkillInTraining, skills );

    //encode an entry for each one.
    std::vector<InventoryItemRef>::iterator cur, end;
    cur = skills.begin();
    end = skills.end();
    for(; cur != end; cur++) {
        if(!(*cur)->Populate(entry)) {
            codelog(ITEM__ERROR, "%s (%u): Failed to load skill item %u for CharGetInfo", m_itemName.c_str(), itemID(), (*cur)->itemID());
        } else {
            result->SetItem(new PyInt((*cur)->itemID()), new PyObject("util.KeyVal", entry.Encode()));
        }
    }

    return result;
}

PyObject *Character::GetDescription() const
{
    util_Row row;

    row.header.push_back("description");

    row.line = new PyList;
    row.line->AddItemString( description().c_str() );

    return row.Encode();
}

PyTuple *Character::GetSkillQueue() {
    // return skills from skill queue
    PyList *list = new PyList;

    SkillQueue::iterator cur, end;
    cur = m_skillQueue.begin();
    end = m_skillQueue.end();
    for(; cur != end; cur++)
    {
        SkillQueue_Element el;

        el.typeID = cur->typeID;
        el.level = cur->level;

        list->AddItem( el.Encode() );
    }

    // now encapsulate it in a tuple with the free points
    PyTuple *tuple = new PyTuple(2);
    tuple->SetItem(0, list);
    // sending 0, as done on retail, doesn't fuck up calculation for some reason
    // so we can take the same shortcut here
    tuple->SetItem(1, new PyInt(0));

    return tuple;
}

SkillRef Character::GetSkillInQueue(uint32 index)
{
    SkillQueue::iterator cur, end;
    cur = m_skillQueue.begin();
    end = m_skillQueue.end();
    for (; cur != end; cur++)
    {
        if (index == 0)
        {
            uint32 typeID = cur->typeID;
            return GetSkill(typeID);
        }
        index--;
    }

    return SkillRef();
}

InventoryItemRef Character::GetImplant(uint32 slot)
{

    InventoryItemRef item;
    if (m_implants.find(slot) != m_implants.end())
    {
        item = m_implants[slot];
    }
    return item;
}

void Character::AddItem(InventoryItemRef item)
{
    Inventory::AddItem( item );

    if (item->flag() == flagImplant)
    {
        // Skill has been added ...
        if (item->categoryID() != EVEDB::invCategories::Implant)
        {
            _log(ITEM__WARNING, "%s (%u): %s has been added with flag %d.", itemName().c_str(), itemID(), item->category()->categoryName.c_str(), (int) item->flag());
        }
        else
        {
            item->ChangeSingleton(true);
            uint32 slot = item->getAttribute(AttrImplantness).get_int();
            if (m_implants.find(slot) != m_implants.end())
            {
                // Remove existing implant.
                InventoryItemRef existing = m_implants[slot];
                for (int i = AttrCharismaBonus; i <= AttrWillpowerBonus; i++)
                {
                    setAttribute(i, getAttribute(i).get_int()
                                 - existing->getAttribute(i).get_int()
                                 + item->getAttribute(i).get_int());
                }
            }
            else
            {
                for (int i = AttrCharismaBonus; i <= AttrWillpowerBonus; i++)
                {
                    setAttribute(i, getAttribute(i).get_int()
                                 + item->getAttribute(i).get_int());
                }
            }
            // Install new implant
            m_implants[slot] = item;
            SaveAttributes();

            // This is a hack to try and get implants to show up.
            //std::map<int32, PyRep *> changes;
            //changes[ixLocationID] = new PyInt(item->locationID());
            //changes[ixFlag] = new PyInt(item->flag());
            //SendItemChange(ownerID(), changes); //changes is consumed
        }
    }

    if (item->flag() == flagSkill || item->flag() == flagSkillInTraining)
    {
        // Skill has been added ...
        if (item->categoryID() != EVEDB::invCategories::Skill)
        {
            _log(ITEM__WARNING, "%s (%u): %s has been added with flag %d.", itemName().c_str(), itemID(), item->category()->categoryName.c_str(), (int) item->flag());
        }
        else
        {
            SkillRef skill = SkillRef::StaticCast( item );

            if( !skill->singleton() )
            {
                _log( ITEM__TRACE, "%s (%u): Injecting %s.", itemName().c_str(), itemID(), item->itemName().c_str() );

                // Make it singleton and set initial skill values.
                skill->ChangeSingleton( true );

                skill->setAttribute(AttrSkillLevel, 0);
                skill->setAttribute(AttrSkillPoints, 0);
            }
            // Do sanity check on skill level.
            if (skill->getAttribute(AttrSkillLevel).get_int() >= 5)
            {
                skill->setAttribute(AttrSkillLevel, 5);
                skill->setAttribute(AttrSkillPoints, skill->GetSPForLevel(5));
            }
            if (skill->flag() != flagSkillInTraining)
            {
                skill->setAttribute(AttrExpiryTime, 0);
            }
            else
            {
                // This should be training, make sure it's started.
                StartTraining(skill->typeID());
            }
        }
    }
}

void Character::RemoveItem(InventoryItemRef item)
{
    Inventory::RemoveItem(item);
    if (item->flag() == flagImplant)
    {
        // Item removed is an implant.
        uint32 slot = item->getAttribute(AttrImplantness).get_int();
        if (m_implants.find(slot) != m_implants.end())
        {
            // Implant slot found
            if (m_implants[slot] == item)
            {
                // Implant found.
                m_implants.erase(slot);
                // Remove implant bonuses.
                for (int i = AttrCharismaBonus; i <= AttrWillpowerBonus; i++)
                {
                    setAttribute(i, getAttribute(i).get_int()
                                 - item->getAttribute(i).get_int());
                }
            }
        }
    }
}

void Character::SaveCharacter()
{
    _log( ITEM__TRACE, "Saving character %u.", itemID() );

    // Calculate total Skill Points trained at this time to save to DB:
    _CalculateTotalSPTrained();

    SysLog::Debug("Character::SaveCharacter()", "Saving all basic character info and attribute info to DB for character %s...", itemName().c_str());
    // character data
    InventoryDB::SaveCharacter(
        itemID(),
        CharacterData(
            accountID(),
            title().c_str(),
            description().c_str(),
            gender(),
            bounty(),
            balance(),
            aurBalance(),
            securityRating(),
            logonMinutes(),
            m_totalSPtrained.get_float(),
            corporationID(),
            allianceID(),
            warFactionID(),
            stationID(),
            solarSystemID(),
            constellationID(),
                      regionID(),
                      m_bloodline,
            ancestryID(),
            careerID(),
            schoolID(),
            careerSpecialityID(),
            startDateTime(),
            createDateTime(),
            corporationDateTime(),
            shipID()
        )
    );

    // corporation data
    InventoryDB::SaveCorpMemberInfo(
        itemID(),
        CorpMemberInfo(
            corporationHQ(),
            corpRole(),
            rolesAtAll(),
            rolesAtBase(),
            rolesAtHQ(),
            rolesAtOther()
        )
    );

    // Save this character's own attributes:
    SaveAttributes();
}

void Character::SaveFullCharacter()
{
    _log( ITEM__TRACE, "Saving character %u.", itemID() );

    SysLog::Debug("Character::SaveFullCharacter()", "Saving FULL set of character info, skills, items, etc to DB for character %s...", itemName().c_str());

	// First save basic character info and attributes:
	SaveCharacter();

	// BAD BAD BAD: This is taking minutes and minutes for high SP chars when all we need to do is save the current skill in training:
    // Loop through all skills and save each one:
/*
	std::vector<InventoryItemRef> skills;
    GetSkillsList( skills );
    std::vector<InventoryItemRef>::iterator cur, end;
    cur = skills.begin();
    end = skills.end();
    for(; cur != end; cur++)
		cur->get()->SaveItem();
        //cur->get()->SaveAttributes();
*/
	SkillRef currentTraining = GetSkillInTraining();
	if( currentTraining.get() != NULL )
		currentTraining->SaveItem();

    // Loop through all items owned by this Character and save each one:
	// TODO

	// Loop through all contracts or other non-item things owned by this Character and save each one:
	// TODO

	SaveCertificates();
}

void Character::SaveSkillQueue() const {
    _log( ITEM__TRACE, "Saving skill queue of character %u.", itemID() );

    // skill queue
    InventoryDB::SaveSkillQueue(
        itemID(),
        m_skillQueue
    );
}

void Character::SaveCertificates() const
{
    _log( ITEM__TRACE, "Saving Implants of character %u", itemID() );

    InventoryDB::SaveCertificates(
        itemID(),
        m_certificates
        );
}

void Character::SetActiveShip(uint32 shipID)
{
    m_shipID = shipID;
}

bool Character::canUse(InventoryItemRef item)
{
    int requiredAttr[] = {AttrRequiredSkill1, AttrRequiredSkill2, AttrRequiredSkill3, AttrRequiredSkill4, AttrRequiredSkill5, AttrRequiredSkill6};
    int requiredLevel[] = {AttrRequiredSkill1Level, AttrRequiredSkill2Level, AttrRequiredSkill3Level, AttrRequiredSkill4Level, AttrRequiredSkill5Level, AttrRequiredSkill6Level};

    for (int i = 0; i < 6; i++)
    {
        // Is there a required skill?
        uint32 skillTypeID = item->getAttribute(requiredAttr[i]).get_int();
        if (skillTypeID != 0)
        {
            // There is a required skill.
            SkillRef requiredSkill = GetSkill(skillTypeID);
            if (requiredSkill.get() == nullptr)
            {
                // We don't have the required skill.
                return false;
            }
            // Do we have the required level?
            if (requiredSkill->GetSkillLevel() < item->getAttribute(requiredLevel[i]).get_int())
            {
                // We do not have necessary level.
                return false;
            }
        }
    }
    // We have all skills needed.
    return true;
}

void Character::_CalculateTotalSPTrained()
{
    // Loop through all skills trained and calculate total SP this character has trained so far,
    // NOT including the skill currently being trained:
    EvilNumber totalSP = 0.0f;
    std::vector<InventoryItemRef> skills;
    GetSkillsList( skills );
    std::vector<InventoryItemRef>::iterator cur, end;
    cur = skills.begin();
    end = skills.end();
    for(; cur != end; cur++)
    {
        totalSP = totalSP + cur->get()->getAttribute(AttrSkillPoints); // much cleaner and more accurate    -allan
    }

    m_totalSPtrained = totalSP;
}


