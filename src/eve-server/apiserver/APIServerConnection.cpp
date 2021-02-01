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
    Author:        Aknor Jaden, adapted from ImageServer.h authored by caytchen
*/

#include "eve-server.h"

#include "apiserver/APIServer.h"
#include "apiserver/APIServerConnection.h"

boost::asio::const_buffers_1 APIServerConnection::_responseOK = boost::asio::buffer("HTTP/1.0 200 OK\r\nContent-Type: text/xml\r\n\r\n", 43);
                                                        // The last parameter must be exactly the # of chars in the string, otherwise
                                                        // a browser will not recognize the xml structure and think the document is empty
                                                        // if the size is larger than this string.
//boost::asio::const_buffers_1 APIServerConnection::_responseNotFound = boost::asio::buffer("HTTP/1.0 404 - File or directory not found.\r\n\r\n", 26);
boost::asio::const_buffers_1 APIServerConnection::_responseRedirectBegin = boost::asio::buffer("HTTP/1.0 301 Moved Permanently\r\nLocation: ", 42);
boost::asio::const_buffers_1 APIServerConnection::_responseRedirectEnd = boost::asio::buffer("\r\n\r\n", 4);
boost::asio::const_buffers_1 APIServerConnection::_responseNoContent = boost::asio::buffer("HTTP/1.0 204 No Content", 23);
boost::asio::const_buffers_1 APIServerConnection::_responseNotFound = boost::asio::buffer(
"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">"
"<html xmlns=\"http://www.w3.org/1999/xhtml\">"
"<head>"
"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"/>"
"<title>404 - File or directory not found.</title>"
"<style type=\"text/css\">"
"<!--"
"body{margin:0;font-size:.7em;font-family:Verdana, Arial, Helvetica, sans-serif;background:#EEEEEE;}"
"fieldset{padding:0 15px 10px 15px;} "
"h1{font-size:2.4em;margin:0;color:#FFF;}"
"h2{font-size:1.7em;margin:0;color:#CC0000;} "
"h3{font-size:1.2em;margin:10px 0 0 0;color:#000000;} "
"#header{width:96%;margin:0 0 0 0;padding:6px 2% 6px 2%;font-family:\"trebuchet MS\", Verdana, sans-serif;color:#FFF;"
"background-color:#555555;}"
"#content{margin:0 0 0 2%;position:relative;}"
".content-container{background:#FFF;width:96%;margin-top:8px;padding:10px;position:relative;}"
"-->"
"</style>"
"</head>"
"<body>"
"<div id=\"header\"><h1>Server Error</h1></div>"
"<div id=\"content\">"
" <div class=\"content-container\"><fieldset>"
"  <h2>404 - File or directory not found.</h2>"
"  <h3>The resource you are looking for might have been removed, had its name changed, or is temporarily unavailable.</h3>"
" </fieldset></div>"
"</div>"
"</body>"
"</html>"
, 1187);

APIServerConnection::APIServerConnection(boost::asio::io_context& io)
    : _socket(io)
{
}

boost::asio::ip::tcp::socket& APIServerConnection::socket()
{
    return _socket;
}

void APIServerConnection::Process()
{
    // receive all HTTP headers from the client
    boost::asio::async_read_until(_socket, _buffer, "\r\n\r\n", std::bind(&APIServerConnection::ProcessHeaders, shared_from_this()));
}

void APIServerConnection::ProcessHeaders()
{
    std::istream stream(&_buffer);
    std::string query;
    std::string request;
    std::string get_chk_str;
    std::string post_chk_str;
    int pos;
    int parameterCount;
    std::string param;
    std::string value;

    // Clear API Command Call container:
    m_apiCommandCall.clear();

    // Get the first header line, every request line ends with "\r\n"
    // GET /service/ServiceHandler.xml.aspx?param1=value&param2=value&param3=value HTTP/1.0\r\n
    // POST /service/ServiceHandler.xml.aspx HTTP/1.0\r\n
    std::getline(stream, request, '\r');
    query = request;

    get_chk_str = request.substr(0,3);
    post_chk_str = request.substr(0,4);

    if (get_chk_str.compare("GET") == 0)
    {
        sLog.Debug( "APIServerConnection::ProcessHeaders()", "RECEIVED new HTTP GET request..." );

        // Format of an HTTP GET query:
        // 0    5     10          20
        // GET /service/ServiceHandler.xml.aspx?param1=value&param2=value&param3=value HTTP/1.0\r\n
        _http_cmd_str = get_chk_str;

        request = request.substr(4);    // Strip off the "GET " prefix

        // Find first space at end of header, if there is one, and strip off the rest of the line, ie the " HTTP/1.0\r\n" string
        int del = request.find_first_of(' ');
        if (del == std::string::npos)
        {
            NotFound();
            return;
        }
        request = request.substr(0,del);

        if (!starts_with(request, "/"))
        {
            NotFound();
            return;
        }
        request = request.substr(1);

        pos = request.find_first_of('/');
        _service = request.substr(0,pos);
        m_apiCommandCall.insert( std::pair<std::string, std::string>( "service", _service ) );
        request = request.substr(pos+1);
        pos = request.find_first_of('?');
        _service_handler = request.substr(0,pos);
        m_apiCommandCall.insert( std::pair<std::string, std::string>( "servicehandler", _service_handler ) );
        request = request.substr(pos+1);

        //// DUPLICATE
        // Parse the query portion of the GET to a series of string pairs ("param", "value") from the URI
        while( (pos = request.find_first_of('=')) >= 0 )
        {
            param = request.substr(0,pos);
            std::transform(param.begin(), param.end(), param.begin(), tolower);
            request = request.substr(pos+1);
            pos = request.find_first_of('&');
            if( pos < 0 )
                value = request;
            else
            {
                value = request.substr(0,pos);
                request = request.substr(pos);
                if( request.substr(0,5) == "&amp;" )  // Strip out "&amp;" encoded for "&"
                    request = request.substr(5);
                else
                    request = request.substr(1);
            }
            m_apiCommandCall.insert( std::pair<std::string, std::string>( param, value ) );
        }

        _xmlData = sAPIServer.GetXML(&m_apiCommandCall);
        if (!_xmlData)
        {
            sLog.Error("APIServerConnection::ProcessHeaders()", "Unknown or malformed EVEmu API HTTP CMD Received:\r\n%s\r\n", query.c_str());
            NotFound();
            return;
        }

        // Print out to the Log with basic info on the API call and all parameters and their values parsed out
        sLog.Debug("APIServerConnection::ProcessHeaders()", "HTTP %s CMD Received: Service: %s, Handler: %s", _http_cmd_str.c_str(), _service.c_str(), _service_handler.c_str());
        APICommandCall::const_iterator cur, end;
        cur = m_apiCommandCall.begin();
        end = m_apiCommandCall.end();
        for (int i=1; cur != end; cur++, i++)
            sLog.Debug("        ", "%d: param = %s,  value = %s", i, cur->first.c_str(), cur->second.c_str() );

        // first we have to send the responseOK, then our actual result
        boost::asio::async_write(_socket, _responseOK, boost::asio::transfer_all(), std::bind(&APIServerConnection::SendXML, shared_from_this()));
        //// DUPLICATE
    }
    else if (post_chk_str.compare("POST") == 0)
    {
        sLog.Debug( "APIServerConnection::ProcessHeaders()", "RECEIVED new HTTP POST request..." );

        // Format of an HTTP GET query:
        //
        // POST /service/ServiceHandler.xml.aspx HTTP/1.0\r\n
        // Content-Type: application/x-www-form-urlencoded\r\n
        // Host: api.eve-online.com\r\n
        // Content-Length: 86\r\n
        // \r\n
        // param1=value&param2=value&param3=value\r\n
        // \r\n

        _http_cmd_str = post_chk_str;

        request = request.substr(5);    // Strip off the "POST " prefix

        // Find first space at end of header, if there is one, and strip off the rest of the line, ie the " HTTP/1.0\r\n" string
        int del = request.find_first_of(' ');
        if (del == std::string::npos)
        {
            NotFound();
            return;
        }
        request = request.substr(0,del);

        if (!starts_with(request, "/"))
        {
            NotFound();
            return;
        }
        request = request.substr(1);

        pos = request.find_first_of('/');
        _service = request.substr(0,pos);
        m_apiCommandCall.insert( std::pair<std::string, std::string>( "service", _service ) );
        request = request.substr(pos+1);
        _service_handler = request;
        m_apiCommandCall.insert( std::pair<std::string, std::string>( "servicehandler", _service_handler ) );

        // Read the integer after 'Content-Length:' and use that as the # of bytes in the next step
        while( (request.substr( 0,15 ).compare( "Content-Length:" )) != 0 )
        {
            std::getline(stream, request, '\r');
            request = request.substr(1);
            query += request;
        }
        pos = request.find_first_of(' ');
        request = request.substr( pos+1 );
        uint32 postDataBytes = atoi( request.c_str() );
        std::getline(stream, request, '\n');

        sLog.Debug( "APIServerConnection::ProcessHeaders()", "    POST Content-Length = %u bytes", postDataBytes );

        // Keep reading lines until we get past the next "\r\n" line (blank line):
        while( request.compare( "\r" ) != 0 )
        {
            std::getline(stream, request, '\n');
        }

        std::getline(stream, request, '\n');
        pos = request.find_first_of('\r');
        request = request.substr( 0,pos );

        if( request.compare( "" ) != 0 )
        {
            // Decode the arguments of the POST data block here since asio did NOT stop reading past the first "\r\n\r\n"
            //// DUPLICATE
            // Parse the query portion of the GET to a series of string pairs ("param", "value") from the URI
            sLog.Debug( "APIServerConnection::ProcessHeaders()", "POST data found in ProcessHeaders() !  Parsing..." );
            parameterCount = 0;
            while( (pos = request.find_first_of('=')) >= 0 )
            {
                parameterCount++;
                param = request.substr(0,pos);
                std::transform(param.begin(), param.end(), param.begin(), tolower);
                request = request.substr(pos+1);
                pos = request.find_first_of('&');
                if( pos < 0 )
                    value = request;
                else
                {
                    value = request.substr(0,pos);
                    request = request.substr(pos);
                    if( request.substr(0,5) == "&amp;" )  // Strip out "&amp;" encoded for "&"
                        request = request.substr(5);
                    else
                        request = request.substr(1);
                }
                m_apiCommandCall.insert( std::pair<std::string, std::string>( param, value ) );
            }

            // Did we somehow not detect a lack of POST data?  If so, and NO parameters were recovered, queue up the trigger for PostProcessHeaders():
            if( parameterCount == 0 )
            {
                // Call boost::asio::async_read() and feed it the # of bytes from step 1) to get the POST data
                // The 'CompleteCondition' for THIS boost::asio::async_read, a parameter that specifies when to stop reading,
                // is transfer_exactly(contentLength), where contentLength is the # of bytes we just recovered from the "Content-Length" header
                boost::asio::async_read(_socket, _postBuffer, boost::asio::transfer_exactly(postDataBytes), std::bind(&APIServerConnection::ProcessPostData, shared_from_this()));
            }

            _xmlData = sAPIServer.GetXML(&m_apiCommandCall);
            if (!_xmlData)
            {
                sLog.Error("APIServerConnection::ProcessHeaders()", "Unknown or malformed EVEmu API HTTP CMD Received:\r\n%s\r\n", query.c_str());
                NotFound();
                return;
            }

            // Print out to the Log with basic info on the API call and all parameters and their values parsed out
            sLog.Debug("APIServerConnection::ProcessHeaders()", "HTTP %s CMD Received: Service: %s, Handler: %s", _http_cmd_str.c_str(), _service.c_str(), _service_handler.c_str());
            APICommandCall::const_iterator cur, end;
            cur = m_apiCommandCall.begin();
            end = m_apiCommandCall.end();
            for (int i=1; cur != end; cur++, i++)
                sLog.Debug("        ", "%d: param = %s,  value = %s", i, cur->first.c_str(), cur->second.c_str() );

            // first we have to send the responseOK, then our actual result
            boost::asio::async_write(_socket, _responseOK, boost::asio::transfer_all(), std::bind(&APIServerConnection::SendXML, shared_from_this()));
            //// DUPLICATE
        }
        else
        {
            // Call boost::asio::async_read() and feed it the # of bytes from step 1) to get the POST data
            // The 'CompleteCondition' for THIS boost::asio::async_read, a parameter that specifies when to stop reading,
            // is transfer_exactly(contentLength), where contentLength is the # of bytes we just recovered from the "Content-Length" header
            boost::asio::async_read(_socket, _postBuffer, boost::asio::transfer_exactly(postDataBytes), std::bind(&APIServerConnection::ProcessPostData, shared_from_this()));
        }
    }
    else
    {
        NotFound();
        return;
    }
}

void APIServerConnection::ProcessPostData()
{
    std::istream stream(&_postBuffer);
    std::string query;
    std::string request;
    int pos;
    std::string param;
    std::string value;

    std::getline(stream, request, '\r');

    // Check for empty POST data block, and if empty, return without sending anything back:
    if( request.compare( "" ) == 0 )
    {
        sLog.Error("APIServerConnection::ProcessPostData()", "POST data block is COMPLETELY EMPTY!!" );
        boost::asio::async_write(_socket, _responseNoContent, boost::asio::transfer_all(), std::bind(&APIServerConnection::Close, shared_from_this()));
        //NotFound();
        return;
    }

    _http_cmd_str += request;

    // Parse the data portion of the POST to a series of string pairs ("param", "value") from the URI
    while( (pos = request.find_first_of('=')) >= 0 )
    {
        param = request.substr(0,pos);
        std::transform(param.begin(), param.end(), param.begin(), tolower);
        request = request.substr(pos+1);
        pos = request.find_first_of('&');
        if( pos < 0 )
            value = request;
        else
        {
            value = request.substr(0,pos);
            request = request.substr(pos);
            if( request.substr(0,5) == "&amp;" )  // Strip out "&amp;" encoded for "&"
                request = request.substr(5);
            else
                request = request.substr(1);
        }
        m_apiCommandCall.insert( std::pair<std::string, std::string>( param, value ) );
    }

    _xmlData = sAPIServer.GetXML(&m_apiCommandCall);
    if (!_xmlData)
    {
        sLog.Error("APIServerConnection::ProcessPostData()", "Unknown or malformed EVEmu API HTTP CMD Received:\r\n%s\r\n", query.c_str());
        NotFound();
        return;
    }

    // Print out to the Log with basic info on the API call and all parameters and their values parsed out
    sLog.Debug("APIServerConnection::ProcessPostData()", "HTTP %s CMD Received: Service: %s, Handler: %s", _http_cmd_str.c_str(), _service.c_str(), _service_handler.c_str());
    APICommandCall::const_iterator cur, end;
    cur = m_apiCommandCall.begin();
    end = m_apiCommandCall.end();
    for (int i=1; cur != end; cur++, i++)
        sLog.Debug("        ", "%d: param = %s,  value = %s", i, cur->first.c_str(), cur->second.c_str() );

    // first we have to send the responseOK, then our actual result
    boost::asio::async_write(_socket, _responseOK, boost::asio::transfer_all(), std::bind(&APIServerConnection::SendXML, shared_from_this()));
}

void APIServerConnection::SendXML()
{
    boost::asio::async_write(_socket, boost::asio::buffer(*_xmlData, _xmlData->size()), boost::asio::transfer_all(), std::bind(&APIServerConnection::Close, shared_from_this()));
}

void APIServerConnection::NotFound()
{
    boost::asio::async_write(_socket, _responseNotFound, boost::asio::transfer_all(), std::bind(&APIServerConnection::Close, shared_from_this()));
}

void APIServerConnection::Redirect()
{
    boost::asio::async_write(_socket, _responseRedirectBegin, boost::asio::transfer_all(), std::bind(&APIServerConnection::RedirectLocation, shared_from_this()));
}

void APIServerConnection::RedirectLocation()
{
    //std::string extension = _service == "Character" ? "jpg" : "png";
    std::stringstream url;
    url << APIServer::FallbackURL << _service;// << "/" << _id;
    _redirectUrl = url.str();
    boost::asio::async_write(_socket, boost::asio::buffer(_redirectUrl), boost::asio::transfer_all(), std::bind(&APIServerConnection::RedirectFinalize, shared_from_this()));
}

void APIServerConnection::RedirectFinalize()
{
    boost::asio::async_write(_socket, _responseRedirectEnd, boost::asio::transfer_all(), std::bind(&APIServerConnection::Close, shared_from_this()));
}

void APIServerConnection::Close()
{
    _socket.close();
}

bool APIServerConnection::starts_with(std::string& haystack, const char *const needle)
{
    return haystack.substr(0, strlen(needle)).compare(needle) == 0;
}

std::tr1::shared_ptr<APIServerConnection> APIServerConnection::create(boost::asio::io_context& io)
{
    return std::tr1::shared_ptr<APIServerConnection>(new APIServerConnection(io));
}
