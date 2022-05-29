/*
 * Copyright (C) 2013-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_platform_exp_h
#define aw_platform_exp_h
#include <aw/config.h>

#ifdef AW_MODULE_PLATOFORM
	#define AW_PLATFORM_EXP AW_EXPORT
#else
	#define AW_PLATFORM_EXP AW_IMPORT
#endif
#endif//aw_platform_exp_h
