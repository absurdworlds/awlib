#ifndef aw_utility_assert_h
#define aw_utility_assert_h

#include <aw/assert/assert_handler.h>
#include <aw/assert/debugger.h>

#include <aw/meta/pp/macro.h>
#include <aw/meta/pp/separators.h>
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

struct assert_message {
	assert_message(const assert_message& other) = default;
	assert_message(assert_message&& other) = default;

	template<typename T>
	assert_message(const T& msg, source_location loc = source_location::current())
		: message(msg), location(loc)
	{
	}

	string_view     message;
	source_location location;
};

template <assert_level level = assert_level::debug, typename Expression, typename... Arg_types>
bool (assert)(Expression&& bool_expr, assert_message msg, Arg_types&&... args)
{
	if constexpr(level > assert_level::maximum)
		return true;

	const bool cond = bool_expr();
	if (!cond) {
		const auto action = assert_fail_fmt(msg.message, msg.location, std::forward<Arg_types>(args)...);
		switch (action)
		{
			case assert_action::abort:
				assert_abort();
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

// TODO: __builtin_assume
#define aw_assert_x(cond, level, message, ...) \
	::aw::assert<::aw::assert_level::level> ( [] { return cond; }, message __VA_OPT__(, ) __VA_ARGS__ )

#define aw_assert_make_args(default, ...) AW_FIRST(__VA_ARGS__ __VA_OPT__(,) default) AW_VA_COMMA(AW_TAIL(__VA_ARGS__))

#define aw_assert(cond, ...) aw_assert_x( cond, current, aw_assert_make_args(#cond, __VA_ARGS__) );
#define aw_assert_release(cond, ...) aw_assert_x( cond, release, aw_assert_make_args(#cond, __VA_ARGS__) );
#define aw_assert_debug(cond, ...) aw_assert_x( cond, debug, aw_assert_make_args(#cond, __VA_ARGS__) );
#define aw_assert_audit(cond, ...) aw_assert_x( cond, audit, aw_assert_make_args(#cond, __VA_ARGS__) );

#endif//aw_utility_assert_h
