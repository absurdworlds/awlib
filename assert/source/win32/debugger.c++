#include "aw/assert/debugger.h"

#include <aw/platform/windows.h>


namespace aw::win32 {
bool is_debugger_present()
{
	return IsDebuggerPresent();
}
} // namespace aw::win32

