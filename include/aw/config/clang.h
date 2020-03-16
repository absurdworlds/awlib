/*
 * Copyright (C) 2014-2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_compiler_setup_2
#define aw_compiler_setup_2
#define AW_COMPILER AW_COMPILER_CLANG
// TODO: apple clang version bullshit
#define AW_CVER_X __clang_major__
#define AW_CVER_Y __clang_minor__
#if defined(__x86_64__) || defined(__amd64__)
	#define AW_ARCH AW_ARCH_X86_64
#elif defined(__i686__) || defined(_X86_)
	#define AW_ARCH AW_ARCH_i686
#endif

#define AW_HAS_EXT__builtin_bswap16 __has_builtin(__builtin_bswap16)
#define AW_HAS_EXT__builtin_bswap32 __has_builtin(__builtin_bswap32)
#define AW_HAS_EXT__builtin_bswap64 __has_builtin(__builtin_bswap64)

#define AW_HAS_EXT__builtin_clz   __has_builtin(__builtin_clz)
#define AW_HAS_EXT__builtin_ctz   __has_builtin(__builtin_ctz)
#define AW_HAS_EXT__builtin_clzll __has_builtin(__builtin_clzll)
#define AW_HAS_EXT__builtin_ctzll __has_builtin(__builtin_ctzll)
#define AW_HAS_EXT__builtin_unreachable __has_builtin(__builtin_unreachable)

#ifdef __SIZEOF_INT128__
#define AW_HAS_EXT__int128 1
#endif

#define AW_ATTRIBUTE( ... ) __attribute__((__VA_ARGS__))

#define aw_force_inline AW_ATTRIBUTE(always_inline) inline
#endif //aw_compiler_setup_2
