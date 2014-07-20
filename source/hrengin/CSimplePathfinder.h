#ifndef __HRENGIN_CSimplePathfinder__
#define __HRENGIN_CSimplePathfinder__

#include <hrengin/ai/IBasePathfinder.h>
#include <hrengin/ai/CPath.h>

namespace hrengin {
namespace ai {

class CPath;

class CSimplePathfinder : public IBasePathfinder
{
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

#endif //__HRENGIN_CSimplePathfinder__