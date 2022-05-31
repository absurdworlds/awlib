#ifndef aw_config_stdlib_h
#define aw_config_stdlib_h

#include <version>

#ifdef AW_STDLIB
#undef AW_STDLIB
#endif

#define AW_STDLIB_UNKNOWN 0
#define AW_STDLIB_GLIBCXX 1
#define AW_STDLIB_LIBCXX 2
#define AW_STDLIB_MSVCSTL 3

#if defined(__GLIBCXX__)
#define AW_STDLIB AW_STDLIB_GLIBCXX
#elif defined(_LIBCPP_VERSION)
#define AW_STDLIB AW_STDLIB_LIBCXX
#elif defined(_MSVC_STL_UPDATE)
#define AW_STDLIB AW_STDLIB_MSVCSTL
#else
#define AW_STDLIB AW_STDLIB_UNKNOWN
#endif

#endif//aw_config_stdlib_h
