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

class ActiveModule : public GenericModule
{
  friend ModuleManager;
public:
    ActiveModule(InventoryItemRef item, ShipRef ship);

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
        EVEEffectRef effect = m_Item->type().GetEffects()->GetDefaultEffect();
        if( effect.get() != NULL )
            return effect->GetIsAssistance() || effect->GetIsOffensive();
        else
            return false;
    }

	// Calls Reserved for components usage only!
protected:
    /**
     * Called when the cycle starts.
     * This is where special effects should be started.
     * This is where weapons should do there damage or launch missiles
     */
	virtual void StartCycle();
    /**
     * Called when the cycle completes.
     * This is where repair/mining modules should do there actions.
     * @param abort True if the module was stopped in mid cycle.
     * @note mining modules should also gather there minerals when deactivated and then not again when the cycle ends.
     */
	virtual void StopCycle(bool abort=false);

    /**
     * Called when charge loading cycle ends.
     */
    virtual void EndLoading();
    /**
     * Begin a new cycle.
     */
    bool BeginCycle();
    /**
     * A cycle has completed and a new cycle might start.
     */
    void ProcessActiveCycle();

public:
    /**
     * Get the targetID of this modules target.
     * @return The targets targetID.
     */
    uint32 GetTargetID() { return m_targetEntity == NULL ? 0 : m_targetEntity->Item()->itemID(); };
    /**
     * Get the targetEntity of this modules target.
     * @return The targets targetEntity.
     */
    SystemEntity *GetTargetEntity() { return m_targetEntity; };
    
    /**
     * Aborts the current cycle, stopping it immediately.
     */
    void AbortCycle();
    /**
     * Ask if cycling should continue.
     * @return True if cycling should continue.
     */
    bool ContinueCycling();

    /**
     * Gets the cycle time remaining.
     * @return the remaining cycle time in ms.
     */
	double GetRemainingCycleTimeMS();
    /**
     * Get if the module is busy.
     * @return true if the module is busy.
     */
    bool isBusy() { return m_timer.Enabled(); };

    virtual bool isActiveModule() { return true; }

protected:
    bool m_Stop;
/****************************************************
	A little note about the timer:
		Timer.Check() has two functions:
			1. It checks if the timer has expired out 
			2. It subtracts from the start time
	Don't be fooled by it's name because if you don't
	call it in a loop, you won't get the time moving.
*****************************************************/
	Timer m_timer;
    EvilNumber m_CycleTime;
    EVEEffectRef m_Effect;
    
	SystemEntity * m_targetEntity;	// we do not own this

	InventoryItemRef m_ChargeRef;		// we do not own this
    uint32 m_ChargeID;                  // use for civilian guns that have a charge but not ammo.
    uint32 m_LoadCycleTime;

    void DoGraphics(bool active, EVEEffectRef Effect = EVEEffectRef(NULL));
};


#endif