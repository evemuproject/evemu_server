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

#ifndef __NET_UTILS_H__INCL__
#define __NET_UTILS_H__INCL__

#ifndef ERRBUF_SIZE
#   define ERRBUF_SIZE 1024
#endif

uint32  ResolveIP(const char* hostname, char* errbuf = 0);
//bool    ParseAddress(const char* iAddress, int32* oIP, int16* oPort, char* errbuf = 0);

#ifdef HAVE_WINSOCK2_H
class InitWinsock
{
public:
    InitWinsock()
    {
        WSADATA wsadata;
        WSAStartup( MAKEWORD( 1, 1 ), &wsadata );
    }
    ~InitWinsock()
    {
        WSACleanup();
    }
};
#endif /* !HAVE_WINSOCK2_H */

#endif /* !__NET_UTILS_H__INCL__ */
