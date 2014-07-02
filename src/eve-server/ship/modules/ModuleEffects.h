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

#ifndef MODULE_EFFECTS_H
#define MODULE_EFFECTS_H

#include "inventory/TypeEffect.h"
#include "utils/Singleton.h"

// ///////////////////// Skill Modifiers Class ///////////////////////////
class SkillBonusModifier
{
public:
    SkillBonusModifier(uint32 skillID);
    ~SkillBonusModifier();

    //accessors for the data loaded, if any, from the dgmSkillBonusModifiers table:
    uint32 GetSkillID()                                          { return m_SkillID; }
    uint32 GetSizeOfModifierList()                                { return ((m_SkillID == 0) || (!m_ModifierLoaded)) ? 0 : m_numOfIDs; }
    uint32 GetEffectID(uint32 index)                              { return ((m_SkillID == 0) || (!m_ModifierLoaded)) ? 0 : m_EffectIDs[index]; }
    uint32 GetSourceAttributeID(uint32 index)                    { return ((m_SkillID == 0) || (!m_ModifierLoaded)) ? 0 : m_SourceAttributeIDs[index]; }
    uint32 GetTargetAttributeID(uint32 index)                    { return ((m_SkillID == 0) || (!m_ModifierLoaded)) ? 0 : m_TargetAttributeIDs[index]; }
    EVECalculationType GetCalculationType(uint32 index)            { return ((m_SkillID == 0) || (!m_ModifierLoaded)) ? (EVECalculationType)0 : (EVECalculationType)m_CalculationTypeIDs[index];}
	EVECalculationType GetReverseCalculationType(uint32 index)    { return ((m_SkillID == 0) || (!m_ModifierLoaded)) ? (EVECalculationType)0 : (EVECalculationType)m_ReverseCalculationTypeIDs[index];}
    typeTargetGroupIDlist * GetTargetGroupIDlist(uint32 index)    { return ((m_SkillID == 0) || (!m_ModifierLoaded)) ? 0 : m_TargetGroupIDlists.find(index)->second; }
    uint32 GetTargetChargeSize(uint32 index)					{ return ((m_SkillID == 0) || (!m_ModifierLoaded)) ? 0 : m_TargetChargeSizes[index]; }
    uint32 GetAppliedPerLevel(uint32 index)                    { return ((m_SkillID == 0) || (!m_ModifierLoaded)) ? 0 : m_AppliedPerLevelList[index]; }
	uint32 GetTargetTypeToWhichEffectApplied(uint32 index)        { return ((m_SkillID == 0) || (!m_ModifierLoaded)) ? 0 : m_AffectedTypes[index]; }
    uint32 GetEffectApplicationType(uint32 index)               { return ((m_SkillID == 0) || (!m_ModifierLoaded)) ? 0 : m_AffectingTypes[index]; }

	bool IsModifierLoaded() { return m_ModifierLoaded; }

private:
    void _Populate(uint32 skillID);

	uint32 m_SkillID;
    uint32 m_numOfIDs;
	uint32 * m_EffectIDs;
    uint32 * m_SourceAttributeIDs;
    uint32 * m_TargetAttributeIDs;
    uint32 * m_CalculationTypeIDs;
	std::map<uint32, std::string> m_Descriptions;
    uint32 * m_ReverseCalculationTypeIDs;
    std::map<uint32, typeTargetGroupIDlist *> m_TargetGroupIDlists;
    uint32 * m_TargetChargeSizes;
	uint32 * m_AppliedPerLevelList;
	uint32 * m_AffectingTypes;
	uint32 * m_AffectedTypes;

	bool m_ModifierLoaded;
};
//////////////////////////////////////////////////////////////////////////


// ///////////////////// Ship Modifiers Class ///////////////////////////
class ShipBonusModifier
{
public:
    ShipBonusModifier(uint32 shipID);
    ~ShipBonusModifier();

    //accessors for the data loaded, if any, from the dgmSkillBonusModifiers table:
    uint32 GetShipID()                                          { return m_ShipID; }
    uint32 GetSizeOfModifierList()                                { return ((m_ShipID == 0) || (!m_ModifierLoaded)) ? 0 : m_numOfIDs; }
    uint32 GetEffectID(uint32 index)                              { return ((m_ShipID == 0) || (!m_ModifierLoaded)) ? 0 : m_EffectIDs[index]; }
    uint32 GetAttributeSkillID(uint32 index)                    { return ((m_ShipID == 0) || (!m_ModifierLoaded)) ? 0 : m_AttributeSkillIDs[index]; }
    uint32 GetSourceAttributeID(uint32 index)                    { return ((m_ShipID == 0) || (!m_ModifierLoaded)) ? 0 : m_SourceAttributeIDs[index]; }
    uint32 GetTargetAttributeID(uint32 index)                    { return ((m_ShipID == 0) || (!m_ModifierLoaded)) ? 0 : m_TargetAttributeIDs[index]; }
    EVECalculationType GetCalculationType(uint32 index)            { return ((m_ShipID == 0) || (!m_ModifierLoaded)) ? (EVECalculationType)0 : (EVECalculationType)m_CalculationTypeIDs[index];}
	EVECalculationType GetReverseCalculationType(uint32 index)    { return ((m_ShipID == 0) || (!m_ModifierLoaded)) ? (EVECalculationType)0 : (EVECalculationType)m_ReverseCalculationTypeIDs[index];}
    typeTargetGroupIDlist * GetTargetGroupIDlist(uint32 index)    { return ((m_ShipID == 0) || (!m_ModifierLoaded)) ? 0 : m_TargetGroupIDlists.find(index)->second; }
    uint32 GetAppliedPerLevel(uint32 index)                    { return ((m_ShipID == 0) || (!m_ModifierLoaded)) ? 0 : m_AppliedPerLevelList[index]; }
	uint32 GetTargetTypeToWhichEffectApplied(uint32 index)        { return ((m_ShipID == 0) || (!m_ModifierLoaded)) ? 0 : m_AffectedTypes[index]; }
    uint32 GetEffectApplicationType(uint32 index)               { return ((m_ShipID == 0) || (!m_ModifierLoaded)) ? 0 : m_AffectingTypes[index]; }

	bool IsModifierLoaded() { return m_ModifierLoaded; }

private:
    void _Populate(uint32 shipID);

	uint32 m_ShipID;
    uint32 m_numOfIDs;
	uint32 * m_EffectIDs;
    uint32 * m_AttributeSkillIDs;
    uint32 * m_SourceAttributeIDs;
    uint32 * m_TargetAttributeIDs;
    uint32 * m_CalculationTypeIDs;
	std::map<uint32, std::string> m_Descriptions;
    uint32 * m_ReverseCalculationTypeIDs;
    std::map<uint32, typeTargetGroupIDlist *> m_TargetGroupIDlists;
	uint32 * m_AppliedPerLevelList;
	uint32 * m_AffectingTypes;
	uint32 * m_AffectedTypes;

	bool m_ModifierLoaded;
};
//////////////////////////////////////////////////////////////////////////


// //////////////// Permanent Memory Object Classes //////////////////////
// -----------------------------------------------------------------------


// This class is a singleton object, containing all Skill Bonus Modifiers loaded from dgmSkillBonusModifiers table as memory objects of type SkillBonusModifier:
class DGM_Skill_Bonus_Modifiers_Table
: public Singleton< DGM_Skill_Bonus_Modifiers_Table >
{
public:
    DGM_Skill_Bonus_Modifiers_Table();
    ~DGM_Skill_Bonus_Modifiers_Table();

    // Initializes the Table:
    int Initialize();

    // Returns pointer to SkillBonusModifier object corresponding to the skillID supplied:
    SkillBonusModifier * GetSkillModifier(uint32 skillID);

protected:
    void _Populate();

    std::map<uint32, SkillBonusModifier *> m_SkillBonusModifiersMap;
};

#define sDGM_Skill_Bonus_Modifiers_Table \
    ( DGM_Skill_Bonus_Modifiers_Table::get() )
// -----------------------------------------------------------------------


// This class is a singleton object, containing all Effects loaded from dgmShipBonusModifiers table as memory objects of type EVEEffect:
class DGM_Ship_Bonus_Modifiers_Table
: public Singleton< DGM_Ship_Bonus_Modifiers_Table >
{
public:
    DGM_Ship_Bonus_Modifiers_Table();
    ~DGM_Ship_Bonus_Modifiers_Table();

    // Initializes the Table:
    int Initialize();

    // Returns pointer to ShipBonusModifier object corresponding to the shipID supplied:
    ShipBonusModifier * GetShipModifier(uint32 shipID);

protected:
    void _Populate();

    std::map<uint32, ShipBonusModifier *> m_ShipBonusModifiersMap;
};

#define sDGM_Ship_Bonus_Modifiers_Table \
    ( DGM_Ship_Bonus_Modifiers_Table::get() )
// -----------------------------------------------------------------------



#endif /* MODULE_EFFECTS_H */
//////////////////////////////////////////////////////////////////////////
