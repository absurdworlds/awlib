/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IBaseNavigator_
#define _hrengin_IBaseNavigator_

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace ai {

class IBasePathfinder;

/* Base class for navigator
   Navigators are used to guide an entity in the world
 */
class IBaseNavigator {
public:
	enum class NavState : u32 {
		Idle,
		Wander,
		MoveTo,
		Rotate,
		Follow,
		Avoid,
		GiveWay,
		WaitForPath,
		BlockWay,
		Flock,
		Fail,
		Count
	};

	struct NavProxy {
		Vector3d<f32> position;
		Vector3d<f32> angle;
		f32 speed;
		f32 acceleration;
		/* user pointer */
		void* pointer;
	};

	virtual ~IBaseNavigator() {};

	/* Set target to move towards */
	virtual void go (Vector3d<f32> target) = 0;
	/* Set target to follow */
	virtual void follow (NavProxy& target) = 0;
	/* Wander aimlessly */
	virtual void wander () = 0;
	/* Reset state */
	virtual void abort() = 0;

	/* Move towards goal */
	virtual void move (f32 step) = 0;

	virtual NavProxy& getProxy() = 0;

	virtual NavState getState() const = 0;
};

} // namespace ai
} // namespace hrengin

#endif //_hrengin_IBaseNavigator_
