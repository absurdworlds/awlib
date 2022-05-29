/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_vector_compare_h
#define aw_math_vector_compare_h
#include <aw/math/equals.h>
#include <aw/math/vector.h>
namespace aw {
namespace math {
template<typename T, size_t N>
auto operator==(vector<T,N> const& a, vector<T,N> const& b) -> enable_if<!is_float<T>,bool>
{
	for (size_t i = 0; i < N; ++i)
		if (a[i] != b[i])
			return false;
	return true;
}

template<typename T, size_t N>
auto operator==(vector<T,N> const& a, vector<T,N> const& b) -> enable_if<is_float<T>,bool>
{
	for (size_t i = 0; i < N; ++i)
		if (!math::equals(a[i], b[i]))
			return false;
	return true;
}

template<typename T, size_t N>
bool operator!=(vector<T,N> const& a, vector<T,N> const& b)
{
	return !(a == b);
}
} // namespace math
} // namespace aw
#endif //aw_math_vector_compare_h
