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


#ifndef __TARGETMANAGER_H_INCL__
#define __TARGETMANAGER_H_INCL__

#include "inventory/ItemRef.h"

class SystemEntity;
class PyRep;
class PyTuple;

class TargetManager {
public:
    TargetManager(SystemEntity *self);
    virtual ~TargetManager();

    void doDestruction();

    void process();

    /**
     * Start targeting an entity.
     * @param who The entity to target.
     * @param ship The ship that's targeting the entity.
     * @return True if successful.
     */
    bool startTargeting(SystemEntity *who, ShipRef ship);
    /**
     * Start targeting an entity.
     * @param who The entity to target.
     * @param lockTime The amount of time it will take to target.
     * @param maxLockedTargets The maximum number of target.
     * @param maxTargetLockRange The maximum targeting range.
     * @return True if successful.
     */
    bool startTargeting(SystemEntity *who, double lockTime, uint32 maxLockedTargets, double maxTargetLockRange);

    /**
     * Clear all targets.
     * @param notify_self Whether or not to notify self.
     * @note Does not clear targeted by other entities.
     */
    void clearTargets(bool notify_self = true);
    /**
     * Clear a specific target.
     * @param who The target to clear.
     * @note Does not clear targeted by other entities.
     */
    void clearTarget(SystemEntity *who);
    /**
     * Remove self from bubble.
     * @param notify_self Whether or not to notify self.
     */
    void removeFromBubble(bool notify_self = true);

protected:
    /**
     * Clear this entity from all targeting entities.
     */
    void clearFromTargets();
    /**
     * An outside force caused us to loose a target.
     * @param who The target we lost.
     */
    void targetLost(SystemEntity *who);

    //void TargetedByLocking(SystemEntity *from_who);
    /**
     * Another entity has targeted this entity.
     * @param from_who Who targeted this entity.
     */
    void targetedByLocked(SystemEntity *from_who);
    /**
     * An entity targeting this entity has lost it's targeting.
     * @param from_who Who lost there targeting.
     */
    void targetedByLost(SystemEntity *from_who);

public:
    /**
     * Gets the target from the targetID
     * @param targetID The targetID to look for.
     * @param need_locked True if the target must be fully locked.
     * @return The entity that has been targeted.
     */
    SystemEntity *getTarget(uint32 targetID, bool need_locked = true) const;
    /**
     * Get the first target.
     * @param need_locked True if the target must be fully locked.
     * @return The target or nullptr.
     */
    SystemEntity *getFirstTarget(bool need_locked);

    /**
     * Does this entity have any targets?
     * @return True if this entity has targets.
     */
    bool hasTargets() const
    {
        return (m_targets.empty());
    }

    /**
     * Is this entity targeted?
     * @return True if this entity is targeted.
     */
    bool isTargeted() const
    {
        return (!m_targetedBy.empty());
    }

    /**
     * Get the total number of targets.
     * @return The number of targets.
     */
    uint32 getTotalTargets() const
    {
        return m_targets.size();
    }

    /**
     * Queue a damage message to update target indicators.
     * @param up The message to send.
     */
    void queueTBDestinyEvent(PyTuple **up) const; //queue a destiny event to all people targeting me.
    /**
     * Queue a damage message to update target indicators.
     * @param up The message to send.
     */
    void queueTBDestinyUpdate(PyTuple **up) const; //queue a destiny update to all people targeting me.

    void dump() const;
    /**
     * Calculate the time needed to target an entity
     * @param ship The ship doing the targeting.
     * @param target The target entity.
     * @return 
     */
    uint32 timeToLock(ShipRef ship, SystemEntity *target) const;

    //Packet builders:
    PyList *getTargets() const;
    PyList *getTargeters() const;

protected:

	class TargetedByEntry {
    public:
        TargetedByEntry(SystemEntity *_who)
            : state(Idle), who(_who) { }

        void dump() const;

        enum {
            Idle,
            Locking,
            Locked
        } state;
        SystemEntity *const who;
    };

    class TargetEntry {
    public:
        TargetEntry(SystemEntity *_who)
            : state(Idle), who(_who), timer(0) { }

        void dump() const;

        enum {
            Idle,
            PassiveLocking,
            Locking,
            Locked
        } state;
        SystemEntity *const who;
        Timer timer;
    };

    bool m_destroyed;    //true if we have already taken care of destruction logic.
    SystemEntity *const m_self;    //we do not own this.
    std::map<SystemEntity *, TargetedByEntry *> m_targetedBy;    //we own these values, not the keys
    std::map<SystemEntity *, TargetEntry *> m_targets;    //we own these values, not the keys
    uint32 m_maxLockedTargets = 0;
    double m_maxTargetLockRange = 0;
};

#endif


