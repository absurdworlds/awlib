/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <thread>

#include "Sound.h"

namespace awrts {
namespace audio {

ALSound::ALSound(ALuint bufferHandle)
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

ALSound::~ALSound()
{
	alDeleteSources(1, &source_);
}

bool ALSound::play()
{
#if 0
	// I realized that there is no need to use separate thread, because
	// there is no need to free resources, so we don't need to wait for
	// sound to stop

	stopped_ = false;

	std::thread playThread(&Sound::playThreaded, this);

	playThread.detach();
#endif
	ALint source_state;

	alGetSourcei(source_, AL_SOURCE_STATE, &source_state);

	if(source_state == AL_PLAYING)
		return false;

	alSourcePlay(source_);
	return true;
}

bool ALSound::stop()
{
	alSourceStop(source_);
#if 0
	// unless I figure something more elegant
	stopped_ = true;
#endif
	return true;
}

void ALSound::move(Vector3d pos, f32 timeStep)
{
	vel_[0] = (pos[0] - pos_[0]) / timeStep;
	vel_[1] = (pos[1] - pos_[1]) / timeStep;
	vel_[2] = (pos[2] - pos_[2]) / timeStep;
	pos_[0] = pos[0];
	pos_[1] = pos[1];
	pos_[2] = pos[2];

	alSourcefv(source_, AL_POSITION, pos_);
	alSourcefv(source_, AL_VELOCITY, vel_);
}

void ALSound::setPosition(Vector3d pos)
{
	vel_[0] = 0;
	vel_[1] = 0;
	vel_[2] = 0;
	pos_[0] = pos[0];
	pos_[1] = pos[1];
	pos_[2] = pos[2];

	alSourcefv(source_, AL_POSITION, pos_);
	alSourcefv(source_, AL_VELOCITY, vel_);
}

void ALSound::playThreaded()
{
}

} // namespace audio
} // namespace awrts
