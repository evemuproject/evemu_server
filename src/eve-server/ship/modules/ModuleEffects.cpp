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
    Author:        Aknor Jaden, Luck
*/

#include "eve-server.h"

#include "ship/modules/ModuleEffects.h"

// ////////////////////// SkillBonusModifier Class ////////////////////////////
SkillBonusModifier::SkillBonusModifier(uint32 skillID)
{
	m_SkillID = skillID;
    m_numOfIDs = 0;
	m_EffectIDs = NULL;
    m_SourceAttributeIDs = NULL;
    m_TargetAttributeIDs = NULL;
    m_CalculationTypeIDs = NULL;
    m_ReverseCalculationTypeIDs = NULL;
    m_TargetChargeSizes = NULL;
	m_AppliedPerLevelList = NULL;
	m_AffectingTypes = NULL;
	m_AffectedTypes = NULL;

	m_ModifierLoaded = false;

	_Populate(skillID);
}

SkillBonusModifier::~SkillBonusModifier()
{
    if( m_numOfIDs > 0 )
	{
		delete m_SourceAttributeIDs;
		delete m_TargetAttributeIDs;
		delete m_CalculationTypeIDs;
		delete m_ReverseCalculationTypeIDs;
		delete m_TargetChargeSizes;
		delete m_AppliedPerLevelList;
		delete m_AffectingTypes;
		delete m_AffectedTypes;
	}
}

void SkillBonusModifier::_Populate(uint32 skillID)
{
    DBQueryResult *res = new DBQueryResult();
    ModuleDB::GetDgmSkillBonusModifiers(skillID, *res);

    DBResultRow row1;
	if( res->GetRowCount() == 0 )
	{
        sLog.Error("SkillBonusModifier","Could not populate skill bonus modifier information for skillID: %u from the 'dgmSkillBonusModifiers' table", skillID);
		m_ModifierLoaded = false;
	}
    else
    {
		m_EffectIDs = new uint32[res->GetRowCount()];
		m_SourceAttributeIDs = new uint32[res->GetRowCount()];
		m_TargetAttributeIDs = new uint32[res->GetRowCount()];
		m_CalculationTypeIDs = new uint32[res->GetRowCount()];
		m_ReverseCalculationTypeIDs = new uint32[res->GetRowCount()];
		m_TargetChargeSizes = new uint32[res->GetRowCount()];
		m_AppliedPerLevelList = new uint32[res->GetRowCount()];
		m_AffectingTypes = new uint32[res->GetRowCount()];
		m_AffectedTypes = new uint32[res->GetRowCount()];

		int count = 0;
		std::string targetGroupIDs;
		typeTargetGroupIDlist * TargetGroupIDs;

		while( res->GetRow(row1) )
		{
			m_EffectIDs[count] = row1.GetUInt(0);
			m_SourceAttributeIDs[count] = row1.GetUInt(1);
			m_TargetAttributeIDs[count] = row1.GetUInt(2);
			m_CalculationTypeIDs[count] = row1.GetUInt(3);
			m_Descriptions.insert(std::pair<uint32,std::string>(count,row1.GetText(4)));
			m_ReverseCalculationTypeIDs[count] = row1.GetUInt(5);
			targetGroupIDs = row1.GetText(6);
			m_TargetChargeSizes[count] = row1.GetUInt(7);
			m_AppliedPerLevelList[count] = row1.GetUInt(8);
			m_AffectingTypes[count] = row1.GetUInt(9);
			m_AffectedTypes[count] = row1.GetUInt(10);

			TargetGroupIDs = new typeTargetGroupIDlist;
			if( !(targetGroupIDs.empty()) )
			{
				// targetGroupIDs string is not empty, so extract one number at a time until it is empty
				int pos = 0;
				std::string tempString = "";

				pos = targetGroupIDs.find_first_of(';');
				if( pos < 0 )
					pos = targetGroupIDs.length()-1;	// we did not find any ';' characters, so targetGroupIDs contains only one number
				tempString = targetGroupIDs.substr(0,pos);

				while( (pos = targetGroupIDs.find_first_of(';')) > 0 )
				{
					tempString = targetGroupIDs.substr(0,pos);
					TargetGroupIDs->insert(TargetGroupIDs->begin(), (atoi(tempString.c_str())));
					targetGroupIDs = targetGroupIDs.substr(pos+1,targetGroupIDs.length()-1);
				}

				// Get final number now that there are no more separators to find:
				if( !(targetGroupIDs.empty()) )
					TargetGroupIDs->insert(TargetGroupIDs->begin(), (atoi(targetGroupIDs.c_str())));

				m_TargetGroupIDlists.insert(std::pair<uint32, typeTargetGroupIDlist *>(count, TargetGroupIDs));
			}

			count++;
		}

		if( count == 0 )
		{
			;//sLog.Error("SkillBonusModifier","Could not populate bonus modifier information for skillID: %u from the 'dgmSkillBonusModifiers' table as the SQL query returned ZERO rows", skillID);
			m_ModifierLoaded = false;
		}
		else
		{
			m_numOfIDs = count;
			m_ModifierLoaded = true;
		}
	}

    delete res;
    res = NULL;
}


// ////////////////////// ShipBonusModifier Class ////////////////////////////
ShipBonusModifier::ShipBonusModifier(uint32 shipID)
{
	m_ShipID = shipID;
    m_numOfIDs = 0;
	m_EffectIDs = NULL;
	m_AttributeSkillIDs = NULL;
    m_SourceAttributeIDs = NULL;
    m_TargetAttributeIDs = NULL;
    m_CalculationTypeIDs = NULL;
    m_ReverseCalculationTypeIDs = NULL;
	m_AppliedPerLevelList = NULL;
	m_AffectingTypes = NULL;
	m_AffectedTypes = NULL;

	m_ModifierLoaded = false;

	_Populate(shipID);
}

ShipBonusModifier::~ShipBonusModifier()
{
    if( m_numOfIDs > 0 )
	{
		delete m_AttributeSkillIDs;
		delete m_SourceAttributeIDs;
		delete m_TargetAttributeIDs;
		delete m_CalculationTypeIDs;
		delete m_ReverseCalculationTypeIDs;
		delete m_AppliedPerLevelList;
		delete m_AffectingTypes;
		delete m_AffectedTypes;
	}
}

void ShipBonusModifier::_Populate(uint32 shipID)
{
    DBQueryResult *res = new DBQueryResult();
    ModuleDB::GetDgmShipBonusModifiers(shipID, *res);

    DBResultRow row1;
	if( res->GetRowCount() == 0 )
	{
        sLog.Error("ShipBonusModifier","Could not populate ship bonus modifier information for shipID: %u from the 'dgmShipBonusModifiers' table", shipID);
		m_ModifierLoaded = false;
	}
    else
    {
		m_EffectIDs = new uint32[res->GetRowCount()];
		m_AttributeSkillIDs = new uint32[res->GetRowCount()];
		m_SourceAttributeIDs = new uint32[res->GetRowCount()];
		m_TargetAttributeIDs = new uint32[res->GetRowCount()];
		m_CalculationTypeIDs = new uint32[res->GetRowCount()];
		m_ReverseCalculationTypeIDs = new uint32[res->GetRowCount()];
		m_AppliedPerLevelList = new uint32[res->GetRowCount()];
		m_AffectingTypes = new uint32[res->GetRowCount()];
		m_AffectedTypes = new uint32[res->GetRowCount()];

		int count = 0;
		std::string targetGroupIDs;
		typeTargetGroupIDlist * TargetGroupIDs;

		while( res->GetRow(row1) )
		{
			m_EffectIDs[count] = row1.GetUInt(0);
			m_AttributeSkillIDs[count] = row1.GetUInt(1);
			m_SourceAttributeIDs[count] = row1.GetUInt(2);
			m_TargetAttributeIDs[count] = row1.GetUInt(3);
			m_CalculationTypeIDs[count] = row1.GetUInt(4);
			m_Descriptions.insert(std::pair<uint32,std::string>(count,row1.GetText(5)));
			m_ReverseCalculationTypeIDs[count] = row1.GetUInt(6);
			targetGroupIDs = row1.GetText(7);
			m_AppliedPerLevelList[count] = row1.GetUInt(8);
			m_AffectingTypes[count] = row1.GetUInt(9);
			m_AffectedTypes[count] = row1.GetUInt(10);

			TargetGroupIDs = new typeTargetGroupIDlist;
			if( !(targetGroupIDs.empty()) )
			{
				// targetGroupIDs string is not empty, so extract one number at a time until it is empty
				int pos = 0;
				std::string tempString = "";

				pos = targetGroupIDs.find_first_of(';');
				if( pos < 0 )
					pos = targetGroupIDs.length()-1;	// we did not find any ';' characters, so targetGroupIDs contains only one number
				tempString = targetGroupIDs.substr(0,pos);

				while( (pos = targetGroupIDs.find_first_of(';')) > 0 )
				{
					tempString = targetGroupIDs.substr(0,pos);
					TargetGroupIDs->insert(TargetGroupIDs->begin(), (atoi(tempString.c_str())));
					targetGroupIDs = targetGroupIDs.substr(pos+1,targetGroupIDs.length()-1);
				}

				// Get final number now that there are no more separators to find:
				if( !(targetGroupIDs.empty()) )
					TargetGroupIDs->insert(TargetGroupIDs->begin(), (atoi(targetGroupIDs.c_str())));

				m_TargetGroupIDlists.insert(std::pair<uint32, typeTargetGroupIDlist *>(count, TargetGroupIDs));
			}

			count++;
		}

		if( count == 0 )
		{
			;//sLog.Error("ShipBonusModifier","Could not populate bonus modifier information for shipID: %u from the 'dgmShipBonusModifiers' table as the SQL query returned ZERO rows", shipID);
			m_ModifierLoaded = false;
		}
		else
		{
			m_numOfIDs = count;
			m_ModifierLoaded = true;
		}
	}

    delete res;
    res = NULL;
}


// ////////////////////// DGM_Skill_Bonus_Modifiers_Table Class ////////////////////////////
DGM_Skill_Bonus_Modifiers_Table::DGM_Skill_Bonus_Modifiers_Table()
{
}

DGM_Skill_Bonus_Modifiers_Table::~DGM_Skill_Bonus_Modifiers_Table()
{
    // TODO: loop through entire std::map<> and delete ALL entries, calling ~SkillBonusModifiers() on each
}

int DGM_Skill_Bonus_Modifiers_Table::Initialize()
{
    _Populate();

    return 1;
}

void DGM_Skill_Bonus_Modifiers_Table::_Populate()
{
    //first get list of all effects from dgmSkillBonusModifiers table
    DBQueryResult *res = new DBQueryResult();
    ModuleDB::GetAllDgmSkillBonusModifiers(*res);

    //counter
    SkillBonusModifier * mSkillBonusModifierPtr;
    mSkillBonusModifierPtr = NULL;
    uint32 skillID;

	uint32 total_modifier_count = 0;
	uint32 error_count = 0;

	//go through and populate each skill bonus modifier
    DBResultRow row;
    while( res->GetRow(row) )
    {
        skillID = row.GetInt(0);
        mSkillBonusModifierPtr = new SkillBonusModifier(skillID);
		if( mSkillBonusModifierPtr->IsModifierLoaded() )
			m_SkillBonusModifiersMap.insert(std::pair<uint32, SkillBonusModifier *>(skillID,mSkillBonusModifierPtr));
		else
			error_count++;

		total_modifier_count++;
    }

	if( error_count > 0 )
		sLog.Error("DGM_Skill_Bonus_Modifiers_Table::_Populate()","ERROR Populating the DGM_Skill_Bonus_Modifiers_Table memory object: %u of %u skill bonus modifiers failed to load!", error_count, total_modifier_count);

	sLog.Log("DGM_Skill_Bonus_Modifiers_Table", "..........%u total modifier objects loaded", total_modifier_count);

    //cleanup
    delete res;
    res = NULL;
}

SkillBonusModifier * DGM_Skill_Bonus_Modifiers_Table::GetSkillModifier(uint32 skillID)
{
    // return SkillBonusModifier * corresponding to skillID from m_SkillBonusModifiersMap
    SkillBonusModifier * mSkillBonusModifierPtr = NULL;
    std::map<uint32, SkillBonusModifier *>::iterator skillBonusModifierMapIterator;

    if( (skillBonusModifierMapIterator = m_SkillBonusModifiersMap.find(skillID)) == m_SkillBonusModifiersMap.end() )
        return NULL;
    else
    {
        mSkillBonusModifierPtr = skillBonusModifierMapIterator->second;
        return mSkillBonusModifierPtr;
    }
}


// ////////////////////// DGM_Skill_Bonus_Modifiers_Table Class ////////////////////////////
DGM_Ship_Bonus_Modifiers_Table::DGM_Ship_Bonus_Modifiers_Table()
{
}

DGM_Ship_Bonus_Modifiers_Table::~DGM_Ship_Bonus_Modifiers_Table()
{
    // TODO: loop through entire std::map<> and delete ALL entries, calling ~ShipBonusModifiers() on each
}

int DGM_Ship_Bonus_Modifiers_Table::Initialize()
{
    _Populate();

    return 1;
}

void DGM_Ship_Bonus_Modifiers_Table::_Populate()
{
    //first get list of all effects from dgmShipBonusModifiers table
    DBQueryResult *res = new DBQueryResult();
    ModuleDB::GetAllDgmSkillBonusModifiers(*res);

    //counter
    ShipBonusModifier * mShipBonusModifierPtr;
    mShipBonusModifierPtr = NULL;
    uint32 shipID;

	uint32 total_modifier_count = 0;
	uint32 error_count = 0;

	//go through and populate each ship bonus modifier
    DBResultRow row;
    while( res->GetRow(row) )
    {
        shipID = row.GetInt(0);
        mShipBonusModifierPtr = new ShipBonusModifier(shipID);
		if( mShipBonusModifierPtr->IsModifierLoaded() )
			m_ShipBonusModifiersMap.insert(std::pair<uint32, ShipBonusModifier *>(shipID,mShipBonusModifierPtr));
		else
			error_count++;

		total_modifier_count++;
    }

	if( error_count > 0 )
		sLog.Error("DGM_Ship_Bonus_Modifiers_Table::_Populate()","ERROR Populating the DGM_Ship_Bonus_Modifiers_Table memory object: %u of %u ship bonus modifiers failed to load!", error_count, total_modifier_count);

	sLog.Log("DGM_Ship_Bonus_Modifiers_Table", "..........%u total modifier objects loaded", total_modifier_count);

    //cleanup
    delete res;
    res = NULL;
}

ShipBonusModifier * DGM_Ship_Bonus_Modifiers_Table::GetShipModifier(uint32 shipID)
{
    // return ShipBonusModifier * corresponding to shipID from m_ShipBonusModifiersMap
    ShipBonusModifier * mShipBonusModifierPtr = NULL;
    std::map<uint32, ShipBonusModifier *>::iterator shipBonusModifierMapIterator;

    if( (shipBonusModifierMapIterator = m_ShipBonusModifiersMap.find(shipID)) == m_ShipBonusModifiersMap.end() )
        return NULL;
    else
    {
        mShipBonusModifierPtr = shipBonusModifierMapIterator->second;
        return mShipBonusModifierPtr;
    }
}
