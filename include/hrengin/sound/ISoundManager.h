/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ISoundManager_
#define _hrengin_ISoundManager_

#include <hrengin/sound/sound.h>

namespace hrengin {
namespace sound {
class ISound;

//! This class is used to manage all audio output
class ISoundManager {
public:
	virtual ~ISoundManager()
	{
	};

	virtual void addSound(const char* fileName) = 0;
	virtual void initSounds() = 0;
	virtual void playSound(const char* fileName) = 0;
};

//! Create new sound manager
HR_SND_EXP ISoundManager* createSoundManager();

} // namespace sound
} // namespace hrengin
#endif//_hrengin_ISoundManager_
