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
    Author:        Aknor Jaden
*/

#include "eve-server.h"

#include "apiserver/APICharacterManager.h"
#include "inventory/AttributeEnum.h"

APICharacterManager::APICharacterManager(const PyServiceMgr &services)
: APIServiceManager(services)
{
}

std::tr1::shared_ptr<std::string> APICharacterManager::ProcessCall(const APICommandCall * pAPICommandCall)
{
    sLog.Debug("APIAdminManager::ProcessCall()", "EVEmu API - Character Service Manager");

    if( pAPICommandCall->find( "servicehandler" ) == pAPICommandCall->end() )
    {
        sLog.Error( "APICharacterManager::ProcessCall()", "Cannot find 'servicehandler' specifier in pAPICommandCall packet" );
        return std::tr1::shared_ptr<std::string>(new std::string(""));
    }

    if( pAPICommandCall->find( "servicehandler" )->second == "CharacterSheet.xml.aspx" )
        return _CharacterSheet(pAPICommandCall);
    if( pAPICommandCall->find( "servicehandler" )->second == "SkillQueue.xml.aspx" )
        return _SkillQueue(pAPICommandCall);
    if( pAPICommandCall->find( "servicehandler" )->second == "SkillInTraining.xml.aspx" )
        return _SkillInTraining(pAPICommandCall);
    //else if( pAPICommandCall->find( "servicehandler" )->second == "TODO.xml.aspx" )
    //    return _TODO(pAPICommandCall);
    else
    {
        sLog.Error("APIAdminManager::ProcessCall()", "EVEmu API - Admin Service Manager - ERROR: Cannot resolve '%s' as a valid service query for Admin Service Manager",
            pAPICommandCall->find("servicehandler")->second.c_str() );
        return std::tr1::shared_ptr<std::string>(new std::string(""));
    }
    sLog.Debug("APICharacterManager::ProcessCall()", "EVEmu API - Character Service Manager");

    return BuildErrorXMLResponse( "9999", "EVEmu API Server: Character Manager - Unknown call." );
}

std::tr1::shared_ptr<std::string> APICharacterManager::_CharacterSheet(const APICommandCall * pAPICommandCall)
{
    size_t i;

    sLog.Error( "APICharacterManager::_CharacterSheet()", "TODO: Insert code to validate userID and apiKey" );

    sLog.Debug("APICharacterManager::_CharacterSheet()", "EVEmu API - Character Service Manager - CALL: CharacterSheet.xml.aspx");

    if( pAPICommandCall->find( "userid" ) == pAPICommandCall->end() )
    {
        sLog.Error( "APICharacterManager::_CharacterSheet()", "ERROR: No 'userID' parameter found in call argument list - exiting with error and sending back NOTHING" );
        return BuildErrorXMLResponse( "106", "Must provide userID parameter for authentication." );
    }

    if( pAPICommandCall->find( "apikey" ) == pAPICommandCall->end() )
    {
        sLog.Error( "APICharacterManager::_CharacterSheet()", "ERROR: No 'apiKey' parameter found in call argument list - exiting with error and sending back NOTHING" );
        return BuildErrorXMLResponse( "203", "Authentication failure." );
    }

    if( pAPICommandCall->find( "characterid" ) == pAPICommandCall->end() )
    {
        sLog.Error( "APICharacterManager::_CharacterSheet()", "ERROR: No 'characterID' parameter found in call argument list - exiting with error and sending back NOTHING" );
        return BuildErrorXMLResponse( "105", "Invalid characterID." );
    }

    // Make calls to the APICharacterDB class to grab all data for this call and populate the xml structure with that data
    uint32 characterID = atoi( pAPICommandCall->find( "characterid" )->second.c_str() );
    std::vector<std::string> skillTypeIDList;
    std::vector<std::string> skillPointsList;
    std::vector<std::string> skillLevelList;
    std::vector<std::string> skillPublishedList;
    m_charDB.GetCharacterSkillsTrained( characterID, skillTypeIDList, skillPointsList, skillLevelList, skillPublishedList );

    std::vector<std::string> charInfoList;
    m_charDB.GetCharacterInfo( characterID, charInfoList );

    std::map<std::string, std::string> charAttributes;
    m_charDB.GetCharacterAttributes( characterID, charAttributes );

    sLog.Error( "APICharacterManager::_CharacterSheet()", "INFO: Sections Currently hard-coded: attributeEnhancers, certificates, corporation roles" );

    std::vector<std::string> rowset;
    _BuildXMLHeader();
    {
        _BuildXMLTag( "result" );
        {
            _BuildSingleXMLTag( "characterID", std::string(itoa(characterID)) );
            _BuildSingleXMLTag( "name", charInfoList.at(12) );
            _BuildSingleXMLTag( "DoB", Win32TimeToString(strtoull(charInfoList.at(8).c_str(), NULL, 0) ));
            _BuildSingleXMLTag( "race", charInfoList.at(11) );
            _BuildSingleXMLTag( "bloodLine", charInfoList.at(10) );
            _BuildSingleXMLTag( "ancestry", charInfoList.at(9) );
            _BuildSingleXMLTag( "gender", ( (atoi(charInfoList.at(14).c_str()) > 0) ? "Male" : "Female") );
            _BuildSingleXMLTag( "corporationName", charInfoList.at(13) );
            _BuildSingleXMLTag( "corporationID", charInfoList.at(2) );
            _BuildSingleXMLTag( "allianceName", "none" );
            _BuildSingleXMLTag( "allianceID", "0" );
            _BuildSingleXMLTag( "cloneName", "Clone Grade Pi" );
            _BuildSingleXMLTag( "cloneSkillPoints", "54600000" );
            _BuildSingleXMLTag( "balance", charInfoList.at(0) );

            // TODO: code these for real, as what follows are hard coded examples to fill out the whole xml document:
            // Attribute Enhancers (implants)
            _BuildXMLTag( "attributeEnhancers" );
            {
                /*
                _BuildXMLTag( "memoryBonus" );
                {
                    _BuildSingleXMLTag( "augmentatorName", "Memory Augmentation - Basic" );
                    _BuildSingleXMLTag( "augmentatorValue", "3" );
                }
                _CloseXMLTag(); // close tag "memoryBonus"
                _BuildXMLTag( "perceptionBonus" );
                {
                    _BuildSingleXMLTag( "augmentatorName", "Ocular Filter - Basic" );
                    _BuildSingleXMLTag( "augmentatorValue", "3" );
                }
                _CloseXMLTag(); // close tag "perceptionBonus"
                _BuildXMLTag( "willpowerBonus" );
                {
                    _BuildSingleXMLTag( "augmentatorName", "Neural Boost - Basic" );
                    _BuildSingleXMLTag( "augmentatorValue", "3" );
                }
                _CloseXMLTag(); // close tag "willpowerBonus"
                _BuildXMLTag( "intelligenceBonus" );
                {
                    _BuildSingleXMLTag( "augmentatorName", "Snake Delta" );
                    _BuildSingleXMLTag( "augmentatorValue", "3" );
                }
                _CloseXMLTag(); // close tag "intelligenceBonus"
                _BuildXMLTag( "charismaBonus" );
                {
                    _BuildSingleXMLTag( "augmentatorName", "Limited Social Adaptation Chip" );
                    _BuildSingleXMLTag( "augmentatorValue", "3" );
                }
                _CloseXMLTag(); // close tag "charismaBonus"
                */
            }
            _CloseXMLTag(); // close tag "attributeEnhancers"

            // TODO: code these for real, as what follows are hard coded examples to fill out the whole xml document:
            // Attributes
            _BuildXMLTag( "attributes" );
            {
                _BuildSingleXMLTag( "intelligence", charAttributes.find( std::string(itoa(AttrIntelligence)))->second );
                _BuildSingleXMLTag( "memory", charAttributes.find( std::string(itoa(AttrMemory)))->second );
                _BuildSingleXMLTag( "charisma", charAttributes.find( std::string(itoa(AttrCharisma)))->second );
                _BuildSingleXMLTag( "perception", charAttributes.find( std::string(itoa(AttrPerception)))->second );
                _BuildSingleXMLTag( "willpower", charAttributes.find( std::string(itoa(AttrWillpower)))->second );
            }
            _CloseXMLTag(); // close tag "attributes"

            // Skills
            rowset.clear();
            rowset.push_back("typeID");
            rowset.push_back("skillpoints");
            rowset.push_back("level");
            rowset.push_back("published");
            _BuildXMLRowSet( "skills", "typeID", &rowset );
            {
                for(i=0; i<skillTypeIDList.size(); i++)
                {
                    rowset.clear();
                    rowset.push_back(skillTypeIDList.at(i));
                    rowset.push_back(skillPointsList.at(i));
                    rowset.push_back(skillLevelList.at(i));
                    rowset.push_back(skillPublishedList.at(i));
                    _BuildXMLRow( &rowset );
                }
            }
            _CloseXMLRowSet();  // close rowset "skills"

            // TODO: code these for real, as what follows are hard coded examples to fill out the whole xml document:
            // Certificates:
            rowset.clear();
            rowset.push_back("certificateID");
            _BuildXMLRowSet( "certificates", "certificateID", &rowset );
            {
            //    for(i=0; i<skillTypeIDList.size(); i++)
            //    {
                    rowset.clear();
                    //rowset.push_back(certificatesList.at(i));
                    rowset.push_back("1");
                    _BuildXMLRow( &rowset );
            //    }
            }
            _CloseXMLRowSet();  // close rowset "certificates"

            // TODO: code these for real, as what follows are hard coded examples to fill out the whole xml document:
            // Corporation Roles:
            //rowset.clear();
            //rowset.push_back("");
            //_BuildXMLRowSet( "", "", &rowset );
            //{
            //}
            _CloseXMLRowSet();  // close rowset ""
        }
        _CloseXMLTag(); // close tag "result"
    }
    _CloseXMLHeader( EVEAPI::CacheStyles::Long );

    return _GetXMLDocumentString();
}

std::tr1::shared_ptr<std::string> APICharacterManager::_SkillQueue(const APICommandCall * pAPICommandCall)
{
    size_t i;

    sLog.Error( "APICharacterManager::_SkillQueue()", "TODO: Insert code to validate userID and apiKey" );

    sLog.Debug("APICharacterManager::_SkillQueue()", "EVEmu API - Character Service Manager - CALL: SkillQueue.xml.aspx");

    if( pAPICommandCall->find( "userid" ) == pAPICommandCall->end() )
    {
        sLog.Error( "APICharacterManager::_SkillQueue()", "ERROR: No 'userID' parameter found in call argument list - exiting with error and sending back NOTHING" );
        return BuildErrorXMLResponse( "106", "Must provide userID parameter for authentication." );
    }

    if( pAPICommandCall->find( "apikey" ) == pAPICommandCall->end() )
    {
        sLog.Error( "APICharacterManager::_SkillQueue()", "ERROR: No 'apiKey' parameter found in call argument list - exiting with error and sending back NOTHING" );
        return BuildErrorXMLResponse( "203", "Authentication failure." );
    }

    if( pAPICommandCall->find( "characterid" ) == pAPICommandCall->end() )
    {
        sLog.Error( "APICharacterManager::_SkillQueue()", "ERROR: No 'characterID' parameter found in call argument list - exiting with error and sending back NOTHING" );
        return BuildErrorXMLResponse( "105", "Invalid characterID." );
    }

    // Make calls to the APICharacterDB class to grab all data for this call and populate the xml structure with that data
    uint32 characterID = atoi( pAPICommandCall->find( "characterid" )->second.c_str() );

    std::map<std::string, std::string> charLearningAttributesString;
    std::map<uint32, uint32> charLearningAttributes;
    m_charDB.GetCharacterAttributes( characterID, charLearningAttributesString );
    charLearningAttributes.insert( std::pair<uint32, uint32>( AttrMemory, ((uint32)(atoi(charLearningAttributesString.find(std::string(itoa(AttrMemory)))->second.c_str()))) ));
    charLearningAttributes.insert( std::pair<uint32, uint32>( AttrIntelligence, ((uint32)(atoi(charLearningAttributesString.find(std::string(itoa(AttrIntelligence)))->second.c_str()))) ));
    charLearningAttributes.insert( std::pair<uint32, uint32>( AttrCharisma, ((uint32)(atoi(charLearningAttributesString.find(std::string(itoa(AttrCharisma)))->second.c_str()))) ));
    charLearningAttributes.insert( std::pair<uint32, uint32>( AttrWillpower, ((uint32)(atoi(charLearningAttributesString.find(std::string(itoa(AttrWillpower)))->second.c_str()))) ));
    charLearningAttributes.insert( std::pair<uint32, uint32>( AttrPerception, ((uint32)(atoi(charLearningAttributesString.find(std::string(itoa(AttrPerception)))->second.c_str()))) ));

    std::vector<std::string> queueOrderList;
    std::vector<std::string> queueSkillTypeIdList;
    std::vector<std::string> queueSkillLevelList;
    std::vector<std::string> queueSkillRankList;
    std::vector<std::string> queueSkillIdList;
    std::vector<std::string> queueSkillPrimaryAttrList;
    std::vector<std::string> queueSkillSecondaryAttrList;
    std::vector<std::string> queueSkillPointsTrainedList;

    uint32 queueSkillPrimaryAttribute;
    uint32 queueSkillSecondaryAttribute;
    std::vector<uint32> queueSkillStartSP;
    std::vector<uint32> queueSkillEndSP;
    std::vector<uint64> queueSkillStartTime;
    std::vector<uint64> queueSkillEndTime;
    EvilNumber spPerMinute(0.0);
    EvilNumber skillStartSP(0.0);
    EvilNumber skillEndSP(0.0);
    EvilNumber timeNow(0.0);
    uint64 skillStartTime;
    uint64 skillEndTime;

    bool status = m_charDB.GetCharacterSkillQueue( characterID, queueOrderList, queueSkillTypeIdList, queueSkillLevelList, queueSkillRankList,
        queueSkillIdList, queueSkillPrimaryAttrList, queueSkillSecondaryAttrList, queueSkillPointsTrainedList );

    sLog.Error( "APICharacterManager::_SkillQueue()", "INFO: Calculation of Skill End Time based on Effective SP/min does NOT include implants/boosters at this time" );

    if( status )
    {
        timeNow = EvilTimeNow();
        for( i=0; i<queueOrderList.size(); i++ )
        {
            queueSkillPrimaryAttribute = charLearningAttributes.find( atoi(queueSkillPrimaryAttrList.at(i).c_str()) )->second;
            queueSkillSecondaryAttribute = charLearningAttributes.find( atoi(queueSkillSecondaryAttrList.at(i).c_str()) )->second;
            skillStartSP = EvilNumber(atoi( queueSkillPointsTrainedList.at(i).c_str() ));
            queueSkillStartSP.push_back( static_cast<uint32>( skillStartSP.get_int() ));
            skillEndSP = SkillPointsAtLevel( atoi(queueSkillLevelList.at(i).c_str()), atoi(queueSkillRankList.at(i).c_str()) );
            queueSkillEndSP.push_back( static_cast<uint32>( skillEndSP.get_int() ) );
            spPerMinute = SkillPointsPerMinute( queueSkillPrimaryAttribute, queueSkillSecondaryAttribute );
            skillStartTime = static_cast<uint64>(SkillStartingTime( skillStartSP, skillEndSP, spPerMinute, timeNow ).get_int());
            skillEndTime = static_cast<uint64>(SkillEndingTime( skillStartSP, skillEndSP, spPerMinute, timeNow ).get_int());
            queueSkillStartTime.push_back( skillStartTime );
            queueSkillEndTime.push_back( skillEndTime );
            timeNow = skillEndTime;
        }
    }

    // EXAMPLE:
    std::vector<std::string> rowset;
    _BuildXMLHeader();
    {
        _BuildXMLTag( "result" );
        {
            // Skill Queue
            rowset.push_back("queuePosition");
            rowset.push_back("typeID");
            rowset.push_back("level");
            rowset.push_back("startSP");
            rowset.push_back("endSP");
            rowset.push_back("startTime");
            rowset.push_back("endTime");
            _BuildXMLRowSet( "skillqueue", "queuePosition", &rowset );
            {
                if( status )
                {
                    for(i=0; i<queueOrderList.size(); i++)
                    {
                        rowset.clear();
                        rowset.push_back( queueOrderList.at(i) );
                        rowset.push_back( queueSkillTypeIdList.at(i) );
                        rowset.push_back( queueSkillLevelList.at(i) );
                        rowset.push_back( std::string(itoa(queueSkillStartSP.at(i))) );
                        rowset.push_back( std::string(itoa(queueSkillEndSP.at(i))) );
                        rowset.push_back( Win32TimeToString(queueSkillStartTime.at(i)) );
                        rowset.push_back( Win32TimeToString(queueSkillEndTime.at(i)) );
                        _BuildXMLRow( &rowset );
                    }
                }
            }
            _CloseXMLRowSet();  // close rowset "skillqueue"
        }
        _CloseXMLTag(); // close tag "result"
    }
    _CloseXMLHeader( EVEAPI::CacheStyles::Modified );

    return _GetXMLDocumentString();
}

std::tr1::shared_ptr<std::string> APICharacterManager::_SkillInTraining(const APICommandCall * pAPICommandCall)
{
    sLog.Error( "APICharacterManager::_SkillInTraining()", "TODO: Insert code to validate userID and apiKey" );

    sLog.Debug("APICharacterManager::_SkillInTraining()", "EVEmu API - Character Service Manager - CALL: SkillInTraining.xml.aspx");

    if( pAPICommandCall->find( "userid" ) == pAPICommandCall->end() )
    {
        sLog.Error( "APICharacterManager::_SkillInTraining()", "ERROR: No 'userID' parameter found in call argument list - exiting with error and sending back NOTHING" );
        return BuildErrorXMLResponse( "106", "Must provide userID parameter for authentication." );
    }

    if( pAPICommandCall->find( "apikey" ) == pAPICommandCall->end() )
    {
        sLog.Error( "APICharacterManager::_SkillInTraining()", "ERROR: No 'apiKey' parameter found in call argument list - exiting with error and sending back NOTHING" );
        return BuildErrorXMLResponse( "203", "Authentication failure." );
    }

    if( pAPICommandCall->find( "characterid" ) == pAPICommandCall->end() )
    {
        sLog.Error( "APICharacterManager::_SkillInTraining()", "ERROR: No 'characterID' parameter found in call argument list - exiting with error and sending back NOTHING" );
        return BuildErrorXMLResponse( "105", "Invalid characterID." );
    }

    // Make calls to the APICharacterDB class to grab all data for this call and populate the xml structure with that data
    uint32 characterID = atoi( pAPICommandCall->find( "characterid" )->second.c_str() );

    std::map<std::string, std::string> charLearningAttributesString;
    std::map<uint32, uint32> charLearningAttributes;
    m_charDB.GetCharacterAttributes( characterID, charLearningAttributesString );
    charLearningAttributes.insert( std::pair<uint32, uint32>( AttrMemory, ((uint32)(atoi(charLearningAttributesString.find(std::string(itoa(AttrMemory)))->second.c_str()))) ));
    charLearningAttributes.insert( std::pair<uint32, uint32>( AttrIntelligence, ((uint32)(atoi(charLearningAttributesString.find(std::string(itoa(AttrIntelligence)))->second.c_str()))) ));
    charLearningAttributes.insert( std::pair<uint32, uint32>( AttrCharisma, ((uint32)(atoi(charLearningAttributesString.find(std::string(itoa(AttrCharisma)))->second.c_str()))) ));
    charLearningAttributes.insert( std::pair<uint32, uint32>( AttrWillpower, ((uint32)(atoi(charLearningAttributesString.find(std::string(itoa(AttrWillpower)))->second.c_str()))) ));
    charLearningAttributes.insert( std::pair<uint32, uint32>( AttrPerception, ((uint32)(atoi(charLearningAttributesString.find(std::string(itoa(AttrPerception)))->second.c_str()))) ));

    std::vector<std::string> queueOrderList;
    std::vector<std::string> queueSkillTypeIdList;
    std::vector<std::string> queueSkillLevelList;
    std::vector<std::string> queueSkillRankList;
    std::vector<std::string> queueSkillIdList;
    std::vector<std::string> queueSkillPrimaryAttrList;
    std::vector<std::string> queueSkillSecondaryAttrList;
    std::vector<std::string> queueSkillPointsTrainedList;

    uint32 queueSkillPrimaryAttribute;
    uint32 queueSkillSecondaryAttribute;
    std::vector<uint32> queueSkillStartSP;
    std::vector<uint32> queueSkillEndSP;
    std::vector<uint64> queueSkillStartTime;
    std::vector<uint64> queueSkillEndTime;
    EvilNumber spPerMinute(0.0);
    EvilNumber skillStartSP(0.0);
    EvilNumber skillEndSP(0.0);
    EvilNumber timeNow(0.0);
    uint64 skillStartTime;
    uint64 skillEndTime;

    bool status = m_charDB.GetCharacterSkillQueue( characterID, queueOrderList, queueSkillTypeIdList, queueSkillLevelList, queueSkillRankList,
        queueSkillIdList, queueSkillPrimaryAttrList, queueSkillSecondaryAttrList, queueSkillPointsTrainedList );

    if( status )
    {
        sLog.Error( "APICharacterManager::_SkillInTraining()", "INFO: Calculation of Skill End Time based on Effective SP/min does NOT include implants/boosters at this time" );
        timeNow = EvilTimeNow();

        queueSkillPrimaryAttribute = charLearningAttributes.find( atoi(queueSkillPrimaryAttrList.at(0).c_str()) )->second;
        queueSkillSecondaryAttribute = charLearningAttributes.find( atoi(queueSkillSecondaryAttrList.at(0).c_str()) )->second;
        skillStartSP = EvilNumber(atoi( queueSkillPointsTrainedList.at(0).c_str() ));
        queueSkillStartSP.push_back( static_cast<uint32>( skillStartSP.get_int() ));
        skillEndSP = SkillPointsAtLevel( atoi(queueSkillLevelList.at(0).c_str()), atoi(queueSkillRankList.at(0).c_str()) );
        queueSkillEndSP.push_back( static_cast<uint32>( skillEndSP.get_int() ) );
        spPerMinute = SkillPointsPerMinute( queueSkillPrimaryAttribute, queueSkillSecondaryAttribute );
        skillStartTime = static_cast<uint64>(SkillStartingTime( skillStartSP, skillEndSP, spPerMinute, timeNow ).get_int());
        skillEndTime = static_cast<uint64>(SkillEndingTime( skillStartSP, skillEndSP, spPerMinute, timeNow ).get_int());
        queueSkillStartTime.push_back( skillStartTime );
        queueSkillEndTime.push_back( skillEndTime );
    }

    // EXAMPLE:
    std::vector<std::string> rowset;
    _BuildXMLHeader();
    {
        _BuildXMLTag( "result" );
        {
            if( status )
            {
                _BuildSingleXMLTag( "currentTQTime", Win32TimeToString(static_cast<uint64>(timeNow.get_int())) );
                _BuildSingleXMLTag( "trainingEndTime", Win32TimeToString(skillEndTime) );
                _BuildSingleXMLTag( "trainingStartTime", Win32TimeToString(skillStartTime) );
                _BuildSingleXMLTag( "trainingTypeID", queueSkillTypeIdList.at(0) );
                _BuildSingleXMLTag( "trainingStartSP", std::string(itoa(skillStartSP.get_int())) );
                _BuildSingleXMLTag( "trainingDestinationSP", std::string(itoa(skillEndSP.get_int())) );
                _BuildSingleXMLTag( "trainingToLevel", queueSkillLevelList.at(0) );
                _BuildSingleXMLTag( "skillInTraining", "1" );
            }
            else
            {
                _BuildSingleXMLTag( "skillInTraining", "0" );
            }
        }
        _CloseXMLTag(); // close tag "result"
    }
    _CloseXMLHeader( EVEAPI::CacheStyles::Modified );

    return _GetXMLDocumentString();
}
