/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_ALvector_
#define _awrts_ALvector_

#include <al.h>

#include <awrts/math/Vector3d.h>

namespace awrts {
namespace audio {

typedef Vector3d<ALfloat> ALVector3d;

Vector3d<f32> toHrengin(ALVector3d vec)
{
	return Vector3d<f32>(vec[0], vec[1], vec[2]);
}

ALVector3d toAL(Vector3d<f32> vec)
{
	return ALVector3d(vec[0], vec[1], vec[2]);
}

} // namespace audio
} // namespace awrts
#endif //_awrts_ALvector_
