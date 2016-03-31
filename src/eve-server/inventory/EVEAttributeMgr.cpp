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

#include "Client.h"
#include "EntityList.h"
#include "inventory/EVEAttributeMgr.h"
#include "inventory/InventoryDB.h"
#include "inventory/InventoryItem.h"

/************************************************************************/
/* Start of new attribute system                                        */
/************************************************************************/
AttributeMap::AttributeMap( InventoryItem & item ) : mItem(item), mChanged(true), mDefault(false)
{
    // load the initial attributes for this item
    //Load();
}

AttributeMap::AttributeMap( InventoryItem & item, bool bDefaultMap ) : mItem(item), mChanged(true), mDefault(bDefaultMap)
{
    // load the initial attributes for this item, if we are acting as container for "default" attributes
    //if(mDefault)
	//	Load();
}

bool AttributeMap::SetAttribute( uint32 attributeId, EvilNumber &num, bool nofity /*= true*/ )
{
    AttrMapItr itr = mAttributes.find(attributeId);

    /* most attribute have default value's which are related to the item type */
    if (itr == mAttributes.end()) {
        mAttributes.insert(std::make_pair(attributeId, num));
		mChanged = true;	// Mark the map as having been modified by a new attribute being added
        if (nofity == true)
            return Add(attributeId, num);
        return true;
    }

    if (itr->second == num && itr->second.get_type() == num.get_type())
    {
        return false;
    }

    // notify dogma to change the attribute, if we are unable to queue the change
    // event. Don't change the value.
    if (nofity == true)
        if (!Change(attributeId, itr->second, num))
            return false;

    itr->second = num;

	mChanged = true;	// Mark the map as having been modified

    return true;
}

EvilNumber AttributeMap::GetAttribute( const uint32 attributeId ) const
{
    AttrMapConstItr itr = mAttributes.find(attributeId);
    if (itr != mAttributes.end()) {
        return itr->second;
    }
    else
    {
        // ONLY output ERROR message for a "missing" attributeID if it is not in the list of commonly "not found" attributes:
        switch( attributeId)
        {
            case AttrCustomCharismaBonus:
            case AttrCustomWillpowerBonus:
            case AttrCustomPerceptionBonus:
            case AttrCustomMemoryBonus:
            case AttrCustomIntelligenceBonus:
            case AttrCharismaBonus:
            case AttrIntelligenceBonus:
            case AttrMemoryBonus:
            case AttrPerceptionBonus:
            case AttrWillpowerBonus:
            case AttrCapacity:
            case AttrQuantity:
            case AttrRequiredSkill1:
            case AttrRequiredSkill2:
            case AttrRequiredSkill3:
            case AttrRequiredSkill4:
            case AttrRequiredSkill5:
            case AttrRequiredSkill6:
            case AttrCanFitShipGroup1:
            case AttrCanFitShipGroup2:
            case AttrCanFitShipGroup3:
            case AttrCanFitShipGroup4:
            case AttrCanFitShipType1:
            case AttrCanFitShipType2:
            case AttrCanFitShipType3:
            case AttrCanFitShipType4:
            case AttrSubSystemSlot:
                // DO NOT OUTPUT AN ERROR ON THESE MISSING ATTRIBUTES SINCE THEY ARE COMMONLY "MISSING" FROM MANY ITEMS
                break;

            default:
                SysLog::Error("AttributeMap::GetAttribute()", "unable to find attribute: %u for item %u, '%s' of type %u", attributeId, mItem.itemID(), mItem.itemName().c_str(), mItem.typeID());
                break;
        }

        return EvilNumber(0);
    }
}

bool AttributeMap::HasAttribute(const uint32 attributeID) const
{
    AttrMapConstItr itr = mAttributes.find(attributeID);
    if (itr != mAttributes.end())
        return true;
    else
        return false;
}

bool AttributeMap::Change( uint32 attributeID, EvilNumber& old_val, EvilNumber& new_val )
{
   Notify_OnModuleAttributeChange modChange;

	modChange.ownerID = mItem.ownerID();
	modChange.itemKey = mItem.itemID();
	modChange.attributeID = attributeID;
	modChange.time = Win32TimeNow();
	modChange.newValue = new_val.GetPyObject();
	modChange.oldValue = old_val.GetPyObject();

	return SendAttributeChanges(modChange.Encode());
}

bool AttributeMap::Add( uint32 attributeID, EvilNumber& num )
{
  Notify_OnModuleAttributeChange modChange;

	modChange.ownerID = mItem.ownerID();
	modChange.itemKey = mItem.itemID();
	modChange.attributeID = attributeID;
	modChange.time = Win32TimeNow();
	modChange.newValue = num.GetPyObject();
	modChange.oldValue = num.GetPyObject();

	return SendAttributeChanges(modChange.Encode());
}

bool AttributeMap::SendAttributeChanges( PyTuple* attrChange )
{
    if (attrChange == NULL)
    {
        SysLog::Error("AttributeMap", "unable to send NULL packet");
        return false;
    }

    // Oh hell, this character finding needs to be optimized ( redesigned so its not needed.. ).
    if( (mItem.ownerID() == 1) || (IsStation(mItem.itemID())) )
    {
        // This item is owned by the EVE System either directly, as in the case of a character object,
        // or indirectly, as in the case of a Station, which is owned by the corporation that runs it.
        // So, we don't need to queue up Destiny events in these cases.
        return true;
    }
    else
    {
        Client *client = EntityList::FindCharacter(mItem.ownerID());
        //Client *client = ItemFactory::GetUsingClient();

        if (client == NULL)
        {
            //Log::Error("AttributeMap::SendAttributeChanges()", "unable to find client:%u", mItem.ownerID());
            //return false;
            return true;
        }
        else
        {
            if( client->Destiny() == NULL )
            {
                //Log::Warning( "AttributeMap::SendAttributeChanges()", "client->Destiny() returned NULL" );
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
    //this isn't particularly efficient, but until I write a better solution, this will do
    DBQueryResult res;

    if (!DBcore::RunQuery(res, "SELECT * FROM dgmTypeAttributes WHERE typeID='%u'", mItem.typeID()))
    {
        SysLog::Error("AttributeMap", "Error in db load query: %s", res.error.c_str());
        return false;
    }

    DBResultRow row;
    EvilNumber attrVal;
    uint32 attributeID;

    int amount = res.GetRowCount();
    for (int i = 0; i < amount; i++)
    {
        res.GetRow(row);
        attributeID = row.GetUInt(1);
        if( attributeID == attrID )
        {
            if(!row.IsNull(2))
                attrVal = row.GetUInt64(2);
            else
                attrVal = row.GetDouble(3);

            SetAttribute(attributeID, attrVal, notify);
        }
    }

    return true;

}

bool AttributeMap::Load()
{
    /* First, we load default attributes values using existing attribute system */
    DgmTypeAttributeSet *attr_set = sDgmTypeAttrMgr.GetDgmTypeAttributeSet( mItem.typeID() );
    if (attr_set == NULL)
        return false;

    DgmTypeAttributeSet::AttrSetItr itr = attr_set->attributeset.begin();

    for (; itr != attr_set->attributeset.end(); itr++)
        SetAttribute((*itr)->attributeID, (*itr)->number, false);

    /* Then we load the saved attributes from the db, if there are any yet, and overwrite the defaults */
    DBQueryResult res;

	if(mDefault)
    {
        if (!DBcore::RunQuery(res, "SELECT * FROM srvEntity_default_attributes WHERE itemID='%u'", mItem.itemID()))
        {
			SysLog::Error("AttributeMap (DEFAULT)", "Error in db load query: %s", res.error.c_str());
			return false;
		}
	}
	else
    {
        if (!DBcore::RunQuery(res, "SELECT * FROM srvEntity_attributes WHERE itemID='%u'", mItem.itemID()))
        {
			SysLog::Error("AttributeMap", "Error in db load query: %s", res.error.c_str());
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

    /*
        /// EXISTING AttributeMap::Load() function
        DBQueryResult res;

        if(!DBcore::RunQuery(res,"SELECT * FROM srvEntity_attributes WHERE itemID='%u'", mItem.itemID())) {
        Log::Error("AttributeMap", "Error in db load query: %s", res.error.c_str());
        return false;
    }

    DBResultRow row;

    int amount = res.GetRowCount();

    // Right now, assume that we need to load all attributes with default values from dgmTypeAttributes table
    // IF AND ONLY IF the number of attributes pulled from the srvEntity_attributes table for this item is ZERO:
    if( amount > 0 )
    {
        // This item was found in the 'srvEntity_attributes' table, so load all attributes found there
        // into the Attribute Map for this item:
        for (int i = 0; i < amount; i++)
        {
            res.GetRow(row);
            EvilNumber attr_value;
            uint32 attributeID = row.GetUInt(1);
            if ( !row.IsNull(2) )
                attr_value = row.GetInt64(2);
            else if( !row.IsNull(3) )
                attr_value = row.GetDouble(3);
            else
                Log::Error( "AttributeMap::Load()", "Both valueInt and valueFloat fields of this (itemID,attributeID) = (%u,%u) are NULL.", row.GetInt(0), attributeID );

            SetAttribute(attributeID, attr_value, false);
            //Add(attributeID, attr_value);
        }
    }
    else
    {
        // This item was NOT found in the 'srvEntity_attributes' table, so let's assume that
        // this item was just created.
        // 1) Get complete list of attributes with default values from dgmTypeAttributes table using the item's typeID:
        DgmTypeAttributeSet *attr_set = sDgmTypeAttrMgr.GetDgmTypeAttributeSet( mItem.typeID() );
        if (attr_set == NULL)
            return false;

        DgmTypeAttributeSet::AttrSetItr itr = attr_set->attributeset.begin();

        // Store all these attributes to the item's AttributeMap
        for (; itr != attr_set->attributeset.end(); itr++)
        {
            SetAttribute((*itr)->attributeID, (*itr)->number, false);
            //Add((*itr)->attributeID, (*itr)->number);
        }

        // 2) Save these newly created and loaded attributes to the 'srvEntity_attributes' table
        SaveAttributes();
    }

    return true;
*/
}

bool AttributeMap::SaveIntAttribute(uint32 attributeID, int64 value)
{
    // SAVE INTEGER ATTRIBUTE
    DBerror err;

	if(mDefault)
    {
        if (!DBcore::RunQuery(err,
			"REPLACE INTO srvEntity_default_attributes"
			"   (itemID, attributeID, valueInt, valueFloat)"
			" VALUES"
			"   (%u, %u, %d, NULL)",
			mItem.itemID(), attributeID, value)
		) {
			codelog(SERVICE__ERROR, "Failed to store DEFAULT attribute %d for item %u: %s", attributeID, mItem.itemID(), err.c_str());
			return false;
		}
	}
	else
    {
        if (!DBcore::RunQuery(err,
			"REPLACE INTO srvEntity_attributes"
			"   (itemID, attributeID, valueInt, valueFloat)"
			" VALUES"
			"   (%u, %u, %d, NULL)",
			mItem.itemID(), attributeID, value)
		) {
			codelog(SERVICE__ERROR, "Failed to store attribute %d for item %u: %s", attributeID, mItem.itemID(), err.c_str());
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
        if (!DBcore::RunQuery(err,
			"REPLACE INTO srvEntity_default_attributes"
			"   (itemID, attributeID, valueInt, valueFloat)"
			" VALUES"
			"   (%u, %u, NULL, %f)",
			mItem.itemID(), attributeID, value)
		) {
			codelog(SERVICE__ERROR, "Failed to store DEFAULT attribute %d for item %u: %s", attributeID, mItem.itemID(), err.c_str());
			return false;
		}
	}
	else
    {
        if (!DBcore::RunQuery(err,
			"REPLACE INTO srvEntity_attributes"
			"   (itemID, attributeID, valueInt, valueFloat)"
			" VALUES"
			"   (%u, %u, NULL, %f)",
			mItem.itemID(), attributeID, value)
		) {
			codelog(SERVICE__ERROR, "Failed to store attribute %d for item %u: %s", attributeID, mItem.itemID(), err.c_str());
			return false;
		}
	}

    return true;
}

/* hmmm only save 'state' related attributes... and calculate the rest on the fly....*/
/* we should save skills */
bool AttributeMap::Save()
{
    bool success = false;

    /* if nothing changed... it means this action has been successful we return true... */
    if (mChanged == false)
        return true;

    AttrMapItr itr = mAttributes.begin();
    AttrMapItr itr_end = mAttributes.end();
    std::string values;
    for (; itr != itr_end; itr++)
    {
        char buf[1024];
        if (itr->second.get_type() == evil_number_int)
        {
            std::sprintf(buf, "(%u, %u, %" PRId64 ", NULL)",
                         mItem.itemID(), itr->first, itr->second.get_int());
        }
        else if (itr->second.get_type() == evil_number_float)
        {
            std::sprintf(buf, "(%u, %u, NULL, %f)",
                         mItem.itemID(), itr->first, itr->second.get_float());
        }
        if (values.length() > 0)
        {
            values += ", ";
        }
        values += buf;
    }
    if (values.length() > 0)
    {
        DBerror err;
        if (mDefault)
        {
            success = DBcore::RunQuery(err,
                                       "REPLACE INTO srvEntity_default_attributes (itemID, attributeID, valueInt, valueFloat) VALUES %s",
                                       values.c_str());
        }
        else
        {
            success = DBcore::RunQuery(err,
                                       "REPLACE INTO srvEntity_attributes (itemID, attributeID, valueInt, valueFloat) VALUES %s",
                                       values.c_str());
        }

        if (!success)
        {
            SysLog::Error("AttributeMap", "unable to save attribute");
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
    // Remove all attributes from the srvEntity_default_attributes table or srvEntity_attributes table for this item:
    DBerror err;

	if(mDefault)
    {
        if (!DBcore::RunQuery(err,
			"DELETE"
			" FROM srvEntity_default_attributes"
			" WHERE itemID=%u",
			mItem.itemID()
		))
		{
			SysLog::Error( "AttributeMap::Delete()", "Failed to delete DEFAULT item %u: %s", mItem.itemID(), err.c_str());
			return false;
		}
	}
	else
    {
        if (!DBcore::RunQuery(err,
			"DELETE"
			" FROM srvEntity_attributes"
			" WHERE itemID=%u",
			mItem.itemID()
		))
		{
			SysLog::Error( "AttributeMap::Delete()", "Failed to delete item %u: %s", mItem.itemID(), err.c_str());
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
