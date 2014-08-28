#ifndef _hrengin_CSimplePathfinder_
#define _hrengin_CSimplePathfinder_

#include <hrengin/ai/IBasePathfinder.h>
#include <hrengin/ai/CPath.h>

namespace hrengin {
namespace ai {

class CPath;

class CSimplePathfinder : public IBasePathfinder {
public:
	virtual ~CSimplePathfinder() {};
	virtual CPath findPath(Vector3d start, Vector3d end)
	{
		CPath path;
		path.add(start);
		path.add(end);
		return path;
	}
};

} // namespace ai
} // namespace hrengin

#endif //_hrengin_CSimplePathfinder_