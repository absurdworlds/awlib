
#ifndef __HG_CONFIG_H__
#define __HG_CONFIG_H__

#include "Base/Config/hrVersions.h"

/* Windows platform */
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
	#define _HR_ØINDOWS
#endif

/* Determine compiler */
#if defined(__clang__)
	/* Clang/LLVM. ---------------------------------------------- */
	
#elif defined(__ICC) || defined(__INTEL_COMPILER)
	/* Intel ICC/ICPC. ------------------------------------------ */
	#define __HRCMP_ICC__
#elif defined(__GNUC__) || defined(__GNUG__)
	/* GNU GCC/G++. --------------------------------------------- */
	#define __HRCMP_GNU__
#elif defined(__HP_cc) || defined(__HP_aCC)
	/* Hewlett-Packard C/aC++. ---------------------------------- */

#elif defined(__IBMC__) || defined(__IBMCPP__)
	/* IBM XL C/C++. -------------------------------------------- */
	#define __HRCMP_IBM__

#elif defined(_MSC_VER)
	/* Microsoft Visual Studio. --------------------------------- */
	#define __HRCMP_MSC__
#elif defined(__PGI)
	/* Portland Group PGCC/PGCPP. ------------------------------- */

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
	/* Oracle Solaris Studio. ----------------------------------- */
#endif

#ifndef FORCEINLINE
	#ifdef __HRCMP_MSC__
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

#ifndef __FUNCTION_NAME__
	#ifdef __HRCMP_MSC__
		#define __FUNCTION_NAME__   __FUNCTION__  
	#else
		#define __FUNCTION_NAME__   __func__ 
	#endif
#else
	#if defined(__HRCMP_MSC__)
		#pragma message("Macro __FUNCTION_NAME__ already defined, please undefine it :(")
	#elif defined(__HRCMP_ICC__) || defined(__HRCMP_GNU__) || defined(__HRCMP_IBM__)
		#warning "Macro __FUNCTION_NAME__ already defined, please undefine it :("
	#else
	#endif
#endif

//#define _HR_PHYSICS_HAVOK
//#define _HR_PHYSICS_NEWTON

#define _HR_STR(arg) #arg

#endif //__HG_CONFIG_H__