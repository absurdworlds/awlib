#include <map>
#include <string>

#include <bass/bass.h>

#include <hrengin/hrengin.h>
#include <hrengin/hrengin.sound.h>
#include <hrengin/sound/ISound.h>

#include "CSoundManager.h"

namespace hrengin {
namespace filesystem {

const std::string soundpath("../data/sound/");

} // namespace filesystem

namespace sound {

void CSoundManager::addSound(const char* fileName)
{
	std::string path(filesystem::soundpath + fileName);
	soundMap_[fileName] = BASS_SampleLoad(FALSE, path.c_str(), 0, 0, 10, BASS_SAMPLE_MONO);
}

void CSoundManager::initSounds()
{
	BASS_Init(-1, 44100, 0, GetWindow(), 0);
	BASS_Set3DFactors(1, 0.5, 1);

	addSound("generic_ready03.wav");
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
