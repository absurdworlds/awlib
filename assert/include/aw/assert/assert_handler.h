#ifndef aw_assert_handler_h
#define aw_assert_handler_h

#include <string>

#include <aw/types/string_view.h>
#include <aw/string/format.h>
#include <aw/utility/exceptions.h>

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
#if AW_FORMAT != AW_NO_FORMAT
	if constexpr(sizeof...(Arg_types) > 0)
	{
		aw_try {
			// No std::forward here: make_format_args need lvalues
			std::string message = aw::vformat( msg, aw::make_format_args(args...) );
			return assert_fail(message, loc);
		} aw_catch(...) {
			// a message that cannot be formatted is reported as written,
			// rather than being worse than the assertion it describes
			return assert_fail(msg, loc);
		}
	}
	else
#endif
	{
		return assert_fail(msg, loc);
	}
}


AW_ASSERT_EXP
assert_handler_func* install_assert_handler(assert_handler_func* handler);

} // namespace aw

#endif//aw_assert_handler_h
