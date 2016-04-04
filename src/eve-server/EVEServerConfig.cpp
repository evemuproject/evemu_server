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
    Author:     Zhur, Bloody.Rabbit
 */

#include "eve-server.h"

#include "EVEServerConfig.h"

EVEServerConfig::EVEConfigRates EVEServerConfig::rates;
EVEServerConfig::EVEConfigAccount EVEServerConfig::account;
EVEServerConfig::EVEConfigCharacter EVEServerConfig::character;
EVEServerConfig::EVEConfigDatabase EVEServerConfig::database;
EVEServerConfig::EVEConfigFiles EVEServerConfig::files;
EVEServerConfig::EVEConfigNet EVEServerConfig::net;

/*************************************************************************/
/* EVEServerConfig                                                       */

/*************************************************************************/
EVEServerConfig::EVEServerConfig()
{
    // Set sane defaults

    // rates
    rates.skillRate = 1.0;
    rates.npcBountyMultiply = 1.0;
    rates.secRate = 1.0;
    rates.corporationStartupCost = 1599800;

    // account
    account.autoAccountRole = 0;
    account.loginMessage = "";

    // character
    character.startBalance = 6666000000.0f;
    character.startStation = 0;
    character.startSecRating = 0.0;
    character.startCorporation = 0;
    character.terminationDelay = 90 /*s*/;

    // database
    database.host = "localhost";
    database.port = 3306;
    database.username = "eve";
    database.password = "eve";
    database.db = "evemu";

    // files
    files.logDir = "../log/";
    files.logSettings = "../etc/log.ini";
    files.cacheDir = "../server_cache/";
    files.imageDir = "../image_cache/";

    // net
    net.port = 26000;
    net.imageServer = "localhost";
    net.imageServerPort = 26001;
    net.apiServer = "localhost";
    net.apiServerPort = 64;
}

bool EVEServerConfig::ParseFile(const char *file)
{
    auto doc = XMLDocument::loadFile(file);
    auto root = doc->getRoot();
    for (auto member : root->getChildren())
    {
        std::string name = member->getName();
        if (name == "rates")
        {
            ProcessRates(member);
        }
        if (name == "account")
        {
            ProcessAccount(member);
        }
        if (name == "character")
        {
            ProcessCharacter(member);
        }
        if (name == "database")
        {
            ProcessDatabase(member);
        }
        if (name == "files")
        {
            ProcessFiles(member);
        }
        if (name == "net")
        {
            ProcessNet(member);
        }
    }

    return true;
}

bool EVEServerConfig::ProcessRates(const std::shared_ptr<XMLElement> ele)
{
    for (auto value : ele->getChildren())
    {
        if (value->getName() == "skillRate")
        {
            rates.skillRate = std::stof(value->getValue());
        }
        if (value->getName() == "secRate")
        {
            rates.secRate = std::stof(value->getValue());
        }
        if (value->getName() == "npcBountyMultiply")
        {
            rates.npcBountyMultiply = std::stof(value->getValue());
        }
        if (value->getName() == "corporationStartupCost")
        {
            rates.corporationStartupCost = std::stod(value->getValue());
        }
    }

    return true;
}

bool EVEServerConfig::ProcessAccount(const std::shared_ptr<XMLElement> ele)
{
    for (auto value : ele->getChildren())
    {
        if (value->getName() == "autoAccountRole")
        {
            account.autoAccountRole = std::stol(value->getValue());
        }
        if (value->getName() == "loginMessage")
        {
            account.loginMessage = value->getValue();
        }
    }

    return true;
}

bool EVEServerConfig::ProcessCharacter(const std::shared_ptr<XMLElement> ele)
{
    for (auto value : ele->getChildren())
    {
        if (value->getName() == "startBalance")
        {
            character.startBalance = std::stod(value->getValue());
        }
        if (value->getName() == "startStation")
        {
            character.startStation = std::stoi(value->getValue());
        }
        if (value->getName() == "startSecRating")
        {
            character.startSecRating = std::stod(value->getValue());
        }
        if (value->getName() == "startCorporation")
        {
            character.startCorporation = std::stoi(value->getValue());
        }
        if (value->getName() == "terminationDelay")
        {
            character.terminationDelay = std::stoi(value->getValue());
        }
    }

    return true;
}

bool EVEServerConfig::ProcessDatabase(const std::shared_ptr<XMLElement> ele)
{
    for (auto value : ele->getChildren())
    {
        if (value->getName() == "host")
        {
            database.host = value->getValue();
        }
        if (value->getName() == "port")
        {
            database.port = std::stoi(value->getValue());
        }
        if (value->getName() == "username")
        {
            database.username = value->getValue();
        }
        if (value->getName() == "password")
        {
            database.password = value->getValue();
        }
        if (value->getName() == "db")
        {
            database.db = value->getValue();
        }
    }
    return true;
}

bool EVEServerConfig::ProcessFiles(const std::shared_ptr<XMLElement> ele)
{
    for (auto value : ele->getChildren())
    {
        if (value->getName() == "logDir")
        {
            files.logDir = value->getValue();
        }
        if (value->getName() == "logSettings")
        {
            files.logSettings = value->getValue();
        }
        if (value->getName() == "cacheDir")
        {
            files.cacheDir = value->getValue();
        }
        if (value->getName() == "imageDir")
        {
            files.imageDir = value->getValue();
        }
    }
    return true;
}

bool EVEServerConfig::ProcessNet(const std::shared_ptr<XMLElement> ele)
{
    for (auto value : ele->getChildren())
    {
        if (value->getName() == "port")
        {
            net.port = std::stoi(value->getValue());
        }
        if (value->getName() == "imageServerPort")
        {
            net.imageServerPort = std::stoi(value->getValue());
        }
        if (value->getName() == "imageServer")
        {
            net.imageServer = value->getValue();
        }
        if (value->getName() == "apiServerPort")
        {
            net.apiServerPort = std::stoi(value->getValue());
        }
        if (value->getName() == "apiServer")
        {
            net.apiServer = value->getValue();
        }
    }
    return true;
}
