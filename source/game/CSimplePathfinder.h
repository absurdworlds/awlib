/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CSimplePathfinder_
#define _hrengin_CSimplePathfinder_

#include <hrengin/ai/IBasePathfinder.h>
#include <hrengin/ai/Path.h>

namespace hrengin {
namespace ai {

class CSimplePathfinder : public IBasePathfinder {
public:
	virtual ~CSimplePathfinder() {};
	virtual Path findPath(Vector3d<f32> start, Vector3d<f32> end)
	{
		Path path;
		path.addNode(start);
		path.addNode(end);
		return path;
	}
};

} // namespace ai
} // namespace hrengin

#endif //_hrengin_CSimplePathfinder_
