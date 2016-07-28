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

bool LogFilter::Filter::apply(std::string msg)
{
	if (!std::regex_search(msg, include))
		return false;;
	if (std::regex_search(msg, exclude))
		return false;
	return true;
}


void LogFilter::log(Log::Level level, std::string const& src, std::string const& msg)
{
	if (level < minLevel)
		return;
	if (!src_filter.apply(src) || !msg_filter.apply(msg))
		return;
	MultiLog::log(level, src, msg);
}
} // namespace log
} // namespace aw
