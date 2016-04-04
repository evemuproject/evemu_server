/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2016 The EVEmu Team
    For the latest information visit http://evemu.mmoforge.org
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
    Author:     eve-moo
 */

#ifndef XMLDOCUMENT_H
#define	XMLDOCUMENT_H

#include <mutex>
#include <vector>
#include <map>
#include <boost/property_tree/ptree.hpp>

class XMLDocument;

class XMLElement
{
    friend XMLDocument;
public:
    XMLElement(const std::string nme, const std::string val);
    XMLElement(const std::string nme, const boost::property_tree::ptree &tree);
    XMLElement(const XMLElement& orig);
    virtual ~XMLElement();

    /**
     * Get the name of the element.
     * @return The name of the element.
     */
    std::string getName() const
    {
        return name;
    };

    /**
     * Get the string value of the element.
     * @return The string value of the element.
     */
    std::string getValue() const
    {
        return value;
    };

    /**
     * Get the names of all attributes of this element.
     * @return The list of attribute names.
     */
    std::vector<std::string> getAttributeNames() const;

    /**
     * Check if the element has the named attribute.
     * @param attr The attribute to check for.
     * @return True if the attribute exists. False if not.
     */
    bool hasAttribute(std::string attr) const;

    /**
     * Get the value of the attribute.
     * @param attr The attribute to get.
     * @return The value of the attribute.
     * @throws AttributeNotFound
     */
    std::string getAttribute(std::string attr) const;

    /**
     * Get all child elements.
     * @return The list of child elements.
     */
    std::vector<std::shared_ptr<XMLElement>> getChildren() const;

    /**
     * Get a list of child elements with the specified tag name.
     * @param tag The tag to find.
     * @return The list of elements.
     */
    std::vector<std::shared_ptr<XMLElement>> getChildren(std::string tag) const;

private:
    mutable std::mutex lockPtr;
    std::string name;
    std::string value;
    std::map<std::string, std::string> attributes;
    std::vector<std::shared_ptr<XMLElement>> children;

    inline std::unique_lock<std::mutex> getLock() const
    {
        return std::unique_lock<std::mutex>(lockPtr);
    }

    std::string format(const std::string current, const std::string indent) const;
};

class XMLDocument
{
public:
    XMLDocument();
    XMLDocument(const std::string &doc);
    XMLDocument(std::stringstream &docStream);
    XMLDocument(const XMLDocument& orig);
    virtual ~XMLDocument();

    /**
     * Get the documents root element.
     * @return The root element.
     */
    std::shared_ptr<XMLElement> getRoot() const
    {
        return root;
    };

    /**
     * Return a formated string representation of the document.
     * @param indent The indention value to use.
     * @return The formated document.
     */
    std::string format(const std::string indent) const;

    /**
     * Create a document from a file.
     * @param file The file to load.
     * @return The document.
     */
    static std::shared_ptr<XMLDocument> loadFile(std::string file);
private:
    std::shared_ptr<XMLElement> root;

};
#endif
