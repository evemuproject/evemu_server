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
    Author:        Luck
*/

#ifndef ACTIVE_MODULES_H
#define ACTIVE_MODULES_H

#include "Modules.h"

class ActiveModule : public GenericModule
{
public:
    ActiveModule(InventoryItemRef item, ShipRef ship);
    ~ActiveModule();

    virtual void process();
    void activate(SystemEntity * targetEntity);
    void deactivate();
    void load(InventoryItemRef charge);
    void unload();

    //access functions
	InventoryItemRef getLoadedChargeRef() { return m_chargeRef; }
	bool isLoaded() { return m_chargeLoaded; }
    bool requiresTarget()
    {
        if( m_Effects->HasDefaultEffect() )
        {
            //return m_Effects->GetDefaultEffect()->GetIsAssistance() || m_Effects->GetDefaultEffect()->GetIsOffensive();
            return m_Effects->GetDefaultEffect()->GetIsOffensive();
        }
        return false;
    }

    /**
     * Check module specific activation requirements.
     * @param targetEntity The target.
     * @return true if the module can activate.
     */
    virtual bool canActivate(SystemEntity *targetEntity);
    /**
     * Get the modules cycle time.
     * @return The cycle time.
     */
    virtual uint32 getCycleTime();
    /**
     * A cycle has started.
     * @param continuing True if this is continuing from a previous cycle.
     */
    virtual void startCycle(bool continuing) {};
    /**
     * A cycle has ended.
     */
    virtual void endCycle(bool continuing) {};
    /**
     * Can the module abort a cycle?
     * @return True if the cycle can be aborted.
     */
    virtual bool canAbort() {return false;};

protected:
    uint32 m_targetID;  //passed to us by activate
	SystemEntity * m_targetEntity;	// we do not own this

	InventoryItemRef m_chargeRef;		// we do not own this
	bool m_chargeLoaded;

    void doStop();
    /**
     * Show cycle effects.
     */
    virtual void showEffects() { doEffect(true); }
    /**
     * Hide cycle effects.
     */
    virtual void hideEffects() { doEffect(false); }
    std::string currentEffectString;

    void doEffect(bool active);
    void doEffect(bool active, std::string effectString);
    void doEffect(bool active, std::shared_ptr<MEffect> effect);
    void doEffect(bool active, std::shared_ptr<MEffect> effect, std::string effectString);

    double getRemainingCycleTimeMS();
    double getElapsedCycleTimeMS();
    double getTotalCycleTimeMS();

private:
    //internal storage and record keeping
    bool m_Stop;
    Timer m_timer;
};


#endif
