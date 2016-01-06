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

PyCallable_Make_InnerDispatcher(SkillMgrService)
PyCallable_Make_InnerDispatcher(SkillMgrBound)

SkillMgrService::SkillMgrService(PyServiceMgr *mgr)
: PyService(mgr, "skillMgr"),
  m_dispatch(new Dispatcher(this))
{
    _SetCallDispatcher(m_dispatch);
}

SkillMgrService::~SkillMgrService() {
    delete m_dispatch;
}

PyBoundObject *SkillMgrService::_CreateBoundObject(Client *c, const PyRep *bind_args) {
    _log(CLIENT__MESSAGE, "SkillMgrService bind request for:");
    bind_args->Dump(CLIENT__MESSAGE, "    ");

    return(new SkillMgrBound(m_manager, m_db));
}

SkillMgrBound::SkillMgrBound(PyServiceMgr *mgr, CharacterDB &db)
: PyBoundObject(mgr),
  m_dispatch(new Dispatcher(this)),
  m_db(db)
{
    _SetCallDispatcher(m_dispatch);

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
    delete m_dispatch;
}

// TODO: redesign this so this is not needed
void SkillMgrBound::Release()
{
    delete this;
}

PyResult SkillMgrBound::Handle_GetCharacterAttributeModifiers(PyCallArgs &call) {
    // since we don't currently support implants (I think), just a dummy
    // expected data: for (itemID, typeID, operation, value,) in modifiers:
    return new PyTuple(0);
}

PyResult SkillMgrBound::Handle_CharStopTrainingSkill(PyCallArgs &call) {
    CharacterRef ch = call.client->GetChar();

    // clear & update ...
    ch->ClearSkillQueue();
    ch->UpdateSkillQueue();

    return NULL;
 }

PyResult SkillMgrBound::Handle_GetEndOfTraining(PyCallArgs &call) {
    CharacterRef ch = call.client->GetChar();

    return new PyLong( ch->GetEndOfTraining().get_int() );
}

PyResult SkillMgrBound::Handle_GetSkillHistory( PyCallArgs& call )
{
    sLog.Debug( "SkillMgrBound", "Called GetSkillHistory stub." );

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

	// NOTE:  Screenshots from DaVinci show that this call sends back only 20 most recent entries in this history

	// TODO: get most recent 20 entries for skill history from DB table via character object
	CharacterRef ch = call.client->GetChar();
	//ch->GetSkillHistory();

	rowset.lines = new PyList;

    uint32 i = 0;
    PyList* fieldData = new PyList;
    //for( i = 0; i < ?; i++ )
    //{
        fieldData->AddItemLong( 130386773819853860 );
        fieldData->AddItemInt( 37 );
        fieldData->AddItemInt( 28667 );
        fieldData->AddItemInt( 6532 );
        fieldData->AddItemInt( 12000 );
        rowset.lines->AddItem( fieldData );
        fieldData = new PyList;
    //}

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

    sLog.Debug( "SkillMgrBound", "Called CharAddImplant stub." );

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

    sLog.Debug( "SkillMgrBound", "Called RemoveImplantFromCharacter stub." );

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
    if (!m_db.ReportRespec(call.client->GetCharacterID()))
        return NULL;

    // TODO: validate these values (and their sum)
    cref->SetAttribute(AttrCharisma, spec.charisma);
    cref->SetAttribute(AttrIntelligence, spec.intelligence);
    cref->SetAttribute(AttrMemory, spec.memory);
    cref->SetAttribute(AttrPerception, spec.perception);
    cref->SetAttribute(AttrWillpower, spec.willpower);
    cref->SaveAttributes();

    // no return value
    return NULL;
}

PyResult SkillMgrBound::Handle_GetRespecInfo( PyCallArgs& call )
{
    uint32 freeRespecs;
    uint64 lastRespec = 0;
    uint64 nextRespec;
    if (!m_db.GetRespecInfo(call.client->GetCharacterID(), freeRespecs, lastRespec, nextRespec))
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

	sLog.Error("SkillMgrBound::Handle_CharStartTrainingSkillByTypeID()", "TODO: This is used on resuming skill queue, so should be implemented" );
    //sLog.Debug( "SkillMgrBound", "Called CharStartTrainingSkillByTypeID stub." );

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
        SkillRef skill = m_manager->item_factory.GetSkill( *cur );
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
