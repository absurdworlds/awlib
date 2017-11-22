/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_utf_
#define _aw_utf_
#include <cassert>
#include <string>
#include <aw/types/types.h>
#include <aw/meta/pp/macro.h>
#include <aw/math/math.h>
namespace aw {
namespace unicode {
/*!
 * Unsigned integer type capable of holding
 * a single unicode code point.
 */
using code_point = std::uint_least32_t;
constexpr code_point invalid = -1;

//! Check if code point is a surrogate
inline bool isSurrogate(code_point cp)
{
	return code_point(cp) >= 0xD800 && code_point(cp) <= 0xDFFF;
}

//! Check if code point is valid
inline bool isValidCodepoint(code_point cp)
{
	return code_point(cp) < 0x110000 && !isSurrogate(cp);
}
} // namespace unicode
} // namespace aw
#endif//_aw_utf_
