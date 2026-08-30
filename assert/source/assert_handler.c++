#include "aw/assert/assert_handler.h"

#include <atomic>
#include <utility>
#include <csignal>
#include <cstdlib>
#include <aw/config.h>

namespace aw {
#if defined(AW_SUPPORT_PLATFORM_WIN32)
namespace win32 {
assert_action assert_fail(string_view assertion, source_location location);
} // namespace win32
#endif

#if (AW_PLATFORM == AW_PLATFORM_WIN32)
static std::atomic<assert_handler_func*> assert_handler = win32::assert_fail; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
#else
static std::atomic<assert_handler_func*> assert_handler = nullptr; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
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
	auto* handler = assert_handler.load(std::memory_order_acquire);
	if (handler != nullptr)
		return handler(message, location);
	return aw::assert_action::abort;
}

assert_handler_func* install_assert_handler(assert_handler_func* handler)
{
	return assert_handler.exchange(handler, std::memory_order_acq_rel);
}

} // namespace aw
