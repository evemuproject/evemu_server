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
    Author:        Bloody.Rabbit
*/

#include "eve-server.h"

#include "character/Character.h"
#include "character/Skill.h"
#include "inventory/AttributeEnum.h"

#define SKILL_BASE_POINTS 250

/*
 * Skill
 */
Skill::Skill(
    uint32 _skillID,
    // InventoryItem stuff:
             const InvTypeRef _type,
    const ItemData &_data )
: InventoryItem(_skillID, _type, _data)
{
}

SkillRef Skill::Load(uint32 skillID)
{
    return InventoryItem::Load<Skill>( skillID );
}

template<class _Ty>
RefPtr<_Ty> Skill::_LoadSkill(uint32 skillID,
    // InventoryItem stuff:
                              const InvTypeRef type, const ItemData &data)
{
    return SkillRef( new Skill( skillID, type, data ) );
}

SkillRef Skill::Spawn(ItemData &data)
{
    uint32 skillID = _Spawn( data );
    if( skillID == 0 )
        return SkillRef();

    SkillRef skillRef = Skill::Load( skillID );

    skillRef->setAttribute(AttrIsOnline, 1);      // Is Online
	skillRef->SaveItem();

    return skillRef;
}

uint32 Skill::_Spawn(ItemData &data)
{
    // check it's a skill
    const InvTypeRef type = InvType::getType(data.typeID);
    if (type.get() == nullptr)
    {
        return 0;
    }

    if (type->getCategoryID() != EVEDB::invCategories::Skill)
    {
        _log(ITEM__ERROR, "Trying to spawn %s as Skill.", type->getCategory()->categoryName.c_str());
        return 0;
    }

    // spawn item, nothing else
    return InventoryItem::_Spawn( data );
}

double Skill::GetSPForLevel(int level)
{
    double timeConst = getAttribute(AttrSkillTimeConstant).get_float();
    return (uint32) (SKILL_BASE_POINTS * timeConst * std::pow(2, (2.5 * (level - 1))));
}

uint8 Skill::GetSkillLevel()
{
    return getAttribute(AttrSkillLevel).get_int();
}

bool Skill::SetSkillLevel(uint8 level)
{
    if (level > 5 || level < 0)
    {
        return false;
    }
    return setAttribute(AttrSkillLevel, level);
}

double Skill::GetSkillPoints()
{
    return getAttribute(AttrSkillPoints).get_float();
}

bool Skill::SetSkillPoints(double points)
{
    if (points > GetSPForLevel(5) || points < 0)
    {
        return false;
    }
    return setAttribute(AttrSkillPoints, points);
}
