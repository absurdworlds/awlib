#ifndef _hrengin_ISoundManager_
#define _hrengin_ISoundManager_

#include <hrengin/common/api.h>

namespace hrengin {
namespace sound {

class ISound;

class ISoundManager {
public:
	virtual void addSound(const char* fileName) = 0;
	virtual void initSounds() = 0;
	virtual void playSound(const char* fileName) = 0;
};

HRENGINSOUND_API ISoundManager& getSoundManager();

} // namespace sound
} // namespace hrengin

#endif//_hrengin_ISoundManager_