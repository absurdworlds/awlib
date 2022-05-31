/*
 * Copyright (C) 2014-2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_compiler_setup_h
#define aw_compiler_setup_h
/*!
 * \file compiler_setup
 * \brief Setup compiler and platform specific settings
 */

/*
 * TODO: better way to separate platform detection,
 * and choosing which API to use by default
 */

/**** DEFINITIONS ****/
#define AW_COMPILER_GCC     1
#define AW_COMPILER_CLANG   2
#define AW_COMPILER_MSVC    3
#define AW_COMPILER_UNKNOWN 0

#define AW_ARCH_i686   686
#define AW_ARCH_x86_64 8664

// AW_PLATFORM
// AW_PLATFORM_SPECIFIC
#define AW_PLATFORM_POSIX  0
#define AW_PLATFORM_LINUX  1
#define AW_PLATFORM_BSD    2
#define AW_PLATFORM_SUN    3
#define AW_PLATFORM_APPLE  4
#define AW_PLATFORM_WIN32  5
#define AW_PLATFORM_WIN64  6

// When compiling for winelib, both win32 api and posix api can be used
#if    defined(AW_WINE_USE_POSIX)
#define AW_PLATFORM_WINELIB   AW_PLATFORM_POSIX
#else//defined(AW_WINE_USE_WIN32)
#define AW_PLATFORM_WINELIB   AW_PLATFORM_WIN32
#endif

/**** COMPILER VERSION ****/
#ifdef AW_COMPILER
	#undef AW_COMPILER
#endif
#ifdef AW_CVER_X
	#undef AW_CVER_X
#endif
#ifdef AW_CVER_Y
	#undef AW_CVER_Y
#endif

#if defined(__clang__)
// must check __clang__ before _MSC_VER because it may be clang-cl
#include <aw/config/clang.h>
#elif defined(__GNUC__) || defined(__GNUG__)
#include <aw/config/gcc.h>
#elif defined(_MSC_VER)
#include <aw/config/msvc.h>
#else
#include <aw/config/compiler_unknown.h>
#endif

/**** PLATFORM ****/
/* Winelib */
#if defined(__WINE__)
	#define AW_WINELIB
	#define AW_PLATFORM          AW_PLATFORM_WINELIB

	#if defined(_WIN64)
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_WIN64
	#else
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_WIN32
	#endif

	#define AW_SUPPORT_PLATFORM_POSIX 1
	#define AW_SUPPORT_PLATFORM_WIN32 1
/* Windows platform */
#elif defined(_WIN32)
	#define AW_WINDOWS
	#define AW_PLATFORM          AW_PLATFORM_WIN32
	#if defined(_WIN64)
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_WIN64
	#else
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_WIN32
	#endif
	#define AW_SUPPORT_PLATFORM_WIN32 1
/* Unix-like */
#elif defined(__gnu_linux__)
	#define AW_PLATFORM          AW_PLATFORM_POSIX
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_LINUX
	#define AW_SUPPORT_PLATFORM_POSIX 1
#elif defined (__sun)
	#define AW_PLATFORM          AW_PLATFORM_POSIX
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_SUN
	#define AW_SUPPORT_PLATFORM_POSIX 1
	#define AW_SUPPORT_PLATFORM_SUN 1
#elif defined(__APPLE__)
	// TODO
	#define AW_PLATFORM          AW_PLATOFRM_POSIX
	#define AW_PLATFORM_SPECIFIC AW_PLATOFRM_APPLE
	#define AW_SUPPORT_PLATFORM_POSIX 1
	#define AW_SUPPORT_PLATFORM_APPLE 1
#elif defined(BSD)
	#define AW_PLATFORM          AW_PLATFORM_POSIX
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_BSD
	#define AW_SUPPORT_PLATFORM_POSIX 1
#elif defined(__unix__) || defined(POSIX)
	#define AW_PLATFORM          AW_PLATFORM_POSIX
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_POSIX
	#define AW_SUPPORT_PLATFORM_POSIX 1
#endif

#if (AW_SUPPORT_PLATFORM_POSIX)
	#define AW_SUPPORT_PLATFORM_X11 1
#endif

/**** IMPORTS/EXPORTS ****/
#if !defined(AW_STATIC_BUILD)
	#if defined(AW_WINDOWS) || defined(AW_CYGWIN)
		#define AW_EXPORT AW_ATTRIBUTE( dllexport )
		#define AW_IMPORT AW_ATTRIBUTE( dllimport )
		#define AW_PUBLIC
		#define AW_LOCAL
	#else
		#define AW_PUBLIC AW_ATTRIBUTE( visibility ("default") )
		#define AW_LOCAL  AW_ATTRIBUTE( visibility ("hidden")  )
		#define AW_EXPORT AW_PUBLIC
		#define AW_IMPORT AW_PUBLIC
	#endif
#else
	#define AW_EXPORT
	#define AW_IMPORT
#endif //AW_STATIC_BUILD

/**** NON-STANDARD FEATURE TESTING ****/
#define AW_EXT(x) defined(AW_HAS_EXT##x) && AW_HAS_EXT##x
// #define AW_HAS(x) __has_builtin(x)

#define AW_FEATURE(x) AW_HAS_FEATURE_##x

#endif//aw_compiler_setup_h
