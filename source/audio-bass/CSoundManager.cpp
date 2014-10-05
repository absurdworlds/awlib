#include <map>
#include <string>

#include <bass/bass.h>

#include <hrengin/core/paths.h>
#include <hrengin/graphics/IVideoManager.h>

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
	std::string path(io::soundpath + fileName);
	soundMap_[fileName] = BASS_SampleLoad(FALSE, path.c_str(), 0, 0, 10, BASS_SAMPLE_MONO);
}

void CSoundManager::initSounds()
{
//	graphics::IVideoManager& videomgr = graphics::getVideoManager();
//	void* wndHandle = videomgr.getPlatformSpecificData().win32.wndHandle;

	BASS_Init(-1, 44100, 0, 0, 0);
	BASS_Set3DFactors(1, 0.5, 1);

	addSound("generic_ready01.wav");
	addSound("generic_ready02.wav");
	addSound("generic_yes01.wav");
	addSound("generic_yes02.wav");
	addSound("generic2_ready01.wav");
	addSound("generic2_yes01.wav");
}

void CSoundManager::playSound(const char* fileName)
{
	HCHANNEL channel = BASS_SampleGetChannel(soundMap_[fileName], false);
	if (!BASS_ChannelPlay(channel, true)) {
		fprintf(stderr, "DEBUG: can't play the sound %s, m'lord\n", fileName);
	}
}

} // namespace sound
} // namespace hrengin
