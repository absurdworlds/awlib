/*
 * Copyright (C) 2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_SoundManager_
#define _aw_SoundManager_
#include <map>
#include <string>

#include <AL/al.h>
#include <AL/alc.h>

#include <aw/config/config.h>
#include <aw/common/types.h>

#include <aw/sound/SoundManager.h>
#include <aw/sound/Sound.h>

#include "SoundSample.h"

namespace aw {
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
} // namespace aw
#endif//_aw_SoundManager_
