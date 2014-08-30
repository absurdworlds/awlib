//#include <Irrlicht/irrlicht.h>

#include <Windows.h>

#include <hrengin/common/time.h>

#include "CVideoManager.h"

namespace hrengin {

//borrowed from Irrlicht, temporary
HRENGINGRAPHICS_API u32 getTime()
{
	LARGE_INTEGER HighPerformanceFreq;
	QueryPerformanceFrequency(&HighPerformanceFreq);

	DWORD_PTR affinityMask = SetThreadAffinityMask(GetCurrentThread(), 1);
	
	LARGE_INTEGER ticks;
	BOOL queriedOK = QueryPerformanceCounter(&ticks);
	
	SetThreadAffinityMask(GetCurrentThread(), affinityMask);

	if(queriedOK)
		return u32((ticks.QuadPart) * 1000 / HighPerformanceFreq.QuadPart);
	/*static irr::ITimer* timer(graphics::getLocalManager().GetDevice()->getTimer());
	return timer->getTime();*/
	return 0;
}

}