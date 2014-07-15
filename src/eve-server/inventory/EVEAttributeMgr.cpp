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
    Author:     Zhur
*/

#include "eve-server.h"

#include "Client.h"
#include "EntityList.h"
#include "inventory/EVEAttributeMgr.h"
#include "inventory/InventoryDB.h"
#include "inventory/InventoryItem.h"

/************************************************************************/
/* Start of new attribute system                                        */
/************************************************************************/
AttributeMap::AttributeMap( InventoryItemRef item )
: mItem(item),
  mChanged(true),
  mDefault(false)
{
    // load the initial attributes for this item
    //Load();
}

AttributeMap::AttributeMap( InventoryItemRef item, bool bDefaultMap )
: mItem(item),
  mChanged(true),
  mDefault(bDefaultMap)
{
    // load the initial attributes for this item, if we are acting as container for "default" attributes
    //if(mDefault)
	//	Load();
}

bool AttributeMap::SetAttribute( uint32 attributeId, const EvilNumber &num, bool notify /*= true*/ )
{
    AttrMapItr itr = mAttributes.find(attributeId);

    /* most attribute have default value's which are related to the item type */
    if (itr == mAttributes.end()) {
        mAttributes.insert(std::make_pair(attributeId, num));
		mChanged = true;	// Mark the map as having been modified by a new attribute being added
        if (notify == true)
            return Add(attributeId, num);
        return true;
    }

    // I dono if this should happen... in short... if nothing changes... do nothing
    if (itr->second == num)
        return false;

    // notify dogma to change the attribute, if we are unable to queue the change
    // event. Don't change the value.
    if (notify == true)
        if (!Change(attributeId, itr->second, num))
            return false;

    itr->second = num;

	mChanged = true;	// Mark the map as having been modified

    return true;
}

bool AttributeMap::SetAttribute( uint32 attributeId, const int64 &num, bool notify /*= true*/ )
{
    EvilNumber val(num);
    return SetAttribute(attributeId, val, notify);
}

bool AttributeMap::SetAttribute( uint32 attributeId, const double &num, bool notify /*= true*/ )
{
    EvilNumber val(num);
    return SetAttribute(attributeId, val, notify);
}

EvilNumber AttributeMap::GetAttribute( const uint32 attributeId ) const
{
    AttrMapConstItr itr = mAttributes.find(attributeId);
    if (itr != mAttributes.end())
        return itr->second;
    sLog.Error("AttributeMap::GetAttribute()", "unable to find attribute: %u for item %u, '%s' of type %u", attributeId, mItem->itemID(), mItem->itemName().c_str(), mItem->typeID());
    return EvilNumber(0);
}

EvilNumber AttributeMap::GetAttribute( const uint32 attributeId, const EvilNumber &defaultValue ) const
{
    AttrMapConstItr itr = mAttributes.find(attributeId);
    if (itr != mAttributes.end())
        return itr->second;
    return defaultValue;
}

bool AttributeMap::HasAttribute(const uint32 attributeID) const
{
    AttrMapConstItr itr = mAttributes.find(attributeID);
    if (itr != mAttributes.end())
        return true;
    else
        return false;
}

bool AttributeMap::HasAttribute(const uint32 attributeID, EvilNumber &value) const
{
    AttrMapConstItr itr = mAttributes.find(attributeID);
    if (itr != mAttributes.end())
    {
        value = itr->second;
        return true;
    }
    else
        return false;
}

bool AttributeMap::Change( uint32 attributeID, EvilNumber& old_val, const EvilNumber& new_val )
{
    // attributes greater than 10000 are not supported by the client.
    // these are for private internal server use only!
    if(attributeID >= 10000)
        return true;

    Notify_OnModuleAttributeChange modChange;

	modChange.ownerID = mItem->ownerID();
	modChange.itemKey = mItem->itemID();
	modChange.attributeID = attributeID;
	modChange.time = Win32TimeNow();
    EvilNumber n(new_val);
	modChange.newValue = n.GetPyObject();
	modChange.oldValue = old_val.GetPyObject();

	return SendAttributeChanges(modChange.Encode());
}

bool AttributeMap::Add( uint32 attributeID, const EvilNumber& num )
{
    // attributes greater than 10000 are not supported by the client.
    // these are for private internal server use only!
    if(attributeID >= 10000)
        return true;

    Notify_OnModuleAttributeChange modChange;

	modChange.ownerID = mItem->ownerID();
	modChange.itemKey = mItem->itemID();
	modChange.attributeID = attributeID;
	modChange.time = Win32TimeNow();
    EvilNumber n(num);
	modChange.newValue = n.GetPyObject();
	modChange.oldValue = n.GetPyObject();

	return SendAttributeChanges(modChange.Encode());
}

bool AttributeMap::SendAttributeChanges( PyTuple* attrChange )
{
    if (attrChange == NULL)
    {
        sLog.Error("AttributeMap", "unable to send NULL packet");
        return false;
    }

    // Oh hell, this character finding needs to be optimized ( redesigned so its not needed.. ).
    if( (mItem->ownerID() == 1) || (IsStation(mItem->itemID())) )
    {
        // This item is owned by the EVE System either directly, as in the case of a character object,
        // or indirectly, as in the case of a Station, which is owned by the corporation that runs it.
        // So, we don't need to queue up Destiny events in these cases.
        return true;
    }
    else
    {
        Client *client = sEntityList.FindCharacter(mItem->ownerID());
        //Client *client = this->mItem->GetItemFactory()->GetUsingClient();

        if (client == NULL)
        {
            //sLog.Error("AttributeMap::SendAttributeChanges()", "unable to find client:%u", mItem->ownerID());
            //return false;
            return true;
        }
        else
        {
            if( client->Destiny() == NULL )
            {
                //sLog.Warning( "AttributeMap::SendAttributeChanges()", "client->Destiny() returned NULL" );
                //return false;
            }
            else
                client->QueueDestinyEvent(&attrChange);

            return true;
        }
    }
}

bool AttributeMap::ResetAttribute(uint32 attrID, bool notify)
{
    EvilNumber value = mItem->GetDefaultAttribute(attrID);
    return SetAttribute(attrID, value, notify);
}

bool AttributeMap::Load()
{
    /* First, we load default attributes values using existing attribute system */
    DgmTypeAttributeSet *attr_set = sDgmTypeAttrMgr.GetDmgTypeAttributeSet( mItem->typeID() );
    if (attr_set != NULL)
    {
        DgmTypeAttributeSet::AttrSetItr itr = attr_set->attributeset.begin();

        for (; itr != attr_set->attributeset.end(); itr++)
            SetAttribute((*itr)->attributeID, (*itr)->number, false);
    }

    /* Then we load the saved attributes from the db, if there are any yet, and overwrite the defaults */
    DBQueryResult res;

	if(mDefault)
	{
		if(!sDatabase.RunQuery(res, "SELECT * FROM entity_default_attributes WHERE itemID='%u'", mItem->itemID())) {
			sLog.Error("AttributeMap (DEFAULT)", "Error in db load query: %s", res.error.c_str());
			return false;
		}
	}
	else
	{
		if(!sDatabase.RunQuery(res, "SELECT * FROM entity_attributes WHERE itemID='%u'", mItem->itemID())) {
			sLog.Error("AttributeMap", "Error in db load query: %s", res.error.c_str());
			return false;
		}
	}

    DBResultRow row;

    int amount = res.GetRowCount();
    for (int i = 0; i < amount; i++)
    {
        EvilNumber attr_value;
        res.GetRow(row);
        uint32 attributeID = row.GetUInt(1);
        if (!row.IsNull(2))
            attr_value = row.GetInt64(2);
        else
            attr_value = row.GetDouble(3);
        SetAttribute(attributeID, attr_value, false);
    }

    return true;
}

bool AttributeMap::SaveIntAttribute(uint32 attributeID, int64 value)
{
    // SAVE INTEGER ATTRIBUTE
    DBerror err;

	if(mDefault)
	{
		if(!sDatabase.RunQuery(err,
			"REPLACE INTO entity_default_attributes"
			"   (itemID, attributeID, valueInt, valueFloat)"
			" VALUES"
			"   (%u, %u, %d, NULL)",
			mItem->itemID(), attributeID, value)
		) {
			codelog(SERVICE__ERROR, "Failed to store DEFAULT attribute %d for item %u: %s", attributeID, mItem->itemID(), err.c_str());
			return false;
		}
	}
	else
	{
		if(!sDatabase.RunQuery(err,
			"REPLACE INTO entity_attributes"
			"   (itemID, attributeID, valueInt, valueFloat)"
			" VALUES"
			"   (%u, %u, %d, NULL)",
			mItem->itemID(), attributeID, value)
		) {
			codelog(SERVICE__ERROR, "Failed to store attribute %d for item %u: %s", attributeID, mItem->itemID(), err.c_str());
			return false;
		}
	}

    return true;
}

bool AttributeMap::SaveFloatAttribute(uint32 attributeID, double value)
{
    // SAVE FLOAT ATTRIBUTE
    DBerror err;

	if(mDefault)
	{
		if(!sDatabase.RunQuery(err,
			"REPLACE INTO entity_default_attributes"
			"   (itemID, attributeID, valueInt, valueFloat)"
			" VALUES"
			"   (%u, %u, NULL, %f)",
			mItem->itemID(), attributeID, value)
		) {
			codelog(SERVICE__ERROR, "Failed to store DEFAULT attribute %d for item %u: %s", attributeID, mItem->itemID(), err.c_str());
			return false;
		}
	}
	else
	{
		if(!sDatabase.RunQuery(err,
			"REPLACE INTO entity_attributes"
			"   (itemID, attributeID, valueInt, valueFloat)"
			" VALUES"
			"   (%u, %u, NULL, %f)",
			mItem->itemID(), attributeID, value)
		) {
			codelog(SERVICE__ERROR, "Failed to store attribute %d for item %u: %s", attributeID, mItem->itemID(), err.c_str());
			return false;
		}
	}

    return true;
}

/* hmmm only save 'state' related attributes... and calculate the rest on the fly....*/
/* we should save skills */
bool AttributeMap::Save()
{
    /* if nothing changed... it means this action has been successful we return true... */
    if (mChanged == false)
        return true;

    std::ostringstream Inserts;
    // start the insert into command.
    Inserts << "INSERT INTO ";
    // set the appropriate table name.
    if(mDefault)
        Inserts << "entity_default_attributes";
    else
        Inserts << "entity_attributes";
    Inserts << " (itemID, attributeID, valueInt, valueFloat) ";
    bool first = true;
    AttrMapItr itr = mAttributes.begin();
    AttrMapItr itr_end = mAttributes.end();
    for (; itr != itr_end; itr++)
    {
        // if this is the first row specify the VALUES keyword
        if(first == true)
        {
            Inserts << "VALUES";
            first = false;
        }
        // otherwise coma separate the values.
        else
            Inserts << ", ";
        // itemID and attributeID keys.
        Inserts << "(" << mItem->itemID() << ", " << itr->first << ", ";
        // the value to set.
        if ( itr->second.get_type() == evil_number_int ) {
            Inserts << itr->second.get_int() << ", NULL)";
        } else {
            Inserts << " NULL, " << itr->second.get_float() << ")";
        }
    }

    // did we get at least 1 insert?
    if(first != true)
    {
        // finish creating the command.
        Inserts << "ON DUPLICATE KEY UPDATE ";
        Inserts << "valueInt=VALUES(valueInt), ";
        Inserts << "valueFloat=VALUES(valueFloat)";
        // execute the command.
        DBerror err;
        if (!sDatabase.RunQuery(err, Inserts.str().c_str()))
        {
            sLog.Error("AttributeMap", "unable to save attributes");
            return false;
        }
    }

    mChanged = false;

    return true;
}


bool AttributeMap::SaveAttributes()
{
    return Save();
}

bool AttributeMap::Delete()
{
    // Remove all attributes from the entity_default_attributes table or entity_attributes table for this item:
    DBerror err;
    
	if(mDefault)
	{
		if(!sDatabase.RunQuery(err,
			"DELETE"
			" FROM entity_default_attributes"
			" WHERE itemID=%u",
			mItem->itemID()
		))
		{
			sLog.Error( "AttributeMap::Delete()", "Failed to delete DEFAULT item %u: %s", mItem->itemID(), err.c_str());
			return false;
		}
	}
	else
	{
		if(!sDatabase.RunQuery(err,
			"DELETE"
			" FROM entity_attributes"
			" WHERE itemID=%u",
			mItem->itemID()
		))
		{
			sLog.Error( "AttributeMap::Delete()", "Failed to delete item %u: %s", mItem->itemID(), err.c_str());
			return false;
		}
	}

	mAttributes.clear();

	mChanged = false; // just synced with database, no need to save

    return true;
}

AttributeMap::AttrMapItr AttributeMap::begin()
{
    return mAttributes.begin();
}

AttributeMap::AttrMapItr AttributeMap::end()
{
    return mAttributes.end();
}
/************************************************************************/
/* End of new attribute system                                          */
/************************************************************************/

TypeAttributeMap::TypeAttributeMap(uint32 typeID, const TypeData &_data)
{
    m_typeID = typeID;
    // set up some inventory type attributes.  These come from the invTypes table.
    mAttributes[AttrRadius] = _data.radius;
    mAttributes[AttrMass] = _data.mass;
    mAttributes[AttrVolume] = _data.volume;
    mAttributes[AttrCapacity] = _data.capacity;
    mAttributes[AttrRaceID] = _data.race;
    // get the Type Attributes
    DgmTypeAttributeSet *attr_set = sDgmTypeAttrMgr.GetDmgTypeAttributeSet( typeID );
    if (attr_set != NULL)
    {
        DgmTypeAttributeSet::AttrSetItr itr = attr_set->attributeset.begin();
        for (; itr != attr_set->attributeset.end(); itr++)
            mAttributes[(*itr)->attributeID] = (*itr)->number;
    }
}

EvilNumber TypeAttributeMap::GetAttribute( const uint32 attributeId ) const
{
    AttrMapConstItr itr = mAttributes.find(attributeId);
    if (itr != mAttributes.end())
        return itr->second;
    sLog.Error("TypeAttributeMap::GetAttribute()", "unable to find attribute: %u for type %u", attributeId, m_typeID);
    return EvilNumber(0);
}

EvilNumber TypeAttributeMap::GetAttribute( const uint32 attributeId, const EvilNumber &defaultValue ) const
{
    AttrMapConstItr itr = mAttributes.find(attributeId);
    if (itr != mAttributes.end())
        return itr->second;
    return defaultValue;
}

bool TypeAttributeMap::HasAttribute(const uint32 attributeID) const
{
    AttrMapConstItr itr = mAttributes.find(attributeID);
    if (itr != mAttributes.end())
        return true;
    else
        return false;
}

bool TypeAttributeMap::HasAttribute(const uint32 attributeID, EvilNumber &value) const
{
    AttrMapConstItr itr = mAttributes.find(attributeID);
    if (itr != mAttributes.end())
    {
        value = itr->second;
        return true;
    }
    else
        return false;
}

