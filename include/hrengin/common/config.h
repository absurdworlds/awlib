/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_config_
#define _hrengin_config_

/* Windows platform */
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
	#define _HR_ØINDOWS
#endif

#if defined(__clang__)
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#elif defined(__GNUC__) || defined(__GNUG__)
#elif defined(_MSC_VER)
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
