#include <aw/platform/debugger.h>

#if AW_SUPPORT_PLATFORM_POSIX

#if (AW_PLATFORM_SPECIFIC == AW_PLATFORM_LINUX)
#include <fstream>
#include <string>

#include <aw/types/string_view.h>
#endif

namespace aw::platform::posix {
#if (AW_PLATFORM_SPECIFIC == AW_PLATFORM_LINUX)
bool is_debugger_present()
{
	// Linux reports the tracing process as "TracerPid" in /proc/self/status,
	// with 0 when nothing is tracing "self".
	std::ifstream status("/proc/self/status");

	constexpr string_view field = "TracerPid:";

	// TODO: std::string allocates which might be problematic in some cases
	std::string line;
	while (std::getline(status, line)) {
		if (!line.starts_with(field))
			continue;

		return line.find_first_not_of(" \t0", field.size()) != std::string::npos;
	}

	return false;
}
#else
bool is_debugger_present()
{
	// TODO: macOS needs sysctl() and P_TRACED; BSD has a similar interface
	return false;
}
#endif
} // namespace aw::platform::posix
#endif
