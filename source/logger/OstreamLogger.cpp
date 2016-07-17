/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/logger/OstreamLogger.h>
namespace aw {
inline namespace log {
void OstreamLogger::log(Log::Level level, std::string const& src, std::string const& msg)
{
	// TODO: dedicated function
	std::string lev = [&] {
		switch (level) {
		case Log::Info:     return "info    ";
		case Log::Warning:  return "warning ";
		case Log::Error:    return "error   ";
		case Log::Critical: return "critical";
		};
	}();
	stream << "[" << src << "] " << lev << ": " << msg << "\n";
}
} // namespace log
} // namespace aw
