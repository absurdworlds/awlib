/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/types/string_view.h>
#include <aw/log/ostream_logger.h>
#include <aw/utility/string/join.h>
namespace aw {
namespace {
constexpr string_view describe(log::level level)
{
	switch (level) {
	case log::info:     return "info:     ";
	case log::warning:  return "warning:  ";
	case log::error:    return "error:    ";
	case log::critical: return "critical: ";
	default:            return {};
	};
}
} // namespace

inline namespace v1 {
std::string format_message(log::level level, string_view src, string_view msg)
{
	constexpr std::string_view sep = ": ";
	const     std::string_view lvl = describe(level);
	return string::concatenate(src, sep, lvl, msg);
}

void ostream_logger::message(log::level level, string_view src, string_view msg)
{
	stream << format_message(level, src, msg) << '\n';
}
} // namespace v1
} // namespace aw
