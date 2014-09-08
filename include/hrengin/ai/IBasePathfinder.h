/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IBasePathfinder_
#define _hrengin_IBasePathfinder_

#include <hrengin/common/api.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace ai {

class CPath;

class IBasePathfinder {
public:
	virtual CPath findPath(Vector3d<f32> start, Vector3d<f32> end) = 0;
};

HRENGIN_API IBasePathfinder* createSimplePathfinder();

} // namespace ai
} // namespace hrengin

#endif //_hrengin_IBasePathfinder_
