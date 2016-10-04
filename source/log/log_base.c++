/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/log/log_filter.h>
#include <aw/log/regex_filter.h>
namespace aw {
inline namespace v1 {
void multi_log::message(log::level level, string_view src, string_view msg)
{
	for (auto recv : loggers)
		recv->message(level, src, msg);
}

bool regex_filter::operator()(string_view msg)
{
	if (!std::regex_search(std::string{msg}, include))
		return false;
	if (std::regex_search(std::string{msg}, exclude))
		return false;
	return true;
}


void log_filter::message(log::level level, string_view src, string_view msg)
{
	if (level < min_level)
		return;
	if (!src_filter(src) || !msg_filter(msg))
		return;
	multi_log::message(level, src, msg);
}
} // namespace v1
} // namespace aw
