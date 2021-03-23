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
    Author:        Zhur
*/

#ifndef _SKILLMGR_SERVICE_H
#define _SKILLMGR_SERVICE_H

#include "character/CharacterDB.h"
#include "PyBoundObject.h"
#include "PyService.h"

class SkillMgrService : public PyService {
public:
    SkillMgrService(PyServiceMgr *mgr);
    virtual ~SkillMgrService();

protected:
    class Dispatcher;
    Dispatcher *const m_dispatch;

    CharacterDB m_db;

    //overloaded in order to support bound objects:
    virtual PyBoundObject *CreateBoundObject(Client *pClient, const PyRep *bind_args);
};

class SkillMgrBound
: public PyBoundObject
{
public:
    SkillMgrBound(PyServiceMgr *mgr, CharacterDB &db);
    virtual ~SkillMgrBound();

    virtual void Release();

    PyCallable_DECL_CALL(InjectSkillIntoBrain);

    PyCallable_DECL_CALL(CharStartTrainingSkill);
    PyCallable_DECL_CALL(CharStartTrainingSkillByTypeID);
    PyCallable_DECL_CALL(CharStopTrainingSkill);
    PyCallable_DECL_CALL(GetEndOfTraining);
    PyCallable_DECL_CALL(GetSkillHistory);
    PyCallable_DECL_CALL(CharAddImplant);
    PyCallable_DECL_CALL(RemoveImplantFromCharacter);

    PyCallable_DECL_CALL(GetSkillQueueAndFreePoints);

    PyCallable_DECL_CALL(SaveSkillQueue);

    PyCallable_DECL_CALL(AddToEndOfSkillQueue);

    PyCallable_DECL_CALL(RespecCharacter);
    PyCallable_DECL_CALL(GetRespecInfo);
    PyCallable_DECL_CALL(GetCharacterAttributeModifiers);

protected:
    class Dispatcher;
    Dispatcher *const m_dispatch;

    CharacterDB &m_db;
};

#endif

