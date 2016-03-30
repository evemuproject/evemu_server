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
    Author:        Bloody.Rabbit
*/

#ifndef __BLUEPRINT_ITEM__H__INCL__
#define __BLUEPRINT_ITEM__H__INCL__

#include "inv/InvBlueprintType.h"
#include "inventory/InventoryItem.h"

/*
 * Basic container for raw blueprint data.
 */
class BlueprintData {
public:
    BlueprintData(
        bool _copy = false,
        uint32 _materialLevel = 0,
        uint32 _productivityLevel = 0,
        int32 _licensedProductionRunsRemaining = 0
    );

    // Content:
    bool copy;
    uint32 materialLevel;
    uint32 productivityLevel;
    int32 licensedProductionRunsRemaining;
};

/*
 * InventoryItem, which represents blueprint
 */
class Blueprint
: public InventoryItem
{
    friend class InventoryItem;    // to let it construct us
public:
    /**
     * Loads blueprint from DB.
     *
     * @param[in] blueprintID ID of blueprint to load.
     * @return Pointer to new Blueprint object; NULL if failed.
     */
    static BlueprintRef Load(uint32 blueprintID);
    /**
     * Spawns new blueprint.
     *
     * @param[in] data Item data (for srvEntity table).
     * @param[in] bpData Blueprint-specific data.
     * @return Pointer to new Blueprint object; NULL if failed.
     */
    static BlueprintRef Spawn(ItemData &data, BlueprintData &bpData);

/*
     * Public fields:
     */
    const InvBlueprintTypeRef blueprintType() const
    {
        return m_blueprintType;
    }

    const InvBlueprintTypeRef parentBlueprintType() const
    {
        return InvBlueprintType::getBlueprintType(m_blueprintType->parentBlueprintTypeID);
    }

    bool copy() const
    {
        return (m_copy);
    }
    uint32                  materialLevel() const { return(m_materialLevel); }
    uint32                  productivityLevel() const { return(m_productivityLevel); }
    int32                   licensedProductionRunsRemaining() const { return(m_licensedProductionRunsRemaining); }

    /*
     * Primary public interface:
     */
    void Delete();

    // Copy:
    void SetCopy(bool copy);

    // Material level:
    void SetMaterialLevel(uint32 materialLevel);
    bool AlterMaterialLevel(int32 materialLevelChange);

    // Productivity level:
    void SetProductivityLevel(uint32 productivityLevel);
    bool AlterProductivityLevel(int32 producitvityLevelChange);

    // Licensed production runs:
    void SetLicensedProductionRunsRemaining(int32 licensedProductionRunsRemaining);
    void AlterLicensedProductionRunsRemaining(int32 licensedProductionRunsRemainingChange);

    /*
     * Helper routines:
     */
    // overload to split the blueprints properly
    InventoryItemRef Split(int32 qty_to_take, bool notify=true) { return SplitBlueprint( qty_to_take, notify ); }
    BlueprintRef SplitBlueprint(int32 qty_to_take, bool notify=true);

    // overload to do proper merge
    bool Merge(InventoryItemRef to_merge, int32 qty=0, bool notify=true);    //consumes ref!

    // some blueprint-related stuff

    bool infinite() const
    {
        return (licensedProductionRunsRemaining() < 0);
    }

    double wasteFactor() const
    {
        return ((m_blueprintType->wasteFactor / 100.0) / (1 + materialLevel()));
    }

    double materialMultiplier() const
    {
        return (1.0 + wasteFactor());
    }

    double timeMultiplier() const
    {
        return (1.0 - (timeSaved() / m_blueprintType->productionTime));
    }

    double timeSaved() const
    {
        return ((1.0 - (1.0 / (1 + productivityLevel()))) * m_blueprintType->productivityModifier);
    }

    InvTypeRef productType()
    {
        InvType::getType(m_blueprintType->productTypeID);
    }
    /*
     * Primary public packet builders:
     */
    PyDict *GetBlueprintAttributes() const;

protected:
    Blueprint(
        uint32 _blueprintID,
        // InventoryItem stuff:
              const InvTypeRef _bpType,
        const ItemData &_data,
        // Blueprint stuff:
        const BlueprintData &_bpData
    );

    /*
     * Member functions
     */
    using InventoryItem::_Load;

    // Template loader:
    template<class _Ty>
    static RefPtr<_Ty> _LoadItem(uint32 blueprintID,
        // InventoryItem stuff:
                                 const InvTypeRef bpType, const ItemData &data)
    {
        // check it's blueprint type
        if (bpType->getCategoryID() != EVEDB::invCategories::Blueprint)
        {
            SysLog::Error("Blueprint", "Trying to load %s as Blueprint.", bpType->getCategory()->categoryName.c_str());
            return RefPtr<_Ty>();
        }

        // we are blueprint; pull additional blueprint info
        BlueprintData bpData;
        if( !InventoryDB::GetBlueprint( blueprintID, bpData ) )
            return RefPtr<_Ty>();

        return _Ty::template _LoadBlueprint<_Ty>( blueprintID, bpType, data, bpData );
    }

    // Actual loading stuff:
    template<class _Ty>
    static RefPtr<_Ty> _LoadBlueprint(uint32 blueprintID,
        // InventoryItem stuff:
                                      const InvTypeRef bpType, const ItemData &data,
        // Blueprint stuff:
        const BlueprintData &bpData
    );

    static uint32 _Spawn(
        // InventoryItem stuff:
        ItemData &data,
        // Blueprint stuff:
        BlueprintData &bpData
    );

    void SaveBlueprint() const;

    /*
     * Member variables
     */
    bool      m_copy;
    uint32    m_materialLevel;
    uint32    m_productivityLevel;
    int32 m_licensedProductionRunsRemaining;
    InvBlueprintTypeRef m_blueprintType;
};

#endif /* !__BLUEPRINT_ITEM__H__INCL__ */

