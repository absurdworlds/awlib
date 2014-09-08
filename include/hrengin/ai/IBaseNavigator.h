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

enum NavState : u32 {
	NA_STATE_IDLE,
	NA_STATE_VALIDATE,
	NA_STATE_GUARD,
	NA_STATE_MOVETO,
	NA_STATE_FOLLOW,
	NA_STATE_AVOID,
	NA_STATE_GIVEWAY,
	NA_STATE_BLOCKWAY,
	NA_STATE_ATTACHED,
	NA_STATE_COUNT
};

class IBaseNavigator {
public:
	virtual ~IBaseNavigator() {};
	//virtual void SetPathfinder(IBasePathfinder* pathfinder) = 0;
		
	//
	virtual bool checkState(NavState state) = 0;
	virtual NavState getState() = 0;

	virtual void start(Vector3d<f32> destination) = 0;
	virtual bool move(f32 timeStep) = 0;
	virtual void stop() = 0;
	virtual void setFollow() = 0;
	virtual void attachToGroup() = 0;
};

} // namespace ai
} // namespace hrengin

#endif //_hrengin_IBaseNavigator_
