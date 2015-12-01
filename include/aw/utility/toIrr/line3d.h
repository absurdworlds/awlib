/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_ToIrr_line__
#define aw_ToIrr_line__
#include <irrlicht/line3d.h>

#include <aw/math/Line3d.h>

namespace aw {
inline Line3d<f32> toAW(irr::core::line3df const& irrLine)
{
	irr::core::vector3df const& start = irrLine.start;
	irr::core::vector3df const& end = irrLine.end;
	return Line3d<f32>(start.X,start.Y,start.Z,end.X,end.Y,end.Z);
}

inline irr::core::line3df toIrr(Line3d<f32> const& awLine)
{
	Vector3d<f32> const& start = awLine.start;
	Vector3d<f32> const& end = awLine.end;
	return irr::core::line3df(start.x,start.y,start.z,end.x,end.y,end.z);
}
} // namespace aw
#endif//aw_ToIrr_line__
