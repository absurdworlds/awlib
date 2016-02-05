/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_utf_
#define _aw_utf_
#include <cassert>
#include <aw/common/types.h>
#include <aw/utility/macro.h>
#include <aw/math/math.h>
namespace aw {
namespace unicode {
//! Check if code point is a surrogate
inline bool isSurrogate(u32 cp)
{
	return (CodePoint(cp) >= 0xD800 &&
		CodePoint(cp) <= 0xDFFF);
}

//! Check if code point is valid
inline bool isValidCodepoint(u32 cp)
{
	return CodePoint(cp) < 0x110000 && !isSurrogate(cp);
}
} // namespace unicode
} // namespace aw
#endif//_aw_utf_
