/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_SoundManager_
#define _aw_SoundManager_
#include <aw/sound/sound.h>

namespace aw {
namespace sound {
class Sound;

//! This class is used to manage all audio output
class SoundManager {
public:
	virtual ~SoundManager () = default;

	virtual void addSound (char const* fileName) = 0;
	virtual void initSounds () = 0;
	virtual void playSound (char const* fileName) = 0;
};

//! Create new sound manager
AW_SND_EXP SoundManager* createSoundManager ();

} // namespace sound
} // namespace aw
#endif//_aw_SoundManager_
