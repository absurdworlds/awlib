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
#define AW_COMPILER AW_COMPILER_GCC
#define AW_CVER_X __GNUC__
#define AW_CVER_Y __GNUC_MINOR__
#if defined(__x86_64__) || defined(__amd64__)
	#define AW_ARCH AW_ARCH_X86_64
#elif defined(__i686__) || defined(_X86_)
	#define AW_ARCH AW_ARCH_i686
#endif

#if (AW_CVER_X > 4) || (AW_CWER_X == 4 && AW_CVER_Y >= 8)
#define AW_HAS_EXT__builtin_bswap16 1
#endif
#if (AW_CVER_X > 4) || (AW_CWER_X == 4 && AW_CVER_Y >= 3)
#define AW_HAS_EXT__builtin_bswap32 1
#define AW_HAS_EXT__builtin_bswap64 1
#endif
#endif //aw_compiler_setup_2
