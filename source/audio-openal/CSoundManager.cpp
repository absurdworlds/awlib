
#include <assert.h>

#include <map>
#include <string>
#include <thread>

#include <hrengin/filesystem/hrenginpaths.h>
#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/core/ILogger.h>

#include "ALutil.h"
#include "RIFFReader.h"

#include "CSoundManager.h"

namespace hrengin {
namespace sound {


HRENGINSOUND_API ISoundManager& getSoundManager()
{
	static CSoundManager singleton;
	return singleton;
}

void CSoundManager::addSound(const char* fileName)
{
	SoundSample sample;

	std::string path(io::soundpath + fileName);
	readWAV(path, sample);

	soundMap_[fileName] = sample;
	//soundMap_[fileName] = BASS_SampleLoad(FALSE, path.c_str(), 0, 0, 10, BASS_SAMPLE_MONO);
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

void CSoundManager::initSounds()
{
	//graphics::IVideoManager& videomgr = graphics::getVideoManager();
	//void* wndHandle = videomgr.getPlatformSpecificData().win32.wndHandle;

	device_ = alcOpenDevice(NULL);
	logError();
	if (!device_) {
		printf("[OpenAL] unable to open sound device");
	}

	context_ = alcCreateContext(device_, NULL);
	logError();
}

void CSoundManager::playSound(const char* fileName)
{
	SoundSample* wave = &soundMap_[fileName];
	std::thread threadPlay(&CSoundManager::threadedPlay, this, wave);
	threadPlay.detach();
}

void CSoundManager::threadedPlay(SoundSample* wave)
{
	if (!alcMakeContextCurrent(context_)) {
		printf("[OpenAL] unable to set current context");
	}

	alcMakeContextCurrent(context_);
	logError();

	ALuint source;
	ALuint buffer;

	alGenBuffers(1, &buffer);
	logError();
	alGenSources(1, &source);
	logError();

	ALenum format = toAlEnum(wave->channels, wave->bitsPerSample);

	alBufferData(buffer, format, wave->data, wave->size, wave->sampleRate);
	logError();

	ALfloat sourcePos[] = { 0.0, 0.0, 0.0 };
	ALfloat sourceVel[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
	logError();

	alSourcei (source, AL_BUFFER,   buffer);
	logError();
	alSourcef (source, AL_PITCH,    1.0f     );
	alSourcef (source, AL_GAIN,     1.0f     );
	alSourcefv(source, AL_POSITION, sourcePos);
	alSourcefv(source, AL_VELOCITY, sourceVel);
	alSourcei (source, AL_LOOPING,  AL_FALSE );
	logError();

	alSourcePlay(source);
	
	ALint source_state;

	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	logError("unable to get source state");
	while (source_state == AL_PLAYING) {
		alGetSourcei(source, AL_SOURCE_STATE, &source_state);
		logError("unable to get source state");
	}

	//alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	alcMakeContextCurrent(NULL);
}


    

/*	alcMakeContextCurrent(context_);
	
	//alDeleteBuffers(1, buffer);*/

} // namespace sound
} // namespace hrengin
