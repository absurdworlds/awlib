/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_platform_api_
#define _hrengin_platform_api_

#include <hrengin/common/config.h>

#ifdef _HR_ØINDOWS

#ifdef HRENGIN_PLATFORM
	#if defined(_MSC_VER)
		#define HR_PLATFORM_API __declspec(dllexport)
	#elif defined(_GNUC_)
		#define HR_PLATFORM_API __attribute__ ((dllexport))
	#endif
#else
	#if defined(_MSC_VER)
		#define HR_PLATFORM_API __declspec(dllimport)
	#elif defined(_GNUC_)
		#define HR_PLATFORM_API __attribute__ ((dllimport))
	#endif
#endif

#else
	#define HR_PLATFORM_API
#endif

#endif//_hrengin_platform_api_
