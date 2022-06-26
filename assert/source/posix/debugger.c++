#include "aw/assert/debugger.h"

#ifdef AW_SUPPORT_PLATFORM_POSIX
namespace aw::posix {
bool is_debugger_present()
{
// TODO https://stackoverflow.com/a/24969863/3469976
	return false;
}
} // namespace aw::linux
#endif
