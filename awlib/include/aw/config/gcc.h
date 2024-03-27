// Not a bug: all of compiler_setup headers have the same include guard
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

#define AW_HAS_warning 1

// TODO: minimal compiler version
#define AW_HAS_EXT__builtin_clz 1
#define AW_HAS_EXT__builtin_ctz 1
#define AW_HAS_EXT__builtin_clzll 1
#define AW_HAS_EXT__builtin_ctzll 1
#define AW_HAS_EXT__builtin_unreachable 1

#ifdef __SIZEOF_INT128__
#define AW_HAS_EXT__int128 1
#endif

#define AW_HAS_IMPL(x) AW_HAS_EXT##x

#define AW_ATTRIBUTE( ... ) __attribute__((__VA_ARGS__))

#define aw_force_inline AW_ATTRIBUTE(always_inline) inline

#define AW_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#endif //aw_compiler_setup_2
