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
	Author:		Luck
*/

#ifndef __MODULEMANAGER_H_INCL__
#define __MODULEMANAGER_H_INCL__

class InventoryItem;
class SystemEntity;
class Client;

//generic modulee base class
class GenericModule
{
public:
	GenericModule();
	
	~GenericModule();

};

class PassiveModule : public GenericModule
{

};

class RigModule : public PassiveModule
{

};

class SubSystemModule : public PassiveModule
{

};

//container for all ships modules
class ModuleContainer
{
public:
	ModuleContainer(uint32 lowSlots, uint32 medSlots, uint32 highSlots, uint32 rigSlots, uint32 subSystemSlots);
	
	void AddModule(uint32 flag, GenericModule * mod);
	GenericModule * GetModule(uint32 flag);
	
private:

	void _addHighSlotModule(uint32 flag, GenericModule * mod);
	void _addMediumSlotModule(uint32 flag, GenericModule * mod);
	void _addLowSlotModule(uint32 flag, GenericModule * mod);
	void _addRigModule(uint32 flag, GenericModule * mod);
	void _addSubSystemModule(uint32 flag, GenericModule * mod);

	GenericModule * _getHighSlotModule(uint32 flag);
	GenericModule * _getMediumSlotModule(uint32 flag);
	GenericModule * _getLowSlotModule(uint32 flag);
	GenericModule * _getRigModule(uint32 flag);
	GenericModule * _getSubSystemModule(uint32 flag);
	
	EVEItemSlotType _checkBounds(uint32 flag);
	bool			_isLowSlot(uint32 flag);
	bool			_isMediumSlot(uint32 flag);
	bool			_isHighSlot(uint32 flag);
	bool			_isRigSlot(uint32 flag);
	bool			_isSubSystemSlot(uint32 flag);

	GenericModule * m_HighSlotModules[MAX_HIGH_SLOT_COUNT];
	GenericModule * m_MediumSlotModules[MAX_MEDIUM_SLOT_COUNT];
	GenericModule * m_LowSlotModules[MAX_LOW_SLOT_COUNT];
	GenericModule * m_RigModules[MAX_RIG_COUNT];
	GenericModule * m_SubSystemModules[MAX_ASSEMBLY_COUNT];

	uint32 m_LowSlots;
	uint32 m_MediumSlots;
	uint32 m_HighSlots;
	uint32 m_RigSlots;
	uint32 m_SubSystemSlots;
	
};


class ModuleManager {
public:
	ModuleManager( Ship * ship );
	~ModuleManager();
	
private:
	//access to the ship that owns us.  We do not own this
	Ship * m_Ship;

	//module arrays
		

};

#endif


