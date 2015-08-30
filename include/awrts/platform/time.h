/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_time_
#define _awrts_time_

#include <awrts/common/types.h>

#include <awrts/platform/platform.h>

namespace awrts {
/*!
 * Get time elapsed from some moment.
 * Platfrom-dependent. May not be consistent between different executions of 
 * the application, so it should be probed at every startup.
 */
HR_SYS_EXP u32 getTime();

} // namespace awrts
#endif//_awrts_time_
