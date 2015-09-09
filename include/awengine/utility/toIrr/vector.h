/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_hrToIrr_
#define _awrts_hrToIrr_
#include <irrlicht/vector3d.h>
#include <awrts/math/Vector3d.h>

namespace awrts {
inline Vector3d<f32> toAW(irr::core::vector3df const& irrVec)
{
	return Vector3d<f32>(irrVec.X, irrVec.Y, irrVec.Z);
}

inline irr::core::vector3df toIrr(Vector3d<f32> const& awVec)
{
	return irr::core::vector3df(awVec.x,awVec.y,awVec.z);
}

inline Vector3d<i32> toAW(irr::core::vector3di const& irrVec)
{
	return Vector3d<i32>(irrVec.X, irrVec.Y, irrVec.Z);
}

inline irr::core::vector3di toIrr(Vector3d<i32> const& awVec)
{
	return irr::core::vector3di(awVec.x,awVec.y,awVec.z);
}
} // namespace awrts
#endif//_awrts_hrToIrr_
