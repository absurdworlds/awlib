/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_config_
#define _hrengin_config_ //TODO: split this file into 'config.h' and 'setup.h'

#define HR_32BIT

/* Windows platform */
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
	#define HR_WINDOWS
#endif

#if defined(__clang__)
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#elif defined(__GNUC__) || defined(__GNUG__)
	#if __x86_64__
		#undef HR_32BIT
		#define HR_64BIT
	#endif
#elif defined(_MSC_VER)
	#if defined(_WIN64) || defined(WIN64)
		#undef HR_32BIT
		#define HR_64BIT
	#endif
#endif

#if defined(_MSC_VER)
	#pragma warning(disable: 4244) 
#endif

/*! Uncomment used graphics library */
#define HR_GRAPHICS_IRRLICHT
//#define HR_GRAPHICS_OGRE
//#define HR_GRAPHICS_OSG
//#define HR_GRAPHICS_HRENGIN

#endif //_hrengin_config_
