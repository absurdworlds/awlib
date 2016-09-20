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

// TODO: improve this, to make platforms non-mutually-exclusive
// (i.e. make both win32 and posix available under winelib)

/**** DEFINITIONS ****/
#define AW_COMPILER_GCC   1
#define AW_COMPILER_CLANG 2
#define AW_COMPILER_MSVC  3

#define AW_ARCH_i686   686
#define AW_ARCH_x86_64 8664

#define AW_PLATFORM_POSIX  0
#define AW_PLATFORM_LINUX  1
#define AW_PLATFORM_BSD    2
#define AW_PLATFORM_OSX    3
#define AW_PLATFORM_WIN32  4
#define AW_PLATFORM_WIN64  5

// When compiling for winelib, both win32 api and posix api can be used
#if   defined(AW_WINE_POSIX)
#define AW_PLATFORM_WINE   AW_PLATFORM_POSIX
#elif defined(AW_WINE_WIN32)
#define AW_PLATFORM_WINE   AW_PLATFORM_WIN32
#else
#define AW_PLATFORM_WINE   6
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

#if defined(__GNUC__) || defined(__GNUG__)
#include <aw/config/gcc.h>
#elif defined(__clang__)
#include <aw/config/clang.h>
#elif defined(_MSC_VER)
#include <aw/config/msvc.h>
#endif

/**** PLATFORM ****/
/* Winelib */
#if defined(__WINE__)
	#define AW_PLATFORM          AW_PLATFORM_WINE

	#if defined(_WIN64)
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_WIN64
	#else
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_WIN32
	#endif
/* Windows platform */
#elif defined(_WIN32)
	#define AW_WINDOWS
	#define AW_PLATFORM          AW_PLATFORM_WIN32
	#if defined(_WIN64)
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_WIN64
	#else
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_WIN32
	#endif
/* Unix-like */
#elif defined(__gnu_linux__)
	#define AW_PLATFORM          AW_PLATFORM_POSIX
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_LINUX
#elif defined(BSD)
	#define AW_PLATFORM          AW_PLATFORM_POSIX
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_BSD
#elif defined(__unix__) || defined(POSIX)
	#define AW_PLATFORM          AW_PLATFORM_POSIX
	#define AW_PLATFORM_SPECIFIC AW_PLATFORM_POSIX
#endif

/**** IMPORTS/EXPORTS ****/
#if defined(AW_WINDOWS) || defined(AW_CYGWIN)
	#if defined(_MSC_VER)
		#define AW_EXPORT __declspec(dllexport)
		#define AW_IMPORT __declspec(dllimport)
	#elif defined(__GNUC__)
		#define AW_EXPORT __attribute__ ((dllexport))
		#define AW_IMPORT __attribute__ ((dllimport))
	#endif
	#define AW_PUBLIC
	#define AW_LOCAL
#else
	#if defined(__clang__) || __GNUC__ >= 4
		#define AW_VISIBILITY_SUPPORT 1
	#else
		#define AW_VISIBILITY_SUPPORT 0
	#endif
	#if AW_VISIBILITY_SUPPORT == 1
		#define AW_PUBLIC __attribute__ ((visibility ("default")))
		#define AW_LOCAL  __attribute__ ((visibility ("hidden")))
		#define AW_EXPORT AW_PUBLIC
		#define AW_IMPORT AW_PUBLIC
	#else
		#define AW_EXPORT
		#define AW_IMPORT
		#define AW_PUBLIC
		#define AW_LOCAL
	#endif
#endif

/**** NON-STANDARD FEATURE TESTING ****/
#define AW_EXT(x) AW_HAS_EXT##x
// #define AW_HAS(x) __has_builtin(x)

#define AW_FEATURE(x) AW_HAS_FEATURE_##x

#endif//aw_compiler_setup_h
