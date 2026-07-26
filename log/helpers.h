/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/types/string_view.h>
#include <aw/log/log.h>
namespace aw {
inline namespace v1 {
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
} // namespace v1
} // namespace aw
