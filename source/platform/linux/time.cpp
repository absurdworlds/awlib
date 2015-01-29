/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <time.h>

#include <hrengin/platform/time.h>
#include <hrengin/platform/platform.h>

namespace hrengin {
//! Get clock resolution, in nanoseconds
u32 getClockResolution()
{
	struct timespec res;
	int rc = clock_getres(CLOCK_MONOTONIC, &res);
	
	if(rc == 0) {
		return res.tv_nsec;
	}
	return 0;
}

/*!
 * Get time elapsed from some moment.
 * Platfrom-dependent. May not be consistent between different executions of 
 * the application, so it should be probed at every startup.
 */
HR_SYS_EXP u32 getTime()
{
	struct timespec tp;
	int rc = clock_gettime(CLOCK_MONOTONIC, &tp);
	if(rc == 0) {
		return (tp.tv_sec * 1000) + (tp.tv_nsec / 1000000);
	}
	return 0;
}
} // namespace hrengin
