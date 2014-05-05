
#ifndef __HG_CONFIG_H__
#define __HG_CONFIG_H__

#include "Base/Config/hrVersions.h"

// Windows platform
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
	#define _HR_ØINDOWS
#endif

#ifndef FORCEINLINE
	#ifdef _MSC_VER
		#define FORCEINLINE __forceinline
	#else
		#define FORCEINLINE inline
	#endif
#endif

#ifdef HRENGIN_EXPORTS
	#define HRENGIN_API __declspec(dllexport)
#else
	#define HRENGIN_API __declspec(dllimport)
#endif

#define _HR_PHYSICS_HAVOK

#endif //__HG_CONFIG_H__