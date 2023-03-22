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

enum surrogate : code_point {
	high_begin = 0xD800,
	high_end   = 0xDBFF,
	low_begin  = 0xDC00,
	low_end    = 0xDFFF,
	begin      = high_begin,
	end        = low_end,
};

//! Check if code point is a surrogate
inline bool is_surrogate(code_point cp)
{
	return cp >= surrogate::begin && cp <= surrogate::end;
}

//! Check if code point is valid
inline bool is_valid_code_point(code_point cp)
{
	return code_point(cp) < 0x110000 && !is_surrogate(cp);
}

//! Helper class for converting between code points and code units
template<size_t N, typename Unit>
class bitword {
public:
	enum : size_t {
		bits = N,
		mask = (1u << N) - 1u,
	};

	/*!
	 * Get nth sextet from a code point \a cp.
	 * \param n Number of the word. Starts with zero (lowest bits)
	 */
	static Unit get(code_point cp, Unit n)
	{
		return (cp >> bits*n) & mask;
	}

	static code_point add(code_point cp, Unit unit)
	{
		return (cp << bits) | (unit & mask);
	}
};

} // namespace unicode
} // namespace aw
#endif//_aw_utf_
