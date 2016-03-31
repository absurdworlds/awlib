/*
 * Copyright (C) 2014      absurdworlds
 * Copyright (C) 2014-2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_equals_h
#define aw_math_equals_h
#include <aw/math/float.h>
namespace aw {
template <typename T>
auto equals(T a, T b) -> enable_if<is_float<T>, bool>
{
	return compare_ulps(a, b);
}

template <typename T>
auto equals(T a, T b) -> enable_if<!is_float<T>, bool>
{
	return a == b;
}
} //namespace math
} //namespace aw
#endif//aw_math_equals_h
