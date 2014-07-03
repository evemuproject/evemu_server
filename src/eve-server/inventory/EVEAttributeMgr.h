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

#ifndef __EVE_ATTRIBUTE_MGR__H__INCL__
#define __EVE_ATTRIBUTE_MGR__H__INCL__

/*
 * This file contains EVE-specific derivations of attribute managers.
 */

#include "inventory/ItemRef.h"
#include "ship/dgmtypeattributeinfo.h"

class PyRep;
class TypeData;
class ItemType;
class ItemFactory;
class InventoryItem;
class InventoryDB;

/**
 * @brief rewrite of the item attribute system.
 *
 * @author Captnoord.
 * @date Juni 2010
 * @note keeping track of the base value of the attribute is not implemented.
 * Besides the fact in increases memory concumption its unclear how to design it
 * at this moment.
 */
class AttributeMap
{
public:
    /**
     * we store our keeper so we can use it in the various functions.
     * @note capt: the way I see it this isn't really needed... ( design thingy )
     *
     * @param[in] item reference to the InventoryItem for which attributes will be managed
     */
    AttributeMap(InventoryItemRef item);

    /**
     * we store our keeper so we can use it in the various functions.
     * @note capt: the way I see it this isn't really needed... ( design thingy )
	 * @note aknor: this is a secondary constructor that allows the parent object to specify whether this class instance will make use of the 'entity_default_attributes' table or the 'entity_attributes' table
     *
     * @param[in] item reference to the InventoryItem for which attributes will be managed
     * @param[in] bDefaultMap boolean indicating whether this attribute map uses 'entity_default_attributes' table or 'entity_attributes' table
     */
    AttributeMap(InventoryItemRef item, bool bDefaultMap);

	/**
     * @brief set the attribute with @num
     *
     * set the attribute with @num
     *
     * @param[in] attributeId the attribute id that needs to be changed.
     * @param[in] num the number the attribute needs to be changed in.
     *
     * @retval true  The attribute has successfully been set and queued.
     * @retval false The attribute change has not been queued but has not been changed.
     */
    bool SetAttribute(uint32 attributeId, const EvilNumber &num, bool notify = true);
	/**
     * @brief set the attribute with @num
     *
     * set the attribute with @num
     *
     * @param[in] attributeId the attribute id that needs to be changed.
     * @param[in] num the number the attribute needs to be changed in.
     *
     * @retval true  The attribute has successfully been set and queued.
     * @retval false The attribute change has not been queued but has not been changed.
     */
    bool SetAttribute(uint32 attributeId, const int64 &num, bool notify = true);
	/**
     * @brief set the attribute with @num
     *
     * set the attribute with @num
     *
     * @param[in] attributeId the attribute id that needs to be changed.
     * @param[in] num the number the attribute needs to be changed in.
     *
     * @retval true  The attribute has successfully been set and queued.
     * @retval false The attribute change has not been queued but has not been changed.
     */
    bool SetAttribute(uint32 attributeId, const double &num, bool notify = true);

    /**
     * GetAttribute
     * Retrieves the attribute of the entity.
     * @param attributeID the attribute to check for.
     * @returns the attribute value
     * @note a value of zero is returned and an error message generated if the value is not found.
     *
     * @note this function should be used very infrequently and only for specific reasons
     */
    EvilNumber GetAttribute(const uint32 attributeId) const;
    /**
     * GetAttribute
     * Retrieves the attribute of the entity.
     * @note Should only be used when the attribute might not be defined.
     * @param attributeID the attribute to check for.
     * @param defaultValue a default value to return if no attribute is found.
     * @returns the attribute value or the default value.
     * @note does not generate an error message if the value is not found.
     *
     * @note this function should be used very infrequently and only for specific reasons
     */
    EvilNumber GetAttribute(const uint32 attributeID, const EvilNumber &defaultValue) const;

    /**
     * HasAttribute
     * Checks to see if the entity has the specified attribute.
     * @param attributeID the attribute to check for.
     * @returns true if this item has the attribute 'attributeID', false if it does not have this attribute
     *
     * @note this function should be used very infrequently and only for specific reasons
     */
    bool HasAttribute(const uint32 attributeID) const;
    
    /**
     * HasAttribute
     * Checks to see if the entity has the specified attribute.
     * value not altered if attribute not found.  This could be useful for preserving a default value.
     * @param attributeID the attribute to check for.
     * @param value the location to return the attribute if it exist.
     * @returns true if this item has the attribute 'attributeID', false if it does not have this attribute
     *
     * @note this function should be used very infrequently and only for specific reasons
     */
    bool HasAttribute(const uint32 attributeID, EvilNumber &value) const;

    /* ATM we don't load or save as we assume that all attribute modifiers are calculated on the fly
     * except charge attributes but we won't handle them for now
     */
    bool Save();

	// Allow users to force changed flag to true, indicating that Save() should really save attributes to the database
	void ForceChanged() { ; }//mChanged = true; }

    bool Delete();

    // load the default attributes that come with the itemID


    typedef std::map<uint32, EvilNumber>    AttrMap;
    typedef AttrMap::iterator               AttrMapItr;
    typedef AttrMap::const_iterator         AttrMapConstItr;

    bool Load();

    /**
     * SaveAttributes
     *
     * @note this function always saves everything and doesn't take into account the fact that we should only save the
     * changes attributes.
     */
    bool SaveAttributes();
    bool SaveIntAttribute(uint32 attributeID, int64 value);
    bool SaveFloatAttribute(uint32 attributeID, double value);

    /**
     * ResetAttribute
     * Reload the attribute from the default attribute map
     * @param attrID the attribute to reset.
     * @param notify whether or not to notify the client.
     */
    bool ResetAttribute(uint32 attrID, bool notify);

    //void set_item(InventoryItem *item) {mItem = item;}

    /**
     * @brief return the begin iterator of the AttributeMap
     *
     *
     *
     * @return the begin iterator of the AttributeMap
     * @note this way to solve the attribute system problems are quite hacky... but atm its needed
     */
    AttrMapItr begin();

    /**
     * @brief return the end iterator of the AttributeMap
     *
     *
     *
     * @return the end iterator of the AttributeMap
     * @note this way to solve the attribute system problems are quite hacky... but atm its needed
     */
    AttrMapItr end();

protected:
    /**
     * @brief internal function to handle the change.
     *
     * @param[in] attributeId the attribute id that needs to be changed.
     * @param[in] num the number the attribute needs to be changed in.
     *
     * @retval true  The attribute change has successfully been set and queued.
     * @retval false The attribute change has not been queued but has been changed.
     */
    bool Change(uint32 attributeID, EvilNumber& old_val, const EvilNumber& new_val);

    /**
     * @brief internal function to handle adding attributes.
     *
     * @param[in] attributeId the attribute id that needs to be added.
     * @param[in] num the number the attribute needs to be set to.
     *
     * @retval true  The attribute has successfully been added and queued.
     * @retval false The attribute addition has not been queued and not been changed.
     */
    bool Add(uint32 attributeID, const EvilNumber& num);

    /**
     * @brief queue the attribute changes into the QueueDestinyEvent system.
     *
     * @param[in] attrChange the attribute id that needs to be added.
     *
     * @retval true  The attribute has successfully been added and queued.
     * @retval false The attribute addition has not been queued and not been changed.
     */
    bool SendAttributeChanges(PyTuple* attrChange);

    bool SaveIntAttribute(uint32 attributeID);
    bool SaveFloatAttribute(uint32 attributeID);

    /** we belong to this item..
     * @note possible design flaw because only items contain AttributeMap's so
     *       we don't need to store this.
     */
    InventoryItemRef mItem;

    /**
     * @note possible design flaw, stack corruption because of a enormous amount
     *       of 'EvilNumber' objects not fitting into the stack.
     */
    AttrMap mAttributes;

    /**
     * we set and we clear this flag when we change attributes of this item....
     * @note we should improve this idea... and only save the changed attributes...
     *       but that is for the future.
     */
    bool mChanged;

    /**
     * we set this true to tell the class methods to use attributes from 'entity_default_attributes' table
	 * instead of the normal 'entity_attributes' table
     */
    bool mDefault;
};

/**
 * class for storing attributes for item type
 */
class TypeAttributeMap
{
public:
    /**
     * we store our keeper so we can use it in the various functions.
     * @note capt: the way I see it this isn't really needed... ( design thingy )
     *
     * @param[in] item reference to the InventoryItem for which attributes will be managed
     */
    TypeAttributeMap(uint32 type, const TypeData &_data);
    /**
     * GetAttribute
     * Retrieves the attribute of the entity.
     * @param attributeID the attribute to check for.
     * @returns the attribute value
     * @note a value of zero is returned and an error message generated if the value is not found.
     *
     * @note this function should be used very infrequently and only for specific reasons
     */
    EvilNumber GetAttribute(const uint32 attributeId) const;
    /**
     * GetAttribute
     * Retrieves the attribute of the entity.
     * @note Should only be used when the attribute might not be defined.
     * @param attributeID the attribute to check for.
     * @param defaultValue a default value to return if no attribute is found.
     * @returns the attribute value or the default value.
     * @note does not generate an error message if the value is not found.
     *
     * @note this function should be used very infrequently and only for specific reasons
     */
    EvilNumber GetAttribute(const uint32 attributeID, const EvilNumber &defaultValue) const;

    /**
     * HasAttribute
     * Checks to see if the entity has the specified attribute.
     * @param attributeID the attribute to check for.
     * @returns true if this item has the attribute 'attributeID', false if it does not have this attribute
     *
     * @note this function should be used very infrequently and only for specific reasons
     */
    bool HasAttribute(const uint32 attributeID) const;
    
    /**
     * HasAttribute
     * Checks to see if the entity has the specified attribute.
     * value not altered if attribute not found.  This could be useful for preserving a default value.
     * @param attributeID the attribute to check for.
     * @param value the location to return the attribute if it exist.
     * @returns true if this item has the attribute 'attributeID', false if it does not have this attribute
     *
     * @note this function should be used very infrequently and only for specific reasons
     */
    bool HasAttribute(const uint32 attributeID, EvilNumber &value) const;
    
    typedef std::map<uint32, EvilNumber>    AttrMap;
    typedef AttrMap::iterator               AttrMapItr;
    typedef AttrMap::const_iterator         AttrMapConstItr;
    
protected:
    /**
     * @note possible design flaw, stack corruption because of a enormous amount
     *       of 'EvilNumber' objects not fitting into the stack.
     */
    AttrMap mAttributes;
    
    uint32 m_typeID;
};

#endif /* __EVE_ATTRIBUTE_MGR__H__INCL__ */
