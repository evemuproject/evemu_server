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
    Author:        Luck
*/

#ifndef ACTIVE_MODULE_PROCESSING_COMPONENT_H
#define ACTIVE_MODULE_PROCESSING_COMPONENT_H

#include "ship/modules/components/ModifyShipAttributesComponent.h"

class ActiveModule;

class ActiveModuleProcessingComponent
{
public:

    ActiveModuleProcessingComponent(InventoryItemRef item, ActiveModule * mod, ShipRef ship, ModifyShipAttributesComponent * shipAttrMod);
    ~ActiveModuleProcessingComponent();

	void Process();

	void ActivateCycle();
    void DeactivateCycle();
	void AbortCycle();

    bool ShouldProcessActiveCycle();

    void ProcessActiveCycle();
	void ProcessDeactivateCycle();

	double GetRemainingCycleTimeMS();

private:
    //internal storage and record keeping
    bool m_Stop;
	Timer m_timer;


    //internal access to owner
	InventoryItemRef m_Item;
    ActiveModule *m_Mod;
    ShipRef m_Ship;
    ModifyShipAttributesComponent * m_ShipAttrModComp;

};

#endif
