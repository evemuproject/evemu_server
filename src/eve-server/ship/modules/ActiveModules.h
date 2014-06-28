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

#ifndef ACTIVE_MODULES_H
#define ACTIVE_MODULES_H

#include "Modules.h"
#include "ship/modules/components/ModifyShipAttributesComponent.h"
#include "ship/modules/components/ActiveModuleProcessingComponent.h"

class ActiveModule : public GenericModule
{
  friend ActiveModuleProcessingComponent;
  friend ModuleManager;
public:
    ActiveModule(InventoryItemRef item, ShipRef ship);
    ~ActiveModule();

	virtual void Process();
    virtual void Offline();
	virtual void Activate(SystemEntity * targetEntity);
    virtual void Deactivate();
    virtual void Load(InventoryItemRef charge);
    virtual void Unload();

    //access functions
    ModulePowerLevel GetModulePowerLevel()                    { return isHighPower() ? MODULE_BANK_HIGH_POWER : ( isMediumPower() ? MODULE_BANK_MEDIUM_POWER : MODULE_BANK_LOW_POWER); }

	InventoryItemRef GetLoadedChargeRef()					{ return m_ChargeRef; }

	virtual bool isLoaded()											{ return m_ChargeRef.get() != NULL; }
    virtual bool isRig()                                            { return false; }
    virtual bool isSubSystem()                                        { return false; }
    bool requiresTarget()
    {
        if( m_Effects->HasDefaultEffect() )
            return m_Effects->GetDefaultEffect()->GetIsAssistance() || m_Effects->GetDefaultEffect()->GetIsOffensive();
        else
            return false;
    }

	// Calls Reserved for components usage only!
private:
    /**
     * Called when the cycle starts.
     * This is where special effects should be started.
     * This is where weapons should do there damage or launch missiles
     */
	virtual void StartCycle()									{ /* Do nothing here */ }
    /**
     * Called when the cycle completes.
     * This is where repair/mining modules should do there actions.
     * @note mining modules should also gather there minerals when deactivated and then not again when the cycle ends.
     */
	virtual void EndCycle()									{ /* Do nothing here */ }

    /**
     * Called when charge loading cycle ends.
     */
    virtual void EndLoading(InventoryItemRef charge);
    /**
     * Get the targetID of this modules target.
     * @return The targets targetID.
     */

public:
    uint32 GetTargetID() { return m_targetEntity == NULL ? 0 : m_targetEntity->Item()->itemID(); };
    /**
     * Get the targetEntity of this modules target.
     * @return The targets targetEntity.
     */
    SystemEntity *GetTargetEntity() { return m_targetEntity; };
    
    bool isBusy() {
      return m_ActiveModuleProc->IsBusy();
    }

protected:
	ActiveModuleProcessingComponent * m_ActiveModuleProc;
	SystemEntity * m_targetEntity;	// we do not own this

	InventoryItemRef m_ChargeRef;		// we do not own this
    bool m_RequiresCharge;
    uint32 m_LoadCycleTime;

};


#endif