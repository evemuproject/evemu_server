
 /**
  * @name RamMethods.cpp
  *   methods for R.A.M. activities
  *
  * @Author:         Allan
  * @date:          9Jan18
  */

#include "PyCallable.h"

#include "../eve-common/EVE_Character.h"
#include "Client.h"
#include "manufacturing/Blueprint.h"
#include "manufacturing/RamMethods.h"
#include "station/StationDataMgr.h"

static const uint32 RAM_PRODUCTION_TIME_LIMIT = 60*60*24*30;   //30 days

/*
 * # Manufacturing Logging:
 * MANUF__ERROR
 * MANUF__WARNING
 * MANUF__MESSAGE
 * MANUF__INFO
 * MANUF__DEBUG
 * MANUF__TRACE
 * MANUF__DUMP
 */

/*
 *    NOT IMPLEMENTED EXCEPTIONS:
 ************************************
 *    RamRemoteInstalledItemImpounded             - impound of installedItem
 *    RamInstallJob_InstalledItemChanged          - some cache expiration??
 */


void RamMethods::ActivityCheck(Client* const pClient, const Call_InstallJob& args, BlueprintRef bpRef)
{
    if (bpRef.get() == nullptr)
        throw(PyException(MakeUserError("RamInventionNoOutput")));

    // check validity of activity
    if ((args.activityID < EvERam::Activity::Manufacturing)
    or  (args.activityID > EvERam::Activity::Invention))
        throw(PyException(MakeUserError("RamAssemblyLineHasNoActivity")));

    const ItemType* pType(nullptr);
    switch(args.activityID) {
        case EvERam::Activity::Manufacturing: {
            if (!bpRef->infinite()
            and ((bpRef->runs() - args.runs) < 0))
                    throw(PyException(MakeUserError("RamTooManyProductionRuns")));

            pType = &bpRef->productType();
        } break;
        case EvERam::Activity::ResearchMaterial:
        case EvERam::Activity::ResearchTime: {
            if (bpRef->copy())
                throw(PyException(MakeUserError("RamCannotResearchABlueprintCopy")));
            pType = &bpRef->type();
        } break;
        case EvERam::Activity::Copying: {
            if (bpRef->copy())
                throw(PyException(MakeUserError("RamCannotCopyABlueprintCopy")));
            pType = &bpRef->type();
        } break;
        case EvERam::Activity::Invention: {
            if (!bpRef->copy() or bpRef->infinite())
                throw(PyException(MakeUserError("RamCannotInventABlueprintOriginal")));

            uint32 pTypeID = FactoryDB::GetTech2Blueprint(bpRef->typeID());
            if (pTypeID == 0)
                throw(PyException(MakeUserError("RamInventionNoOutput")));

            if (bpRef->runs() < 1)
                throw(PyException(MakeUserError("RamTooManyProductionRuns")));

            pType = &bpRef->productType();
        } break;
        case EvERam::Activity::ReverseEngineering:  // RE is ONLY at experimental POS module...cannot do RE in stations.  right now, this will never hit.
        case EvERam::Activity::ResearchTech:    // cannot find any reference to this.  not used?
        case EvERam::Activity::Duplicating:     // ancient pre-apoc 'copy' activity.  no longer used.
        default: {
            // not supported
            sLog.Error("RAM::InstallJob()", "Unsupported Activity %u sent by %s(%u).", args.activityID, pClient->GetName(), pClient->GetCharacterID());
            throw(PyException(MakeUserError("RamActivityInvalid")));
        }
    }

    if (pType == nullptr)
        throw(PyException(MakeUserError("RamNoKnownOutputType")));

    if (!FactoryDB::IsProducableBy(args.AssemblyLineID, pType))
        throw(PyException(MakeUserError("RamBadEndProductForActivity")));
}

void RamMethods::JobsCheck(Character* pChar, const Call_InstallJob& args)
{
    if (args.activityID == EvERam::Activity::Manufacturing) {
        uint32 jobCount = FactoryDB::CountManufacturingJobs(pChar->itemID());
        uint charMaxJobs = pChar->GetAttribute(AttrManufactureSlotLimit).get_int()
                            + pChar->GetSkillLevel(EvESkill::MassProduction)
                            + pChar->GetSkillLevel(EvESkill::AdvancedMassProduction);

        if (charMaxJobs <= jobCount) {
            std::map<std::string, PyRep *> exceptArgs;
            exceptArgs["current"] = new PyInt(jobCount);
            exceptArgs["max"] = new PyInt(charMaxJobs);
            throw(PyException(MakeUserError("MaxFactorySlotUsageReached", exceptArgs)));
        }
    } else {
        uint charMaxJobs = pChar->GetAttribute(AttrMaxLaborotorySlots).get_int()
                            + pChar->GetSkillLevel(EvESkill::LaboratoryOperation)
                            + pChar->GetSkillLevel(EvESkill::AdvancedLaboratoryOperation);

        uint32 jobCount = FactoryDB::CountResearchJobs(pChar->itemID());
        if (charMaxJobs <= jobCount) {
            std::map<std::string, PyRep *> exceptArgs;
            exceptArgs["current"] = new PyInt(jobCount);
            exceptArgs["max"] = new PyInt(charMaxJobs);
            throw(PyException(MakeUserError("MaxResearchFacilitySlotUsageReached", exceptArgs)));
        }
    }
}

void RamMethods::InstallationCheck(Client*const pClient, int32 lineLocationID)
{
    if (IsStation(lineLocationID)) {
        uint32 regionID = sDataMgr.GetStationRegion(lineLocationID);
        if (!IsRegion(regionID))
            throw(PyException(MakeUserError("RamIsNotAnInstallation")));
        if (pClient->GetRegionID() != regionID)
            throw(PyException(MakeUserError("RamRangeLimitationRegion")));
    } else {
        // get structure data and run tests
        // RamStructureNotInSpace
        // RamStructureNotIsSolarsystem
    }

    // check player skill for limits
    // RamRangeLimitation
    // RamRangeLimitationJumps
    // RamRangeLimitationJumpsNoSkill

    /*
     *        jumpsPerSkillLevel =
     *        {0: -1,   // station/structure
     *         1: 0,    // system
     *         2: 5,
     *         3: 10,
     *         4: 20,
     *         5: 50}
     */
}

void RamMethods::LinePermissionCheck(Client*const pClient, const Call_InstallJob& args)
{
    // get properties
    EvERam::LineRestrictions data = EvERam::LineRestrictions();
    if (!FactoryDB::GetAssemblyLineRestrictions(args.AssemblyLineID, data))
        throw(PyException(MakeUserError("RamInstallationHasNoDefaultContent")));

    // check validity of activity
    if ((data.activityID < EvERam::Activity::Manufacturing)
    or  (data.activityID > EvERam::Activity::Invention))
        throw(PyException(MakeUserError("RamAssemblyLineHasNoActivity")));

    // verify corp roles
    if (args.isCorpJob) {
        int64 roles(pClient->GetCorpRole());
        // check slot rental permissions first
        if (args.activityID == EvERam::Activity::Manufacturing) {
            if (roles & Corp::Role::CanRentFactorySlot != Corp::Role::CanRentFactorySlot)
                throw(PyException(MakeUserError("RamCannotInstallWithoutRentFactorySlot")));
        } else {
            if (roles & Corp::Role::CanRentResearchSlot != Corp::Role::CanRentResearchSlot)
                throw(PyException(MakeUserError("RamCannotInstallWithoutRentResearchSlot")));
        }
        if (roles & Corp::Role::FactoryManager != Corp::Role::FactoryManager)
            throw(PyException(MakeUserError("RamCannotInstallForCorpByRoleFactoryManager")));
        if (roles & Corp::Role::Director != Corp::Role::Director)
            throw(PyException(MakeUserError("RamCannotInstallForCorpByRole")));
    }

    // check usage restriction
    if (data.rMask & EvERam::RestrictionMask::ByAlliance == EvERam::RestrictionMask::ByAlliance) {
        if (data.ownerID != pClient->GetAllianceID())
            throw(PyException(MakeUserError("RamAccessDeniedWrongAlliance")));
    }
    if (data.rMask & EvERam::RestrictionMask::ByCorp == EvERam::RestrictionMask::ByCorp) {
        if (data.ownerID != pClient->GetCorporationID())
            throw(PyException(MakeUserError("RamAccessDeniedWrongCorp")));
    }

    // check standing
    if (data.rMask & EvERam::RestrictionMask::ByStanding == EvERam::RestrictionMask::ByStanding) {
        // get standings
        if (args.isCorpJob) {
            if (data.minStanding > StandingDB::GetStanding(data.ownerID, pClient->GetCorporationID()))
                throw(PyException(MakeUserError("RamAccessDeniedCorpStandingTooLow")));
        } else {
            if (data.minStanding > pClient->GetChar()->GetStandingModified(data.ownerID))
                throw(PyException(MakeUserError("RamAccessDeniedStandingTooLow")));
        }
    }

    // check security rating
    if (data.rMask & EvERam::RestrictionMask::BySecurity == EvERam::RestrictionMask::BySecurity) {
        if (args.isCorpJob) {
            /** @todo  corp secStatus????  didnt know that was a thing.  */
            if (data.minCorpSec > pClient->GetChar()->corpSecRating())
                throw(PyException(MakeUserError("RamAccessDeniedCorpSecStatusTooLow")));
            if (data.maxCorpSec < pClient->GetChar()->corpSecRating())
                throw(PyException(MakeUserError("RamAccessDeniedCorpSecStatusTooHigh")));
        } else {
            if (data.minCharSec > pClient->GetSecurityRating())
                throw(PyException(MakeUserError("RamAccessDeniedSecStatusTooLow")));
            if (data.maxCharSec < pClient->GetSecurityRating())
                throw(PyException(MakeUserError("RamAccessDeniedSecStatusTooHigh")));
        }
    }
}

void RamMethods::ItemOwnerCheck(Client*const pClient, const Call_InstallJob& args, BlueprintRef bpRef)
{
    // ownership
    if (args.isCorpJob) {
        if (bpRef->ownerID() != pClient->GetCorporationID())
            throw(PyException(MakeUserError("RamCannotInstallItemForAnotherCorp")));
    } else {
        // this one is checked in client
        if (bpRef->ownerID() != pClient->GetCharacterID())
            throw(PyException(MakeUserError("RamCannotInstallItemForAnother")));
    }
}

void RamMethods::ItemLocationCheck(Client*const pClient, const Call_InstallJob& args, InventoryItemRef installedItem)
{
    // a lot of this is checked in client.  need to verify
    if (IsStation(args.lineContainerID)) {
        if (installedItem->locationID() != args.lineContainerID) {
            if (args.lineContainerID == pClient->GetLocationID()) {
                std::map<std::string, PyRep *> exceptArgs;
                exceptArgs["location"] = new PyString(stDataMgr.GetStationName(args.lineContainerID));
                if (args.isCorpJob) {
                    throw(PyException(MakeUserError("RamCorpInstalledItemWrongLocation", exceptArgs)));
                } else {
                    throw(PyException(MakeUserError("RamInstalledItemWrongLocation", exceptArgs)));
                }
            } else {
                throw(PyException(MakeUserError("RamRemoteInstalledItemNotInStation")));
            }
        } else {
            if (args.isCorpJob) {
                if (!IsHangarFlag(installedItem->flag())) {
                    if (args.lineContainerID == pClient->GetLocationID()) {
                        std::map<std::string, PyRep *> exceptArgs;
                        exceptArgs["location"] = new PyString(stDataMgr.GetStationName(args.lineContainerID));
                        throw(PyException(MakeUserError("RamCorpInstalledItemWrongLocation", exceptArgs)));
                    } else {
                        throw(PyException(MakeUserError("RamRemoteInstalledItemNotInOffice")));
                    }
                }
            } else {
                if (installedItem->flag() != flagHangar) {
                    if (args.lineLocationID == pClient->GetLocationID()) {
                        std::map<std::string, PyRep *> exceptArgs;
                        exceptArgs["location"] = new PyString(stDataMgr.GetStationName(args.lineContainerID));
                        throw(PyException(MakeUserError("RamInstalledItemWrongLocation", exceptArgs)));
                    } else {
                        throw(PyException(MakeUserError("RamRemoteInstalledItemInStationNotHangar")));
                    }
                }
            }
        }
    } else if (args.lineContainerID == pClient->GetShipID()) {
        if (pClient->GetChar()->flag() != flagPilot)
            throw(PyException(MakeUserError("RamAccessDeniedNotPilot")));

        if (args.isCorpJob and (installedItem->flag() == flagCargoHold))
            throw(PyException(MakeUserError("RamCorpInstalledItemNotInCargo")));

        if (installedItem->locationID() != args.lineContainerID)
            throw(PyException(MakeUserError("RamInstalledItemMustBeInShip")));
    } else {
        /* this will be POS assembly modules and Outpost checks
        *  RamStationIsNotConstructed
        *  RamInstalledItemMustBeInInstallation
        *  RamInstalledItemBadLocationStructure
        *  RamInstalledItemInStructureNotInContainer
        *  RamInstalledItemInStructureUnknownLocation
        */
        throw(PyException(MakeCustomError("R.A.M. at POS/Outpost not supported yet")));
    }
}

void RamMethods::HangarRolesCheck(Client* const pClient, int16 flagID)
{
    int64 roles(pClient->GetCorpRole());
    switch (flagID) {
        case flagHangar: {
            if (roles & Corp::Role::HangarCanTake1 != Corp::Role::HangarCanTake1)
                throw(PyException(MakeUserError("RamAccessDeniedToBOMHangar")));
        } break;
        case flagCorpHangar2: {
            if (roles & Corp::Role::HangarCanTake2 != Corp::Role::HangarCanTake2)
                throw(PyException(MakeUserError("RamAccessDeniedToBOMHangar")));
        } break;
        case flagCorpHangar3: {
            if (roles & Corp::Role::HangarCanTake3 != Corp::Role::HangarCanTake3)
                throw(PyException(MakeUserError("RamAccessDeniedToBOMHangar")));
        } break;
        case flagCorpHangar4: {
            if (roles & Corp::Role::HangarCanTake4 != Corp::Role::HangarCanTake4)
                throw(PyException(MakeUserError("RamAccessDeniedToBOMHangar")));
        } break;
        case flagCorpHangar5: {
            if (roles & Corp::Role::HangarCanTake5 != Corp::Role::HangarCanTake5)
                throw(PyException(MakeUserError("RamAccessDeniedToBOMHangar")));
        } break;
        case flagCorpHangar6: {
            if (roles & Corp::Role::HangarCanTake6 != Corp::Role::HangarCanTake6)
                throw(PyException(MakeUserError("RamAccessDeniedToBOMHangar")));
        } break;
        case flagCorpHangar7: {
            if (roles & Corp::Role::HangarCanTake7 != Corp::Role::HangarCanTake7)
                throw(PyException(MakeUserError("RamAccessDeniedToBOMHangar")));
        } break;
    }
}

void RamMethods::LocationRolesCheck(Client*const pClient, const CorpPathElement &data)
{
    int64 roles(0);
    // this will verify corp roles at location
    uint32 stationID(data.officeFolderID - STATION_OFFICE_OFFSET);
    if (stationID == pClient->GetCorpHQ()) {
        roles = pClient->GetRolesAtHQ();
        /** @todo determine what roles are required here and test */
    } else {
        // not hq  is this a base?
        /** @todo finish this.  */
    }

}

void RamMethods::MaterialSkillsCheck(Client* const pClient, uint32 runs, const PathElement& bomLocation, const Rsp_InstallJob& rsp, const std::vector< EvERam::RequiredItem >& reqItems)
{
    std::map<uint16, InventoryItemRef> items;   // typeID, itemRef
    GetBOMItemsMap( bomLocation, items );

    std::map<std::string, PyRep *> args;
    for (auto cur : reqItems) {
        if (cur.isSkill) { // check skill (quantity is required level)
            if (pClient->GetChar()->GetSkillLevel(cur.typeID) < cur.quantity) {
                std::map<std::string, PyRep *> args;
                args["item"] = new PyInt(cur.typeID);
                args["skillLevel"] = new PyInt(cur.quantity);
                throw(PyException(MakeUserError("RamNeedSkillForJob", args)));
            }
        } else {
            uint32 qtyNeeded = ceil(cur.quantity * rsp.materialMultiplier * runs);
            if (cur.damagePerJob == 1)
                qtyNeeded = ceil(qtyNeeded * rsp.charMaterialMultiplier);
            std::map<uint16, InventoryItemRef>::iterator itr = items.find(cur.typeID);
            if (itr != items.end())
                if (itr->second->typeID() == cur.typeID) {
                    if (itr->second->quantity() < qtyNeeded)
                        qtyNeeded -= itr->second->quantity();
                    else
                        qtyNeeded = 0;
                }

            if (qtyNeeded)
                args["item"] = new PyInt( cur.typeID );
        }
    }

    if (!args.empty())
        throw(PyException(MakeUserError("RamNeedMoreForJob", args)));
}

void RamMethods::ProductionTimeCheck(uint32 productionTime)
{
    if (productionTime > RAM_PRODUCTION_TIME_LIMIT) {
        std::map<std::string, PyRep *> args;
        args["productionTime"] = new PyInt(productionTime);
        args["limit"] = new PyInt(RAM_PRODUCTION_TIME_LIMIT);
        throw(PyException(MakeUserError("RamProductionTimeExceedsLimits", args)));
    }
}

void RamMethods::VerifyCompleteJob(const Call_CompleteJob &args, EvERam::JobProperties &data, Client* const pClient)
{
    // this isnt entirely right....if job is installed in ship, receiver must be pilot in active ship to complete job.
    if (args.containerID == pClient->GetShipID())
        if (pClient->GetChar()->flag() != flagPilot)
            throw(PyException(MakeUserError("RamCompletionMustBeInShip")));

    if (IsCorp(data.ownerID)) {
        if (data.ownerID == pClient->GetCorporationID()) {
            if ((pClient->GetCorpRole() & Corp::Role::FactoryManager) != Corp::Role::FactoryManager)
                throw(PyException(MakeUserError("RamCompletionAccessDeniedByCorpRole")));
        } else  // alliances not implemented
            throw(PyException(MakeUserError("RamCompletionAccessDenied")));
    }

    if (data.status != EvERam::Status::InProgress)
        throw(PyException(MakeUserError("RamCompletionJobCompleted")));

    if (!args.cancel and (data.endTime > GetFileTimeNow()))
        throw(PyException(MakeUserError("RamCompletionInProduction")));
}

bool RamMethods::Calculate(const Call_InstallJob &args, BlueprintRef bpRef, Character* pChar, Rsp_InstallJob &into)
{
    // get line data
    if (!FactoryDB::GetAssemblyLineProperties(args.AssemblyLineID, pChar, into, args.isCorpJob))
        return false;

    // set char defaults
    into.charTimeMultiplier = 1.0;
    into.charMaterialMultiplier = 1.0;

    const ItemType* pType(nullptr);
    switch(args.activityID) {
        case EvERam::Activity::Manufacturing: {
            pType = &bpRef->productType();
            FactoryDB::GetMultipliers(args.AssemblyLineID, pType, into);
            into.materialMultiplier += bpRef->GetME();
            into.materialMultiplier *= sConfig.ram.MatMod;
            into.charTimeMultiplier *= (1.0f - (0.04f * pChar->GetSkillLevel(EvESkill::Industry)));
            into.productionTime = EvEMath::RAM::ProductionTime(bpRef->type().productionTime(), bpRef->type().productivityModifier(),
                                                               bpRef->pLevel(), into.timeMultiplier);
            // modify base time by char multiplier
            into.productionTime *= into.charTimeMultiplier;
            // if time modifier is set in config, apply that now
            into.productionTime *= sConfig.ram.ProdTime;
        } break;
        case EvERam::Activity::ResearchMaterial: {
            pType = &bpRef->type();
            FactoryDB::GetMultipliers(args.AssemblyLineID, pType, into);
            into.productionTime = EvEMath::RAM::ME_ResearchTime(bpRef->type().researchMaterialTime(),
                                                                pChar->GetSkillLevel(EvESkill::Metallurgy), into.timeMultiplier
                                                                /*implant modifier here*/);
            into.productionTime *= sConfig.ram.ResME;
            into.charTimeMultiplier *= pChar->GetAttribute(AttrMineralNeedResearchSpeed).get_float();
        }  break;
        case EvERam::Activity::ResearchTime: {
            pType = &bpRef->type();
            FactoryDB::GetMultipliers(args.AssemblyLineID, pType, into);
            //ch->GetAttribute(AttrResearchCostPercent).get_int();   << this is not used

            into.productionTime = EvEMath::RAM::PE_ResearchTime(bpRef->type().researchProductivityTime(),
                                                                pChar->GetSkillLevel(EvESkill::Research), into.timeMultiplier
                                                                /*implant modifier here*/);
            into.productionTime *= sConfig.ram.ResPE;
            into.charTimeMultiplier *= pChar->GetAttribute(AttrManufacturingTimeResearchSpeed).get_float();
        }  break;
        case EvERam::Activity::Copying: {
            pType = &bpRef->type();
            FactoryDB::GetMultipliers(args.AssemblyLineID, pType, into);
            into.productionTime = EvEMath::RAM::CopyTime(bpRef->type().researchCopyTime(),
                                                         pChar->GetSkillLevel(EvESkill::Science), into.timeMultiplier
                                                         /*implant modifier here*/);
            into.productionTime *= sConfig.ram.CopyTime;
            into.charTimeMultiplier *= pChar->GetAttribute(AttrCopySpeedPercent).get_float();
            //bpRef->type().chanceOfDuplicating();
        }  break;
        case EvERam::Activity::Invention: {
            pType = &bpRef->type();
            FactoryDB::GetMultipliers(args.AssemblyLineID, pType, into);
            into.productionTime = EvEMath::RAM::InventionTime(bpRef->type().researchTechTime(),
                                                              pChar->GetSkillLevel(EvESkill::AdvancedLaboratoryOperation),
                                                              into.timeMultiplier
                                                              /*implant modifier here*/);
            into.productionTime *= sConfig.ram.InventTime;
        } break;
        case EvERam::Activity::ReverseEngineering: {
            pType = &bpRef->type();
            FactoryDB::GetMultipliers(args.AssemblyLineID, pType, into);
            // base research time for RE is one hour
            into.productionTime = 3600; // in seconds
            into.productionTime *= sConfig.ram.ReTime;
            //bpRef->type().chanceOfRE();
        } break;
    }

    // calculate cost
    into.usageCost *= ceil(into.productionTime / 3600.0f);
    into.cost = into.installCost + into.usageCost;
    // multiply single run time by run count for total time
    into.productionTime *= args.runs;

    into.maxJobStartTime = FactoryDB::GetNextFreeTime(args.AssemblyLineID);

    return true;
}

void RamMethods::EncodeBillOfMaterials(const std::vector<EvERam::RequiredItem> &reqItems, float materialMultiplier, float charMaterialMultiplier, uint32 runs, BillOfMaterials &into)
{
    PySafeDecRef( into.extras.lines );
    into.extras.lines = new PyList();
    PySafeDecRef( into.wasteMaterials.lines );
    into.wasteMaterials.lines = new PyList();
    PySafeDecRef( into.rawMaterials.lines );
    into.rawMaterials.lines = new PyList();

    for (auto cur : reqItems) {
        if (cur.isSkill) {
            into.skills[cur.typeID] = new PyInt(cur.quantity);
            continue;
        }

        // otherwise, make line for material list
        MaterialList_Line line;
        line.requiredTypeID = cur.typeID;
        line.quantity = (int32)ceil(cur.quantity * materialMultiplier * runs);
        line.damagePerJob = cur.damagePerJob;
        line.isSkillCheck = false;  // no idea what is this for
        line.requiresHP = false;    // no idea what is this for

        /** @todo update this shit.....  */
        // "Extra material" is not affected by skills, and return upon completion
        // "Raw material" is fully consumed and affected by skills/efficiency
        // "Waste Material" is amount of material wasted ...
        if (cur.extra) {
            into.extras.lines->AddItem( line.Encode() );
        } else {
            // if there are losses, make line for waste material list
            if (charMaterialMultiplier > 1.0) {
                MaterialList_Line wastage( line );  // simply copy original line ...
                wastage.quantity = (int32)ceil(wastage.quantity * (charMaterialMultiplier - 1.0)); // ... and calculate proper quantity
                into.wasteMaterials.lines->AddItem( wastage.Encode() );
            }
            into.rawMaterials.lines->AddItem( line.Encode() );
        }
    }
}

void RamMethods::EncodeMissingMaterials(const std::vector<EvERam::RequiredItem> &reqItems, const PathElement &bomLocation, Client *const pClient, float materialMultiplier, float charMaterialMultiplier, int32 runs, std::map<int32, PyRep *> &into) {
    //
    std::vector<InventoryItemRef> skills, items;

    //get the skills
    pClient->GetChar()->GetMyInventory()->GetItemsByFlag(flagSkill, skills);

    //get the items
    GetBOMItems( bomLocation, items );

    //now do the check
    uint32 qtyReq(0);
    for (auto cur : reqItems) {
        qtyReq = cur.quantity;
        if (!cur.isSkill) {
            qtyReq = (uint32)ceil(qtyReq * materialMultiplier * runs);
            if (cur.damagePerJob == 1)
                qtyReq = (uint32)ceil(qtyReq * charMaterialMultiplier);
        }

        std::vector<InventoryItemRef>::iterator curi, endi;
        if (cur.isSkill) {
            curi = skills.begin();
            endi = skills.end();
        } else {
            curi = items.begin();
            endi = items.end();
        }

        for (; curi != endi and qtyReq > 0; ++curi) {
            if (((*curi)->typeID() == cur.typeID)
            and (((*curi)->ownerID() == pClient->GetCharacterID())
              or ((*curi)->ownerID() == pClient->GetCorporationID()))) {
                if (cur.isSkill) {
                    qtyReq -= std::min(qtyReq, (*curi)->GetAttribute(AttrSkillLevel).get_uint32() );
                } else {
                    qtyReq -= std::min(qtyReq, (uint32)(*curi)->quantity() );
                }
            }
        }

        if (qtyReq > 0)
            into[cur.typeID] = new PyInt(qtyReq);
    }
}
void RamMethods::GetBOMItems(const PathElement& bomLocation, std::vector< InventoryItemRef >& into)
{
    Inventory *inventory = sItemFactory.GetInventoryFromId( bomLocation.locationID );
    if (inventory != nullptr )
        inventory->GetItemsByFlag((EVEItemFlags)bomLocation.flagID, into );
}

void RamMethods::GetBOMItemsMap(const PathElement& bomLocation, std::map< uint16, InventoryItemRef >& into)
{
    Inventory *inventory = sItemFactory.GetInventoryFromId( bomLocation.locationID );
    if (inventory != nullptr )
        inventory->GetTypesByFlag( (EVEItemFlags)bomLocation.flagID, into );
}

/* For each material required for a blueprint (from invTypeMaterials), the quantity is affected by ME research and skills.
 * Then there’s the extra materials, which come from the ramTypeRequirements table for that BP.
 * Next, any materials in ramTypeRequirements which are marked as recyclable, have their recycled materials (from invTypeMaterials) subtracted from the list of materials required for the produced item.
 * The remaining materials from invTypeMaterials are then modified by skills and ME research as follows:
 *      xmatls = ramTypeRequirements.extra
 *      reqMatls = (invTypeMaterials.reqMatls - xmatls)
 *      waste = reqMatls * charSkills (which is wastage multiplier based on skills)
 *      totalReqMatls = (reqMatls * skill mods) + xmatls + waste
 */
void RamMethods::GetAdjustedRamRequiredMaterials()
{
    // will need to update this using above formula for correct material list

}

const char* RamMethods::GetActivityName(int8 activityID)
{
    switch (activityID) {
        case EvERam::Activity::Copying:             return "Copying";
        case EvERam::Activity::Manufacturing:       return "Manufacturing";
        case EvERam::Activity::Invention:           return "Invention";
        case EvERam::Activity::ResearchMaterial:    return "Research ME";
        case EvERam::Activity::ResearchTime:        return "Research PE";
        case EvERam::Activity::ReverseEngineering:  return "Reverse Engineering";
        // these last 2 should never hit
        case EvERam::Activity::Duplicating:
        case EvERam::Activity::ResearchTech: {
            codelog(MANUF__ERROR, "RamMethods::GetActivityName - invalid activity sent: %u", activityID);
        } break;
    }
    return "Undefined";
}

