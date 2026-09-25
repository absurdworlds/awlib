// Not a bug: all of compiler_setup headers have the same include guard
#ifndef aw_compiler_setup_2
#define aw_compiler_setup_2
#define AW_COMPILER AW_COMPILER_GCC
#define AW_CVER_X __GNUC__
#define AW_CVER_Y __GNUC_MINOR__

#if __GNUC__ < 10
#error "GCC 10 or newer is required"
#endif

#if defined(__x86_64__) || defined(__amd64__)
	#define AW_ARCH AW_ARCH_x86_64
#elif defined(__i686__) || defined(_X86_)
	#define AW_ARCH AW_ARCH_i686
#endif

// GCC doc:
// The relevant bytes of the representation of the object
// are treated as an object of the type used for the access.
// See Type-punning. This may be a trap representation.
#define AW_HAS_EXTENSION_type_punning_union 1

#ifdef __SIZEOF_INT128__
#define AW_HAS_EXTENSION_int128 1
#endif

#define AW_ATTRIBUTE( ... ) __attribute__((__VA_ARGS__))

#define aw_force_inline AW_ATTRIBUTE(always_inline) inline

#define AW_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#endif //aw_compiler_setup_2
