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
    Author:        Luck
*/

#ifndef ACTIVE_MODULE_PROCESSING_COMPONENT_H
#define ACTIVE_MODULE_PROCESSING_COMPONENT_H

#include "ship/modules/components/ModifyShipAttributesComponent.h"

class ActiveModule;

class ActiveModuleProcessingComponent
{
public:

    ActiveModuleProcessingComponent(InventoryItemRef item, ActiveModule * mod, ShipRef ship);
    ~ActiveModuleProcessingComponent();

    /**
     * Check the timer and see if a cycle has been completed.
     * Start a new cycle if the module has not been stopped.
     */
	void Process();

    /**
     * Activates a module cycle timer and triggers StartCycle()
     * @param buttonEffect the effect id for the ships module button.
     */
	void ActivateCycle(uint32 effectID) { ActivateCycle(effectID, InventoryItemRef()); };
    /**
     * Activates a module cycle timer and triggers StartCycle()
     * @param buttonEffect the effect id for the ships module button.
     * @param charge the charge currently loaded into the module.
     */
	void ActivateCycle(uint32 effectID, InventoryItemRef charge);
    /**
     * Flags the cycle to stop at completion of current cycle.
     */
    void DeactivateCycle();

private:
    /**
     * Begin a new cycle.
     */
    bool BeginCycle();
    /**
     * A cycle has completed and a new cycle might start.
     */
    void ProcessActiveCycle();
    
    void StartButton();
    void EndButton();

public:
    /**
     * Gets the cycle time remaining.
     * @return the remaining cycle time in ms.
     */
	double GetRemainingCycleTimeMS();
    /**
     * Get if the module is busy.
     * @return true if the module is busy.
     */
    bool IsBusy() { return m_ButtonCycle; };

private:
    //internal storage and record keeping
    bool m_Stop;
	Timer m_timer;

    bool m_ButtonCycle;
    EvilNumber m_CycleTime;
    MEffect *m_Effect;
	InventoryItemRef m_Charge;

    //internal access to owner
	InventoryItemRef m_Item;
    ActiveModule *m_Mod;
    ShipRef m_Ship;

};

#endif