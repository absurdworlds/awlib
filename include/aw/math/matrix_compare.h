/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_matrix_compare_h
#define aw_math_matrix_compare_h
#include <aw/math/matrix.h>
#include <aw/math/vector_compare.h>
namespace aw {
namespace math {
template<typename T, size_t N, size_t M>
bool operator==(matrix<T,N,M> const& a, matrix<T,N,M> const b)
{
	for (size_t i = 0; i < N; ++i)
		if (a[i] != b[i])
			return false;
	return true;
}
} // namespace math
} // namespace aw
#endif //aw_math_matrix_compare_h
