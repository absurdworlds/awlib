#ifndef _hrengin_ALvector_
#define _hrengin_ALvector_

#include <al.h>

#include <hrengin/math/Vector3d.h>

namespace hrengin {
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
} // namespace hrengin
#endif //_hrengin_ALvector_
