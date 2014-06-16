#ifndef __HRENGIN_SOUND_hrenginsound_H__
#define __HRENGIN_SOUND_hrenginsound_H__


#include <hrengin/hrengin.h>
#include <hrengin/sound/ISound.h>
#include <hrengin/sound/ISoundManager.h>


namespace hrengin
{
namespace sound
{

HRENGINSOUND_API ISoundManager& getSoundManager();
	
} // namespace sound
} // namespace hrengin

#endif//__HRENGIN_SOUND_hrenginsound_H__