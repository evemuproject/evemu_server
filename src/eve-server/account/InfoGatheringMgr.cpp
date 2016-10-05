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

#include "PyServiceCD.h"
#include "account/InfoGatheringMgr.h"

PyCallable_Make_InnerDispatcher(InfoGatheringMgr)

InfoGatheringMgr::InfoGatheringMgr()
: PyService("infoGatheringMgr", new Dispatcher(this))
{
    PyCallable_REG_CALL(InfoGatheringMgr, GetStateAndConfig);
    PyCallable_REG_CALL(InfoGatheringMgr, LogInfoEventsFromClient);

}

InfoGatheringMgr::~InfoGatheringMgr() {
}

PyResult InfoGatheringMgr::Handle_GetStateAndConfig(PyCallArgs &call) {

    PyDict *rsp = new PyDict;

    rsp->SetItemString("clientWorkerInterval", new PyInt(600000)); //Default From packetlogs is 600000
    rsp->SetItemString("isEnabled", new PyInt(0)); //0 = Disabled, 1 = Enabled. Set to 0 becuase jsut gettting rid of exception.

    PyDict *aggregates = new PyDict();
    aggregates->SetItem(new PyInt(2), new BuiltinSet({1, 2, 3}));
    aggregates->SetItem(new PyInt(3), new BuiltinSet({1, 2, 6}));
    aggregates->SetItem(new PyInt(4), new BuiltinSet({1, 2, 6}));
    aggregates->SetItem(new PyInt(5), new BuiltinSet({1, 2, 6}));
    aggregates->SetItem(new PyInt(6), new BuiltinSet({1, 2, 3, 4}));
    aggregates->SetItem(new PyInt(7), new BuiltinSet({1}));
    aggregates->SetItem(new PyInt(8), new BuiltinSet({1, 4}));
    aggregates->SetItem(new PyInt(9), new BuiltinSet({1, 4}));
    aggregates->SetItem(new PyInt(12), new BuiltinSet({1, 2, 3}));
    aggregates->SetItem(new PyInt(13), new BuiltinSet({1, 2, 3}));
    aggregates->SetItem(new PyInt(14), new BuiltinSet({1, 2, 3}));
    aggregates->SetItem(new PyInt(17), new BuiltinSet({1}));
    aggregates->SetItem(new PyInt(18), new BuiltinSet({1, 3}));
    aggregates->SetItem(new PyInt(19), new BuiltinSet({1, 2}));
    aggregates->SetItem(new PyInt(20), new BuiltinSet({1, 3}));
    aggregates->SetItem(new PyInt(21), new BuiltinSet({1, 3}));
    aggregates->SetItem(new PyInt(22), new BuiltinSet({1, 2, 3, 4, 5}));
    aggregates->SetItem(new PyInt(25), new BuiltinSet({1, 6}));
    aggregates->SetItem(new PyInt(26), new BuiltinSet({1}));
    aggregates->SetItem(new PyInt(27), new BuiltinSet({1, 2, 6, 7}));
    aggregates->SetItem(new PyInt(28), new BuiltinSet({1, 4}));
    aggregates->SetItem(new PyInt(29), new BuiltinSet({1, 3, 6}));
    aggregates->SetItem(new PyInt(30), new BuiltinSet({1}));
    aggregates->SetItem(new PyInt(32), new BuiltinSet({1, 2, 6, 7}));
    aggregates->SetItem(new PyInt(33), new BuiltinSet({1, 2, 6}));
    aggregates->SetItem(new PyInt(34), new BuiltinSet({1, 2, 6}));
    rsp->SetItemString("infoTypeAggregates", aggregates);
    rsp->SetItemString("infoTypesOncePerRun", new BuiltinSet(new PyList()));
    PyDict *params = new PyDict();
    params->SetItem(new PyInt(2), new BuiltinSet({0, 1, 2, 3, 4}));
    params->SetItem(new PyInt(3), new BuiltinSet({0, 1, 2, 3, 6}));
    params->SetItem(new PyInt(4), new BuiltinSet({0, 1, 2, 3, 6}));
    params->SetItem(new PyInt(5), new BuiltinSet({0, 1, 2, 3, 6}));
    params->SetItem(new PyInt(6), new BuiltinSet({0, 1, 2, 3, 4, 5}));
    params->SetItem(new PyInt(7), new BuiltinSet({0, 1, 3}));
    params->SetItem(new PyInt(8), new BuiltinSet({0, 1, 3, 4}));
    params->SetItem(new PyInt(9), new BuiltinSet({0, 1, 3, 4}));
    params->SetItem(new PyInt(12), new BuiltinSet({0, 1, 2, 3, 4}));
    params->SetItem(new PyInt(13), new BuiltinSet({0, 1, 2, 3, 9}));
    params->SetItem(new PyInt(14), new BuiltinSet({0, 1, 2, 3, 9}));
    params->SetItem(new PyInt(15), new BuiltinSet({0, 1, 2, 3, 4, 5}));
    params->SetItem(new PyInt(16), new BuiltinSet({0, 1, 2, 3, 4, 5, 9, 10}));
    params->SetItem(new PyInt(17), new BuiltinSet({0, 1, 3, 4, 5}));
    params->SetItem(new PyInt(18), new BuiltinSet({0, 1, 3, 4}));
    params->SetItem(new PyInt(19), new BuiltinSet({0, 1, 2, 3, 4, 5}));
    params->SetItem(new PyInt(20), new BuiltinSet({0, 1, 3, 4}));
    params->SetItem(new PyInt(21), new BuiltinSet({0, 1, 3, 4}));
    params->SetItem(new PyInt(22), new BuiltinSet({0, 1, 2, 3, 4, 5, 9}));
    params->SetItem(new PyInt(24), new BuiltinSet({0, 1, 2, 3}));
    params->SetItem(new PyInt(25), new BuiltinSet({0, 1, 3, 6, 9}));
    params->SetItem(new PyInt(26), new BuiltinSet({0, 1, 3}));
    params->SetItem(new PyInt(27), new BuiltinSet({0, 1, 2, 3, 6, 7, 9}));
    params->SetItem(new PyInt(28), new BuiltinSet({0, 1, 3, 4}));
    params->SetItem(new PyInt(29), new BuiltinSet({0, 1, 3, 4, 6}));
    params->SetItem(new PyInt(30), new BuiltinSet({0, 1, 3, 4, 5, 9}));
    params->SetItem(new PyInt(32), new BuiltinSet({0, 1, 2, 3, 6, 7}));
    params->SetItem(new PyInt(33), new BuiltinSet({0, 1, 2, 3, 6}));
    params->SetItem(new PyInt(34), new BuiltinSet({0, 1, 2, 3, 6}));
    params->SetItem(new PyInt(35), new BuiltinSet({0, 1, 2, 3, 4, 5, 9, 10, 11}));
    params->SetItem(new PyInt(36), new BuiltinSet({0, 1, 2, 3, 4, 5, 9}));
    params->SetItem(new PyInt(37), new BuiltinSet({0, 1, 2, 3, 4, 5, 9, 10}));
    params->SetItem(new PyInt(38), new BuiltinSet({0, 1, 2, 3, 6}));
    rsp->SetItemString("infoTypeParameters", params);

    PyList *infoTypes = new PyList;
    infoTypes->AddItemInt(999); //Adding a value that was not in live so when its checks list it will always return false for now.

    rsp->SetItemString("infoTypes", new BuiltinSet(infoTypesVals));

    return new PyObject( "util.KeyVal", rsp );
}

PyResult InfoGatheringMgr::Handle_LogInfoEventsFromClient(PyCallArgs &call) {
    return new PyNone;
}
