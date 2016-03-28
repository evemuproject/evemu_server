/* 
 * File:   invTypes.h
 * Author: avianrr
 *
 * Created on March 28, 2016, 2:20 PM
 */

#ifndef INVTYPES_H
#define	INVTYPES_H

#include "eve-compat.h"
#include <string>

class invTypes
{
public:
    invTypes(uint32 _typeID,
             uint32 _groupID,
             std::string _typeName,
             std::string _description,
             uint32 _graphicID,
             double _radius,
             double _mass,
             double _volume,
             double _capacity,
             uint32 _portionSize,
             uint32 _raceID,
             double _basePrice,
             bool _published,
             uint32 _marketGroupID,
             double _chanceOfDuplicating,
             uint32 _iconID,
             uint32 _soundID,
             uint32 _dataID,
             uint32 _typeNameID,
             uint32 _descriptionID
             );
    virtual ~invTypes();

    // From invTypes.
    const uint32 typeID;
    const uint32 groupID;
    const std::string typeName;
    const std::string description;
    const uint32 graphicID;
    const double radius;
    const double mass;
    const double volume;
    const double capacity;
    const uint32 portionSize;
    const uint32 raceID;
    const double basePrice;
    const bool published;
    const uint32 marketGroupID;
    const double chanceOfDuplicating;
    const uint32 iconID;
    // From extInvTypes
    const uint32 soundID;
    const uint32 dataID;
    const uint32 typeNameID;
    const uint32 descriptionID;

private:
    invTypes(const invTypes& orig) = delete;

};

#endif	/* INVTYPES_H */

