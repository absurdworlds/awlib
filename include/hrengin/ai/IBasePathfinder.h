#ifndef _hrengin_IBasePathfinder_
#define _hrengin_IBasePathfinder_

#include <hrengin/common/api.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace ai {

class CPath;

class IBasePathfinde {
	public:
		virtual CPath findPath(Vector3d start, Vector3d end) = 0;
};

HRENGIN_API IBasePathfinder* createSimplePathfinder();

} // namespace ai
} // namespace hrengin

#endif //_hrengin_IBasePathfinder_