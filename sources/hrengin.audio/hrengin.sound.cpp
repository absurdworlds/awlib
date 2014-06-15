#include <map>
#include <string>

#include <bass/bass.h>

#include <hrengin/hrengin.h>
#include <hrengin/hrengin.sound.h>
#include <hrengin/sound/ISound.h>

namespace hrengin
{

namespace filesystem
{

const std::string soundpath("../data/sound/");

}

namespace sound
{

	std::map<std::string,u32>& CSoundManager::getSoundMap()
	{
		static std::map<std::string,u32> sounds_; 
		return sounds_;
	}

void CSoundManager::addSound(const char* fileName)
{
	std::string path(filesystem::soundpath + fileName);
	getSoundMap()[fileName] = BASS_SampleLoad(FALSE,path.c_str(),0,0,10,BASS_SAMPLE_MONO);
}

void CSoundManager::initSounds()
{
	BASS_Init ( -1, 44100, 0, GetWindow(), 0 );
	BASS_Set3DFactors( 1, 0.5, 1 );

	addSound("generic_ready03.wav");
	addSound("generic_yes02.wav");
	addSound("generic2_ready01.wav");
	addSound("generic2_yes01.wav");
}

void CSoundManager::playSound (const char* fileName)
{
	HCHANNEL channel = BASS_SampleGetChannel ( getSoundMap()[fileName], false );
	if (!BASS_ChannelPlay ( channel, true ))
	{
		fprintf(stderr,"DEBUG: can't play the sound %s, m'lord\n",fileName);
	}
}
	
} // namespace sound
} // namespace hrengin


#ifdef _HR_ØINDOWS

#include <windows.h>

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif