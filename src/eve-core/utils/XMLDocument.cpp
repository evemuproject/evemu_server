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

#include "XMLDocument.h"

#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <map>

using boost::property_tree::ptree;

XMLElement::XMLElement(const std::string nme, const std::string val)
{
    name = nme;
    value = val;
}

XMLElement::XMLElement(const std::string nme, const ptree &tree)
{
    name = nme;
    value = tree.get_value<std::string>();
    for (const ptree::value_type &entry : tree)
    {
        if (entry.first == "<xmlattr>")
        {
            continue;
        }
        // Create new child element.
        std::shared_ptr<XMLElement> element(new XMLElement(entry.first, entry.second));
        // Parse the attributes.
        for (ptree::value_type const& attr : entry.second.get_child("<xmlattr>", ptree()))
        {
            element->attributes[attr.first] = attr.second.get_value<std::string>();
        }
        // Add the element to the child list.
        children.push_back(element);
    }
}

XMLElement::XMLElement(const XMLElement& orig)
{
    std::unique_lock<std::mutex> uLock = orig.getLock();
    name = orig.name;
    value = orig.value;
    for (auto attr : orig.attributes)
    {
        attributes[attr.first] = attr.second;
    }
    for (auto child : orig.children)
    {
        std::shared_ptr<XMLElement> nChild(new XMLElement(*child));
        children.push_back(nChild);
    }
}

XMLElement::~XMLElement() { }

std::vector<std::string> XMLElement::getAttributeNames() const
{
    std::unique_lock<std::mutex> uLock = getLock();
    std::vector<std::string> names;
    for (auto entry : attributes)
    {
        names.push_back(entry.first);
    }
    return names;
}

bool XMLElement::hasAttribute(std::string attr) const
{
    std::unique_lock<std::mutex> uLock = getLock();
    return attributes.find(attr) != attributes.end();
}

std::string XMLElement::getAttribute(std::string attr) const
{
    std::unique_lock<std::mutex> uLock = getLock();
    auto itr = attributes.find(attr);
    if (itr == attributes.end())
    {
        return "";
    }
    return itr->second;
}

std::vector<std::shared_ptr<XMLElement>> XMLElement::getChildren() const
{
    std::unique_lock<std::mutex> uLock = getLock();
    return std::vector<std::shared_ptr < XMLElement >> (children);
}

std::vector<std::shared_ptr<XMLElement>> XMLElement::getChildren(std::string tag) const
{
    std::unique_lock<std::mutex> uLock = getLock();
    std::vector<std::shared_ptr < XMLElement>> childs;
    for (auto child : children)
    {
        if (child->name == tag)
        {
            childs.push_back(child);
        }
    }
    return childs;
}

std::string XMLElement::format(const std::string current, const std::string indent) const
{
    std::unique_lock<std::mutex> uLock = getLock();
    std::stringstream out;
    std::string nInd = current;
    if (!name.empty())
    {
        nInd += indent;
        out << current << "<" << name;
    }
    for (auto attr : attributes)
    {
        out << " " << attr.first << "=\"" << attr.second << "\"";
    }
    if (value.length() > 0 || !children.empty())
    {
        if (!name.empty())
        {
            out << ">";
        }
        if (value.length() > 0)
        {
            out << value;
        }
        if (!children.empty())
        {
            if (!name.empty())
            {
                out << std::endl;
            }
            for (auto child : children)
            {
                out << child->format(nInd, indent);
            }
            out << current;
        }
        if (!name.empty())
        {
            out << "</" << name << ">" << std::endl;
        }
    }
    else
    {
        // Empty tag, no value of children.
        if (!name.empty())
        {
            out << "/>" << std::endl;
        }
    }
    return out.str();
}

//--------------------------------------------------

XMLDocument::XMLDocument() { }

XMLDocument::XMLDocument(const std::string &doc)
{
    // Put document into a stream for parsing.
    std::stringstream docStream;
    docStream << doc;
    ptree tree;
    // Read the XML stream.
    boost::property_tree::xml_parser::read_xml(docStream, tree, boost::property_tree::xml_parser::trim_whitespace);
    root.reset(new XMLElement("", tree));
}

XMLDocument::XMLDocument(std::stringstream &docStream)
{
    ptree tree;
    // Read the XML stream.
    boost::property_tree::xml_parser::read_xml(docStream, tree, boost::property_tree::xml_parser::trim_whitespace);
    root.reset(new XMLElement("", tree));
}

XMLDocument::XMLDocument(const XMLDocument& orig)
{
    if (orig.root.get() != nullptr)
    {
        root.reset(new XMLElement(*orig.root.get()));
    }
}

XMLDocument::~XMLDocument() { }

std::shared_ptr<XMLDocument> XMLDocument::loadFile(std::string file)
{
    std::ifstream in(file);
    std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return std::shared_ptr<XMLDocument>(new XMLDocument(contents));
}

std::string XMLDocument::format(const std::string indent) const
{
    if (root.get() != NULL)
    {
        return root->format("", indent);
    }
    return "";
}
