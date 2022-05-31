#ifndef aw_utility_assert_h
#define aw_utility_assert_h

#include <aw/assert/assert_handler.h>
#include <aw/assert/debugger.h>

#include <aw/meta/pp/macro.h>
#include <aw/meta/pp/tuple.h>
#include <aw/meta/source_location.h>

#ifndef aw_default_assert_level
#define aw_default_assert_level release
#endif

#ifndef aw_maximum_assert_level
#define aw_maximum_assert_level release
#endif

namespace aw {
enum class assert_level {
	off,
	release,
	debug,
	audit,
	current = aw_default_assert_level,
	maximum = aw_maximum_assert_level
};

template <assert_level level = assert_level::debug, typename Expression, typename... Arg_types>
bool assert_check(Expression&& expr, string_view msg, source_location loc = source_location::current(), Arg_types&&... args)
{
	if constexpr(level > assert_level::maximum)
		return true;

	const bool cond = expr();
	if (!cond) {
		const auto action = assert_fail_fmt(msg, loc, std::forward<Arg_types>(args)...);
		switch (action)
		{
			case assert_action::abort:
				std::abort();
			case assert_action::stop:
				aw_debug_break;
				[[fallthrough]];
			case assert_action::ignore:
				break;
		}
	}

	return cond;
}
} // namespace aw


// necessary because of default
#define aw_assert_map_audit   audit
#define aw_assert_map_develop develop
#define aw_assert_map_default normal
#define aw_assert_map_normal  normal


// TODO: __builtin_assume
#define aw_assert_x(cond, level, message, ...) \
::aw::assert_check<::aw::assert_level::level> ( [] { return cond; }, message __VA_OPT__(, source_location::current(), ) __VA_ARGS__ )

#define aw_assert_get_level(default, ...) FIRST(__VA_ARGS__ __VA_OPT__(,) default)
#define aw_assert_get_message(default, ...) SECOND(__VA_ARGS__ __VA_OPT__(,) default, default)

#define aw_assert(cond, ...) aw_assert_x( cond, current, __VA_ARGS__ );
#define aw_assert_release(cond, ...) aw_assert_x( cond, release, __VA_ARGS__ );
#define aw_assert_debug(cond, ...) aw_assert_x( cond, debub, __VA_ARGS__ );
#define aw_assert_audit(cond, ...) aw_assert_x( cond, audit, __VA_ARGS__ );

#endif//aw_utility_assert_h
