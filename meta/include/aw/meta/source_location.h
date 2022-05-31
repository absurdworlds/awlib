#ifndef aw_meta_source_location_h
#define aw_meta_source_location_h

#include <aw/config.h>
#include <aw/stdlib.h>

#if (AW_COMPILER == AW_COMPILER_CLANG) && (AW_STDLIB == AW_STDLIB_GLIBCXX)
// clang STILL lacks the __builtin_SOURCE_LOCATION so I have to provide my own implementation...
namespace aw {
struct source_location
{
	const char* file     = "";
	const char* function = "";
	int         line     = 0;
	int         column   = 0;

	// clang supports these builtins since 9.0.0, so no need to check for __has_builtin, we don't support anything earlier
	// GCC supports everything except __builtin_COLUMN since 4.8.0, but this code is used only for clang, so again, no need to check.
	static consteval source_location current(
		const char* file     = __builtin_FILE(),
		const char* function = __builtin_FUNCTION(),
		int         line     = __builtin_LINE(),
		int         column   = __builtin_COLUMN()
	)
	{
		return { file, function, line, column };
	}
};
} // namespace aw
#else
#include <source_location>
namespace aw {
using source_location = std::source_location;
} // namespace aw
#endif


#endif//aw_meta_source_location_h
