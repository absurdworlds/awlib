/*
 * Copyright (C) 2022       Hudd <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_format_h
#define aw_string_format_h
/*
 * This header wraps std::format and
 * falls back to fmtlib if it is not available.
 */

#define AW_NO_FORMAT 0
#define AW_STD_FORMAT 1
#define AW_FMTLIB_FORMAT 2

#ifndef AW_FORMAT
#if __has_include(<format>)
#define AW_FORMAT AW_STD_FORMAT
#elif __has_include(<fmt/format.h>)
#define AW_FORMAT AW_FMTLIB_FORMAT
#else
#define AW_FORMAT AW_NO_FORMAT
#endif
#endif

#if AW_FORMAT == AW_STD_FORMAT
#include <format>
namespace aw {
using std::format;
using std::vformat;
using std::make_format_args;
} // namespace aw
#elif AW_FORMAT == AW_FMTLIB_FORMAT
#include <fmt/format.h>
namespace aw {
using fmt::format;
using fmt::vformat;
using fmt::make_format_args;
} // namespace aw
#endif

#endif//aw_string_format_h
