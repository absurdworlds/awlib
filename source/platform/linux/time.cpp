/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <time.h>
#include <stdio.h>

#include <hrengin/common/time.h>
#include <hrengin/common/api.h>

namespace hrengin {

HR_PLATFORM_API u32 getTime()
{
#if 0
	struct timespec res;
	int rc = clock_getres(CLOCK_MONOTONIC, &res);
	
	if(rc == 0) {
		u32 resolution = res.tv_nsec;
	}
#endif

	struct timespec tp;
	int rc = clock_gettime(CLOCK_MONOTONIC, &tp);
	if(rc == 0) {
		return (tp.tv_sec * 1000) + (tp.tv_nsec / 1000000);
	}
	return 0;
}

} // namespace hrengin
