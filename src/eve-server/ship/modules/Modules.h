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


#ifndef __MODULES_H__
#define __MODULES_H__

#include "inventory/EffectsEnum.h"
#include "inventory/InventoryItem.h"
#include "inventory/ItemRef.h"
#include "ship/Ship.h"
#include "ship/modules/ModuleDefs.h"
#include "ship/modules/ModuleEffects.h"
#include "ship/ShipOperatorInterface.h"
#include "ship/DestinyManager.h"
#include "ship/ModuleManager.h"

//generic module base class - possibly should inherit from RefPtr...

class GenericModule
{
public:
    GenericModule(InventoryItemRef item, ShipRef ship);
    virtual ~GenericModule();

    virtual void process() {  }
    /**
     * Put the module offline.
     * Client command.
     */
    virtual void offline();
    /**
     * Put the module online.
     * Client command.
     */
    virtual void online();

    /**
     * Activate the module.
     * Client command.
     * @param targetEntity The currently selected target.
     */
    virtual void activate(SystemEntity * targetEntity) {  }

    /**
     * Deactivate the module.
     * Client command.
     */
    virtual void deactivate() {  }

    /**
     * Load a charge into the module.
     * Client command.
     * @param charge The charge to load.
     */
    virtual void load(InventoryItemRef charge) {  }

    /**
     * Unload the charge from the module.
     * Client command.
     */
    virtual void unload() {  }

    /**
     * Put the module into overload mode.
     * Client command.
     */
    virtual void overload() {  }

    /**
     * Stop overloading the module.
     * Client command.
     */
    virtual void deOverload() {  }

    virtual void repair()
    {
        m_item->ResetAttribute(AttrHp, true);
    }

    virtual void repair(EvilNumber amount) { m_item->setAttribute(AttrHp, m_item->getAttribute(AttrHp) + amount); }

    //access functions

    InventoryItemRef getItem() { return m_item; }
    virtual uint32 itemID() { return m_item->itemID(); }
    virtual EVEItemFlags flag() { return m_item->flag(); }
    virtual uint32 typeID() { return m_item->typeID(); }
    virtual bool isOnline() { return (m_item->getAttribute(AttrIsOnline) == 1); }
    virtual bool isHighPower() { return m_effects->isHighSlot(); }
    virtual bool isMediumPower() { return m_effects->isMediumSlot(); }
    virtual bool isLowPower() { return m_effects->isLowSlot(); }
    virtual bool isRig();
    virtual bool isSubSystem();
    virtual bool isLoaded() { return false; }
    ModuleStates getModuleState() { return m_moduleState; }
    ChargeStates getChargeState() { return m_chargeState; }
    InventoryItemRef getLoadedChargeRef() { return InventoryItemRef(); }

    virtual bool isTurretFitted();
    virtual bool isLauncherFitted();

    virtual bool isMaxGroupFitLimited();
    ModulePowerLevel getModulePowerLevel();

    void setLog(Task_Log * pLog) { m_pMM_Log = pLog; }
    Task_Log * getLog() { return m_pMM_Log; }

protected:
    InventoryItemRef m_item;
    ShipRef m_ship;
    ModuleEffects * m_effects;

    ModuleStates m_moduleState;
    ChargeStates m_chargeState;

    Task_Log * m_pMM_Log; // We do not own this

    AttributeModifierSourceRef m_shipModifiers;
    AttributeModifierSourceRef m_shipPassiveModifiers;
    AttributeModifierSourceRef m_shipActiveModifiers;
    AttributeModifierSourceRef m_overloadModifiers;
    std::map<uint32, AttributeModifierSourceRef> m_moduleModifiers;

    void generateModifiers();
};

#endif /* __MODULES_H__ */
