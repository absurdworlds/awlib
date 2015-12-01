/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <Windows.h>

#include <aw/platform/time.h>

namespace aw {

AW_SYS_EXP u32 getTime()
{
	//borrowed from Irrlicht, temporary
	LARGE_INTEGER HighPerformanceFreq;
	QueryPerformanceFrequency(&HighPerformanceFreq);

	DWORD_PTR affinityMask = SetThreadAffinityMask(GetCurrentThread(), 1);

	LARGE_INTEGER ticks;
	BOOL queriedOK = QueryPerformanceCounter(&ticks);

	SetThreadAffinityMask(GetCurrentThread(), affinityMask);

	if (queriedOK) {
		return u32((ticks.QuadPart) * 1000 / HighPerformanceFreq.QuadPart);
	}

	return 0;
}
} // namespace aw
