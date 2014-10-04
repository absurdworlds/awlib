/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_api_
#define _hrengin_api_

#include <hrengin/common/config.h>

#ifdef _HR_WINDOWS
	#ifdef HRENGIN_HRENGIN
		#define HRENGIN_API __declspec(dllexport)
	#else
		#define HRENGIN_API __declspec(dllimport)
	#endif
	
	#ifdef HRENGIN_AUDIO
		#if defined(_MSC_VER)
			#define HRENGINSOUND_API __declspec(dllexport)
			#define HR_SOUND_API __declspec(dllexport)
		#elif defined(_GNUC_)
			#define HR_SOUND_API __attribute__ ((dllexport))
		#endif
	#else
		#define HRENGINSOUND_API __declspec(dllimport)
		#define HR_SOUND_API __declspec(dllimport)
	#endif
	
	#ifdef HRENGIN_PHYSICS
		#define HRENGINPHYSICS_API __declspec(dllexport)
	#else
		#define HRENGINPHYSICS_API __declspec(dllimport)
	#endif
		
#else
#endif
	
#endif//_hrengin_api_
