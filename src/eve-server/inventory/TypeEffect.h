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

#ifndef TYPEEFFECT_H
#define	TYPEEFFECT_H

#include "inventory/ItemRef.h"
#include "ship/modules/ModuleDB.h"
#include "ship/modules/ModuleDefs.h"

// ////////////////////// Effects Class ////////////////////////////
typedef std::vector<uint32> typeTargetGroupIDlist;

class EVEEffect
: public RefObject
{
public:
    EVEEffect(uint32 effectID);
    ~EVEEffect();

    //accessors for selected effect
    uint32 GetEffectID()                                        { return (m_EffectID == 0) ? 0 : m_EffectID; }
    std::string GetEffectName()                                    { return (m_EffectID == 0) ? std::string("") : m_EffectName; }
    uint32 GetEffectCategory()                                    { return (m_EffectID == 0) ? 0 : m_EffectCategory; }
    uint32 GetPreExpression()                                    { return (m_EffectID == 0) ? 0 : m_PreExpression; }
    uint32 GetPostExpression()                                    { return (m_EffectID == 0) ? 0 : m_PostExpression; }
    std::string GetDescription()                                { return (m_EffectID == 0) ? std::string("") : m_Description; }
    std::string GetGuid()                                        { return (m_EffectID == 0) ? std::string("") : m_Guid; }
    uint32 GetIconID()                                            { return (m_EffectID == 0) ? 0 : m_IconID; }
    bool GetIsOffensive()                                        { return (m_EffectID == 0) ? false : m_IsOffensive == 1; }
    bool GetIsAssistance()                                        { return (m_EffectID == 0) ? false : m_IsAssistance == 1; }
    uint32 GetDurationAttributeID()                                { return (m_EffectID == 0) ? 0 : m_DurationAttributeID; }
    uint32 GetTrackingSpeedAttributeID()                        { return (m_EffectID == 0) ? 0 : m_TrackingSpeedAttributeID; }
    uint32 GetDischargeAttributeID()                            { return (m_EffectID == 0) ? 0 : m_DischargeAttributeID; }
    uint32 GetRangeAttributeID()                                { return (m_EffectID == 0) ? 0 : m_RangeAttributeID; }
    uint32 GetFalloffAttributeID()                                { return (m_EffectID == 0) ? 0 : m_FalloffAttributeID; }
    bool GetDisallowAutoRepeat()                                { return (m_EffectID == 0) ? false : m_DisallowAutoRepeat == 1; }
    bool GetIsPublished()                                        { return (m_EffectID == 0) ? false : m_Published == 1; }
    std::string GetDisplayName()                                { return (m_EffectID == 0) ? std::string("") : m_DisplayName; }
    bool GetIsWarpSafe()                                        { return (m_EffectID == 0) ? false : m_IsWarpSafe == 1; }
    bool GetRangeChance()                                        { return (m_EffectID == 0) ? false : m_RangeChance == 1; }
    bool GetPropulsionChance()                                    { return (m_EffectID == 0) ? false : m_PropulsionChance == 1; }
    bool GetElectronicChance()                                    { return (m_EffectID == 0) ? false : m_ElectronicChance == 1; }
    uint32 GetDistribution()                                    { return (m_EffectID == 0) ? 0 : m_Distribution; }
    std::string GetSfxName()                                    { return (m_EffectID == 0) ? std::string("") : m_DisplayName; }
    uint32 GetNpcUsageChanceAttributeID()                        { return (m_EffectID == 0) ? 0 : m_NpcUsageChanceAttributeID; }
    uint32 GetNpcActivationChanceAttributeID()                    { return (m_EffectID == 0) ? 0 : m_NpcActivationChanceAttributeID; }
    uint32 GetFittingUsageChanceAttributeID()                    { return (m_EffectID == 0) ? 0 : m_FittingUsageChanceAttributeID; }

    //accessors for the data loaded, if any, from the dgmEffectsInfo table:
    uint32 GetSizeOfAttributeList()                                { return ((m_EffectID == 0) || (!m_EffectsInfoLoaded)) ? 0 : m_numOfIDs; }
    uint32 GetSourceAttributeID(uint32 index)                    { return ((m_EffectID == 0) || (!m_EffectsInfoLoaded)) ? 0 : m_SourceAttributeIDs[index]; }
    uint32 GetTargetAttributeID(uint32 index)                    { return ((m_EffectID == 0) || (!m_EffectsInfoLoaded)) ? 0 : m_TargetAttributeIDs[index]; }
    EVECalculationType GetCalculationType(uint32 index)            { return ((m_EffectID == 0) || (!m_EffectsInfoLoaded)) ? (EVECalculationType)0 : (EVECalculationType)m_CalculationTypeIDs[index];}
	EVECalculationType GetReverseCalculationType(uint32 index)    { return ((m_EffectID == 0) || (!m_EffectsInfoLoaded)) ? (EVECalculationType)0 : (EVECalculationType)m_ReverseCalculationTypeIDs[index];}
    typeTargetGroupIDlist * GetTargetGroupIDlist(uint32 index)    { return ((m_EffectID == 0) || (!m_EffectsInfoLoaded)) ? 0 : m_TargetGroupIDlists.find(index)->second; }
    uint32 GetStackingPenaltyApplied(uint32 index)              { return ((m_EffectID == 0) || (!m_EffectsInfoLoaded)) ? 0 : m_StackingPenaltyAppliedIDs[index]; }
    uint32 GetModuleStateWhenEffectApplied(uint32 index)                    { return ((m_EffectID == 0) || (!m_EffectsInfoLoaded)) ? 0 : m_EffectAppliedInStateIDs[index]; }
    uint32 GetAffectingID(uint32 index)										{ return ((m_EffectID == 0) || (!m_EffectsInfoLoaded)) ? 0 : m_AffectingIDs[index]; }
	uint32 GetTargetTypeToWhichEffectApplied(uint32 index)        { return ((m_EffectID == 0) || (!m_EffectsInfoLoaded)) ? 0 : m_AffectedTypes[index]; }
    uint32 GetEffectApplicationType(uint32 index)               { return ((m_EffectID == 0) || (!m_EffectsInfoLoaded)) ? 0 : m_AffectingTypes[index]; }

	bool IsEffectLoaded() { return m_EffectLoaded; }
	bool IsEffectsInfoLoaded() { return m_EffectsInfoLoaded; }

private:
    void _Populate(uint32 effectID);

    uint32 m_EffectID;
    std::string m_EffectName;
    uint32 m_EffectCategory;
    uint32 m_PreExpression;
    uint32 m_PostExpression;
    std::string m_Description;
    std::string m_Guid;
    uint32 m_IconID;
    uint32 m_IsOffensive;
    uint32 m_IsAssistance;
    uint32 m_DurationAttributeID;
    uint32 m_TrackingSpeedAttributeID;
    uint32 m_DischargeAttributeID;
    uint32 m_RangeAttributeID;
    uint32 m_FalloffAttributeID;
    uint32 m_DisallowAutoRepeat;
    uint32 m_Published;
    std::string m_DisplayName;
    uint32 m_IsWarpSafe;
    uint32 m_RangeChance;
    uint32 m_ElectronicChance;
    uint32 m_PropulsionChance;
    uint32 m_Distribution;
    std::string m_SfxName;
    uint32 m_NpcUsageChanceAttributeID;
    uint32 m_NpcActivationChanceAttributeID;
    uint32 m_FittingUsageChanceAttributeID;

    uint32 m_numOfIDs;
    uint32 * m_SourceAttributeIDs;
    uint32 * m_TargetAttributeIDs;
    uint32 * m_CalculationTypeIDs;
	std::map<uint32, std::string> m_Descriptions;
    uint32 * m_ReverseCalculationTypeIDs;
    std::map<uint32, typeTargetGroupIDlist *> m_TargetGroupIDlists;
    uint32 * m_StackingPenaltyAppliedIDs;
	uint32 * m_EffectAppliedInStateIDs;
	uint32 * m_AffectingIDs;
	uint32 * m_AffectingTypes;
	uint32 * m_AffectedTypes;

	bool m_EffectLoaded;
	bool m_EffectsInfoLoaded;
};
//////////////////////////////////////////////////////////////////////////


// ////////////////////// TypeEffects Class ////////////////////////////

//class contained by all modules that is populated on construction of the module
//this will contain all information about the effects of the module
class TypeEffects
: public RefObject
{
public:
    TypeEffects(uint32 typeID);
    ~TypeEffects() {};

    //this will need to be reworked to implement a singleton architecture...i'll do it later -luck

    //useful accessors - probably a better way to do this, but at least it's fast
    bool isHighSlot() const { return m_HighPower; }
    bool isMediumSlot()const { return m_MediumPower; }
    bool isLowSlot() const { return m_LowPower; }
    bool HasEffect(uint32 effectID) const;
    bool HasDefaultEffect() const { return ( (m_defaultEffect.get() != NULL) ? true : false ); }
    EVEEffectRef GetDefaultEffect() const { return m_defaultEffect; }
    EVEEffectRef GetEffect(uint32 effectID) const;

    typedef std::map<uint32, EVEEffectRef> EffectMap;
    const EffectMap& GetEffects() const { return m_Effects; }

private:

    void _populate(uint32 typeID);

    //data members
    EffectMap m_Effects;
    EVEEffectRef m_defaultEffect;

    //cached stuff
    bool m_HighPower, m_MediumPower, m_LowPower;

};


// This class is a singleton object, containing all Effects loaded from dgmEffects table as memory objects of type EVEEffect:
class DGM_Effects_Table
: public Singleton< DGM_Effects_Table >
{
public:
    DGM_Effects_Table();
    ~DGM_Effects_Table();

    // Initializes the Table:
    int Initialize();

    // Returns pointer to EVEEffect object corresponding to the effectID supplied:
    EVEEffectRef GetEffect(uint32 effectID);

protected:
    void _Populate();

    std::map<uint32, EVEEffectRef> m_EffectsMap;
};

#define sDGM_Effects_Table \
    ( DGM_Effects_Table::get() )

#endif	/* EVEEffect_H */
