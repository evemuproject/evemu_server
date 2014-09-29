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
    Author:     Zhur, Captnoord
*/

#ifndef _INVENTORY_BOUND_H
#define _INVENTORY_BOUND_H

#include "PyBoundObject.h"
#include "PyService.h"

class InventoryBound
: public PyBoundObject
{
public:
    InventoryBound(PyServiceMgr *mgr, Inventory &inventory, EVEItemFlags flag);
    ~InventoryBound();

    virtual void Release() {
        //I hate this statement
        delete this;
    }

    PyCallable_DECL_CALL(List)
    PyCallable_DECL_CALL(Add)
    PyCallable_DECL_CALL(MultiAdd)
    PyCallable_DECL_CALL(GetItem)
    PyCallable_DECL_CALL(ListStations)
    PyCallable_DECL_CALL(ReplaceCharges)
    PyCallable_DECL_CALL(MultiMerge)
    PyCallable_DECL_CALL(StackAll)
    PyCallable_DECL_CALL(StripFitting)
    PyCallable_DECL_CALL(DestroyFitting)
    PyCallable_DECL_CALL(SetPassword)
    PyCallable_DECL_CALL(CreateBookmarkVouchers)
    PyCallable_DECL_CALL(Voucher)

protected:
    class Dispatcher;
    Dispatcher *const m_dispatch;

    Inventory &mInventory;
    EVEItemFlags mFlag;

    PyRep *_ExecAdd(Client *c, const std::vector<int32> &items, uint32 quantity, EVEItemFlags flag);
};

#endif//_INVENTORY_BOUND_H
