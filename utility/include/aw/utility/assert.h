#ifndef aw_utility_assert_h
#define aw_utility_assert_h
#include <source_location>

#include <aw/meta/pp/macro.h>
#include <aw/meta/pp/tuple.h>

#include <aw/utility/string/compose.h>

#define aw_assert_level_default 1
#define aw_assert_level_normal aw_assert_level_default
#define aw_assert_level_develop 2
#define aw_assert_level_audit 3

#ifndef aw_current_assert_level
#define aw_current_assert_level aw_assert_level_default
#endif

namespace aw {

enum class assert_level {
	off,
	normal  = aw_assert_level_default,
	develop = aw_assert_level_develop,
	audit   = aw_assert_level_audit,
	current = aw_current_assert_level,
};

void assert_fail(string_view assertion, std::source_location location = std::source_location::current());

template <typename... Arg_types>
void assert_fail_fmt(string_view msg, std::source_location loc = std::source_location::current(), Arg_types&&... args)
{
	std::string fmt = string::compose( msg, std::forward<Arg_types>(args)... );
	assert_fail(fmt, loc);
}

template <assert_level level = assert_level::normal, typename... Arg_types>
bool assert_check(bool cond, string_view msg, std::source_location loc = std::source_location::current(), Arg_types&&... args)
{
	if constexpr(level > assert_level::current)
		return true;

	if (!cond) {
		if constexpr(sizeof...(Arg_types) > 0)
			assert_fail_fmt(msg, loc, std::forward<Arg_types>(args)...);
		else
			assert_fail(msg, loc);
	}

	return cond;
}
} // namespace aw

// disables evaluation by applying short-circuiting
#define aw_assert_eval(level, cond) (aw_current_assert_level < aw_assert_level_##level) || (cond)

// necessary because of default
#define aw_assert_map_audit   audit
#define aw_assert_map_develop develop
#define aw_assert_map_default normal
#define aw_assert_map_normal  normal

#define aw_assert_enum(level) ::aw::assert_level::aw_assert_map_##level

// TODO: __builtin_assume
#define aw_assert_x(cond, level, message, ...) \
	::aw::assert_check<aw_assert_enum(level)> ( aw_assert_eval(level, cond), message __VA_OPT__(, std::source_location::current(), ) __VA_ARGS__ )

#define aw_assert_get_level(default, ...) FIRST(__VA_ARGS__ __VA_OPT__(,) default)
#define aw_assert_get_message(default, ...) SECOND(__VA_ARGS__ __VA_OPT__(,) default, default)

#define aw_assert(cond, ...) \
	aw_assert_x( cond, \
	  aw_assert_get_level(default, __VA_ARGS__), \
	  aw_assert_get_message(#cond, __VA_ARGS__) \
	)

#endif//aw_utility_assert_h
