/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_physics_
#define _aw_physics_
#include <aw/config.h>

#ifdef AW_MODULE_PHYSICS
	#define AW_PHYS_EXP AW_EXPORT
#else
	#define AW_PHYS_EXP AW_IMPORT
#endif
#endif//_aw_physics_
