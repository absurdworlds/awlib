
#include <assert.h>

#include <map>
#include <string>
#include <thread>

#include <hrengin/filesystem/hrenginpaths.h>
#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/core/ILogger.h>

#include "ALutil.h"
#include "RIFFReader.h"

#include "CSound.h"
#include "CSoundManager.h"

namespace hrengin {
namespace audio {


HRENGINSOUND_API ISoundManager& getSoundManager()
{
	static CSoundManager singleton;
	return singleton;
}


CSoundManager::CSoundManager()
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

void CSoundManager::loadSound(const char* fileName)
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

ISound3D* CSoundManager::createSound3D(const char* fileName)
{
	if(soundMap_.find(fileName) != soundMap_.end()) {
		return 0;
	}

	ALuint buffer = soundMap_[fileName];

	return new CSound(buffer);
}


void CSoundManager::logError(std::string msg) 
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
CSoundManager::~CSoundManager()
{
	alDeleteBuffers(1, buffer);
}

void CSoundManager::playSound(const char* fileName)
{
	SoundSample* wave = &soundMap_[fileName];
	std::thread threadPlay(&CSoundManager::threadedPlay, this, wave);
	threadPlay.detach();
}
#endif

} // namespace audio
} // namespace hrengin
