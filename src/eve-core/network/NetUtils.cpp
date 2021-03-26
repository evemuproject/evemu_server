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

#include "eve-core.h"

#include "network/NetUtils.h"

uint32 ResolveIP(const char* hostname, char* errbuf) {
#ifdef HAVE_WINSOCK2_H
    static InitWinsock ws;
#endif /* !HAVE_WINSOCK2_H */
    if( errbuf )
        errbuf[0] = 0;

    if( hostname == NULL )
    {
        if( errbuf )
            snprintf(errbuf, ERRBUF_SIZE, "ResolveIP(): hostname == NULL");
        return 0;
    }

    hostent* phostent = gethostbyname( hostname );
    if( phostent == NULL)
    {
        if( errbuf )
#ifdef HAVE_WINSOCK2_H
            snprintf( errbuf, ERRBUF_SIZE, "Unable to get the host name. Error: %i", WSAGetLastError() );
#else /* !HAVE_WINSOCK2_H */
            snprintf( errbuf, ERRBUF_SIZE, "Unable to get the host name. Error: %s", strerror( errno ) );
#endif /* !HAVE_WINSOCK2_H */
        return 0;
    }

    in_addr addr;
    memcpy( &addr, phostent->h_addr, phostent->h_length );

    return addr.s_addr;
}

/*bool ParseAddress(const char* iAddress, int32* oIP, int16* oPort, char* errbuf) {
    Seperator sep(iAddress, ':', 2, 250, false, 0, 0);
    if (sep.argnum == 1 && sep.IsNumber(1)) {
        *oIP = ResolveIP(sep.arg[0], errbuf);
        if (*oIP == 0)
            return false;
        if (oPort)
            *oPort = atoi(sep.arg[1]);
        return true;
    }
    return false;
}*/

