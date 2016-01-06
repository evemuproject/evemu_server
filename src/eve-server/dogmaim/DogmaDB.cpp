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
    Author:        ozatomic
*/

#include "eve-server.h"

#include "dogmaim/DogmaDB.h"

PyRep *DogmaDB::GetOperand() {
    DBQueryResult res;

    if(!sDatabase.RunQuery(res,
        "SELECT "
        " operandID,"
        " operandKey,"
        " description,"
        " format,"
        " arg1categoryID,"
        " arg2categoryID,"
        " resultCategoryID,"
        " pythonFormat"
        " FROM operand"
        ))
    {
        _log(DATABASE__ERROR, "Failed to query war factions: %s.", res.error.c_str());
        return NULL;
    }

    return DBResultToCIndexedRowset(res, "operandID");
}



















