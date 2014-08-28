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
#else
	#define HRENGINGRAPHICS_API __declspec(dllimport)
#endif


#ifdef HRENGIN_FILESYSTEM
	#define HRENGINFILESYSTEM_API __declspec(dllexport)
#else
	#define HRENGINFILESYSTEM_API __declspec(dllimport)
#endif

#endif//__HRENGIN_hrenginapi_H__