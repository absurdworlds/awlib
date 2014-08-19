#ifndef __HRENGIN_IBasePathfinder__
#define __HRENGIN_IBasePathfinder__

#include <hrengin/common/hrenginapi.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace ai {

class CPath;

class IBasePathfinder
{
	public:
		virtual CPath findPath(Vector3d start, Vector3d end) = 0;
};

HRENGIN_API IBasePathfinder* createSimplePathfinder();

} // namespace ai
} // namespace hrengin

#endif //__HRENGIN_IBasePathfinder__