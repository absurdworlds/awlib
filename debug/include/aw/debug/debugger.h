#ifndef aw_debug_debugger_h
#define aw_debug_debugger_h

#include <aw/config.h>

#include <aw/debug/export.h>

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
#include <signal.h>
#endif

namespace aw {
namespace debug {
#ifdef AW_SUPPORT_PLATFORM_POSIX
namespace posix {
AW_DEBUG_EXP bool is_debugger_present();
} // namespace posix
#endif // AW_SUPPORT_PLATFORM_POSIX

#ifdef AW_SUPPORT_PLATFORM_WIN32
namespace win32 {
AW_DEBUG_EXP bool is_debugger_present();
} // namespace win32
#endif

// -------------------------------------
#if (AW_PLATFORM == AW_PLATFORM_POSIX)
using posix::is_debugger_present;

// -------------------------------------
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
using win32::is_debugger_present;

// -------------------------------------
#else
inline bool is_debugger_present() { return false; }
#endif
} // namespace debug
} // namespace aw

// -------------------------------------
// macros

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
#define aw_debug_break_impl ::raise(SIGTRAP)
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
#define aw_debug_break_impl __debugbreak()
#else
#define aw_debug_break_impl do { } while (0)
#endif

#define aw_debug_break \
	do { \
		if (::aw::debug::is_debugger_present()) \
			aw_debug_break_impl;\
	} while (0)


#endif//aw_debug_debugger_h
