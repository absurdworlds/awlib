#ifndef _hrengin_ALvector_
#define _hrengin_ALvector_

#include <AL/al.h>

#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace audio {

typedef hrVector3d<ALfloat> ALVector3d;

Vector3d ALVectorToHrg(ALVector3d vec)
{
	return Vector3d(vec.X, vec.Y, vec.Z);
}

ALVector3d HrgVectorToAL(Vector3d vec)
{
	return ALVector3d(vec.X, vec.Y, vec.Z);
}

} // namespace audio
} // namespace hrengin

#endif //_hrengin_ALvector_
