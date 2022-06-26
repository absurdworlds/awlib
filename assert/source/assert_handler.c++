#include "aw/assert/assert_handler.h"

#include <utility>
#include <csignal>
#include <aw/config.h>

namespace aw {
#if defined(AW_SUPPORT_PLATFORM_WIN32)
namespace win32 {
assert_action assert_fail(string_view assertion, source_location location);
} // namespace win32
#endif

#if (AW_PLATFORM == AW_PLATFORM_WIN32)
static assert_handler_func* assert_handler = win32::assert_fail; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
#else
static assert_handler_func* assert_handler = nullptr; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
#endif

void assert_abort()
{
	// prevent the "abort has been called, debug?" message
	// becuase aw::assert() already provides that functionality
	raise(SIGABRT);
	exit(EXIT_FAILURE);
}

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
