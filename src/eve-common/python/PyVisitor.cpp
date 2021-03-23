/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2021 The EVEmu Team
    For the latest information visit https://github.com/evemuproject/evemu_server
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
    Author:     Zhur, mmcs
    Rewrite:    Allan
*/

#include "../eve-common.h"

#include "python/classes/PyDatabase.h"
#include "python/PyVisitor.h"
//#include "python/PyRep.h"

/************************************************************************/
/* PyVisitor                                                            */
/************************************************************************/
bool PyVisitor::VisitTuple(const PyTuple* rep)
{
    PyTuple::const_iterator itr = rep->begin(), end = rep->end();
    for (;  itr != end; ++itr) {
        //  if/when segfault here and (*itr) == 0x0 then tuple count != tuple->SetItem()
        if (!(*itr)->visit(*this))
            return false;
    }
    return true;
}

bool PyVisitor::VisitList(const PyList* rep)
{
    PyList::const_iterator itr = rep->begin(), end = rep->end();
    for (;  itr != end; ++itr)
        if (!(*itr)->visit(*this))
            return false;

    return true;
}

bool PyVisitor::VisitDict(const PyDict* rep)
{
    PyDict::const_iterator itr = rep->begin(), end = rep->end();
    for (;  itr != end; ++itr) {
        if (!itr->first->visit(*this))
            return false;
        if (!itr->second->visit(*this))
            return false;
    }
    return true;
}

bool PyVisitor::VisitObject(const PyObject* rep)
{
    if (!rep->type()->visit(*this))
        return false;
    if (!rep->arguments()->visit(*this))
        return false;
    return true;
}

bool PyVisitor::VisitObjectEx(const PyObjectEx* rep)
{
    if (!rep->header()->visit(*this))
        return false;

    PyObjectEx::const_list_iterator lItr = rep->list().begin(), lEnd = rep->list().end();
    for (; lItr != lEnd; ++lItr) {
        if (!(*lItr)->visit(*this))
            return false;
    }
    PyObjectEx::const_dict_iterator dItr = rep->dict().begin(), dEnd = rep->dict().end();
    for (; dItr != dEnd; ++dItr) {
        if (!dItr->first->visit(*this))
            return false;
        if (!dItr->second->visit(*this))
            return false;
    }

    return true;
}

bool PyVisitor::VisitPackedRow(const PyPackedRow* rep)
{
    if (!rep->header()->visit(*this))
        return false;

    PyPackedRow::const_iterator itr = rep->begin(), end = rep->end();
    for (;  itr != end; ++itr)
        if (!(*itr)->visit(*this))
            return false;

    return true;
}

bool PyVisitor::VisitSubStruct(const PySubStruct* rep)
{
    if (!rep->sub()->visit(*this))
        return false;
    return true;
}

bool PyVisitor::VisitSubStream(const PySubStream* rep)
{
    if (rep->decoded() == nullptr)  {
        if (rep->data() == nullptr)
            return false;
        rep->DecodeData();
        if (rep->decoded() == nullptr)
            return false;
    }
    if (!rep->decoded()->visit(*this))
        return false;
    return true;
}

bool PyVisitor::VisitChecksumedStream(const PyChecksumedStream* rep)
{
    if (!rep->stream()->visit(*this))
        return false;
    return true;
}

/************************************************************************/
/* PyPfxVisitor                                                         */
/************************************************************************/
PyPfxVisitor::PyPfxVisitor(const char* pfx)
{
    mPfxStack.push(pfx);
}

void PyPfxVisitor::_pfxExtend(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    char* res;
    vasprintf(&res, fmt, ap);

    va_end(ap);

    std::string p(_pfx());
    p += res;
    mPfxStack.push(p);

    SafeFree(res);
}
