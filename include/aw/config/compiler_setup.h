/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_compiler_setup_
#define _aw_compiler_setup_
/*!
 * \file compiler_setup
 * \brief Setup compiler and platform specific settings
 */

// defaults
#define AW_32BIT

/* Windows platform */
#if defined(_WIN32) || defined(_WIN64)
	#define AW_WINDOWS
#endif

#if defined(__clang__)
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#elif defined(__GNUC__) || defined(__GNUG__)
	#if __x86_64__
		#undef AW_32BIT
		#define AW_64BIT
	#endif
#elif defined(_MSC_VER)
	#define AW_COMPILER_MSC
	#if defined(_WIN64)
		#undef AW_32BIT
		#define AW_64BIT
	#endif
	#pragma warning(disable: 4244)
	#pragma warning(disable: 4351)
#endif
#endif //_aw_compiler_setup_
