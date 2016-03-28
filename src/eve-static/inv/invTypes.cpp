/* 
 * File:   invTypes.cpp
 * Author: avianrr
 * 
 * Created on March 28, 2016, 2:20 PM
 */

#include "invTypes.h"

invTypes::invTypes(uint32 _typeID,
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
                   ) :
typeID(_typeID),
groupID(_groupID),
typeName(_typeName),
description(_description),
graphicID(_graphicID),
radius(_radius),
mass(_mass),
volume(_volume),
capacity(_capacity),
portionSize(_portionSize),
raceID(_raceID),
basePrice(_basePrice),
published(_published),
marketGroupID(_marketGroupID),
chanceOfDuplicating(_chanceOfDuplicating),
iconID(_iconID),
soundID(_soundID),
dataID(_dataID),
typeNameID(_typeNameID),
descriptionID(_descriptionID) { }

invTypes::~invTypes() { }

