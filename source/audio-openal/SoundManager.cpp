/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <assert.h>

#include <map>
#include <string>
#include <thread>

#include <aw/core/paths.h>
#include <aw/graphics/VideoManager.h>
#include <aw/core/Logger.h>

#include "ALutil.h"
#include "RIFFReader.h"

#include "Sound.h"
#include "SoundManager.h"

namespace aw {
namespace audio {

AW_SND_EXP SoundManager* createSoundManager()
{
	return new ALSoundManager;
}


ALSoundManager::ALSoundManager()
{
	device_ = alcOpenDevice(NULL);
	logError();
	if (!device_) {
		printf("[OpenAL] unable to open sound device");
	}
	context_ = alcCreateContext(device_, NULL);
	if (!alcMakeContextCurrent(context_)) {
		printf("[OpenAL] unable to set current context");
	}
	logError();
}

void ALSoundManager::loadSound(c consthar* fileName)
{
	if(soundMap_.find(fileName) != soundMap_.end()) {
		return;
	}

	std::string path(io::soundpath + fileName);
	SoundSample wave;

	readWAV(path, wave);

	ALuint buffer;
	ALenum format = toAlEnum(wave.channels, wave.bitsPerSample);

	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, wave.data, wave.size, wave.sampleRate);

	soundMap_[fileName] = buffer;
}

audio::Sound3D* ALSoundManager::createSound3D(char const* fileName)
{
	if(soundMap_.find(fileName) != soundMap_.end()) {
		return 0;
	}

	ALuint buffer = soundMap_[fileName];

	return new ALSound(buffer);
}


void ALSoundManager::logError(std::string msg) 
{
	ALenum alError = alGetError(  );
	if(AL_NO_ERROR != alError) {
		TRACE("[OpenAL]", msg, std::to_string(alError));
	} else {
		alError = alcGetError( device_ );
		if(ALC_NO_ERROR != alError) {
			TRACE("[OpenAL]", msg, std::to_string(alError));
		}
	}
}

#if 0
SoundManager::~SoundManager()
{
	alDeleteBuffers(1, buffer);
}

void SoundManager::playSound(c consthar* fileName)
{
	SoundSample* wave = &soundMap_[fileName];
	std::thread threadPlay(&SoundManager::threadedPlay, this, wave);
	threadPlay.detach();
}
#endif

} // namespace audio
} // namespace aw
