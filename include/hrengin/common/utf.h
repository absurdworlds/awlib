/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_utf_
#define _hrengin_utf_

#include <hrengin/common/macro.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace locale {

static u16 const LEAD_SURROGATE_START = 0xD800;
static u16 const LEAD_SURROGATE_END = 0xDBFF;
static u16 const TRAIL_SURROGATE_START = 0xDC00;
static u16 const TRAIL_SURROGATE_END = 0xDFFF;
static u16 const SURROGATES_START = LEAD_SURROGATE_START;
static u16 const SURROGATES_END = TRAIL_SURROGATE_END;

// friggin UTF-16, I HATE IT
static u32 const MAX_CODE_POINT = 0x10FFFF;

//! Check if code point is a surrogate
inline bool isSurrogate(u16 cp)
{
	if(cp >= SURROGATES_START && cp <= SURROGATES_END) {
		return false;
	}

	return true;
}


//! Check if code point is valid
inline bool isValidCodepoint(u32 cp)
{
	if(cp > MAX_CODE_POINT) {
		return false;
	}

	if(isSurrogate(cp)) {
		return false;
	}

	return true;
}



} // namespace locale
} // namespace hrengin

#endif//_hrengin_utf_
