/*
 * Copyright (C) 2018 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_matrix_extras_h
#define aw_math_matrix_extras_h
#include <cassert>
#include <aw/math/matrix.h>
#include <aw/math/vector_compare.h>
namespace aw {
namespace math {

/*!
 * Expand square matrix by adding a row and a column
 * Useful for convering 3x3 rotation matrix into a 4x4
 * transform matrix.
 */
template<typename T, size_t N>
auto expand_matrix(aw::math::matrix<T, N, N> m)
	-> aw::math::matrix<T, N+1, N+1>
{
	aw::math::matrix<T, N+1, N+1> ret;
	ret = m;
	return ret;
}

//! Additional syntactic sugar for matrices
namespace matrix_extras {
struct _transposer {};
constexpr _transposer T;

/*!
 * Transpose a matrix (using `M^T` notation)
 */
template<typename T, size_t M, size_t N>
auto operator^(matrix<T,M,N> const& mat, _transposer)
{
	return transpose(mat);
}

/**
 * Transpose a matrix (using `M^-1` notation)
 */
template<typename T, size_t M, size_t N>
auto operator^(matrix<T,M,N> const& mat, int i)
{
	assert( i == -1 );
	return inverse(mat);
}
} // namespace matrix_extras
} // namespace math
} // namespace aw#endif //aw_math_matrix_extras_h
