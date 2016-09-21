/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/log/ostream_logger.h>
namespace aw {
inline namespace v1 {
namespace {
char const* describe(log::level level)
{
	switch (level) {
	case log::info:     return "info:    ";
	case log::warning:  return "warning: ";
	case log::error:    return "error:   ";
	case log::critical: return "critical:";
	};
}
} // namespace

std::string format_message(log::level lvl, std::string const& src, std::string const& msg)
{
	std::string fmt;
	fmt.append(1,'[');
	fmt.append(src);
	fmt.append(1,']');
	fmt.append(1,' ');
	fmt.append(describe(lvl));
	fmt.append(msg);
	return fmt;
}

void ostream_logger::message(log::level level, std::string const& src, std::string const& msg)
{
	stream << format_message(level, src, msg) << '\n';
}
} // namespace v1
} // namespace aw
