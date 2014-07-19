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
		path.pathData_.push_back(start);
		path.pathData_.push_back(end);
		return path;
	}
};

HRENGIN_API IBasePathfinder* createSimplePathfinder()
{
	return new CSimplePathfinder;
}

} // namespace ai
} // namespace hrengin

#endif //__HRENGIN_CSimplePathfinder__