#ifndef aw_assert_handler_h
#define aw_assert_handler_h

#include <aw/types/string_view.h>
#include <aw/string/format.h>

#include <aw/assert/export.h>
#include <aw/assert/assert_action.h>
#include <aw/types/string_view.h>
#include <aw/meta/source_location.h>

namespace aw {

using assert_handler_func = assert_action(
	string_view     message,
	source_location location);

[[noreturn]] AW_ASSERT_EXP
void assert_abort();

AW_ASSERT_EXP
assert_action assert_fail(string_view assertion, source_location location = source_location::current());

template <typename... Arg_types>
assert_action assert_fail_fmt(string_view msg, source_location loc = source_location::current(), Arg_types&&... args)
{
	if constexpr(sizeof...(Arg_types) > 0)
	{
		std::string fmt = vformat( msg, make_format_args(std::forward<Arg_types>(args)...) );
		return assert_fail(fmt, loc);
	}
	else
	{
		return assert_fail(msg, loc);
	}
}


AW_ASSERT_EXP
assert_handler_func* install_assert_handler(assert_handler_func* handler);

} // namespace aw

#endif//aw_assert_handler_h
