#ifndef _hrengin_ISoundManager_
#define _hrengin_ISoundManager_

#include <hrengin/common/hrenginapi.h>

namespace hrengin {
namespace audio {

class ISound;
class ISound3D;

class ISoundManager {
public:
	virtual void loadSound(const char* fileName) = 0;
	virtual ISound3D* createSound3D(const char* fileName) = 0;
};

HRENGINSOUND_API ISoundManager& getSoundManager();

} // namespace audio
} // namespace hrengin

#endif//__HRENGIN_SOUND_ISoundManager_H__
