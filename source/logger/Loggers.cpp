/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/logger/LogFilter.h>
namespace aw {
inline namespace log {
void MultiLog::log(Log::Level level, std::string const& src, std::string const& msg)
{
	for (auto recv : recipients)
		recv->log(level, src, msg);
}

void LogFilter::log(Log::Level level, std::string const& src, std::string const& msg)
{
	if (!std::regex_search(src, src_filter))
		return;
	if (!std::regex_search(msg, msg_filter))
		return;
	MultiLog::log(level, src, msg);
}
} // namespace log
} // namespace aw
