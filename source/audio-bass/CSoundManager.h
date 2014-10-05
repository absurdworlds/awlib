#ifndef _hrengin_CSoundManager_
#define _hrengin_CSoundManager_

#include <map>
#include <string>

#include <hrengin/common/config.h>
#include <hrengin/common/types.h>

#include <hrengin/sound/ISound.h>
#include <hrengin/sound/ISoundManager.h>


namespace hrengin {
namespace sound {

class ISound;

class CSoundManager : public ISoundManager
{
public:
	virtual void addSound(const char* fileName);
	virtual void initSounds();
	virtual void playSound(const char* fileName);
private:
	std::map<std::string, u32> soundMap_;
};


} // namespace sound
} // namespace hrengin

#endif//_hrengin_CSoundManager_