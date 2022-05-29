/*
 * Copyright (C) 2014-2016  absurdworlds
 * Copyright (C) 2016       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_h
#define aw_string_h
#include <aw/config.h>

#ifdef AW_MODULE_STRING
	#define AW_STRING_EXP AW_EXPORT
#else
	#define AW_STRING_EXP AW_IMPORT
#endif

// Namespace descriptions for Doxygen
namespace aw {
/*!
 * String support library. Contains various helpers,
 * like compose, split, join.
 */
namespace string {}
}
#endif//aw_string_h
