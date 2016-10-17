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


#ifndef __PYSERVICEMGR_H_INCL__
#define __PYSERVICEMGR_H_INCL__

class PyService;
class PyCallable;
class PyBoundObject;
class PyPacket;
class Client;
class PyRep;
class PySubStruct;
class EntityList;
class ObjCacheService;

class LSCService;

class PyServiceMgr
{
public:
    static void Init(uint32 nodeID);
    static void Shutdown();

    static void Process();

    static void RegisterService(PyService* d);
    static PyService* LookupService(const std::string& name);

    static uint32 GetNodeID()
    {
        return (m_nodeID);
    }

    //object binding, not fully understood yet.
    static PySubStruct *BindObject(Client *who, PyBoundObject *obj, PyDict **dict = nullptr, PyDict *oid = nullptr);
    static PyBoundObject *FindBoundObject(uint32 bindID);
    static void ClearBoundObject(uint32 bindID);
    static void ClearBoundObjects(Client *who);

    //Area to access services by name. This isn't ideal, but it avoids casting.
    //these may be NULL during service init, but should never be after that.
    //we do not own these pointers (we do in their PyService * form though)
    static LSCService *lsc_service;
    static ObjCacheService *cache_service;

protected:
    static std::set<PyService *> m_services; //we own these pointers.

    static uint32 m_nextBindID;

    static uint32 _GetBindID()
    {
        return (m_nextBindID++);
    }

    struct BoundObject
    {
        Client *client;    //we do not own this.
        PyBoundObject *destination;    //we own this. PyServiceMgr deletes it
    };

    typedef std::map<uint32, BoundObject>   ObjectsBoundMap;
    typedef ObjectsBoundMap::iterator       ObjectsBoundMapItr;
    static ObjectsBoundMap m_boundObjects;

    static uint32 m_nodeID;
};

#endif
