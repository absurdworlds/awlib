#ifndef _hrengin_CSound_
#define _hrengin_CSound_

#include <AL/al.h>

#include <hrengin/common/hrengintypes.h>

#include <hrengin/sound/ISound3D.h>

#include "ALVector.h"

namespace hrengin {
namespace audio {

class CSound : public ISound3D {
public:
	CSound(ALuint bufferHandle);
	~CSound();
	virtual bool play();
	virtual bool stop();
	virtual void move(Vector3d pos, f32 timeStep);
	virtual void setPosition(Vector3d pos);

private:
	void playThreaded();
	bool stopped_;

	ALuint source_;
 
	//ALVector3d pos_;
	//ALVector3d vel_;
	ALfloat pos_[3];
	ALfloat vel_[3];
};


} // namespace audio
} // namespace hrengin

#endif//_hrengin_CSound_