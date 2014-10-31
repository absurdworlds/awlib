/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_visibility_
#define _hrengin_visibility_

#include <hrengin/common/config.h>

#if defined(HR_WINDOWS) || defined(HR_CYGWIN)
	#if defined(_MSC_VER)
		#define HR_EXPORT __declspec(dllexport)
		#define HR_IMPORT __declspec(dllimport)
	#elif defined(__GNUC__)
		#define HR_EXPORT __attribute__ ((dllexport))
		#define HR_IMPORT __attribute__ ((dllimport))
	#endif
	#define HR_PUBLIC
	#define HR_LOCAL
#else
	#if defined(__clang__) || __GNUC__ >= 4
		#define HR_VISIBILITY_SUPPORT 1
	#else
		#define HR_VISIBILITY_SUPPORT 0
	#endif
	#if HR_VISIBILITY_SUPPORT == 1
		#define HR_PUBLIC __attribute__ ((visibility ("default")))
		#define HR_LOCAL  __attribute__ ((visibility ("hidden")))

		#define HR_EXPORT HR_PUBLIC
		#define HR_IMPORT HR_PUBLIC
	#else
		#define HR_EXPORT
		#define HR_IMPORT
		#define HR_PUBLIC
		#define HR_LOCAL
	#endif
#endif

#endif//_hrengin_visibility_