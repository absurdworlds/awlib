/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_math_as_string_
#define _aw_math_as_string_
#include <aw/math/Vector2d.h>
#include <aw/math/Vector3d.h>
#include <aw/math/Vector4d.h>
#include <aw/string/as_string.h>
#include <aw/string/compose.h>

namespace aw {
template<typename T>
std::string as_string(Vector2d<T> value)
{
	return string::compose("{%0, %1}", value[0], value[1]);
}

template<typename T>
std::string as_string(Vector3d<T> value)
{
	return string::compose("{%0, %1, %2}", value[0], value[1], value[2]);
}

template<typename T>
std::string as_string(Vector4d<T> value)
{
	return string::compose("{%0, %1, %2, %4}",
	        value[0], value[1], value[2], value[3]);
}
} // namespace aw
#endif//_aw_math_as_string_
