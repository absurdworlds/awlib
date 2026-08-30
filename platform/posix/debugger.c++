#include <aw/platform/debugger.h>

#ifdef AW_SUPPORT_PLATFORM_POSIX
namespace aw::platform::posix {
bool is_debugger_present()
{
// TODO https://stackoverflow.com/a/24969863/3469976
	return false;
}
} // namespace aw::platform::posix
#endif
