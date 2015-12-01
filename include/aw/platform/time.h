/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_time_
#define _aw_time_
#include <aw/common/types.h>
#include <aw/platform/platform.h>

namespace aw {
/*!
 * Get time elapsed from some moment.
 * Platfrom-dependent. May not be consistent between different executions of 
 * the application, so it should be probed at every startup.
 */
AW_SYS_EXP u32 getTime();

} // namespace aw
#endif//_aw_time_
