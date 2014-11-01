/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IBasePathfinder_
#define _hrengin_IBasePathfinder_

#include <hrengin/math/Vector3d.h>

#include <hrengin/ai/ai.h>

namespace hrengin {
namespace ai {
class Path;

class IBasePathfinder {
public:
	virtual Path findPath(Vector3d<f32> start, Vector3d<f32> end) = 0;
};

HR_AI_EXP IBasePathfinder* createSimplePathfinder();

} // namespace ai
} // namespace hrengin
#endif //_hrengin_IBasePathfinder_
