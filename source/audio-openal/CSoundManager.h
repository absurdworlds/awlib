#ifndef _hrengin_CSoundManager_
#define _hrengin_CSoundManager_

#include <map>
#include <string>

#include <hrengin/config/hrConfig.h>
#include <hrengin/common/hrengintypes.h>

#include <hrengin/sound/ISound.h>
#include <hrengin/sound/ISoundManager.h>


#include <AL/al.h>
#include <AL/alc.h>

#include "SoundSample.h"

namespace hrengin {
namespace sound {

class ISound;


class CSoundManager : public ISoundManager {
public:
	virtual void addSound(const char* fileName);
	virtual void initSounds();
	virtual void playSound(const char* fileName);
private:
	ALCdevice* device_;
	ALCcontext* context_;
	ALuint source_;

	std::map<std::string, SoundSample> soundMap_;

	void logError(std::string msg = "");
	void threadedPlay(SoundSample* wave);
};


} // namespace sound
} // namespace hrengin

#endif//_hrengin_CSoundManager_