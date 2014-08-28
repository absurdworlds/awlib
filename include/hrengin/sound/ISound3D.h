#ifndef _hrengin_ISound3D_
#define _hrengin_ISound3D_

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/Vector3d.h>

#include <hrengin/sound/ISound.h>

namespace hrengin {
namespace audio {


class ISound3D : public ISound {
public:
	/* play sound */
	virtual bool play() = 0;

	/* stop playing sound */
	virtual bool stop() = 0;

	/* Move sound to position `pos`, calculating velocity */
	virtual void move(Vector3d pos, f32 timeStep) = 0;

	/* Set sound to `pos` and reset velocity */
	virtual void setPosition(Vector3d pos) = 0;
};


} // namespace audio
} // namespace hrengin

#endif//_hrengin_ISound3D_
