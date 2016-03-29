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
    Author:        eve-moo
 */

#ifndef INVCATEGORY_H
#define	INVCATEGORY_H

#include "eve-compat.h"
#include <string>
#include <memory>
#include <map>
#include <vector>

class InvCategory;
typedef std::shared_ptr<InvCategory> InvCategoryRef;

class InvCategory
{
public:
    InvCategory(uint32 _categoryID,
                std::string _categoryName,
                std::string _description,
                uint32 _iconID,
                bool _published,
                std::vector<uint32> &_groups
                );

    const uint32 categoryID;
    const std::string categoryName;
    const std::string description;
    const uint32 iconID;
    const bool published;

    /**
     * Get the InvCategory for the specified categoryID
     * @param categoryID The categoryID to find.
     * @return The InvCategory or nullptr if not found.
     */
    static std::shared_ptr<InvCategory> getCategory(uint32 categoryID)
    {
        auto itr = s_AllCategories.find(categoryID);
        if (itr == s_AllCategories.end())
        {
            return std::shared_ptr<InvCategory>();
        }
        return itr->second;
    }

    /**
     * Get the InvCategory for the specified categoryID
     * @param categoryID The categoryID to find.
     * @param type The location to store the found type.
     * @return True if type was found.
     */
    static bool getCategory(uint32 categoryID, std::shared_ptr<InvCategory> &type)
    {
        auto itr = s_AllCategories.find(categoryID);
        if (itr == s_AllCategories.end())
        {
            type.reset();
            return false;
        }
        type = itr->second;
        return true;
    }

    /**
     * Get a list of all typeIDs in this category.
     * @param pub True if only published types should be included.
     * @return The list of typeIDs.
     */
    std::vector<uint32> getTypeIDs(bool pub = false)
    {
        if (pub)
        {
            return typesPublished;
        }
        return types;
    }

    /**
     * Get a coma separated list of all typesID usable in SELECT-IN statements.
     * @param pub True if only published types should be included.
     * @return The list of types or an empty string if there are no types.
     */
    std::string getTypesIN(bool pub = false)
    {
        if (pub)
        {
            return typesINPublished;
        }
        return typesIN;
    }

private:
    InvCategory(const InvCategory& orig) = delete;
    virtual ~InvCategory();

    static std::map<uint32, std::shared_ptr<InvCategory>> s_AllCategories;

    /**
     * A list of all typeIDs in this category.
     */
    std::vector<uint32> types;
    /**
     * A list of all typdIDs in this category that are flagged as published.
     */
    std::vector<uint32> typesPublished;
    /**
     * A coma separated string of typeIDs that can be used in a SELECT-IN statement.
     */
    std::string typesIN;
    /**
     * A coma separated string of typeIDs that can be used in a SELECT-IN statement.
     * Containing only types that are flagged published.
     */
    std::string typesINPublished;
};

#endif	/* INVCATEGORY_H */

