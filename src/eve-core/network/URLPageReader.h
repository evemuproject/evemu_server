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
    Author:        eve-moo
 */

#ifndef URLPAGEREADER_H
#define	URLPAGEREADER_H

#ifdef HAVE_WINSOCK2_H
#include <winsock2.h>
#else /* !HAVE_WINSOCK2_H */
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif /* !HAVE_WINSOCK2_H */

/**
 * Get a page of data from a url.
 * @param url The url of the server.
 * @param port The server port.
 * @param page The server page to get.
 * @param headerLines The location to store the response header lines.
 * @param out The page data.
 * @return True if successful.
 */
bool getPageFromURL(const std::string &url, const int port, const std::string &page, std::vector<std::string> &headerLines, std::vector<char> &out)
{
    // Create a socket.
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    // Resolve the hostname.
    hostent *ent;
    if((ent = gethostbyname(url.c_str())) == nullptr)
    {
        SysLog::Debug("URL Reader", "Cannot resolve URL: %s", url.c_str());
        // failed to connect.
        return false;
    }
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    memcpy(&server.sin_addr.s_addr, ent->h_addr, ent->h_length);

    // Connect to the server.
    if(connect(sock, (sockaddr*) & server, sizeof ( server)) == SOCKET_ERROR)
    {
        SysLog::Debug("URL Reader", "Cannot connect to fallback server: %u: %s", errno, strerror(errno));
        // failed to connect.
        return false;
    }
    // Check page format.
    std::string usePage = page;
    if(page.compare(0, 1, "/") != 0)
    {
        usePage = "/" + page;
    }
    // Formulate query.
    std::string query = "GET " + usePage + " HTTP/1.1\r\n";
    query += "Host: " + url + ":" + std::to_string(port) + "\r\n";
    query += "Connection: close\r\n";
    query += "\r\n";
    // Send the query.
    int status = send(sock, query.c_str(), query.size(), 0);
    if(status == SOCKET_ERROR)
    {
        SysLog::Debug("URL Reader", "cannot send image request: %s", strerror(errno));
        // failed to send request.
        return false;
    }
    std::vector<char> recieved;
    char buf[8192];
    // Read from the socket.
    int len = recv(sock, buf, 8192, 0);
    while(len > 0)
    {
        recieved.insert(recieved.end(), buf, buf + len);
        len = recv(sock, buf, 8192, 0);
    };
    // Close the socket.
    close(sock);

    // Find end of header.
    std::string in(recieved.begin(), recieved.end());
    int hEnd = in.find("\r\n\r\n");
    if(hEnd != -1)
    {
        hEnd += 2;
        in = in.substr(0, hEnd);
    }
    hEnd += 2;
    // Get output.
    out.insert(out.begin(), recieved.begin() + hEnd, recieved.end());
    // Clear the temp buffer.
    recieved.clear();
    // Find the individual header lines.
    int ll = 0;
    int nl = in.find("\r\n");
    while(nl != -1 && nl != ll)
    {
        headerLines.push_back(in.substr(ll, nl - ll));
        nl += 2;
        ll = nl;
        nl = in.find("\r\n", ll);
    }

    return true;
}

#endif	/* URLPAGEREADER_H */

