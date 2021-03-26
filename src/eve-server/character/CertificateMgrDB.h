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

#ifndef __CERTIFICATE_MGR_DB__H__INCL__
#define __CERTIFICATE_MGR_DB__H__INCL__

#include "ServiceDB.h"

class PyRep;

class CertificateMgrDB
: public ServiceDB
{
public:
    PyRep *GetMyCertificates(uint32 characterID);
    PyRep *GetCertificateCategories();
    PyRep *GetAllShipCertificateRecommendations();
    PyRep *GetCertificateClasses();

    bool LoadCertificates( uint32 characterID, CertMap &into );
    bool SaveCertificates( uint32 characterID, const CertMap& from );
    void AddCertificate(uint32 charID, CharCerts cert);
    void UpdateCertificate(uint32 charID, uint32 certificateID, bool pub=false);

};

#endif /* __CERTIFICATE_MGR_DB__H__INCL__ */



