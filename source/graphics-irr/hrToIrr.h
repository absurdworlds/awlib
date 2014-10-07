/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_hrToIrr_
#define _hrengin_hrToIrr_

#include <Irrlicht/line3d.h>
#include <hrengin/common/Line3d.h>

namespace hrengin {

inline Vector3d<f32> toIrr(irr::core::vector3df const& irrVec)
{
	return Vector3d<f32>(irrVec.X, irrVec.Y, irrVec.Z);
}

inline irr::core::vector3df toIrr(Vector3d<f32> const& hrVec)
{
	return irr::core::vector3df(hrVec.x,hrVec.y,hrVec.z);
}


inline Line3d<f32> toHrengin(irr::core::line3df const& irrLine)
{
	irr::core::vector3df const& start = irrLine.start;
	irr::core::vector3df const& end = irrLine.end;
	return Line3d<f32>(start.X,start.Y,start.Z,end.X,end.Y,end.Z);
}

inline irr::core::line3df toIrr(Line3d<f32> const& hrLine)
{
	Vector3d<f32> const& start = hrLine.start;
	Vector3d<f32> const& end = hrLine.end;
	return irr::core::line3df(start.x,start.y,start.z,end.x,end.y,end.z);
}

} // namespace hrengin

#endif//_hrengin_hrToIrr_
