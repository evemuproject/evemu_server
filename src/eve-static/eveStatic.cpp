/* 
 * File:   eveStatic.cpp
 * Author: avianrr
 * 
 * Created on March 28, 2016, 2:33 PM
 */

#include "eveStatic.h"
#include "database/dbcore.h"
#include <mutex>

bool EVEStatic::staticLoaded = false;

void EVEStatic::loadStaticData()
{
    static std::mutex sMutex;
    auto lock = std::unique_lock<std::mutex>(sMutex);
    if (staticLoaded)
    {
        return;
    }

    std::string columns = "typeID, groupID, typeName, description,"
            " graphicID, radius, mass, volume, capacity, portionSize,"
            " raceID, basePrice, published, marketGroupID, chanceOfDuplicating,"
            " iconID, soundID, dataID, typeNameID, descriptionID";
    staticLoaded = true;
}
