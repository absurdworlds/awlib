//#include <Irrlicht/irrlicht.h>

#include <Windows.h>

#include <hrengin/common/time.h>
#include <hrengin/platform/api.h>

namespace hrengin {

HR_PLATFORM_API u32 getTime()
{
	//borrowed from Irrlicht, temporary
	LARGE_INTEGER HighPerformanceFreq;
	QueryPerformanceFrequency(&HighPerformanceFreq);

	DWORD_PTR affinityMask = SetThreadAffinityMask(GetCurrentThread(), 1);
	
	LARGE_INTEGER ticks;
	BOOL queriedOK = QueryPerformanceCounter(&ticks);
	
	SetThreadAffinityMask(GetCurrentThread(), affinityMask);

	if(queriedOK) {
		return u32((ticks.QuadPart) * 1000 / HighPerformanceFreq.QuadPart);
	}

	return 0;
}

} // namespace hrengin
