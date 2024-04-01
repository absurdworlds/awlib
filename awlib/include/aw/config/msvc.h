// Not a bug: all of compiler_setup headers have the same include guard
#ifndef aw_compiler_setup_2
#define aw_compiler_setup_2
#define AW_COMPILER AW_COMPILER_MSVC
#define AW_CVER_X _MSC_VER

#if defined(_M_X64)
	#define AW_ARCH AW_ARCH_X86_64
#elif defined(_M_IX86)
	#define AW_ARCH AW_ARCH_i686
#endif

#define AW_HAS_EXT__assume 1
#define AW_HAS_warning 0
// TODO: this is not documented anywhere but works in practice
#define AW_HAS_type_punning_union 1

#define AW_ATTRIBUTE( ... ) __declspec(__VA_ARGS__)

#define aw_force_inline __forceinline

#define AW_FUNCTION_SIGNATURE __FUNCSIG__
#endif //aw_compiler_setup_2
