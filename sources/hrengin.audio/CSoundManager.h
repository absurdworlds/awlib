#ifndef __HRENGIN_SOUND_CSoundManager_H__
#define __HRENGIN_SOUND_CSoundManager_H__

#include <map>
#include <string>

#include <hrengin/config/hrConfig.h>
#include <hrengin/common/hrTypes.h>

namespace hrengin
{
namespace sound
{

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

#endif//__HRENGIN_SOUND_CSoundManager_H__