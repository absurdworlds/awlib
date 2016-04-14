#ifndef aw_math_MatrixNN_h
#define aw_math_MatrixNN_h
#include <algorithm>
namespace aw {

namespace _impl {
template<size_t... Is, typename T, size_t N>
Matrix<T,N,N>& setIdentity(Matrix<T,N,N>& mat, index_sequence<Is...>)
{
	fill(mat, T{});
	int dummy[] = { (mat[Is][Is] = 1, 0)... };
	return mat;
}
} // namespace _impl

template<typename T, size_t N>
Matrix<T,N,N> setIdentity(Matrix<T,N,N>& mat)
{
	return _impl::setIdentity(mat,make_index_sequence<N>{});
}

template<typename T, size_t N>
Matrix<T,N,N> makeIdentity()
{
	Matrix<T,N,N> identity;
	return setIdentity(identity);
}

template <size_t Row, size_t Col, typename T, size_t N>
T matrixMinor(Matrix<T,N,N> const& mat)
{
	auto submatrix = subMatrix<Row,Col>(mat);
	return determinant(submatrix);
}

namespace _impl {
template<size_t I, typename T, size_t N>
T factor(Matrix<T,N,N> const& mat)
{
	T minor = matrixMinor<0,I>(mat);
	T sign = (I % 2)? -1 : 1;

	return sign * minor * get<0,I>(mat);
}

template<size_t...Is, typename T, size_t N>
T determinant(Matrix<T,N,N> const& mat, index_sequence<Is...>)
{
	T val = {};
	int dummy[] = {
		((val += factor<Is>(mat)), 0)...
	};
	return val;
}
} // namespace _impl

template<typename T, size_t N>
T determinant(Matrix<T,N,N> const& mat)
{
	return _impl::determinant(mat, make_index_sequence<N>{});
}

template <typename T>
T determinant(Matrix<T,2,2> mat)
{
	return get<0,0>(mat) * get<1,1>(mat) - get<0,1>(mat) * get<1,0>(mat);
}

template <typename T>
T determinant(Matrix<T,1,1> mat)
{
	return get<0,0>(mat);
}

namespace _impl {
template<size_t I, size_t J, class MatrixT>
void inv(MatrixT& result, MatrixT const& mat)
{
	using T = typename MatrixT::value_type;

	T minor = matrixMinor<J,I>(mat);

	T factor = ((I+J) % 2) ? -1 : 1;

	get<I,J>(result) = factor * minor;
}

template<size_t I, size_t...Js, class MatrixT>
void inv1(MatrixT& result, MatrixT const& mat)
{
	int dummy[] = {
		(inv<I,Js>(result, mat), 0)...
	};
}

template<class MatrixT, size_t...Is>
MatrixT inv2(MatrixT const& mat, index_sequence<Is...>)
{
	MatrixT result = {};
	int dummy[] = {
		(inv1<Is,Is...>(result, mat), 0)...
	};
	return result;
}
} // namespace _impl

template<typename T, size_t N>
opt<Matrix<T,N,N>> inverse(Matrix<T,N,N> const& mat)
{
	T det = determinant(mat);

	if (det == T{})
		return nullopt;

	Matrix<T,N,N> result = _impl::inv2(mat, make_index_sequence<N>{});

	result /= det;

	return result;
}
} // namespace aw
#endif//aw_math_MatrixNN_h
