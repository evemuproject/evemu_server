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
    Author:     eve-moo
*/

#include "eve-common.h"

#include "marshal/EVEMarshal.h"
#include "marshal/EVEUnmarshal.h"
#include "marshal/EVEMarshalOpcodes.h"
#include "python/classes/PyDatabase.h"
#include "python/PyVisitor.h"
#include "python/PyRep.h"
#include "utils/EVEUtils.h"
#include "utils/utfUtils.h"

#include <iomanip>

void PyRep::Dump( const LogType &type, const char* pfx ) const
{
    std::string lpfx = getLogPrefix(type);
    lpfx += pfx;
    std::ostringstream ss;
    dump(ss, lpfx);
    outputLogMsg(type, ss.str().c_str());
}

void PyRep::dump(std::ostringstream &ss, const std::string &pfx) const
{
    ss << pfx << "[PyRep]" << std::endl;
}

void PyInt::dump(std::ostringstream &ss, const std::string &pfx) const
{
    ss << pfx << "[PyInt " << mValue << "]" << std::endl;
}

void PyLong::dump(std::ostringstream &ss, const std::string &pfx) const
{
    ss << pfx << "[PyLong " << mValue << "]" << std::endl;
}

void PyFloat::dump(std::ostringstream &ss, const std::string &pfx) const
{
    ss << pfx << "[PyFloat " << mValue << "]" << std::endl;
}

void PyBool::dump(std::ostringstream &ss, const std::string &pfx) const
{
    ss << pfx << "[PyBool " << (mValue ? "True" : "False") << "]" << std::endl;
}

void PyNone::dump(std::ostringstream &ss, const std::string &pfx) const
{
    ss << pfx << "[PyNone]" << std::endl;
}

void PyBuffer::dump(std::ostringstream &ss, const std::string &pfx) const
{
    std::string pfx1(pfx +   "    ");
    ss << pfx << "[PyBuffer Length= ";
    if(mValue == nullptr)
    {
        ss << "0 <empty>]" << std::endl;
        return;
    }
    ss << mValue->size() << std::endl;
    const Buffer &buf = *mValue;
    if(buf[0] == MarshalHeaderByte || buf[0] == DeflateHeaderByte)
    {
        PyRep *un = InflateUnmarshal(buf);
        if(un != nullptr)
        {
            un->dump(ss, pfx1);
        }
        else
        {
            ss << pfx1 << "<unmarshal fail>" << std::endl;
        }
    }
    else
    {
        pfxHexDumpPreview( pfx1, ss, &buf[0], buf.size() );
    }
    ss << pfx << "]" << std::endl;
}

void PyString::dump(std::ostringstream &ss, const std::string &pfx) const
{
    if(mValue[0] == MarshalHeaderByte || mValue[0] == DeflateHeaderByte)
    {
        PyString *val = new PyString(mValue);
        PyBuffer *buf = new PyBuffer(*val);
        PyRep *un = InflateUnmarshal(buf->content());
        PySafeDecRef(buf);
        if(un != nullptr)
        {
            std::string pfx1(pfx +   "    ");
            ss << pfx << "[PyString <serialized>" << std::endl;
            un->dump(ss, pfx1);
            ss << pfx << "]" << std::endl;
            return;
        }
    }
    if( IsPrintable( mValue ) )
    {
        ss << pfx << "[PyString '" << mValue << "']" << std::endl;
    }
    else
    {
        std::string pfx1(pfx +   "    ");
        ss << pfx << "[PyString <binary, len=" << mValue.size() << ">" << std::endl;
        pfxHexDumpPreview( pfx1, ss, (uint8 *)mValue.c_str(), mValue.size() );
        ss << pfx << "]" << std::endl;
    }
}

void PyWString::dump(std::ostringstream &ss, const std::string &pfx) const
{
    if(mValue[0] == MarshalHeaderByte || mValue[0] == DeflateHeaderByte)
    {
        PyString *val = new PyString(mValue);
        PyBuffer *buf = new PyBuffer(*val);
        PyRep *un = InflateUnmarshal(buf->content());
        PySafeDecRef(buf);
        if(un != nullptr)
        {
            std::string pfx1(pfx +   "    ");
            ss << pfx << "[PyWString <serialized>" << std::endl;
            un->dump(ss, pfx1);
            ss << pfx << "]" << std::endl;
            return;
        }
    }
    if( IsPrintable( mValue ) )
    {
        ss << pfx << "[PyWString '" << mValue << "']" << std::endl;
    }
    else
    {
        std::string pfx1(pfx +   "    ");
        ss << pfx << "[PyWString <binary, len=" << mValue.size() << ">" << std::endl;
        pfxHexDumpPreview( pfx1, ss, (uint8 *)mValue.c_str(), mValue.size() );
        ss << pfx << "]" << std::endl;
    }
}

void PyToken::dump(std::ostringstream &ss, const std::string &pfx) const
{
    ss << pfx << "[PyToken '" << mValue << "']" << std::endl;
}

void PyTuple::dump(std::ostringstream &ss, const std::string &pfx) const
{
    ss << pfx << "[PyTuple length=" << items.size() << "]" << std::endl;
    std::string pfx1(pfx + "    ");
    for(PyRep *rep : items)
    {
        if(rep != nullptr)
        {
            rep->dump(ss, pfx1);
        }
        else
        {
            ss << pfx1 << "<nullptr>" << std::endl;
        }
    }
}

void PyList::dump(std::ostringstream &ss, const std::string &pfx) const
{
    ss << pfx << "[PyList length=" << items.size() << "]" << std::endl;
    std::string pfx1(pfx + "    ");
    for(PyRep *rep : items)
    {
        if(rep != nullptr)
        {
            rep->dump(ss, pfx1);
        }
        else
        {
            ss << pfx1 << "<nullptr>" << std::endl;
        }
    }
}

void PyDict::dump(std::ostringstream &ss, const std::string &pfx) const
{
    ss << pfx << "[PyDict length=" << items.size() << "]" << std::endl;
    std::string pfx_key(pfx +   "    Key: ");
    std::string pfx_value(pfx + "    ==Value: ");
    for(auto entry : items)
    {
        PyRep *key = entry.first;
        PyRep *value = entry.second;
        if(key != nullptr)
        {
            key->dump(ss, pfx_key);
        }
        else
        {
            ss << pfx_key << "<nullptr>" << std::endl;
        }
        if(value != nullptr)
        {
            value->dump(ss, pfx_value);
        }
        else
        {
            ss << pfx_key << "<nullptr>" << std::endl;
        }
    }
}

void PyObject::dump(std::ostringstream &ss, const std::string &pfx) const
{
    ss << pfx << "[PyObject]" << std::endl;
    std::string pfx1(pfx +   "    ");
    std::string pfx2(pfx1 +   "    ");
    if(mType != nullptr)
    {
        ss << pfx1 << "Type='" << mType->content() << "'" << std::endl;
    }
    else
    {
        ss << pfx1 << "Type=<nullptr>" << std::endl;
    }
    if(mArguments != nullptr)
    {
        ss << pfx1 << "Arguments:" << std::endl;
        mArguments->dump(ss, pfx2);
    }
    else
    {
        ss << pfx1 << "Arguments: <nullptr>" << std::endl;
    }
}

void PyObjectEx::dump(std::ostringstream &ss, const std::string &pfx) const
{
    std::string pfx1(pfx +   "    ");
    std::string pfx2(pfx1 +   "    ");
//    PyToken *token = nullptr;
//    if(mHeader != nullptr && mHeader->IsTuple())
//    {
//        PyTuple *headerTuple = mHeader->AsTuple();
//        if(headerTuple->items.size() > 0)
//        {
//            PyRep *t = headerTuple->items[0];
//            if(t != nullptr && t->IsTuple())
//            {
//                if(t->AsTuple()->items.size() > 0)
//                {
//                    t = t->AsTuple()->items[0];
//                }
//            }
//            if(t != nullptr && t->IsToken())
//            {
//                token = t->AsToken();
//            }
//        }
//    }
    if(isType2())
    {
        ss << pfx << "[PyObjectEx Type2]" << std::endl;
    }
    else
    {
        ss << pfx << "[PyObjectEx Normal]" << std::endl;
    }
    if(mHeader == nullptr)
    {
        ss << pfx1 << "Header: <nullptr>" << std::endl;
    }
    else
    {
        ss << pfx1 << "Header:" << std::endl;
        mHeader->dump(ss, pfx2);
    }
    if(mList != nullptr)
    {
        ss << pfx1 << "List Data:" << std::endl;
        for(PyRep *rep : mList->items)
        {
            if(rep != nullptr)
            {
                rep->dump(ss, pfx1);
            }
            else
            {
                ss << pfx2 << "<nullptr>" << std::endl;
            }
        }
    }
    else
    {
        ss << pfx1 << "List Data: <nullptr>" << std::endl;
    }
    if(mDict != nullptr)
    {
        ss << pfx1 << "Dictionary:" << std::endl;
        std::string pfx_key(pfx1 +   "    Key: ");
        std::string pfx_value(pfx1 + "    ==Value: ");
        for(auto entry : mDict->items)
        {
            PyRep *key = entry.first;
            PyRep *value = entry.second;
            if(key != nullptr)
            {
                key->dump(ss, pfx_key);
            }
            else
            {
                ss << pfx_key << "<nullptr>" << std::endl;
            }
            if(value != nullptr)
            {
                value->dump(ss, pfx_value);
            }
            else
            {
                ss << pfx_key << "<nullptr>" << std::endl;
            }
        }
    }
    else
    {
        ss << pfx1 << "Dictonary: <nullptr>" << std::endl;
    }
}

void PyPackedRow::dump(std::ostringstream &ss, const std::string &pfx) const
{
    std::string pfx1(pfx +   "    ");
    std::string pfx2(pfx1 +   "    ");
    if(mHeader == nullptr)
    {
        ss << pfx << "[PyPackedRow columns=<nullptr>]" << std::endl;
        if(mFields == nullptr)
        {
            ss << pfx1 << "Rows: <nullptr>" << std::endl;
        }
        else
        {
            ss << pfx1 << "Rows:" << std::endl;
            mFields->dump(ss, pfx2);
        }
    }
    else
    {
        ss << pfx << "[PyPackedRow columns=" << mHeader->ColumnCount() << "]" << std::endl;
        if(mFields == nullptr)
        {
            ss << pfx1 << "Rows: <nullptr>" << std::endl;
        }
        else
        {
            int i = 0;
            for(PyRep *rep : mFields->items)
            {
                ss << pfx1;
                ss << "['" << mHeader->GetColumnName(i)->content() << "' =>";
                DBTYPE dbType = mHeader->GetColumnType(i);
                auto dbFind = DBTYPE_NAME.find(dbType);
                if(dbFind != DBTYPE_NAME.end())
                {
                    // Output the type string.
                    std::string dbTypeName = dbFind->second;
                    ss << " [" << dbTypeName << "] ";
                }
                else
                {
                    // No type string found output hex value.
                    ss << " [0x" << std::hex << std::setw(2) << std::setfill('0') << mHeader->GetColumnType(i) << "] ";
                }
                if(rep != nullptr)
                {
                    rep->dump(ss, "");
                }
                else
                {
                    ss << "<nullptr>" << std::endl;
                }
                i++;
            }
        }
    }
}

void PySubStruct::dump(std::ostringstream &ss, const std::string &pfx) const
{
    std::string pfx1(pfx + "    ");
    ss << pfx << "[PySubStruct]" << std::endl;
    if(mSub == nullptr)
    {
        ss << pfx1 << "<nullptr>" << std::endl;
    }
    else
    {
        mSub->dump(ss, pfx1);
    }
}

void PySubStream::dump(std::ostringstream &ss, const std::string &pfx) const
{
    std::string pfx1(pfx + "    ");
    if(mDecoded != nullptr)
    {
        ss << pfx << "[PySubStream from rep]" << std::endl;
        mDecoded->dump(ss, pfx1);
    }
    else if(mData != nullptr)
    {
        ss << pfx << "[PySubStream from data]" << std::endl;
        mData->dump(ss, pfx1);
    }
    else
    {
        ss << pfx << "[PySubStream <empty]" << std::endl;
    }
}

void PyChecksumedStream::dump(std::ostringstream &ss, const std::string &pfx) const
{
    std::string pfx1(pfx + "    ");
    ss << pfx << "[PyChecksumedStream checksum=0x]";
    ss << "0x" << std::hex << std::setw(8) << std::setfill('0') << mChecksum;
    ss << std::endl;
    if(mStream != nullptr)
    {
        mStream->dump(ss, pfx1);
    }
    else
    {
        ss << pfx1 << "<nullptr>" << std::endl;
    }
}

void BuiltinSet::dump(std::ostringstream &ss, const std::string &pfx) const
{
    std::string pfx1(pfx + "    ");
    ss << "[BuiltinSet]" << std::endl;
    for(auto obj : values->items)
    {
        obj->dump(ss, pfx1);
    }
}

void DefaultDict::dump(std::ostringstream &ss, const std::string &pfx) const
{
    std::string pfx1(pfx + "    ");
    std::string pfx2(pfx1 + "    ");
    ss << "[DefaultDict]" << std::endl;
    PyDict *kWords = GetKeywords();
    if(kWords != nullptr)
    {
        ss << pfx1 << "Keywords:" << std::endl;
        kWords->dump(ss, pfx2);
    }
}
