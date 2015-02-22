/*
 * Copyright (C) 2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_SoundManager_
#define _hrengin_SoundManager_

#include <map>
#include <string>

#include <al.h>
#include <alc.h>

#include <hrengin/common/config.h>
#include <hrengin/common/types.h>

#include <hrengin/sound/SoundManager.h>
#include <hrengin/sound/Sound.h>

#include "SoundSample.h"

namespace hrengin {
namespace audio {

class SoundManager : public SoundManager {
public:
	SoundManager();
	virtual ~SoundManager() {};

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
} // namespace hrengin
#endif//_hrengin_SoundManager_
