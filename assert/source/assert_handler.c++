#include "aw/assert/assert_handler.h"

#include <utility>

namespace aw {
static assert_handler_func* assert_handler = nullptr; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

assert_action assert_fail(string_view message, source_location location)
{
	if (assert_handler != nullptr)
		return assert_handler(message, location);
	return aw::assert_action::abort;
}

assert_handler_func* install_assert_handler(assert_handler_func* handler)
{
	return std::exchange(assert_handler, handler);
}
} // namespace aw
