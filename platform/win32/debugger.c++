#include <aw/platform/debugger.h>

#include <aw/platform/windows.h>


namespace aw::platform::win32 {
bool is_debugger_present()
{
	return IsDebuggerPresent();
}
} // namespace aw::platform::win32

