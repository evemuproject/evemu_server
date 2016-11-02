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
    Author:     Zhur
*/

#include "eve-common.h"

#include "python/PyPacket.h"
#include "python/PyVisitor.h"
#include "python/PyRep.h"
#include "packets/General.h"

const char* MACHONETMSG_TYPE_NAMES[MACHONETMSG_TYPE_COUNT] =
{
    "AUTHENTICATION_REQ",
    "AUTHENTICATION_RSP",
    "IDENTIFICATION_REQ",
    "IDENTIFICATION_RSP",
    "U4",
    "U5",
    "CALL_REQ",
    "CALL_RSP",
    "TRANSPORTCLOSED",
    "U9",
    "RESOLVE_REQ",
    "RESOLVE_RSP",
    "NOTIFICATION",
    "U13",
    "U14",
    "ERRORRESPONSE",
    "SESSIONCHANGENOTIFICATION",
    "U17",
    "SESSIONINITIALSTATENOTIFICATION",
    "U19",
    "PING_REQ",
    "PING_RSP"
};

PyPacket::PyPacket() : type_string("none"), type(__Fake_Invalid_Type), userid(0), payload(NULL), named_payload(NULL) {}
PyPacket::~PyPacket()
{
    PySafeDecRef(payload);
    PySafeDecRef(named_payload);
}

PyPacket *PyPacket::Clone() const
{
    PyPacket *res = new PyPacket();
    res->type_string = type_string;
    res->type = type;
    res->source = source;
    res->dest = dest;
    res->userid = userid;
    res->payload = pyAs(Tuple, payload->Clone());
    if(named_payload == NULL)
    {
        res->named_payload = NULL;
    }
    else
    {
        res->named_payload = pyAs(Dict, named_payload->Clone());
    }
    return res;
}

void PyPacket::dump(std::ostringstream &ss, const std::string &pfx)
{
    std::string pfx1(pfx + "    ");
    std::string pfx2(pfx1 + "    ");
    std::string pfx3(pfx2 + "    ");
    std::string pfx4(pfx3 + "    ");
    ss << pfx << "PyPacket:" << std::endl;
    ss << pfx1 << "Type: " <<  type_string.c_str() << std::endl;
    ss << pfx1 << "Command: " << MACHONETMSG_TYPE_NAMES[type] << "(" << type << ")" << std::endl;
    ss << pfx1 << "Source:" << std::endl;
    source.dump(ss, pfx2);
    ss << pfx1 << "Destination:" << std::endl;
    dest.dump(ss, pfx2);
    ss << pfx1 << "User ID: " << userid << std::endl;
    ss << pfx1 << "[Payload]" << std::endl;
    bool payloadDumped = false;
    switch (type)
    {
    case NOTIFICATION:
    {
        EVENotificationStream note;
        PyTuple *tup = pyAs(Tuple, payload->Clone());
        if (note.Decode(type_string, tup))
        {
            note.dump(ss, pfx2);
            payloadDumped = true;
        }
        break;
    }
    case CALL_REQ:
    {
        PyCallStream req;
        PyTuple *tup = pyAs(Tuple, payload->Clone());
        if (req.Decode(type_string, tup))
        {
            req.dump(ss, pfx2);
            payloadDumped = true;
        }
        break;
    }
    case CALL_RSP:
    {
        PyTuple *tup1;
        if (pyIsAs(Tuple, payload, tup1))
        {
            if (tup1->items.size() == 1)
            {
                PySubStream *stream;
                if (pyIsAs(SubStream, tup1->items[0], stream))
                {
                    PySubStream *sub = pyAs(SubStream, stream->Clone());
                    sub->DecodeData();
                    if (sub->decoded() != nullptr)
                    {
                        PyRep *pack = sub->decoded();
                        if (pack != nullptr)
                        {
                            ss << pfx2 << "Response:" << std::endl;
                            pack->dump(ss, pfx3);
                            payloadDumped = true;
                        }
                    }
                }
            }
        }
        break;
    }
    case SESSIONCHANGENOTIFICATION:
    {
        SessionChangeNotification sessionChange;
        if( sessionChange.Decode( payload ) )
        {
            ss << pfx2 << "[SessionChangeNotification]" << std::endl;
            ss << pfx3 << "sessionID=" << sessionChange.sessionID << std::endl;
            ss << pfx3 << "clueless=" << sessionChange.clueless << std::endl;
            ss << pfx3 << "Nodes:" << std::endl;
            for(int32 node : sessionChange.nodesOfInterest)
            {
                ss << pfx4 << node << std::endl;
            }
            ss << pfx3 << "Changes:" << std::endl;
            if(sessionChange.changes == nullptr)
            {
                ss << pfx4 << "<nullptr>" << std::endl;
            }
            else
            {
                sessionChange.changes->dump(ss, pfx3);
            }
            payloadDumped = true;
        }
        break;
    }
    case AUTHENTICATION_REQ:
    case AUTHENTICATION_RSP:
    case IDENTIFICATION_REQ:
    case IDENTIFICATION_RSP:
    case TRANSPORTCLOSED:
    case RESOLVE_REQ:
    case RESOLVE_RSP:
    case ERRORRESPONSE:
    case SESSIONINITIALSTATENOTIFICATION:
    case PING_REQ:
    case PING_RSP:
    default:
        break;
    }
    if (!payloadDumped)
    {
        payload->dump(ss, pfx2);
    }
    if (named_payload == nullptr)
    {
        ss << pfx1 << "Named Payload: None" << std::endl;
    }
    else
    {
        ss << pfx1 << "Named Payload:" << std::endl;
        named_payload->dump(ss, pfx2);
    }
}

bool PyPacket::Decode(PyRep **in_packet)
{
    PyRep *packet = *in_packet;  //consume
    *in_packet = NULL;

    PySafeDecRef(payload);
    PySafeDecRef(named_payload);

    PyChecksumedStream* cs;
    if(pyIsAs(ChecksumedStream, packet, cs))
    {
        //TODO: check cs->checksum
        packet = cs->stream();
        PyIncRef( packet );

        PyDecRef( cs );
    }

    //Dragon nuance... it gets wrapped again
    PySubStream* ss;
    if(pyIsAs(SubStream, packet, ss))
    {
        ss->DecodeData();
        if(ss->decoded() == NULL)
        {
            codelog(NET__PACKET_ERROR, "failed: unable to decode initial packet substream.");
            PyDecRef(packet);
            return false;
        }

        packet = ss->decoded();
        PyIncRef( packet );

        PyDecRef( ss );
    }

    PyObject *packeto;
    if(!pyIsAs(Object, packet, packeto))
    {
        codelog(NET__PACKET_ERROR, "failed: packet body is not an 'Object': %s", packet->TypeString());
        PyDecRef(packet);
        return false;
    }

    type_string = packeto->type()->content();

    PyTuple *tuple;
    if(!pyIsAs(Tuple, packeto->arguments(), tuple))
    {
        codelog(NET__PACKET_ERROR, "failed: packet body does not contain a tuple");
        PyDecRef(packet);
        return false;
    }

    if(tuple->items.size() != 7)
    {
        codelog(NET__PACKET_ERROR, "failed: packet body does not contain a tuple of length 7");
        PyDecRef(packet);

        return false;
    }

    PyInt *typer;
    if(!pyIsAs(Int, tuple->items[0], typer))
    {
        codelog(NET__PACKET_ERROR, "failed: First main tuple element is not an integer");
        PyDecRef(packet);

        return false;
    }
    switch(typer->value()) {
    case AUTHENTICATION_REQ:
    case AUTHENTICATION_RSP:
    case IDENTIFICATION_REQ:
    case IDENTIFICATION_RSP:
    case CALL_REQ:
    case CALL_RSP:
    case TRANSPORTCLOSED:
    case RESOLVE_REQ:
    case RESOLVE_RSP:
    case NOTIFICATION:
    case ERRORRESPONSE:
    case SESSIONCHANGENOTIFICATION:
    case SESSIONINITIALSTATENOTIFICATION:
    case PING_REQ:
    case PING_RSP:
        type = (MACHONETMSG_TYPE) typer->value();
        break;
    default:
        codelog(NET__PACKET_ERROR, "failed: Unknown message type %" PRIu64, typer->value());
        PyDecRef(packet);

        return false;
        break;
    }

    //source address
    if(!source.Decode(tuple->items[1]))
    {
        //error printed in decoder
        PyDecRef(packet);

        return false;
    }
    //dest address
    if(!dest.Decode(tuple->items[2]))
    {
        //error printed in decoder
        PyDecRef(packet);

        return false;
    }

    PyInt *i;
    if(pyIsAs(Int, tuple->items[3], i))
    {
        userid = i->value();
    }
    else if(pyIs(None, tuple->items[3]))
    {
        userid = 0;
    }
    else
    {
        codelog(NET__PACKET_ERROR, "failed: User ID has invalid type");
        PyDecRef(packet);
        return false;
    }

    //payload
    if(!(pyIs(Buffer, tuple->items[4]) || pyIsAs(Tuple, tuple->items[4], payload)))
    {
        codelog(NET__PACKET_ERROR, "failed: Fifth main tuple element is not a tuple");
        PyDecRef(packet);
        return false;
    }
    tuple->items[4] = NULL; //we keep this one

    //options dict
    if(pyIs(None, tuple->items[5]))
    {
        named_payload = NULL;
    }
    else if(pyIsAs(Dict, tuple->items[5], named_payload))
    {
        tuple->items[5] = NULL; //we keep this too.
    }
    else
    {
        codelog(NET__PACKET_ERROR, "failed: Sixth main tuple element is not a dict");
        PyDecRef(packet);
        return false;
    }

    PyDecRef(packet);
    return true;
}



PyRep *PyPacket::Encode() {
    PyTuple *arg_tuple = new PyTuple(7);

    //command
    arg_tuple->items[0] = new PyInt(type);

    //source
    arg_tuple->items[1] = source.Encode();

    //dest
    arg_tuple->items[2] = dest.Encode();

    //unknown3
    if(userid == 0)
        arg_tuple->items[3] = new PyNone();
    else
        arg_tuple->items[3] = new PyInt(userid);

    //payload
    //TODO: we don't really need to clone this if we can figure out a way to say "this is read only"
    //or if we can change this encode method to consume the PyPacket (which will almost always be the case)
    arg_tuple->items[4] = payload->Clone();

    //named arguments
    if(named_payload == NULL) {
        arg_tuple->items[5] = new PyNone();
    } else {
        arg_tuple->items[5] = named_payload->Clone();
    }

    //TODO: Not sure what this is, On packets so far they always have as PyNone
    arg_tuple->items[6] = new PyNone();

    return new PyObject( type_string.c_str(), arg_tuple );
}

PyAddress::PyAddress() : type(Invalid), typeID(0), callID(0), service("") {}

void PyAddress::dump(std::ostringstream &ss, const std::string &pfx) const {
    switch(type) {
    case Any:
        ss << pfx << "Any: service='" << service << "' callID=" << callID << std::endl;
        break;
    case Node:
        ss << pfx << "Node: node=" << typeID << " service='" << service << "' callID=" << callID << std::endl;
        break;
    case Client:
        ss << pfx << "Client: node=" << typeID << " service='" << service << "' callID=" << callID << std::endl;
        break;
    case Broadcast:
        ss << pfx << "Broadcast: broadcastID='" << service << "' narrowcast=(not decoded yet) idtype='" << bcast_idtype << std::endl;
        break;
    case Invalid:
        break;
    //no default on purpose
    }
}

void PyAddress::operator=(const PyAddress &right) {
    type = right.type;
    typeID = right.typeID;
    callID = right.callID;
    service = right.service;
    bcast_idtype = right.bcast_idtype;
}

bool PyAddress::Decode(PyRep *&in_object) {
    PyRep *base = in_object;
    in_object = NULL;

    PyObject *obj;
    if(!pyIsAs(Object, base, obj)) {
        codelog(NET__PACKET_ERROR, "Invalid element type, expected object");
        PyDecRef(base);
        return false;
    }

    //do we care about the object type? should be "macho.MachoAddress"

    PyTuple *args;
    if(!pyIsAs(Tuple, obj->arguments(), args)) {
        codelog(NET__PACKET_ERROR, "Invalid argument type, expected tuple");
        PyDecRef(base);
        return false;
    }

    if(args->items.size() < 3)
    {
        codelog(NET__PACKET_ERROR, "Not enough elements in address tuple: %lu", args->items.size());
        args->Dump(NET__PACKET_ERROR, "  ");
        PyDecRef(base);
        return false;
    }

    //decode the address type.
    PyInt *typei;
    if(!pyIsAs(Int, args->items[0], typei))
    {
        codelog(NET__PACKET_ERROR, "Wrong type on address type element (0)");
        args->items[0]->Dump(NET__PACKET_ERROR, "  ");
        PyDecRef(base);
        return false;
    }
    switch(typei->value())
    {
    case Any: {
        if(args->items.size() != 3) {
            codelog(NET__PACKET_ERROR, "Invalid number of elements in Any address tuple: %lu", args->items.size());
            PyDecRef(base);
            return false;
        }
        type = Any;

        if(!_DecodeService(args->items[1])
        || !_DecodeCallID(args->items[2])) {
            PyDecRef(base);
            return false;
        }

        break;
    }
    case Node: {
        if(args->items.size() != 4) {
            codelog(NET__PACKET_ERROR, "Invalid number of elements in Node address tuple: %lu", args->items.size());
            PyDecRef(base);
            return false;
        }
        type = Node;

        if(!_DecodeTypeID(args->items[1])
        || !_DecodeService(args->items[2])
        || !_DecodeCallID(args->items[3])) {
            PyDecRef(base);
            return false;
        }
        break;
    }
    case Client: {
        if(args->items.size() != 4) {
            codelog(NET__PACKET_ERROR, "Invalid number of elements in Client address tuple: %lu", args->items.size());
            PyDecRef(base);
            return false;
        }
        type = Client;

        if(!_DecodeTypeID(args->items[1])
        || !_DecodeCallID(args->items[2])
        || !_DecodeService(args->items[3])) {
            PyDecRef(base);
            return false;
        }

        break;
    }
    case Broadcast: {
        if(args->items.size() != 4) {
            codelog(NET__PACKET_ERROR, "Invalid number of elements in Broadcast address tuple: %lu", args->items.size());
            PyDecRef(base);
            return false;
        }
        type = Broadcast;

        PyString *bid;
        PyString *idt;
        if(!pyIsAs(String, args->items[1], bid)) {
            codelog(NET__PACKET_ERROR, "Invalid type %s for brodcastID", args->items[1]->TypeString());
            PyDecRef(base);
            return false;
        }
        else if(!pyIsAs(String, args->items[3], idt)) {
            codelog(NET__PACKET_ERROR, "Invalid type %s for idtype", args->items[3]->TypeString());
            PyDecRef(base);
            return false;
        }

        service = bid->content();
        bcast_idtype = idt->content();

        //items[2] is either a list or a tuple.
        /*
        //PyList *nclist = pyAs(List, args->items[2]);
        if(!nclist->items.empty()) {
            printf("Not decoding narrowcast list:");
            nclist->Dump(NET__PACKET_ERROR, "     ");
        }*/

        break;
    }
    default:
        codelog(NET__PACKET_ERROR, "Unknown address type: %c", typei->value() );
        PyDecRef(base);
        return false;
    }

    PyDecRef(base);
    return true;
}

PyRep *PyAddress::Encode() {
    PyTuple *t;
    switch(type) {
    case Any:
        t = new PyTuple(3);
        t->items[0] = new PyInt((int)type);

        if(service == "")
            t->items[1] = new PyNone();
        else
            t->items[1] = new PyString(service.c_str());

        if(typeID == 0)
            t->items[2] = new PyNone();
        else
            t->items[2] = new PyLong(typeID);

        break;

    case Node:
        t = new PyTuple(4);
        t->items[0] = new PyInt((int)type);
        t->items[1] = new PyLong(typeID);

        if(service == "")
            t->items[2] = new PyNone();
        else
            t->items[2] = new PyString(service.c_str());

        if(callID == 0)
            t->items[3] = new PyNone();
        else
            t->items[3] = new PyLong(callID);

        break;

    case Client:
        t = new PyTuple(4);
        t->items[0] = new PyInt((int)type);
        t->items[1] = new PyLong(typeID);
        t->items[2] = new PyLong(callID);
        if(service == "")
            t->items[3] = new PyNone();
        else
            t->items[3] = new PyString(service.c_str());

        break;

    case Broadcast:
        t = new PyTuple(4);
        t->items[0] = new PyInt((int)type);
        //broadcastID
        if(service == "")
            t->items[1] = new PyNone();
        else
            t->items[1] = new PyString(service.c_str());
        //narrowcast
        t->items[2] = new PyList();
        //typeID
        t->items[3] = new PyString(bcast_idtype.c_str());

        break;

    case Invalid:
    default:
        //this still needs to be something which will not crash us.
        t = new PyTuple(0);

        break;
    }

    return new PyObject( "macho.MachoAddress", t );
}

bool PyAddress::_DecodeService(PyRep *rep)
{
    PyString *s;
    if(pyIsAs(String, rep, s))
    {
        service = s->content();
    }
    else if(pyIs(None, rep))
    {
        service = "";
    }
    else
    {
        codelog(NET__PACKET_ERROR, "Wrong type on service field");
        rep->Dump(NET__PACKET_ERROR, "  ");
        return false;
    }
    return true;
}

bool PyAddress::_DecodeCallID(PyRep *rep)
{
    PyInt *i;
    if(pyIsAs(Int, rep, i))
    {
        callID = i->value();
    }
    else if(pyIs(None, rep))
    {
        callID = 0;
    }
    else
    {
        codelog(NET__PACKET_ERROR, "Wrong type on callID field");
        rep->Dump(NET__PACKET_ERROR, "  ");
        return false;
    }
    return true;
}

bool PyAddress::_DecodeTypeID(PyRep *rep)
{
    PyInt *i;
    if(pyIsAs(Int, rep, i))
    {
        typeID = i->value();
    }
    else if(pyIs(None, rep))
    {
        typeID = 0;
    }
    else 
    {
        codelog(NET__PACKET_ERROR, "Wrong type on typed ID field");
        rep->Dump(NET__PACKET_ERROR, "  ");
        return false;
    }
    return true;
}


PyCallStream::PyCallStream()
: remoteObject(0),
  method(""),
  arg_tuple(NULL),
  arg_dict(NULL)
{
}

PyCallStream::~PyCallStream() {
    PySafeDecRef(arg_tuple);
    PySafeDecRef(arg_dict);
}

PyCallStream *PyCallStream::Clone() const {
    PyCallStream *res = new PyCallStream();
    res->remoteObject = remoteObject;
    res->remoteObjectStr = remoteObjectStr;
    res->method = method;
    res->arg_tuple = new PyTuple( *arg_tuple );
    if(arg_dict == NULL) {
        res->arg_dict = NULL;
    } else {
        res->arg_dict = new PyDict( *arg_dict );
    }
    return res;
}

void PyCallStream::dump(std::ostringstream &ss, const std::string &pfx)
{
    std::string pfx1(pfx + "    ");
    std::string pfx2(pfx1 + "    ");
    std::string pfx3(pfx2 + "    ");
    ss << pfx << "[PyCallStream]" << std::endl;
    if (remoteObject == 0)
    {
        ss << pfx1 << "Remote Object: '" << remoteObjectStr << "'" << std::endl;
    }
    else
    {
        ss << pfx1 << "Remote Object: " << remoteObject << std::endl;
    }
    ss << pfx1 << "Method: " << method << std::endl;
    bool dumped = false;
    if (method == "MachoBindObject")
    {
        CallMachoBindObject bind;
        PyTuple *tup = pyAs(Tuple, arg_tuple->Clone());
        if (bind.Decode(tup))
        {
            ss << pfx1 << "BindObject:" << std::endl;;
            if (bind.bindParams != nullptr)
            {
                ss << pfx2 << "BindParams:" << std::endl;
                bind.bindParams->dump(ss, pfx3);
            }
            if (bind.call != nullptr)
            {
                PyTuple *tup;
                if (pyIsAs(Tuple, bind.call, tup))
                {
                    if (tup->items.size() == 3)
                    {
                        if (pyIs(String, tup->items[0]) && pyIs(Tuple, tup->items[1]) && pyIs(Dict, tup->items[2]))
                        {
                            ss << pfx2 << "Call: " << pyAs(String, tup->items[0])->content() << std::endl;
                            ss << pfx2 << "Arguments:" << std::endl;
                            tup->items[1]->dump(ss, pfx3);
                            ss << pfx2 << "Named Arguments:" << std::endl;
                            tup->items[2]->dump(ss, pfx3);
                            dumped = true;
                        }
                    }
                }
                else if (pyIs(None, bind.call))
                {
                    dumped = true;
                }
            }
            else
            {
                dumped = true;
            }
        }
    }
    if (!dumped)
    {
        ss << pfx1 << "Arguments:" << std::endl;
        arg_tuple->dump(ss, pfx2);
    }
    if (arg_dict == NULL)
    {
        ss << pfx1 << "Named Arguments: None" << std::endl;
    }
    else
    {
        ss << pfx1 << "Named Arguments:" << std::endl;
        arg_dict->dump(ss, pfx2);
    }
}

bool PyCallStream::Decode(const std::string &type, PyTuple *&in_payload) {
    PyTuple *payload = in_payload;   //consume
    in_payload = NULL;

    PySafeDecRef(arg_tuple);
    PySafeDecRef(arg_dict);
    arg_tuple = NULL;
    arg_dict = NULL;

    if(type != "macho.CallReq") {
        codelog(NET__PACKET_ERROR, "failed: packet payload has unknown string type '%s'", type.c_str());
        PyDecRef(payload);
        return false;
    }

    if (payload->items.size() != 1) {
        codelog(NET__PACKET_ERROR, "invalid tuple length %lu", payload->items.size());
        PyDecRef(payload);
        return false;
    }
    PyTuple *payload2;
    if (!pyIsAs(Tuple, payload->items[0], payload2)) {
        codelog(NET__PACKET_ERROR, "non tuple payload[0]");
        PyDecRef(payload);
        return false;
    }

    if(payload2->items.size() != 2) {
        codelog(NET__PACKET_ERROR, "invalid tuple2 length %lu", payload2->items.size());
        PyDecRef(payload);
        return false;
    }

    //decode inner payload tuple
    //ignore tuple 0, it should be an int, dont know what it is
    PySubStream *ss;
    if(!pyIsAs(SubStream, payload2->items[1], ss)) {
        codelog(NET__PACKET_ERROR, "non-substream type");
        PyDecRef(payload);
        return false;
    }

    ss->DecodeData();
    if(ss->decoded() == NULL) {
        codelog(NET__PACKET_ERROR, "Unable to decode call stream");
        PyDecRef(payload);
        return false;
    }

    PyTuple *maint;
    if(!pyIsAs(Tuple, ss->decoded(), maint)) {
        codelog(NET__PACKET_ERROR, "packet body does not contain a tuple");
        PyDecRef(payload);
        return false;
    }

    if(maint->items.size() != 4)
    {
        codelog(NET__PACKET_ERROR, "packet body has %lu elements, expected %d", maint->items.size(), 4);
        PyDecRef(payload);
        return false;
    }

    //parse first tuple element, unknown
    PyInt *tupleInt;
    PyString *tupleString;
    if(pyIsAs(Int, maint->items[0], tupleInt))
    {
        remoteObject = tupleInt->value();
        remoteObjectStr = "";
    }
    else if(pyIsAs(String, maint->items[0], tupleString))
    {
        remoteObject = 0;
        remoteObjectStr = tupleString->content();
    }
    else
    {
        codelog(NET__PACKET_ERROR, "tuple[0] has invalid type %s", maint->items[0]->TypeString());
        codelog(NET__PACKET_ERROR, " in:");
        payload->Dump(NET__PACKET_ERROR, "    ");
        PyDecRef(payload);
        return false;
    }

    //parse tuple[1]: method name
    PyString *i;
    if(pyIsAs(String, maint->items[1], i))
    {
        method = i->content();
    }
    else
    {
        codelog(NET__PACKET_ERROR, "tuple[1] has non-string type");
        maint->items[1]->Dump(NET__PACKET_ERROR, " --> ");
        codelog(NET__PACKET_ERROR, " in:");
        payload->Dump(NET__PACKET_ERROR, "    ");
        PyDecRef(payload);
        return false;
    }

    //grab argument list.
    if(!pyIsAs(Tuple, maint->items[2], arg_tuple)) {
        codelog(NET__PACKET_ERROR, "argument list has non-tuple type");
        maint->items[2]->Dump(NET__PACKET_ERROR, " --> ");
        codelog(NET__PACKET_ERROR, "in:");
        payload->Dump(NET__PACKET_ERROR, "    ");
        PyDecRef(payload);
        return false;
    }
    maint->items[2] = NULL; //we keep this one

    //options dict
    if(pyIs(None, maint->items[3]))
    {
        arg_dict = NULL;
    }
    else if(pyIsAs(Dict, maint->items[3], arg_dict))
    {
        maint->items[3] = NULL; //we keep this too.
    }
    else
    {
        codelog(NET__PACKET_ERROR, "tuple[3] has non-dict type");
        maint->items[3]->Dump(NET__PACKET_ERROR, " --> ");
        codelog(NET__PACKET_ERROR, "in:");
        payload->Dump(NET__PACKET_ERROR, "    ");
        PyDecRef(payload);
        return false;
    }

    PyDecRef(payload);
    return true;
}

PyTuple *PyCallStream::Encode() {
    PyTuple *res_tuple = new PyTuple(4);

    //remoteObject
    if(remoteObject == 0)
    {
        res_tuple->items[0] = new PyString(remoteObjectStr.c_str());
    }
    else
    {
        res_tuple->items[0] = new PyInt(remoteObject);
    }

    //method name
    res_tuple->items[1] = new PyString(method.c_str());

    //args
    //TODO: we dont really need to clone this if we can figure out a way to say "this is read only"
    //or if we can change this encode method to consume the PyCallStream (which will almost always be the case)
    res_tuple->items[2] = new PyTuple( *arg_tuple );

    //options
    if(arg_dict == NULL)
    {
        res_tuple->items[3] = new PyNone();
    }
    else
    {
        res_tuple->items[3] = new PyDict( *arg_dict );
    }

    //now that we have the main arg tuple, build the unknown stuff around it...
    PyTuple *it2 = new PyTuple(2);
    it2->items[0] = new PyInt(remoteObject==0?1:0); /* some sort of flag, "process here or call UP"....*/
    it2->items[1] = new PySubStream(res_tuple);

    PyTuple *it1 = new PyTuple(2);
    it1->items[0] = it2;
    it1->items[1] = new PyNone();    //this is the "channel" dict if populated.

    return(it1);
}



EVENotificationStream::EVENotificationStream()
:  remoteObject(0),
  args(NULL)
{
}

EVENotificationStream::~EVENotificationStream()
{
    PySafeDecRef(args);
}

EVENotificationStream *EVENotificationStream::Clone() const
{
    EVENotificationStream *res = new EVENotificationStream();
    res->args = pyAs(Tuple, args->Clone());
    return res;
}

void EVENotificationStream::dump(std::ostringstream &ss, const std::string &pfx)
{
    std::string pfx1(pfx + "    ");
    std::string pfx2(pfx1 + "    ");
    ss << pfx << "EVENotificationStream:" << std::endl;
    if (remoteObject == 0)
    {
        if(remoteObjectStr.length() > 0)
        {
            ss << pfx1 << "Remote Object: " << remoteObjectStr << std::endl;
        }
        else
        {
            ss << pfx1 << "Remote Object: <empty string>" << std::endl;;
        }
    }
    else
    {
        ss << pfx1 << "Remote Object: " << remoteObject << std::endl;;
    }
    ss << pfx1 << "Arguments:" << std::endl;
    args->dump(ss, pfx2);
}

bool EVENotificationStream::Decode(const std::string &pkt_type, PyTuple *&in_payload)
{
    PyTuple *payload = in_payload;   //consume
    in_payload = NULL;

    PySafeDecRef(args);
    args = NULL;

    if(pkt_type != "macho.Notification")
    {
        codelog(NET__PACKET_ERROR, "notification payload has unknown string type %s", pkt_type.c_str());
        PyDecRef(payload);
        return false;
    }

    //decode payload tuple
    if(payload->items.size() != 2)
    {
        codelog(NET__PACKET_ERROR, "invalid tuple length %lu", payload->items.size());
        PyDecRef(payload);
        return false;
    }
    PyTuple *payload2;
    if(!pyIsAs(Tuple, payload->items[0], payload2))
    {
        codelog(NET__PACKET_ERROR, "non-tuple payload[0]");
        PyDecRef(payload);
        return false;
    }
    if(payload2->items.size() != 2)
    {
        codelog(NET__PACKET_ERROR, "invalid tuple2 length %lu", payload2->items.size());
        PyDecRef(payload);
        return false;
    }

    //decode inner payload tuple
    //ignore tuple 0, it should be an int, dont know what it is
    PySubStream *ss;
    if(!pyIsAs(SubStream, payload2->items[1], ss))
    {
        codelog(NET__PACKET_ERROR, "non-substream type");
        PyDecRef(payload);
        return false;
    }

    ss->DecodeData();
    if(ss->decoded() == NULL)
    {
        codelog(NET__PACKET_ERROR, "Unable to decode call stream");
        PyDecRef(payload);
        return false;
    }

    PyTuple *robjt;
    if(!pyIsAs(Tuple, ss->decoded(), robjt))
    {
        codelog(NET__PACKET_ERROR, "packet body does not contain a tuple");
        PyDecRef(payload);
        return false;
    }

    if(robjt->items.size() != 2)
    {
        codelog(NET__PACKET_ERROR, "packet body has %lu elements, expected %d", robjt->items.size(), 2);
        PyDecRef(payload);
        return false;
    }

    //parse first tuple element, remote object
    PyInt *tupleInt;
    PyString *tupleString;
    if(pyIsAs(Int, robjt->items[0], tupleInt))
    {
        remoteObject = tupleInt->value();
        remoteObjectStr = "";
    }
    else if(pyIsAs(String, robjt->items[0], tupleString))
    {
        remoteObject = 0;
        remoteObjectStr = tupleString->content();
    }
    else
    {
        codelog(NET__PACKET_ERROR, "main tuple[0] has invalid type %s", robjt->items[0]->TypeString());
        _log(NET__PACKET_ERROR, " in:");
        payload->Dump( NET__PACKET_ERROR, "" );
        PyDecRef(payload);
        return false;
    }

    PyTuple *subt;
    if(!pyIsAs(Tuple, robjt->items[1], subt))
    {
        codelog(NET__PACKET_ERROR, "main tuple[1] has non-tuple type %s", robjt->items[0]->TypeString());
        _log(NET__PACKET_ERROR, " it is:");
        payload->Dump( NET__PACKET_ERROR, "" );
        PyDecRef(payload);
        return false;
    }

    if(subt->items.size() != 2)
    {
        codelog(NET__PACKET_ERROR, "packet body has %lu elements, expected %d", subt->items.size(), 2);
        PyDecRef(payload);
        return false;
    }

    //parse first tuple element, remote object
    if(pyIs(Int, subt->items[0]))
    {
        //PyInt *tuple0 = pyAs(In, maint->items[0]);
        //no idea what this is.
    }
    else
    {
        codelog(NET__PACKET_ERROR, "sub tuple[0] has invalid type %s", subt->items[0]->TypeString());
        _log(NET__PACKET_ERROR, " in:");
        payload->Dump( NET__PACKET_ERROR, "" );
        PyDecRef(payload);
        return false;
    }

    if(!pyIsAs(Tuple, subt->items[1], args))
    {
        codelog(NET__PACKET_ERROR, "subt tuple[1] has non-tuple type %s", robjt->items[0]->TypeString());
        _log(NET__PACKET_ERROR, " it is:");
        payload->Dump( NET__PACKET_ERROR, "" );
        PyDecRef(payload);
        return false;
    }

    subt->items[1] = NULL;

    PyDecRef(payload);
    return true;
}

PyTuple *EVENotificationStream::Encode()
{

    PyTuple *t4 = new PyTuple(2);
    t4->items[0] = new PyInt(1);
    //see notes in other objects about what we could do to avoid this clone.
    t4->items[1] = args->Clone();

    PyTuple *t3 = new PyTuple(2);
    t3->items[0] = new PyInt(0);
    t3->items[1] = t4;

    PyTuple *t2 = new PyTuple(2);
    t2->items[0] = new PyInt(0);
    t2->items[1] = new PySubStream(t3);

    PyTuple *t1 = new PyTuple(2);
    t1->items[0] = t2;
    t1->items[1] = new PyNone();

    return(t1);
/*
    //remoteObject
    if(remoteObject == 0)
        arg_tuple->items[0] = new PyString(remoteObjectStr.c_str());
    else
        arg_tuple->items[0] = new PyInt(remoteObject);

    //method name
    arg_tuple->items[1] = new PyString(method.c_str());

    //args
    //TODO: we dont really need to clone this if we can figure out a way to say "this is read only"
    //or if we can change this encode method to consume the PyCallStream (which will almost always be the case)
    arg_tuple->items[2] = args->Clone();

    //options
    if(included_options == 0) {
        arg_tuple->items[3] = new PyNone();
    } else {
        PyDict *d = new PyDict();
        arg_tuple->items[3] = d;
        if(included_options & oMachoVersion) {
            d->items[ new PyString("machoVersion") ] = new PyInt( macho_version );
        }
    }
    return(arg_tuple);
    */
}
