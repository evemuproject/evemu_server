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
    Author:        eve-moo
*/

#ifndef ATTRIBUTEMODIFIER_H
#define	ATTRIBUTEMODIFIER_H

#include "ship/modules/ModuleEffects.h"
#include "ship/modules/ModuleDefs.h"
#include "inventory/ItemRef.h"
#include <vector>
#include <map>

/**
 * A class that holds the modifier information for a specific attribute.
 */
class AttributeModifier
: public RefObject
{
public:
    /**
     * Create a new attribute modifier.
     * @param item The source item
     * @param effect The effect for this modifier.
     * @param active Is the modifier active?
     */
    AttributeModifier(InventoryItemRef item, std::shared_ptr<MEffect> effect, int effect_index, bool active);
    ~AttributeModifier() { m_item = InventoryItemRef(); };

    /**
     * Checks to see if the modifier modifies the specified attribute.
     * @param attribute The attribute to check.
     * @return true if the modifier affects the attribute.
     */
    bool modifies(uint32 attribute) { return attribute == getTargetAttribute(); };
    /**
     * Checks for stacking penalty.
     * @return true if there is a stacking penalty.
     */
    bool stackPenalty() { return m_effect.get() == NULL ? false : m_effect->GetStackingPenaltyApplied(m_effectIndex) != 0; };
    /**
     * Get whether the modifier is active;
     * @return Ture if the modifier should be applied.
     */
    bool isActive() { return m_active; };
    /**
     * Get the attribute modified by this modifier.
     * @return The modified attribute.
     */
    uint32 getTargetAttribute() { return m_effect.get() == NULL ? 0 : m_effect->GetTargetAttributeID(m_effectIndex); };
    /**
     * Sets the modifiers active state.
     * @param state The new modifier state.
     */
    void setActive(bool state);
    /**
     * Gets the amount the attribute is modified by.
     * @return The fixed amount to modify the attribute by.
     */
    double getAmount();
    /**
     * Gets the modification factor.
     * @return The factor to modify the attribute by.
     */
    double getFactor();

private:
    /**
     * The item creating the modifier.
     */
    InventoryItemRef m_item;
    /**
     * The Effect to use.
     */
    std::shared_ptr<MEffect> m_effect;
    /**
     * The index of the effect info.
     */
    int m_effectIndex;
    /**
     * Indicate if the effect is currently active.
     */
    bool m_active;
};

/**
 * A class to define the source of attributes.
 */
class AttributeModifierSource
: public RefObject
{
public:
    AttributeModifierSource(InventoryItemRef sourceItem);
    ~AttributeModifierSource();

    typedef std::vector<double> FactorList;

    void addModifier(AttributeModifierRef modifier);
    void removeModifier(AttributeModifierRef modifier);
    void getModification(uint32 attrib, double &amount, FactorList &nonStackingFactors, FactorList &stackingFactors);
    static double finalizeModification(double value, double amount, FactorList &nonStackingFactors, FactorList &stackingFactors);
    /**
     * Sets the modifier source active state.
     * @param state The new source state.
     */
    void setActive(bool state);
    void updateModifiers(InventoryItem *item, bool notify);

private:
    InventoryItemRef m_source;
    std::vector<AttributeModifierRef> m_modifiers;
    /**
     * Indicate if the source is currently active.
     */
    bool m_active;

};

#endif	/* ATTRIBUTEMODIFIER_H */

