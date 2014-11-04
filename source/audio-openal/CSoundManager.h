#ifndef _hrengin_CSoundManager_
#define _hrengin_CSoundManager_

#include <map>
#include <string>

#include <al.h>
#include <alc.h>

#include <hrengin/common/config.h>
#include <hrengin/common/types.h>

#include <hrengin/sound/ISoundManager.h>
#include <hrengin/sound/ISound.h>

#include "SoundSample.h"

namespace hrengin {
namespace audio {

class CSoundManager : public ISoundManager {
public:
	CSoundManager();
	virtual ~CSoundManager() {};

	virtual void loadSound(const char* fileName);
	virtual ISound3D* createSound3D(const char* fileName);
private:
	ALCdevice* device_;
	ALCcontext* context_;
	ALuint source_;

	std::map<std::string, ALuint> soundMap_;

	void logError(std::string msg = "");
};

} // namespace audio
} // namespace hrengin
#endif//_hrengin_CSoundManager_
