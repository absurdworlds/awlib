#ifndef aw_math_MatrixNN_h
#define aw_math_MatrixNN_h
#include <algorithm>
namespace aw {
namespace detail {
template<size_t... Is, typename T, size_t N>
Matrix<T,N,N>& setIdentity(Matrix<T,N,N>& mat, index_sequence<Is...>)
{
	fill(mat, T{});
	int dummy[] = { (mat[Is][Is] = 1, 0)... };
	return mat;
}
} // namespace detail

template<typename T, size_t N>
Matrix<T,N,N> setIdentity(Matrix<T,N,N>& mat)
{
	return detail::setIdentity(mat,make_index_sequence<N>{});
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

namespace detail {
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
	T factors[] = { factor<Is>(mat)... };
	return std::accumulate(std::begin(factors), std::end(factors), 0);
}
} // namespace detail

template<typename T, size_t N>
T determinant(Matrix<T,N,N> const& mat)
{
	return detail::determinant(mat, make_index_sequence<N>{});
}

template <typename T>
T determinant(Matrix<T,2,2> mat)
{
	return get<0,0>(mat) * get<1, 1>(mat) - get<0, 1>(mat) * get<1, 0>(mat);
}

template <typename T>
T determinant(Matrix<T,1,1> mat)
{
	return get<0,0>(mat);
}

namespace detail {
template<typename T, size_t N>
struct Inverse {
	Inverse(Matrix<T,N,N> const& mat)
		: mat(mat)
	{
		inverse1(make_index_sequence<N>{});
	}

	operator Matrix<T,N,N>()
	{
		return result;
	}
	
private:
	Matrix<T,N,N> const& mat;
	Matrix<T,N,N> result = {};

	template<size_t...Is>
	void inverse1(index_sequence<Is...>)
	{
		eat( (inverse2<Is>(make_index_sequence<N>{}), 0)...);
	}

	template<size_t I, size_t... Js>
	void inverse2(index_sequence<Js...>)
	{
		eat( (inverse3<I,Js>(), 0)...);
	}

	template<size_t I, size_t J>
	void inverse3()
	{
		T minor = matrixMinor<J,I>(mat);

		T factor = ((I+J) % 2) ? -1 : 1;

		get<I,J>(result) = factor * minor;
	}
};
} // namespace detail

template<typename T, size_t N>
opt<Matrix<T,N,N>> inverse(Matrix<T,N,N> const& mat)
{
	T det = determinant(mat);

	if (det == T{})
		return nullopt;

	Matrix<T,N,N> result = detail::Inverse<T,N>(mat);

	result /= det;

	return result;
}
} // namespace aw
#endif//aw_math_MatrixNN_h
