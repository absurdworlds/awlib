#ifndef __HRENGIN_SOUND_hrenginsound_H__
#define __HRENGIN_SOUND_hrenginsound_H__

#include <map>
#include <string>

#include <hrengin/config/hrConfig.h>
#include <hrengin/common/hrTypes.h>

namespace hrengin
{
namespace sound
{

class ISound;

class HRENGINSOUND_API CSoundManager
{
	public:
		static void addSound(const char* fileName);
		static void initSounds();
		static void playSound (const char* fileName);
	private:
		static std::map<std::string,u32>& getSoundMap();
};

	
} // namespace sound
} // namespace hrengin

#endif//__HRENGIN_SOUND_hrenginsound_H__