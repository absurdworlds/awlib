// Not a bug: all of compiler_setup headers have the same include guard
#ifndef aw_compiler_setup_2
#define aw_compiler_setup_2
#ifdef _MSC_VER
#define AW_COMPILER AW_COMPILER_CLANG_CL
#else
#define AW_COMPILER AW_COMPILER_CLANG
#endif
// TODO: apple clang version bullshit
#define AW_CVER_X __clang_major__
#define AW_CVER_Y __clang_minor__
#define AW_COMPILER_VERSION AW_VERSION(__clang_major__, __clang_minor__, 0)
#define AW_COMPILER_VERSION_MAJOR __clang_major__
#define AW_COMPILER_VERSION_MINOR __clang_minor__

#if defined(__x86_64__) || defined(__amd64__)
	#define AW_ARCH AW_ARCH_X86_64
#elif defined(__i686__) || defined(_X86_)
	#define AW_ARCH AW_ARCH_i686
#endif

#ifdef _MSC_VER
#define AW_COMPILER_FLAVOR AW_COMPILER_MSVC
#else
#define AW_COMPILER_FLAVOR AW_COMPILER_GCC
#endif

#define AW_HAS_warning 1
#define AW_HAS_type_punning_union 1

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

#define AW_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#endif //aw_compiler_setup_2
