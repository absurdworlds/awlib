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
#define AW_COMPILER AW_COMPILER_MVSC
#define AW_CVER_X _MSC_VER

#if defined(_M_X64)
	#define AW_ARCH AW_ARCH_X86_64
#elif defined(_M_IX86)
	#define AW_ARCH AW_ARCH_i686
#endif
#endif //aw_compiler_setup_2
