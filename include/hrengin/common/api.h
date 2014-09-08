/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef __HRENGIN_hrenginapi_H__
#define __HRENGIN_hrenginapi_H__

#ifdef HRENGIN_HRENGIN
	#define HRENGIN_API __declspec(dllexport)
#else
	#define HRENGIN_API __declspec(dllimport)
#endif

#ifdef HRENGIN_AUDIO
	#define HRENGINSOUND_API __declspec(dllexport)
#else
	#define HRENGINSOUND_API __declspec(dllimport)
#endif

#ifdef HRENGIN_PHYSICS
	#define HRENGINPHYSICS_API __declspec(dllexport)
#else
	#define HRENGINPHYSICS_API __declspec(dllimport)
#endif

#ifdef HRENGIN_GRAPHICS
	#define HRENGINGRAPHICS_API __declspec(dllexport)
	#define HR_GRAPHICS_API __declspec(dllexport)
#else
	#define HRENGINGRAPHICS_API __declspec(dllimport)
	#define HR_GRAPHICS_API __declspec(dllimport)
#endif

#ifdef HRENGIN_FILESYSTEM 
	#define HRENGINFILESYSTEM_API __declspec(dllexport)
	#define HR_CORE_API __declspec(dllexport)
#else
	#define HRENGINFILESYSTEM_API __declspec(dllimport)
	#define HR_CORE_API __declspec(dllimport)
#endif

#ifdef HRENGIN_PLATFORM
	#define HRG_PLATFORM_API __declspec(dllexport)
#else
	#define HRG_PLATFORM_API __declspec(dllimport)
#endif
#endif//__HRENGIN_hrenginapi_H__