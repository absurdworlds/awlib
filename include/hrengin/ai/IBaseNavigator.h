#ifndef __HRENGIN_IBaseNavigator__
#define __HRENGIN_IBaseNavigator__

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace ai {

class IBasePathfinder;

enum NavState
{
	NA_STATE_IDLE,
	NA_STATE_VALIDATE,
	NA_STATE_GUARD,
	NA_STATE_MOVETO,
	NA_STATE_FOLLOW,
	NA_STATE_AVOID,
	NA_STATE_GIVEWAY,
	NA_STATE_BLOCKWAY,
	NA_STATE_ATTACHED,
	NA_STATE_COUNT,
	NA_STATE_ = 0x7FFFFFFF //force 32 bit for byte-alignment
};

class IBaseNavigator
{
	public:
		virtual ~IBaseNavigator() {};
		//virtual void SetPathfinder(IBasePathfinder* pathfinder) = 0;
		
		//
		virtual bool checkState(NavState state) = 0;
		virtual NavState getState() = 0;

		virtual void start(Vector3d destination) = 0;
		virtual bool move(f32 timeStep) = 0;
		virtual void stop() = 0;
		virtual void setFollow() = 0;
		virtual void attachToGroup() = 0;
};

} // namespace ai
} // namespace hrengin

#endif //__HRENGIN_IBaseNavigator__
