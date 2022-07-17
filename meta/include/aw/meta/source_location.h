#ifndef aw_meta_source_location_h
#define aw_meta_source_location_h

#include <aw/config.h>
#include <aw/stdlib.h>
#include <cstdint>

#define AW_NO_SOURCE_LOCATION 0
#define AW_STD_SOURCE_LOCATION 1
#define AW_FALLBACK_SOURCE_LOCATION 2

#if __has_include(<source_location>)
// I guess I could check for __cpp_lib_source_location, but I don't want warnings
#if (AW_COMPILER == AW_COMPILER_CLANG) && \
    ( \
        (AW_STDLIB == AW_STDLIB_GLIBCXX && !AW_HAS_BUILTIN(__builtin_source_location) ) || \
        (AW_STDLIB == AW_STDLIB_MSVCSTL && !__cpp_consteval) \
    )
#define AW_SOURCE_LOCATION AW_FALLBACK_SOURCE_LOCATION
#else
#define AW_SOURCE_LOCATION AW_STD_SOURCE_LOCATION
#endif
#else
#define AW_SOURCE_LOCATION AW_FALLBACK_SOURCE_LOCATION
#endif

#if AW_SOURCE_LOCATION == AW_FALLBACK_SOURCE_LOCATION
// clang STILL lacks the __builtin_SOURCE_LOCATION so I have to provide my own implementation...
namespace aw {
class source_location
{
public:
	// clang supports these builtins since 9.0.0, so no need to check for __has_builtin, we don't support anything earlier
	// GCC supports everything except __builtin_COLUMN since 4.8.0, but this code is used only for clang, so again, no need to check.
	// ... and clang doesn't support consteval properly so I've changed it to constexpr
	static constexpr source_location current(
		const char*         file     = __builtin_FILE(),
		const char*         function = __builtin_FUNCTION(),
		std::uint_least32_t line     = __builtin_LINE(),
		std::uint_least32_t column   = __builtin_COLUMN()
	)
	{
		return { file, function, line, column };
	}

	constexpr source_location() = default;

	constexpr std::uint_least32_t line() const noexcept { return _line;  }
	constexpr uint_least32_t column() const noexcept { return _column; }

	constexpr const char* file_name() const noexcept { return _file; }
	constexpr const char* function_name() const noexcept { return _function; }

private:
	constexpr source_location(
			const char* file,
			const char* function,
			std::uint_least32_t line,
			std::uint_least32_t column
		)
		: _file(file), _function(function), _line(line), _column(column)
	{
	}

	const char*         _file     = "";
	const char*         _function = "";
	std::uint_least32_t _line   = 0;
	std::uint_least32_t _column = 0;
};
} // namespace aw
#elif AW_SOURCE_LOCATION == AW_STD_SOURCE_LOCATION
#include <source_location>
namespace aw {
using source_location = std::source_location;
} // namespace aw
#endif


#endif//aw_meta_source_location_h
