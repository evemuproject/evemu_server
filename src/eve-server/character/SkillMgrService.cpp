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
    Author:     Zhur
*/

#include "eve-server.h"

#include "PyServiceCD.h"
#include "character/SkillMgrService.h"
#include "character/CharacterDB.h"
#include "PyServiceMgr.h"

PyCallable_Make_InnerDispatcher(SkillMgrService)
PyCallable_Make_InnerDispatcher(SkillMgrBound)

SkillMgrService::SkillMgrService()
: PyService("skillMgr", new Dispatcher(this))
{
}

SkillMgrService::~SkillMgrService() {
}

PyBoundObject *SkillMgrService::_CreateBoundObject(Client *c, const PyRep *bind_args) {
    _log(CLIENT__MESSAGE, "SkillMgrService bind request for:");
    bind_args->Dump(CLIENT__MESSAGE, "    ");

    return(new SkillMgrBound());
}

SkillMgrBound::SkillMgrBound()
: PyBoundObject(new Dispatcher(this))
{
    m_strBoundObjectName = "SkillMgrBound";

    PyCallable_REG_CALL(SkillMgrBound, InjectSkillIntoBrain)
    PyCallable_REG_CALL(SkillMgrBound, CharStartTrainingSkillByTypeID)
    PyCallable_REG_CALL(SkillMgrBound, CharStopTrainingSkill)
    PyCallable_REG_CALL(SkillMgrBound, GetEndOfTraining)
    PyCallable_REG_CALL(SkillMgrBound, GetSkillHistory)
    PyCallable_REG_CALL(SkillMgrBound, CharAddImplant)
    PyCallable_REG_CALL(SkillMgrBound, RemoveImplantFromCharacter)
    PyCallable_REG_CALL(SkillMgrBound, GetSkillQueueAndFreePoints)
    PyCallable_REG_CALL(SkillMgrBound, SaveSkillQueue)
    PyCallable_REG_CALL(SkillMgrBound, AddToEndOfSkillQueue)

    PyCallable_REG_CALL(SkillMgrBound, GetRespecInfo)
    PyCallable_REG_CALL(SkillMgrBound, RespecCharacter)
    PyCallable_REG_CALL(SkillMgrBound, GetCharacterAttributeModifiers)
}

SkillMgrBound::~SkillMgrBound()
{
}

// TODO: redesign this so this is not needed
void SkillMgrBound::Release()
{
    delete this;
}

PyResult SkillMgrBound::Handle_GetCharacterAttributeModifiers(PyCallArgs &call)
{
    // Called for Attribute re-mapping.
    // expected data: (itemID, typeID, operation, value) in modifiers:
    Call_SingleIntegerArg args;
    if (!args.Decode(&call.tuple))
    {
        codelog(CLIENT__ERROR, "%s: failed to decode arguments", call.client->GetName());
        return NULL;
    }
    uint32 bonusAttr = args.arg - AttrCharisma + AttrCharismaBonus;
    PyList *list = new PyList;
    // Check each slot.
    for (uint32 slot = 1; slot <= 10; slot++)
    {
        // Get the implant for the slot.
        InventoryItemRef item = call.client->GetChar()->GetImplant(slot);
        if (item.get() == nullptr)
        {
            // No implant in this slot.
            continue;
        }
        // Does this implant have the bonus we are looking for?
        if (!item->hasAttribute(bonusAttr))
        {
            // No, continue.
            continue;
        }
        // Add the implant to the list.
        PyTuple *tuple = new PyTuple(4);
        tuple->SetItem(0, new PyInt(item->itemID()));
        tuple->SetItem(1, new PyInt(item->typeID()));
        tuple->SetItem(2, new PyInt(EVECalculationType::CALC_ADDITION)); // operation?
        tuple->SetItem(3, new PyInt(item->getAttribute(bonusAttr).get_int()));
        list->AddItem(tuple);
    }
    return list;
}

PyResult SkillMgrBound::Handle_CharStopTrainingSkill(PyCallArgs &call) {
    CharacterRef ch = call.client->GetChar();

    // clear & update ...
    ch->StopTraining();
    ch->UpdateSkillQueue();

    return NULL;
 }

PyResult SkillMgrBound::Handle_GetEndOfTraining(PyCallArgs &call) {
    CharacterRef ch = call.client->GetChar();

    return new PyLong( ch->GetEndOfTraining().get_int() );
}

PyResult SkillMgrBound::Handle_GetSkillHistory( PyCallArgs& call )
{
    SysLog::Debug( "SkillMgrBound", "Called GetSkillHistory stub." );

    util_Rowset rowset;

    rowset.header.push_back( "logDate" );
    rowset.header.push_back( "eventTypeID" );
    rowset.header.push_back( "skillTypeID" );
    rowset.header.push_back( "relativePoints" );
    rowset.header.push_back( "absolutePoints" );

	// eventTypeIDs:
    // 34 - SkillClonePenalty
    // 36 - SkillTrainingStarted
    // 37 - SkillTrainingComplete
    // 38 - SkillTrainingCanceled
    // 39 - GMGiveSkill
    // 53 - SkillTrainingComplete
    // 307 - SkillPointsApplied

	rowset.lines = new PyList;

    CharacterRef ch = call.client->GetChar();
    uint32 characterID = ch->itemID();
    DBQueryResult res;
    if(!DBcore::RunQuery(res,
                         "SELECT typeID, level, points, eventTime FROM srvChrSkillHistory "
                         " WHERE characterID=%u AND eventID=37 ORDER BY eventTime LIMIT 20",
                         characterID))
    {
        _log(DATABASE__ERROR, "Failed to get skill history for character %u: %s", characterID, res.error.c_str());
    }

    DBResultRow row;
    while(res.GetRow(row))
    {
        PyList* fieldData = new PyList;
        fieldData->AddItemLong(row.GetInt64(3));
        fieldData->AddItemInt(37);
        uint32 typeID = row.GetUInt(0);
        uint32 points = row.GetUInt(2);
        uint32 level = row.GetUInt(1);
        uint32 rel = points;
        SkillRef skill = ch->GetSkill(typeID);
        if(skill.get() != nullptr)
        {
            rel -= skill->GetSPForLevel(level - 1);
        }
        fieldData->AddItemInt(typeID);
        fieldData->AddItemInt(rel);
        fieldData->AddItemInt(points + 1);
        rowset.lines->AddItem( fieldData );
    }

    return rowset.Encode();
}

PyResult SkillMgrBound::Handle_CharAddImplant( PyCallArgs& call )
{
    //takes itemid
    Call_SingleIntegerArg args;
    if( !args.Decode( &call.tuple ) )
    {
        codelog( CLIENT__ERROR, "%s: failed to decode arguments", call.client->GetName() );
        return NULL;
    }

    CharacterRef charRef = call.client->GetChar();
    if (charRef->GetSkillInTraining().get() != nullptr)
    {
        // TO-DO: throw proper error.
        throw (PyException(MakeUserError("RespecSkillInTraining")));
    }
    InventoryItemRef item = ItemFactory::GetItem(args.arg);
    if (item.get() != nullptr)
    {
        if (!charRef->canUse(item))
        {
            // Do not have necessary skills.
            return NULL;
        }
        if (item->quantity() > 1)
        {
            item = item->Split(1);
        }
        InventoryItemRef existing = charRef->GetImplant(item->getAttribute(AttrImplantness).get_int());
        if (existing.get() != nullptr && existing != item)
        {
            // We are replacing an existing implant!
            // Delete Item,  Unplugged implants are destroyed!
            item->Delete();
        }
        item->Move(charRef->itemID(), flagImplant);
    }

    return NULL;
}

PyResult SkillMgrBound::Handle_RemoveImplantFromCharacter( PyCallArgs& call )
{
    //takes itemid
    Call_SingleIntegerArg args;
    if( !args.Decode( &call.tuple ) )
    {
        codelog( CLIENT__ERROR, "%s: failed to decode arguments", call.client->GetName() );
        return NULL;
    }

    CharacterRef charRef = call.client->GetChar();
    InventoryItemRef item = ItemFactory::GetItem(args.arg);
    if (item.get() != nullptr)
    {
        // Delete Item,  Unplugged implants are destroyed!
        item->Delete();
    }

    return NULL;
}

PyResult SkillMgrBound::Handle_GetSkillQueueAndFreePoints(PyCallArgs &call) {
    // returns list of skills currently in the skill queue.
    CharacterRef ch = call.client->GetChar();

    return ch->GetSkillQueue();
}

 PyResult SkillMgrBound::Handle_SaveSkillQueue(PyCallArgs &call) {
    Call_SaveSkillQueue args;
    if(!args.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "%s: failed to decode arguments", call.client->GetName());
        return NULL;
    }

    CharacterRef ch = call.client->GetChar();

    ch->ClearSkillQueue();

    SkillQueue_Element el;
    std::vector<PyRep*>::const_iterator cur, end;
    cur = args.queue->begin();
    end = args.queue->end();
    for (; cur != end; cur++)
    {
        if( !el.Decode( *cur ) )
        {
            _log(CLIENT__ERROR, "%s: Failed to decode element of SkillQueue. Skipping.", call.client->GetName());
            continue;
        }

        ch->AddToSkillQueue( el.typeID, el.level );
    }

    ch->UpdateSkillQueue();

    SkillRef first = ch->GetSkillInQueue(0);
    if (first.get() != nullptr)
    {
        // Make sure first skill is training.
        ch->StartTraining(first->typeID());
    }

    return NULL;
 }

PyResult SkillMgrBound::Handle_AddToEndOfSkillQueue(PyCallArgs &call) {
    Call_TwoIntegerArgs args;
    if(!args.Decode(&call.tuple)) {
        codelog(CLIENT__ERROR, "%s: failed to decode arguments", call.client->GetName());
        return NULL;
    }

    CharacterRef ch = call.client->GetChar();

    ch->AddToSkillQueue(args.arg1, args.arg2);
    ch->UpdateSkillQueue();

    return NULL;
}

PyResult SkillMgrBound::Handle_RespecCharacter(PyCallArgs &call)
{
    Call_RespecCharacter spec;
    if (!spec.Decode(call.tuple))
    {
        codelog(CLIENT__ERROR, "Failed to decode RespecCharacter arguments");
        return NULL;
    }

	CharacterRef cref = call.client->GetChar();
	if( cref->GetSkillInTraining() )
		throw(PyException(MakeUserError("RespecSkillInTraining")));

    // return early if this is an illegal call
    if (!CharacterDB::ReportRespec(call.client->GetCharacterID()))
        return NULL;

    // TODO: validate these values (and their sum)
    cref->setAttribute(AttrCharisma, spec.charisma);
    cref->setAttribute(AttrIntelligence, spec.intelligence);
    cref->setAttribute(AttrMemory, spec.memory);
    cref->setAttribute(AttrPerception, spec.perception);
    cref->setAttribute(AttrWillpower, spec.willpower);
    cref->SaveAttributes();

    // no return value
    return NULL;
}

PyResult SkillMgrBound::Handle_GetRespecInfo( PyCallArgs& call )
{
    uint32 freeRespecs;
    uint64 lastRespec = 0;
    uint64 nextRespec;
    if (!CharacterDB::GetRespecInfo(call.client->GetCharacterID(), freeRespecs, lastRespec, nextRespec))
    {
        // insert dummy values
        freeRespecs = 0;
        lastRespec = 0;
        nextRespec = 0;
    }

    PyDict* result = new PyDict;
    result->SetItemString( "lastRespecDate", new PyInt( lastRespec ) );
    result->SetItemString( "freeRespecs", new PyInt( freeRespecs ) );
    result->SetItemString( "nextTimedRespec", new PyLong( nextRespec ) );

    return result;
}

PyResult SkillMgrBound::Handle_CharStartTrainingSkillByTypeID( PyCallArgs& call )
{
    Call_SingleIntegerArg args;
    if( !args.Decode( &call.tuple ) )
    {
        codelog( CLIENT__ERROR, "%s: failed to decode arguments", call.client->GetName() );
        return NULL;
    }

    CharacterRef charRef = call.client->GetChar();
    charRef->StartTraining(args.arg);
    //Log::Error("SkillMgrBound::Handle_CharStartTrainingSkillByTypeID()", "TODO: This is used on resuming skill queue, so should be implemented");
    //Log::Debug( "SkillMgrBound", "Called CharStartTrainingSkillByTypeID stub." );

    return NULL;
}

PyResult SkillMgrBound::Handle_InjectSkillIntoBrain(PyCallArgs &call)
{
    Call_InjectSkillIntoBrain args;
    if( !args.Decode( &call.tuple ) ) {
        codelog( CLIENT__ERROR, "%s: failed to decode arguments", call.client->GetName() );
        return NULL;
    }

    CharacterRef ch = call.client->GetChar();

    std::vector<int32>::iterator cur, end;
    cur = args.skills.begin();
    end = args.skills.end();
    for(; cur != end; cur++)
    {
        SkillRef skill = ItemFactory::GetSkill(*cur);
        if( !skill )
        {
            codelog( ITEM__ERROR, "%s: failed to load skill item %u for injection.", call.client->GetName(), *cur );
            continue;
        }

        if( !ch->InjectSkillIntoBrain( (SkillRef)skill ) )
        {
            //TODO: build and send UserError about injection failure.
            codelog(ITEM__ERROR, "%s: Injection of skill %u failed", call.client->GetName(), skill->itemID() );
        }
    }

    // TODO: send notification that the skill(s) injection was successful.
    return NULL;
}
