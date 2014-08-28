
#include <thread>

#include "CSound.h"


namespace hrengin {
namespace audio {

CSound::CSound(ALuint bufferHandle)
: pos_(), vel_() 
{
	alGenSources(1, &source_);

	alSourcei (source_, AL_BUFFER, bufferHandle);
	alSourcef (source_, AL_PITCH, 1.0f);
	alSourcef (source_, AL_GAIN, 1.0f);
	alSourcefv(source_, AL_POSITION, pos_);
	alSourcefv(source_, AL_VELOCITY, vel_);
	alSourcei (source_, AL_LOOPING, AL_FALSE);
}

CSound::~CSound()
{
	alDeleteSources(1, &source_);
}

bool CSound::play()
{
#if 0
	// I realized that there is no need to use separate thread, because
	// there is no need to free resources, so we don't need to wait for
	// sound to stop

	stopped_ = false;

	std::thread playThread(&CSound::playThreaded, this);

	playThread.detach();
#endif
	ALint source_state;

	alGetSourcei(source_, AL_SOURCE_STATE, &source_state);
	
	if(source_state == AL_PLAYING) {
		return false;
	}

	alSourcePlay(source_);
	return true;
}

bool CSound::stop()
{
	alSourceStop(source_);
#if 0
	// unless I figure something more elegant
	stopped_ = true;
#endif
	return true;
}

void CSound::move(Vector3d pos, f32 timeStep)
{
	vel_[0] = (pos.X - pos_[0]) / timeStep;
	vel_[1] = (pos.Y - pos_[1]) / timeStep;
	vel_[2] = (pos.Z - pos_[2]) / timeStep;
	pos_[0] = pos.X;
	pos_[1] = pos.Y;
	pos_[2] = pos.Z;

	alSourcefv(source_, AL_POSITION, pos_);
	alSourcefv(source_, AL_VELOCITY, vel_);
}

void CSound::setPosition(Vector3d pos)
{
	vel_[0] = 0;
	vel_[1] = 0;
	vel_[2] = 0;
	pos_[0] = pos.X;
	pos_[1] = pos.Y;
	pos_[2] = pos.Z;

	alSourcefv(source_, AL_POSITION, pos_);
	alSourcefv(source_, AL_VELOCITY, vel_);
}

void CSound::playThreaded()
{
}


} // namespace audio
} // namespace hrengin