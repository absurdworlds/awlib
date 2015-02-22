/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_BaseNavigator_
#define _hrengin_BaseNavigator_

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {

class BaseEntity;

namespace ai {

class BasePathfinder;
class GroupNavigator;

/* Base class for navigator
 * Navigators are used to guide an entity in the world
 */
class BaseNavigator {
public:
	/* enumeration for different states and behaviors */
	enum class NavState : u32 {
		// stand idle
		Idle,
		// wander aimlessly
		Wander,
		// move towards goal
		MoveTo,
		// follow behind target
		Follow,
		// pursue target
		Pursue,
		// flee from target
		Flee,
		// Avoid obstacles (when can not find a path)
		// i.e. when proxy is surrounded
		Avoid,
		// give way
		GiveWay,
		// wait util path is free
		WaitForPath,
		// try to block target's path
		BlockWay,
		// stick to group
		Group,
		Count
	};

	/* temporary proxy implementation */
	struct NavProxy {
		BaseEntity* client;
	};

	virtual ~BaseNavigator() {};

	//virtual Proxy const& getProxy() const = 0;
	//virtual void setGoal(BaseNavigator::Proxy const& goal) = 0;
	//virtual Proxy const& getGoal() const = 0;
	//virtual void setAction(BaseNavigator::Action const action) = 0;
	//virtual Action const getAction() const = 0;

	//! Set target to move towards
	virtual void go(Vector3d<f32> target) = 0;
	//! Set target to follow
	virtual void follow(NavProxy* target) = 0;
	//! Set target to pursue
	virtual void pursue(NavProxy* target) = 0;
	//! Attacj navigator to a group
	virtual void attach(GroupNavigator* group) = 0;
	//! Wander aimlessly
	virtual void wander() = 0;
	//! Reset state
	virtual void abort() = 0;

	//! Navigate towards goal
	virtual void navigate(f32 timeDelta) = 0;


	virtual NavState getState() const = 0;
};

} // namespace ai
} // namespace hrengin
#endif //_hrengin_BaseNavigator_
