/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_matrixNN_h
#define aw_math_matrixNN_h
#include <algorithm>
#include <aw/types/optional.h>
namespace aw {
namespace math {
namespace _impl {
template<size_t... Is, typename T, size_t N>
matrix<T,N,N>& set_identity(matrix<T,N,N>& mat, index_sequence<Is...>)
{
	fill(mat, T{});
	(void(mat[Is][Is] = 1), ...);
	return mat;
}
} // namespace _impl

template<typename T, size_t N>
matrix<T,N,N> set_identity(matrix<T,N,N>& mat)
{
	return _impl::set_identity(mat,make_index_sequence<N>{});
}

template<typename T, size_t N>
matrix<T,N,N> make_identity()
{
	matrix<T,N,N> identity;
	return set_identity(identity);
}

template <size_t Row, size_t Col, typename T, size_t N>
T matrix_minor(matrix<T,N,N> const& mat)
{
	auto submatrix = sub_matrix<Row,Col>(mat);
	return determinant(submatrix);
}

namespace _impl {
template<size_t I, typename T, size_t N>
T factor(matrix<T,N,N> const& mat)
{
	T minor = matrix_minor<0,I>(mat);
	T sign = (I % 2)? -1 : 1;

	return sign * minor * get<0,I>(mat);
}

template<size_t...Is, typename T, size_t N>
T determinant(matrix<T,N,N> const& mat, index_sequence<Is...>)
{
	return (factor<Is>(mat) + ...);
}
} // namespace _impl

template<typename T, size_t N>
T determinant(matrix<T,N,N> const& mat)
{
	return _impl::determinant(mat, make_index_sequence<N>{});
}

template <typename T>
T determinant(matrix<T,2,2> mat)
{
	return get<0,0>(mat) * get<1,1>(mat) - get<0,1>(mat) * get<1,0>(mat);
}

template <typename T>
T determinant(matrix<T,1,1> mat)
{
	return get<0,0>(mat);
}

namespace _impl {
template<size_t I, size_t J, class MatrixT>
void inv(MatrixT& result, MatrixT const& mat)
{
	using T = typename MatrixT::value_type;

	T const minor = matrix_minor<J,I>(mat);

	T const factor = ((I+J) % 2) ? -1 : 1;

	get<I,J>(result) = factor * minor;
}

template<size_t I, size_t...Js, class MatrixT>
void inv1(MatrixT& result, MatrixT const& mat)
{
	(inv<I,Js>(result, mat), ...);
}

template<class MatrixT, size_t...Is>
MatrixT inv2(MatrixT const& mat, index_sequence<Is...>)
{
	MatrixT result = {};
	(inv1<Is,Is...>(result, mat), ...);
	return result;
}
} // namespace _impl

template<typename T, size_t N>
optional<matrix<T,N,N>> inverse(matrix<T,N,N> const& mat)
{
	T det = determinant(mat);

	if (det == T{})
		return nullopt;

	matrix<T,N,N> result = _impl::inv2(mat, make_index_sequence<N>{});

	result /= det;

	return result;
}
} // namespace math
} // namespace aw
#endif//aw_math_matrixNN_h
