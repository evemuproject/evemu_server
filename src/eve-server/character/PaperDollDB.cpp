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
    Author:        Reve
    Providing clothes to the poor
*/

#include "eve-server.h"

#include "character/PaperDollDB.h"

PyRep* PaperDollDB::GetPaperDollAvatar(uint32 charID) const {

    DBQueryResult res;
    if (!sDatabase.RunQuery(res,
		" (SELECT hairDarkness FROM avatars WHERE `charID`=%u ) ", charID))
    {
        _log(DATABASE__ERROR, "Error in GetMyPaperDollData query: %s", res.error.c_str());
        return (NULL);
    }

	DBResultRow row;

	res.GetRow(row);

	return DBRowToRow(row, "util.Row");
}

PyRep* PaperDollDB::GetPaperDollAvatarColors(uint32 charID) const {

    DBQueryResult res;
    if (!sDatabase.RunQuery(res,
		" (SELECT colorID, colorNameA, colorNameBC, weight, gloss  FROM avatar_colors WHERE `charID`=%u ) ", charID))
    {
        _log(DATABASE__ERROR, "Error in GetMyPaperDollData query: %s", res.error.c_str());
        return (NULL);
    }

    return DBResultToCRowset(res);
}

PyRep* PaperDollDB::GetPaperDollAvatarModifiers(uint32 charID) const {

    DBQueryResult res;
    if (!sDatabase.RunQuery(res,
		" (SELECT modifierLocationID, paperdollResourceID, paperdollResourceVariation FROM avatar_modifiers WHERE `charID`=%u ) ", charID))
    {
        _log(DATABASE__ERROR, "Error in GetMyPaperDollData query: %s", res.error.c_str());
        return (NULL);
    }

    return DBResultToCRowset(res);
}

PyRep* PaperDollDB::GetPaperDollAvatarSculpts(uint32 charID) const {

    DBQueryResult res;
    if (!sDatabase.RunQuery(res,
		" (SELECT sculptLocationID, weightUpDown, weightLeftRight, weightForwardBack FROM avatar_sculpts WHERE `charID`=%u ) ", charID))
    {
        _log(DATABASE__ERROR, "Error in GetMyPaperDollData query: %s", res.error.c_str());
        return (NULL);
    }

    return DBResultToCRowset(res);
}
