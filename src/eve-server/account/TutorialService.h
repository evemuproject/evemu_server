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
    Author:        Zhur
*/


#ifndef __TUTORIALSVC_SERVICE_H_INCL__
#define __TUTORIALSVC_SERVICE_H_INCL__

#include "account/TutorialDB.h"
#include "PyService.h"

class TutorialService : public PyService
{
public:
    TutorialService(PyServiceMgr *mgr);
    virtual ~TutorialService();

protected:
    class Dispatcher;
    Dispatcher *const m_dispatch;

    TutorialDB m_db;

    PyCallable_DECL_CALL(GetTutorialInfo)
    PyCallable_DECL_CALL(GetTutorials)
    PyCallable_DECL_CALL(GetCriterias)
    //LogAborted(tutnum=5, int=1, int=11)
    PyCallable_DECL_CALL(GetCategories)
    PyCallable_DECL_CALL(GetContextHelp)
    PyCallable_DECL_CALL(GetCharacterTutorialState)
    PyCallable_DECL_CALL(GetTutorialsAndConnections)
    PyCallable_DECL_CALL(GetCareerAgents)
};

#endif
