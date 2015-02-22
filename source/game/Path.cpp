/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <hrengin/ai/Path.h>

namespace hrengin {
namespace ai {

Path::const_iterator findClosestNode(Path::const_iterator& first,
	Path::const_iterator& last, Vector3d<f32> point)
{
	f32 closestDistance = std::numeric_limits<f32>::max();
	Path::const_iterator closest = first;

	for(auto it = first; it != last; ++ it) {
		f32 diff = (*it - point).squareLength();

		if(diff < closestDistance) {
			closestDistance = diff;
			closest = it;
		} else if(closestDistance < diff) {
			return --it;
		}
	}

	return closest;
}

} // namespace ai
} // namespace hrengin
