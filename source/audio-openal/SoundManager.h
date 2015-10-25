/*
 * Copyright (C) 2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_SoundManager_
#define _awrts_SoundManager_
#include <map>
#include <string>

#include <AL/al.h>
#include <AL/alc.h>

#include <awengine/config/config.h>
#include <awengine/common/types.h>

#include <awengine/sound/SoundManager.h>
#include <awengine/sound/Sound.h>

#include "SoundSample.h"

namespace awrts {
namespace audio {

class SoundManager : public SoundManager {
public:
	SoundManager();
	virtual ~SoundManager() = default;

	virtual void loadSound(char const* fileName);
	virtual Sound3D* createSound3D(char const* fileName);
private:
	ALCdevice* device_;
	ALCcontext* context_;
	ALuint source_;

	std::map<std::string, ALuint> soundMap_;

	void logError(std::string msg = "");
};

} // namespace audio
} // namespace awrts
#endif//_awrts_SoundManager_
