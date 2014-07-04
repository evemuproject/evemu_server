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
    Author:        Luck, Aknor Jaden
*/


#ifndef __MODULEMANAGER_H_INCL__
#define __MODULEMANAGER_H_INCL__

class DestinyManager;
class InventoryItem;
class GenericModule;
class SystemEntity;
class Client;
class ModuleManager;
class Basic_Log;

#include "ship/modules/Modules.h"
#include "ship/modules/ModuleDefs.h"


//////////////////////////////////////////////////////////////////////////////////
//
// --- Explanation of all this confusing crap in here:
//
// We need a map of maps to store modifiers from activated effects of modules, skills, ships, implants, subsystems, rigs, etc
// So, what we've done here is to create a std::map<uint32 attributeID, ModifierMap>  This contains a ModifierMap class object
// for each attributeID added to this outer map.  For each attribute that is modified by one or more originators (module, rig,
// ship, skill, implant, etc), an inner map is created and added to this outer map.  The ModifierMap class contains this inner map,
// which is actually a std::multimap<double modifierValue, Modifier modifierObject>  The reason we use a multimap here is that
// a multimap allows multiple key values that are exactly the same, which you'll get if you fit more than one module of the exact
// same type.  The modifier value is used as the key since we need the list of all modifiers for a single attributeID to be sorted
// largest modifier value to smallest to zero to smaller negative modifier values to largest negative modifier value.  This sort
// is needed in order to properly apply stacking penalties.  The stacking penalties as explained here http://wiki.eveuniversity.org/Eve_math
// indicate that the largest modifier value does not get penalized, but the 2nd largest on down get increasingly larger penalties applied.
// The penalties will NOT be applied into the Modifier class objects, but only when the ModuleManager class methods process these modifiers
// onto the attributes AFTER any Module class objects are called to change state and apply either new or updated modifiers into
// these Modifier Maps.
//
// Each Module class object will make the public calls to the ModuleManager to add Modifiers to the Modifier Map for a particular
// attributeID, so let's talk about these classes.
//
// The Modifier class just contains basic information on a single modifier value inserted by an 'originator', some source of the
// modifier value (module, skill, ship, implant, rig, subsystem, etc).  Every Modifier class object created by an originator
// is inserted into a ModifierMapType, which is a std::multimap<double modifierValue, ModifierRef modifierRef> structure.  It is
// a std::multimap<> with double as key value, which are the modifier values themselves so that the multimap can sort the pairs
// according to the values of the modifier values.
//
// Each of these ModifierMapType structures are inserted into one of a handful of ModifierMaps structures, each of which are
// std::map<uint32 attributeID, ModifierMap * modifierMap>  Each pair is keyed to the attributeID for the attribute that will
// be modified by the list of modifier values stored in the ModifierMap object.  There are multiple ModifierMaps objects in the
// ModuleManager class, one for Subsystems, one for Ships and Skills, one for Modules and Rigs, one for Implants, and one for
// Remotely applied modifiers from external hostile entities.
//
// More to follow, and this will be copied to http://wiki.evemu.org
//
//     -- Aknor Jaden
//
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
// Container for all ships modules
#pragma region ModuleContainer

class ModuleContainer
{
public:
    ModuleContainer(uint32 lowSlots, uint32 medSlots, uint32 highSlots, uint32 rigSlots, uint32 subSystemSlots,
        uint32 turretSlots, uint32 launcherSlots, ModuleManager * myManager);
    ~ModuleContainer();

    bool AddModule(uint32 flag, GenericModule * mod);
    bool RemoveModule(EVEItemFlags flag);
    bool RemoveModule(uint32 itemID);
    GenericModule * GetModule(EVEItemFlags flag);
    GenericModule * GetModule(uint32 itemID);

	uint32 GetAvailableSlotInBank(EveEffectEnum slotBank);

    int NumberOfSameType(uint32 typeID);

    //batch processes handlers
    void Process();
    void OfflineAll();
    void OnlineAll();
    void DeactivateAll();
    void UnloadAll();

    //useful accessors
	bool isSlotOccupied(EVEItemFlags flag);
    bool isHighPower(uint32 itemID);
    bool isMediumPower(uint32 itemID);
    bool isLowPower(uint32 itemID);
    bool isRig(uint32 itemID);
    bool isSubSystem(uint32 itemID);

    uint32 GetFittedTurretCount() { return m_TotalTurretsFitted; }
    uint32 GetFittedLauncherCount() { return m_TotalLaunchersFitted; }
    uint32 GetFittedModuleCountByGroup(uint32 groupID);

	void GetModuleListOfRefs(std::vector<InventoryItemRef> * pModuleList);
    void SaveModules();

private:

    //internal enums
    enum processType
    {
        typeOnlineAll,
        typeOfflineAll,
        typeDeactivateAll,
        typeUnloadAll,
        typeProcessAll
    };

    enum slotType
    {
        highSlot,
        mediumSlot,
        lowSlot,
        rigSlot,
        subSystemSlot
    };

    void _removeModule(EVEItemFlags flag, GenericModule * mod);

    void _process(processType p);
    void _processEx(processType p, slotType t);

    GenericModule * _getHighSlotModule(uint32 flag);
    GenericModule * _getMediumSlotModule(uint32 flag);
    GenericModule * _getLowSlotModule(uint32 flag);
    GenericModule * _getRigModule(uint32 flag);
    GenericModule * _getSubSystemModule(uint32 flag);

    void _removeHighSlotModule(uint32 flag);
    void _removeMediumSlotModule(uint32 flag);
    void _removeLowSlotModule(uint32 flag);
    void _removeRigSlotModule(uint32 flag);
    void _removeSubSystemModule(uint32 flag);

    EVEItemSlotType _checkBounds(uint32 flag);

    bool _isLowSlot(uint32 flag);
    bool _isMediumSlot(uint32 flag);
    bool _isHighSlot(uint32 flag);
    bool _isRigSlot(uint32 flag);
    bool _isSubSystemSlot(uint32 flag);

    void _initializeModuleContainers();

    //we own these
    GenericModule ** m_HighSlotModules;
    GenericModule ** m_MediumSlotModules;
    GenericModule ** m_LowSlotModules;
    GenericModule ** m_RigModules;
    GenericModule ** m_SubSystemModules;

    uint32 m_LowSlots;
    uint32 m_MediumSlots;
    uint32 m_HighSlots;
    uint32 m_RigSlots;
    uint32 m_SubSystemSlots;
    uint32 m_TurretSlots;
    uint32 m_LauncherSlots;

    uint32 m_TotalTurretsFitted;
    uint32 m_TotalLaunchersFitted;
    std::map<uint32, uint32> m_ModulesFittedByGroupID;

    ModuleManager * m_MyManager;        // we do not own this
};

#pragma endregion
/////////////////////////// END MODULECONTAINER //////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
// Primary Module Manager class
#pragma region ModuleManager

class ModuleManager
{
public:
    ModuleManager(Ship *const ship);
    ~ModuleManager();

    bool IsSlotOccupied(uint32 flag);
	uint32 GetAvailableSlotInBank(EveEffectEnum slotBank);

    bool InstallRig(InventoryItemRef item, EVEItemFlags flag);
    void UninstallRig(uint32 itemID);
    bool InstallSubSystem(InventoryItemRef item, EVEItemFlags flag);
    bool SwapSubSystem(InventoryItemRef item, EVEItemFlags flag);
    bool FitModule(InventoryItemRef item, EVEItemFlags flag);
    void UnfitModule(uint32 itemID);
    void Online(uint32 itemID);
    void OnlineAll();
    void Offline(uint32 itemID);
    void OfflineAll();
    int32 Activate(uint32 itemID, std::string effectName, uint32 targetID, uint32 repeat);
    void Deactivate(uint32 itemID, std::string effectName);
    void DeactivateAllModules();
    void Overload(uint32 itemID);
    void DeOverload(uint32 itemID);
    void DamageModule(uint32 itemID, EvilNumber val);
    void RepairModule(uint32 itemID);
    void LoadCharge(std::vector<InventoryItemRef> &chargeList, EVEItemFlags flag);
    void UnloadCharge(EVEItemFlags flag);
    void UnloadAllModules();
    void CharacterLeavingShip();
    void CharacterBoardingShip();
    void ShipWarping();
    void ShipJumping();
    void Process();
   /**
     * Get a list of all module in the same group.
     * @param typeID The groupID of the modules to get.
     * @param level The power level of the modules to get.
     * @return The list of modules.
     */
    std::vector<GenericModule *> GetStackedItems(uint32 typeID, ModulePowerLevel level);  //should only be used by components

    GenericModule * GetModule(EVEItemFlags flag)    { return m_Modules->GetModule(flag); }
    GenericModule * GetModule(uint32 itemID)        { return m_Modules->GetModule(itemID); }

	InventoryItemRef GetLoadedChargeOnModule(EVEItemFlags flag);

	void GetModuleListOfRefs(std::vector<InventoryItemRef> * pModuleList);
    void SaveModules();

	Basic_Log * GetLogger() { return m_pLog; }

private:
    bool _fitModule(InventoryItemRef item, EVEItemFlags flag);

    ModuleCommand _translateEffectName(std::string s);

    void _SendInfoMessage(const char* fmt, ...);
    void _SendErrorMessage(const char* fmt, ...);

    //access to the ship its system entity that owns us.  We do not own these
    Ship * m_Ship;

    //modules storage, we own this
    ModuleContainer * m_Modules;                    // Holds Module class objects in container arrays, one for each slot bank, rig, subsystem

	Basic_Log * m_pLog;
};

#pragma endregion
/////////////////////////// END MODULE MANAGER //////////////////////////////////

#endif  /* MODULE_MANAGER_H */


