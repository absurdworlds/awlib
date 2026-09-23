#include <aw/debug/debugger.h>

#include <aw/platform/windows.h>


namespace aw::debug::win32 {
bool is_debugger_present()
{
	return IsDebuggerPresent();
}
} // namespace aw::debug::win32

