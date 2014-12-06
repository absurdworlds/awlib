/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_time_
#define _hrengin_time_

#include <hrengin/common/types.h>

#include <hrengin/platform/platform.h>

namespace hrengin {
//! Get system time in milliseconds
HR_SYS_EXP u32 getTime ();

} // namespace hrengin
#endif//_hrengin_time_
