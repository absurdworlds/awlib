/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_visibility_
#define _awrts_visibility_
#include <awrts/config/compiler_setup.h>
/*!
 * \file visibility
 * \brief Defines import/export macro.
 */
#if defined(AW_WINDOWS) || defined(AW_CYGWIN)
	#if defined(_MSC_VER)
		#define AW_EXPORT __declspec(dllexport)
		#define AW_IMPORT __declspec(dllimport)
	#elif defined(__GNUC__)
		#define AW_EXPORT __attribute__ ((dllexport))
		#define AW_IMPORT __attribute__ ((dllimport))
	#endif
	#define AW_PUBLIC
	#define AW_LOCAL
#else
	#if defined(__clang__) || __GNUC__ >= 4
		#define AW_VISIBILITY_SUPPORT 1
	#else
		#define AW_VISIBILITY_SUPPORT 0
	#endif
	#if AW_VISIBILITY_SUPPORT == 1
		#define AW_PUBLIC __attribute__ ((visibility ("default")))
		#define AW_LOCAL  __attribute__ ((visibility ("hidden")))
		#define AW_EXPORT AW_PUBLIC
		#define AW_IMPORT AW_PUBLIC
	#else
		#define AW_EXPORT
		#define AW_IMPORT
		#define AW_PUBLIC
		#define AW_LOCAL
	#endif
#endif
#endif//_awrts_visibility_
