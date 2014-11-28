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
    Author:     Zhur
*/

#include "eve-core.h"

#include <chrono>

#include "utils/utils_time.h"

const uint64 Win32Time_Second = 10000000L;
const uint64 Win32Time_Minute = Win32Time_Second*60;
const uint64 Win32Time_Hour = Win32Time_Minute*60;
const uint64 Win32Time_Day = Win32Time_Hour*24;
const uint64 Win32Time_Month = Win32Time_Day*30;
const uint64 Win32Time_Year = Win32Time_Month*12;

static const uint64 SECS_BETWEEN_EPOCHS = 11644473600LL;
static const uint64 SECS_TO_100NS = 10000000; // 10^7

uint64 UnixTimeToWin32Time( time_t sec, uint32 nsec ) {
    return(
        (((uint64) sec) + SECS_BETWEEN_EPOCHS) * SECS_TO_100NS
        + (nsec / 100)
    );
}

void Win32TimeToUnixTime( uint64 win32t, time_t &unix_time, uint32 &nsec ) {
    win32t -= (SECS_BETWEEN_EPOCHS * SECS_TO_100NS);
    nsec = (win32t % SECS_TO_100NS) * 100;
    win32t /= SECS_TO_100NS;
    unix_time = win32t;
}

std::string Win32TimeToString(uint64 win32t) {
    time_t unix_time;
    uint32 nsec;
    Win32TimeToUnixTime(win32t, unix_time, nsec);

    char buf[256];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&unix_time));

    return(buf);
}

uint64 Win32TimeNow() {
#ifdef HAVE_WINDOWS_H
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    return((uint64(ft.dwHighDateTime) << 32) | uint64(ft.dwLowDateTime));
#else /* !HAVE_WINDOWS_H */
    return(UnixTimeToWin32Time(time(NULL), 0));
#endif /* !HAVE_WINDOWS_H */
}

double GetTimeMSeconds() {
    /*  higher resolution times....the 'GetTimeSeconds' defined above with interger resolution suxs for
     *  speed/time data manipulation
     *
     * win32timenow returns tenths resolution.
     * 1305821829.40000000
     *
     * resolution of double will give 1 ten-millionth precision (5 places, or 1/100000)
     *   using milliseconds should be high enough for warp distance calculations
     */

    // WINDOWS USERS......this should get ms precision, but i have no way to test it.

    //  NOTE  std::chrono and system_clock::now() require C++11
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();     // return in nanoseconds
    double millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    millis /= 1000;
    return (millis);
}
