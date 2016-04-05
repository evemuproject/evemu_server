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
    Author:        Zhur
*/

#include "eve-server.h"

#include "inventory/AttributeEnum.h"
#include "ship/Ship.h"
#include "ship/TargetManager.h"
#include "system/SystemEntity.h"
#include "system/SystemBubble.h"

TargetManager::TargetManager(SystemEntity *self)
: m_destroyed(false),
  m_self(self)
{
}

TargetManager::~TargetManager()
{
    doDestruction();
}

//I am not happy with this:
//this function exists to deal with a specific problem with the
// destruction chain where we reference a SystemEntity (m_self), which
// also contains their TargetManager. The TargetManager object is
// not destroyed until the base SystemEntity is destroyed, but
// the SystemEntity pointer itself becomes invalid as soon as the
// first child class in its hierarchy (such as Client or NPC) are
// destroyed. Thus, all terminal children of SystemEntity must call
// this from their destructor.

void TargetManager::doDestruction()
{
    if(!m_destroyed)
    {
        m_destroyed = true;
        removeFromBubble(false);
    }
}

void TargetManager::process()
{
    int targetNum = 0;
    std::vector<SystemEntity *> targetLost;
    //process outgoing targeting
    for (auto cur : m_targets)
    {
        TargetEntry *target = cur.second;
        switch (target->state)
        {
            case TargetEntry::Locking:
                //see if we are finished locking...
                if (target->timer.Check())
                {
                    // They are locked.
                    target->timer.Disable();
                    target->state = TargetEntry::Locked;
                    _log(TARGET__TRACE, "%u has finished locking %u", m_self->GetID(), cur.first->GetID());
                    m_self->TargetAdded(cur.first);
                    cur.first->targets.targetedByLocked(m_self);
                }
                break;
            case TargetEntry::Idle:
            case TargetEntry::Locked:
            case TargetEntry::PassiveLocking:
                targetNum++;
                //nothing to do right now...
                if (targetNum > m_maxLockedTargets)
                {
                    // This is a hack fix.
                    targetLost.push_back(cur.first);
                    continue;
                }
                Vector3D rangeToTarget(m_self->GetPosition() - cur.first->GetPosition());
                if (rangeToTarget.length() - cur.first->GetRadius() > m_maxTargetLockRange)
                {
                    targetLost.push_back(cur.first);
                    continue;
                }
                break;
        }
    }
    for (auto target : targetLost)
    {
        clearTarget(target);
    }
}

bool TargetManager::startTargeting(SystemEntity *who, ShipRef ship)
{ // needs another argument: "ShipRef ship" to access ship attributes
    //first make sure they are not already in the list
    std::map<SystemEntity *, TargetEntry *>::iterator res;
    res = m_targets.find(who);
    if (res != m_targets.end())
    {
        //what to do?
        _log(TARGET__TRACE, "Told to start targeting %u, but we are already processing them. Ignoring request.", who->GetID());
        return false;
    }

    //Check that they aren't targeting themselves
    if (who == m_self)
    {
        return false;
    }

    // Check against max locked target count
    m_maxLockedTargets = ship->GetAttribute(AttrMaxLockedTargets).get_int();
    //    if (m_targets.size() >= m_maxLockedTargets)
    //    {
    //        // TO-DO: send real max targets notice.
    //        return false;
    //    }

    if (m_self->Bubble()->GetEntity(who->GetID()) == nullptr)
    {
        // Target not in our bubble.
        return false;
    }

    // Check against max locked target range
    m_maxTargetLockRange = ship->GetAttribute(AttrMaxTargetRange).get_float();
    //    Vector3D rangeToTarget(who->GetPosition(), m_self->GetPosition());
    //    if (rangeToTarget.length() - who->GetRadius() > m_maxTargetLockRange)
    //    {
    //        // TO-DO: send real out of range notice.
    //        return false;
    //    }

    // Calculate Time to Lock target:
    uint32 lockTime = timeToLock(ship, who);

    TargetEntry *te = new TargetEntry(who);
    te->state = TargetEntry::Locking;
    te->timer.Start(lockTime);
    m_targets[who] = te;

    _log(TARGET__TRACE, "%u started targeting %u (%u ms lock time)", m_self->GetID(), who->GetID(), lockTime);
    return true;
}

bool TargetManager::startTargeting(SystemEntity *who, double lockTime, uint32 maxLockedTargets, double maxTargetLockRange)
{
    //first make sure they are not already in the list
    std::map<SystemEntity *, TargetEntry *>::iterator res;
    res = m_targets.find(who);
    if (res != m_targets.end())
    {
        //what to do?
        _log(TARGET__TRACE, "Told to start targeting %u, but we are already processing them. Ignoring request.", who->GetID());
        return false;
    }

    //Check that they aren't targeting themselves
    if (who == m_self)
    {
        return false;
    }

    // Check against max locked target count
    m_maxLockedTargets = maxLockedTargets;
    //    if (m_targets.size() >= m_maxLockedTargets)
    //    {
    //        // TO-DO: send real max targets notice.
    //        return false;
    //    }

    if (m_self->Bubble()->GetEntity(who->GetID()) == nullptr)
    {
        // Target not in our bubble.
        return false;
    }

    // Check against max locked target range
    m_maxTargetLockRange = maxTargetLockRange;
    //    Vector3D rangeToTarget(who->GetPosition(), m_self->GetPosition());
    //    if (rangeToTarget.length() - who->GetRadius() > m_maxTargetLockRange)
    //    {
    //        // TO-DO: send real out of range notice.
    //        return false;
    //    }

    TargetEntry *te = new TargetEntry(who);
    te->state = TargetEntry::Locking;
    te->timer.Start(lockTime);
    m_targets[who] = te;

    _log(TARGET__TRACE, "%u started targeting %u (%u ms lock time)", m_self->GetID(), who->GetID(), lockTime);
    return true;
}

void TargetManager::clearTargets(bool notify_self)
{
    _log(TARGET__TRACE, "%u is clearing all targets", m_self->GetID());
    for (auto cur : m_targets)
    {
        _log(TARGET__TRACE, "%u has cleared target %u during clear all.", m_self->GetID(), cur.first->GetID());
        cur.first->targets.targetedByLost(m_self);
        delete cur.second;
    }
    m_targets.clear();
    if (notify_self)
    {
        m_self->TargetsCleared();
    }
}

void TargetManager::clearTarget(SystemEntity *who)
{
    //let the other entity know they are no longer targeted.
    who->targets.targetedByLost(m_self);
    //clear it from our own state
    targetLost(who);
}

void TargetManager::removeFromBubble(bool notify_self)
{
    clearFromTargets();
    clearTargets(notify_self);
    _log(TARGET__TRACE, "%u has cleared all targeting information.", m_self->GetID());
}

void TargetManager::clearFromTargets()
{
    std::vector<SystemEntity *> toNotify;
    toNotify.reserve(m_targetedBy.size());

    //first, clean up our internal structure.
    for (auto cur : m_targetedBy)
    {
        //do not notify until we clear our target list! otherwise bad things happen.
        toNotify.push_back(cur.first);
        delete cur.second;
    }
    m_targetedBy.clear();

    for (auto notify : toNotify)
    {
        notify->targets.targetLost(m_self);
    }
}

void TargetManager::targetLost(SystemEntity *who)
{
    std::map<SystemEntity *, TargetEntry *>::iterator res;
    res = m_targets.find(who);
    if(res == m_targets.end()) {
        //not found...
        return;
    }
    //clear our internal state for this target (BEFORE the callback!)
    m_targets.erase(res);

    _log(TARGET__TRACE, "%u has lost target %u", m_self->GetID(), who->GetID());

    m_self->TargetLost(who);
}

/*void TargetManager::TargetedByLocking(SystemEntity *from_who) {
    //first make sure they are not already in the list
    std::map<SystemEntity *, TargetedByEntry *>::iterator res;
    res = m_targetedBy.find(from_who);
    if(res != m_targetedBy.end()) {
        //just re-use the old entry...
    } else {
        //new entry.
        TargetedByEntry *te = new TargetedByEntry(from_who);
        te->state = TargetedByEntry::Locking;
        m_targetedBy[from_who] = te;
    }
    //no notification, should we even track this event??
}*/

void TargetManager::targetedByLocked(SystemEntity *from_who)
{
    //first make sure they are not already in the list
    std::map<SystemEntity *, TargetedByEntry *>::iterator res;
    res = m_targetedBy.find(from_who);
    if (res != m_targetedBy.end())
    {
        //just re-use the old entry...
        res->second->state = TargetedByEntry::Locked;
    }
    else
    {
        //new entry.
        TargetedByEntry *te = new TargetedByEntry(from_who);
        te->state = TargetedByEntry::Locking;
        m_targetedBy[from_who] = te;
    }
    _log(TARGET__TRACE, "%u has been locked by %u", m_self->GetID(), from_who->GetID());
    m_self->TargetedAdd(from_who);
}

void TargetManager::targetedByLost(SystemEntity *from_who)
{
    //first make sure they are not already in the list
    std::map<SystemEntity *, TargetedByEntry *>::iterator res;
    res = m_targetedBy.find(from_who);
    if (res != m_targetedBy.end())
    {
        delete res->second;
        m_targetedBy.erase(res);
        m_self->TargetedLost(from_who);
        _log(TARGET__TRACE, "%u is no longer locked by %u", m_self->GetID(), from_who->GetID());
    }
    else
    {
        //not found.. do nothing to our state, no notification?
        _log(TARGET__TRACE, "%u was notified of targeted lost by %u, but they did not have us targeted in the first place.", m_self->GetID(), from_who->GetID());
    }
}

SystemEntity *TargetManager::getTarget(uint32 targetID, bool need_locked) const
{
    for (auto cur : m_targets)
    {
        if (cur.first->GetID() != targetID)
        {
            // Not the target we are looking for.
            continue;
        }
        // Found our target, are we locked?
        if (need_locked && cur.second->state != TargetEntry::Locked)
        {
            // Nope, and we need a locked target.
            return nullptr;
        }
        return (cur.first);
    }
    // Target not found.
    return nullptr;
}

SystemEntity *TargetManager::getFirstTarget(bool need_locked)
{
    if (m_targets.empty())
    {
        return nullptr;
    }
    if (!need_locked)
    {
        //we know there is at least one entry here...
        return (m_targets.begin()->first);
    }

    for (auto cur : m_targets)
    {
        if (cur.second->state == TargetEntry::Locked)
        {
            return (cur.first);
        }
    }
    return nullptr;
}

void TargetManager::queueTBDestinyEvent(PyTuple** up_in) const
{
    PyTuple* up = *up_in;
    *up_in = nullptr; //could optimize out one of the Clones in here...

    PyTuple* up_dup = nullptr;

    for (auto cur : m_targetedBy)
    {
        if (up_dup == nullptr)
        {
            up_dup = new PyTuple(*up);
        }

        cur.first->QueueDestinyEvent(&up_dup);
        //they may not have consumed it (NPCs for example), so dont re-dup it in that case.
    }

    PySafeDecRef( up_dup );
    PyDecRef( up );
}

void TargetManager::queueTBDestinyUpdate(PyTuple** up_in) const
{
    PyTuple* up = *up_in;
    *up_in = nullptr; //could optimize out one of the Clones in here...

    PyTuple* up_dup = nullptr;

    for (auto cur : m_targetedBy)
    {
        if (up_dup == nullptr)
        {
            up_dup = new PyTuple(*up);
        }

        cur.first->QueueDestinyUpdate(&up_dup);
        //they may not have consumed it (NPCs for example), so dont re-dup it in that case.
    }

    PySafeDecRef( up_dup );
    PyDecRef( up );
}

PyList *TargetManager::getTargets() const
{
    PyList *result = new PyList();
    for (auto cur : m_targets)
    {
        result->AddItemInt(cur.first->GetID());
    }
    return result;
}

PyList *TargetManager::getTargeters() const
{
    PyList *result = new PyList();
    for (auto cur : m_targetedBy)
    {
        result->AddItemInt(cur.first->GetID());
    }
    return result;
}

uint32 TargetManager::timeToLock(ShipRef ship, SystemEntity *target) const
{
    if (target == nullptr)
    {
        return 0;
    }
    double scanRes = ship->GetAttribute(AttrScanResolution).get_float();
    InventoryItemRef item = target->Item();
    double sigRad = 500;
    if (item.get() != nullptr)
    {
        if (item->HasAttribute(AttrSignatureRadius))
        {
            sigRad = item->GetAttribute(AttrSignatureRadius).get_float();
        }
    }

    double sigFactor = std::asinh(sigRad);
    double time = (40000.0 / scanRes) / (sigFactor * sigFactor);

    return static_cast<uint32> (time * 1000); // Timer uses ms instead of seconds
}

void TargetManager::TargetEntry::dump() const
{
    const char *sname = "Unknown State";
    switch (state)
    {
    case Idle:
        sname = "Idle Entry";
        break;
    case PassiveLocking:
        sname = "Passive Locking";
        break;
    case Locking:
        sname = "Locking";
        break;
    case Locked:
        sname = "Locked";
        break;
        //no default on purpose.
    }
    _log(TARGET__TRACE, "    Targeted %s (%u): %s (%s %d ms)",
         who->GetName(),
         who->GetID(),
         sname,
         timer.Enabled() ? "Running" : "Disabled",
         timer.GetRemainingTime()
         );
}

void TargetManager::TargetedByEntry::dump() const
{
    const char *sname = "Unknown State";
    switch (state)
    {
    case Idle:
        sname = "Idle Entry";
        break;
    case Locking:
        sname = "Locking";
        break;
    case Locked:
        sname = "Locked";
        break;
        //no default on purpose.
    }
    _log(TARGET__TRACE, "    Targeted By %s (%u): %s",
         who->GetName(),
         who->GetID(),
         sname
         );
}

void TargetManager::dump() const
{
    _log(TARGET__TRACE, "Target Dump for %u:", m_self->GetID());
    {
        std::map<SystemEntity *, TargetEntry *>::const_iterator cur, end;
        cur = m_targets.begin();
        end = m_targets.end();
        for (; cur != end; cur++)
        {
            cur->second->dump();
        }
    }
    {
        std::map<SystemEntity *, TargetedByEntry *>::const_iterator cur, end;
        cur = m_targetedBy.begin();
        end = m_targetedBy.end();
        for (; cur != end; ++cur)
        {
            cur->second->dump();
        }
    }
}
