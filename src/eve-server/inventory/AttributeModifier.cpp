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
    Author:     eve-moo
 */

#include "eve-server.h"

#include "inventory/InventoryItem.h"
#include "inventory/AttributeModifier.h"

AttributeModifier::AttributeModifier(InventoryItemRef item, std::shared_ptr<MEffect> effect, int effect_index, bool active)
: RefObject( 0 ),
  m_effect(effect)
{
    m_item = item;
    m_effectIndex = effect_index;
    m_active = active;
}

void AttributeModifier::setActive(bool state)
{
    if (state != m_active)
    {
        m_active = state;
    }
}

double AttributeModifier::getAmount()
{
    if (m_effect.get() == NULL)
    {
        return 0;
    }
    EVECalculationType m_Type = m_effect->GetCalculationType(m_effectIndex);
    if (m_Type == CALC_ADDITION)
    {
        return m_item->getAttribute(m_effect->GetSourceAttributeID(m_effectIndex)).get_float();
    }
    if (m_Type == CALC_SUBTRACTION)
    {
        return -(m_item->getAttribute(m_effect->GetSourceAttributeID(m_effectIndex)).get_float());
    }
    return 0;
}

double AttributeModifier::getFactor()
{
    if (m_effect.get() == NULL)
    {
        return 0;
    }
    double source = m_item->getAttribute(m_effect->GetSourceAttributeID(m_effectIndex)).get_float();
    EVECalculationType m_Type = m_effect->GetCalculationType(m_effectIndex);
    if(m_Type == CALC_PERCENTAGE)
    {
// possible problem with effectInfo 657 in groupID 78 with calc_percentage.
// some modules have value 1 that should be 1% not 0% change
        if (source < 2 && source > 0 && m_effect->GetEffectID() != 657)
        {
            return (1.0 - source) * 100;
        }
        else
        {
            return (100.0 - source);
        }
    }
    if(m_Type == CALC_DIFFERENCE)
    {
        if (source > 0)
        {
            return -(1.0 - source) * 100;
        }
        else
        {
            return source;
        }
    }
    if(m_Type == CALC_MULTIPLIER)
    {
        return source * 100;
    }
    return 0;
}

AttributeModifierSource::AttributeModifierSource(InventoryItemRef sourceItem)
: RefObject( 0 )
{
    m_source = sourceItem;
    m_active = true;
}

AttributeModifierSource::~AttributeModifierSource()
{
    m_modifiers.clear();
    m_source = InventoryItemRef();
}

void AttributeModifierSource::addModifier(AttributeModifierRef modifier)
{
    std::vector<AttributeModifierRef>::iterator itr = std::find(m_modifiers.begin(), m_modifiers.end(), modifier);
    if (itr == m_modifiers.end())
    {
        m_modifiers.push_back(modifier);
    }
}

void AttributeModifierSource::removeModifier(AttributeModifierRef modifier)
{
    std::vector<AttributeModifierRef>::iterator itr = std::find(m_modifiers.begin(), m_modifiers.end(), modifier);
    if (itr != m_modifiers.end())
    {
        m_modifiers.erase(itr);
    }
}

void AttributeModifierSource::getModification(uint32 attrib, double &amount, FactorList &nonStackingFactors, FactorList &stackingFactors)
{
    if (m_active == false)
    {
        return;
    }
    for (AttributeModifierRef modifier : m_modifiers)
    {
        if (modifier->modifies(attrib) && modifier->isActive() == true)
        {
            // add fixed change amount.
            amount += modifier->getAmount();
            // check for change factor.
            if (modifier->getFactor() == 0)
            {
                continue;
            }
            if (modifier->stackPenalty())
            {
                // yes this has a stacking penalty.
                stackingFactors.push_back(modifier->getFactor());
            }
            else
            {
                // no stack penalty.
                nonStackingFactors.push_back(modifier->getFactor());
            }
        }
    }
}

double AttributeModifierSource::finalizeModification(double value, double amount, FactorList &nonStackingFactors, FactorList &stackingFactors)
{
    // Add the fixed adjustment amount.
    value += amount;
    // Sort the modification factors so the highest is least penalized.
    // Sort by absolute value as some modifiers are negatives!
    std::sort(stackingFactors.begin(), stackingFactors.end(), [](double x, double y) { return abs(x) > abs(y); } );
    // Loop through the stack penalized factors.
    double N = 0; // Number of modules found.
    // Loop through the list and calculate the penalized factors.
    for (auto stack : stackingFactors)
    {
        // Increment the module count.
        N++;
        // Calculate stack penalty.
        double penalty = exp(-pow(N - 1, 2) / 7.1289);
        // Calculate the adjusted factor.
        double factor = (stack) * penalty;
        // Push the factor on the non-stacking list for proper sorting.
        nonStackingFactors.push_back(factor);
    }
    // Sort the factors.
    // Sort by absolute value as some modifiers are negatives!
    std::sort(nonStackingFactors.begin(), nonStackingFactors.end(), [](double x, double y) { return abs(x) > abs(y); } );
    // Loop through the factors.
    for (auto noStack : nonStackingFactors)
    {
        // Apply the factor.
        value += value * ((noStack) / 100.0);
    }
    // Return the result.
    return value;
}

void AttributeModifierSource::setActive(bool state)
{
    if (state != m_active)
    {
        m_active = state;
    }
}

void AttributeModifierSource::updateModifiers(InventoryItem *item, bool notify)
{
    if (item == NULL)
    {
        return;
    }
    for (AttributeModifierRef modifier : m_modifiers)
    {
        item->ResetAttribute(modifier->getTargetAttribute(), notify);
    }
}
