/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/log/ostream_logger.h>
#include <aw/utility/string/join.h>
#include "helpers.h"
namespace aw {
inline namespace v1 {
namespace {
std::string format_message(log::level level, string_view src, string_view msg)
{
	constexpr std::string_view sep = ": ";
	const     std::string_view lvl = describe(level);
	return string::concatenate(src, sep, lvl, msg);
}
} // namespace

void ostream_logger::message(log::level level, string_view src, string_view msg)
{
	stream << format_message(level, src, msg) << '\n';
}
} // namespace v1
} // namespace aw
