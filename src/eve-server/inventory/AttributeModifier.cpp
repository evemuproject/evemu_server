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
    Author:     avianrr
 */

#include "eve-server.h"

#include "inventory/InventoryItem.h"
#include "inventory/AttributeModifier.h"

AttributeModifier::AttributeModifier(InventoryItemRef item, EVEEffectRef effect, int effect_index, bool active)
: RefObject( 0 ),
  m_Effect(effect)
{
    m_Item = item;
    m_EffectIndex = effect_index;
    m_Active = active;
}

void AttributeModifier::SetActive(bool state)
{
    if (state != m_Active)
    {
        m_Active = state;
    }
}

double AttributeModifier::GetAmount()
{
    if(m_Effect.get() == NULL)
        return 0;
    EVECalculationType m_Type = m_Effect->GetCalculationType(m_EffectIndex);
    if(m_Type == CALC_ADDITION)
        return m_Item->GetAttribute(m_Effect->GetSourceAttributeID(m_EffectIndex)).get_float();
    if(m_Type == CALC_SUBTRACTION)
        return -(m_Item->GetAttribute(m_Effect->GetSourceAttributeID(m_EffectIndex)).get_float());
    return 0;
}

double AttributeModifier::GetFactor()
{
    if(m_Effect.get() == NULL)
        return 0;
    double source = m_Item->GetAttribute(m_Effect->GetSourceAttributeID(m_EffectIndex)).get_float();
    EVECalculationType m_Type = m_Effect->GetCalculationType(m_EffectIndex);
    if(m_Type == CALC_PERCENTAGE)
    {
        if(source < 2 && source > 0)
            return (1.0 - source) * 100;
        else
            return (100.0 - source);
    }
    if(m_Type == CALC_DIFFERENCE)
    {
        if(source < 2 && source > 0)
            return -(1.0 - source) * 100;
        else
            return source;
    }
    return 0;
}

AttributeModifierSource::AttributeModifierSource(InventoryItemRef sourceItem)
: RefObject( 0 )
{
    m_Source = sourceItem;
    m_Active = true;
}

AttributeModifierSource::~AttributeModifierSource()
{
    m_Modifiers.clear();
    m_Source = InventoryItemRef();
}

void AttributeModifierSource::AddModifier(AttributeModifierRef modifier)
{
    std::vector<AttributeModifierRef>::iterator itr = std::find(m_Modifiers.begin(), m_Modifiers.end(), modifier);
    if (itr == m_Modifiers.end())
        m_Modifiers.push_back(modifier);
}

void AttributeModifierSource::RemoveModifier(AttributeModifierRef modifier)
{
    std::vector<AttributeModifierRef>::iterator itr = std::find(m_Modifiers.begin(), m_Modifiers.end(), modifier);
    if (itr != m_Modifiers.end())
        m_Modifiers.erase(itr);
}

void AttributeModifierSource::GetModification(uint32 attrib, double &amount, FactorList &nonStackingFactors, FactorList &stackingFactors)
{
    if(m_Active == false)
        return;
    std::vector<AttributeModifierRef>::iterator itr = m_Modifiers.begin();
    for (;itr != m_Modifiers.end(); itr++)
    {
        AttributeModifierRef modifier = *itr;
        if (modifier->Modifies(attrib) && modifier->IsActive() == true)
        {
            // add fixed change amount.
            amount += modifier->GetAmount();
            // check for change factor.
            if (modifier->GetFactor() == 0)
                continue;
            if (modifier->StackPenalty())
            {
                // yes this has a stacking penalty.
                stackingFactors.push_back(modifier->GetFactor());
            }
            else
            {
                // no stack penalty.
                nonStackingFactors.push_back(modifier->GetFactor());
            }
        }
    }
}

double AttributeModifierSource::FinalizeModification(double value, double amount, FactorList &nonStackingFactors, FactorList &stackingFactors)
{
    // Add the fixed adjustment amount.
    value += amount;
    // Sort the modification factors so the highest is least penalized.
    // Sort by absolute value as some modifiers are negatives!
    std::sort(stackingFactors.begin(), stackingFactors.end(), [](double x, double y) { return abs(x) < abs(y); } );
    // Loop through the stack penalized factors.
    double N = 0; // Number of modules found.
    // Loop through the list and calculate the penalized factors.
    FactorList::iterator itr = stackingFactors.begin();
    for (; itr != stackingFactors.end(); itr++)
    {
        // Increment the module count.
        N++;
        // Calculate stack penalty.
        double penalty = exp(-pow(N - 1, 2) / 7.1289);
        // Calculate the adjusted factor.
        double factor = (*itr) * penalty;
        // Push the factor on the non-stacking list for proper sorting.
        nonStackingFactors.push_back(factor);
    }
    // Sort the factors.
    // Sort by absolute value as some modifiers are negatives!
    std::sort(nonStackingFactors.begin(), nonStackingFactors.end(), [](double x, double y) { return abs(x) < abs(y); } );
    // Loop through the factors.
    itr = nonStackingFactors.begin();
    for (; itr != nonStackingFactors.end(); itr++)
    {
        // Apply the factor.
        value += value * ((*itr) / 100.0);
    }
    // Return the result.
    return value;
}

void AttributeModifierSource::SetActive(bool state)
{
    if (state != m_Active)
    {
        m_Active = state;
    }
}

void AttributeModifierSource::UpdateModifiers(InventoryItem *item, bool notify)
{
    if(item == NULL)
        return;
    std::vector<AttributeModifierRef>::iterator itr = m_Modifiers.begin();
    for (;itr != m_Modifiers.end(); itr++)
    {
        AttributeModifierRef modifier = *itr;
        item->ResetAttribute(modifier->GetTargetAttribute(), notify);
    }
}