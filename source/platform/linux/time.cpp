
#include <time.h>

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
		return tp.tv_nsec / 1000;
	}
	return 0;
}

} // namespace hrengin
