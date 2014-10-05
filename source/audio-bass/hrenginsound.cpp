
#include <hrengin/hrengin.sound.h>

#include "CSoundManager.h"

namespace hrengin
{

namespace sound
{

HRENGINSOUND_API ISoundManager& getSoundManager()
{
	static CSoundManager singleton;
	return singleton;
}

} // namespace sound
} // namespace hrengin
