/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_matrix_h
#define aw_math_matrix_h
#include <aw/math/vector.h>
namespace aw::math {
template<typename T, size_t M, size_t N>
struct matrix;

/*!
 * \{
 * Access matrix rows and columns as vectors.
 */
template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,N>& row(matrix<T,M,N>& mat);
template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,N> const& row(matrix<T,M,N> const& mat);

template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,M> col(matrix<T,M,N> const& mat);
/* \} */

/* \{
 * Access element at row \a I and column \a J
 */
template<size_t I, size_t J, typename T, size_t M, size_t N>
constexpr T& get(matrix<T,M,N>& mat);
template<size_t I, size_t J, typename T, size_t M, size_t N>
constexpr T const& get(matrix<T,M,N> const& mat);

template<size_t I, size_t J, typename T, size_t M, size_t N>
constexpr T get(matrix<T,M,N>&& mat) { return get<I,J>( mat ); }
template<size_t I, size_t J, typename T, size_t M, size_t N>
constexpr T get(matrix<T,M,N> const&& mat) { return get<I,J>( mat ); }
/*! \} */

/*! \{
 * Linear access to matrix elements
 */
template<size_t I, typename T, size_t M, size_t N>
constexpr T& get(matrix<T,M,N>& mat) { return get<I / N, I % N>( mat ); }
template<size_t I, typename T, size_t M, size_t N>
constexpr T const& get(matrix<T,M,N> const& mat) { return get<I / N, I % N>( mat ); }

template<size_t I, typename T, size_t M, size_t N>
constexpr T get(matrix<T,M,N>&& mat) { return get<I / N, I % N>( mat ); }
template<size_t I, typename T, size_t M, size_t N>
constexpr T get(matrix<T,M,N> const&& mat) { return get<I / N, I % N>( mat ); }
/* \} */
} // namespace aw::math


namespace aw::math {
namespace _impl {
namespace mat {

template<class T, size_t M, size_t N, size_t...Is>
constexpr vector<T,M> mul(matrix<T,M,N> const& mat, vector<T,N> const& vec, index_sequence<Is...>)
{
	return { dot(row<Is>(mat), vec) ... };
}

template<class T, size_t M, size_t N, size_t...Js>
constexpr vector<T,N> mul(vector<T,M> const& vec, matrix<T,M,N> const& mat, index_sequence<Js...>)
{
	return { dot(col<Js>(mat), vec) ... };
}

template<class T, size_t M, size_t N, size_t P, size_t...Is>
constexpr matrix<T,M,P> mul(matrix<T,M,N> const& A, matrix<T,N,P> const& B, index_sequence<Is...>)
{
	return { row<Is>(A) * B ... };
}


template<typename M, size_t...Is>
constexpr typename M::column_type col(M const& a, size_t j, index_sequence<Is...>)
{
	return { row<Is>(a)[j]... };
}

template<class T, size_t M, size_t N, size_t...Js>
static constexpr matrix<T,N,M> transpose(matrix<T,M,N> const& mat, index_sequence<Js...>)
{
	return { col<Js>(mat)... };
}

template<typename M, typename Func, size_t...Js>
static constexpr void for_each_column(M& mat, Func func, index_sequence<Js...>)
{
	(void(func(mat[Js])), ...);
}

template<typename M, typename Func, size_t...Is>
static constexpr void for_each_row(M& mat, Func func, index_sequence<Is...>)
{
	(void(func(mat[Is])), ...);
}

template<typename M, typename Func, size_t...Is>
static constexpr void for_each(M& mat, Func func, index_sequence<Is...>)
{
	(row<Is>(mat).for_each(func), ...);
}

} // namespace mat
} // namespace _impl


template<typename T, size_t M, size_t N>
struct matrix {
	constexpr static size_t num_columns = N;
	constexpr static size_t num_rows = M;

	static_assert(num_columns > 0, "Matrix must have at least one column.");
	static_assert(num_rows > 0, "Matrix must have at least one row.");

	static constexpr auto row_indices    = make_index_sequence<M>{};
	static constexpr auto column_indices = make_index_sequence<N>{};

	using value_type = T;
	using column_type = vector<T, M>;
	using row_type    = vector<T, N>;

	row_type rows[M];

	constexpr matrix& operator=(matrix const& other)
	{
		_impl::vec::assign(*this, other, row_indices);
		return *this;
	}

	template<size_t M1, size_t N1>
	constexpr matrix& operator=(matrix<T,M1,N1> const& other)
	{
		static_assert(M > M1);
		static_assert(N > N1);
		_impl::vec::assign(*this, other, other.row_indices);
		return *this;
	}

	constexpr row_type const& operator[](size_t idx) const
	{
		return rows[idx];
	}

	constexpr row_type& operator[](size_t idx)
	{
		return rows[idx];
	}

	constexpr matrix& operator+=(matrix const& other)
	{
		_impl::vec::add(*this, other, row_indices);
		return *this;
	}


	constexpr matrix& operator-=(matrix const& other)
	{
		_impl::vec::sub(*this, other, row_indices);
		return *this;
	}

	constexpr matrix& operator*=(matrix const& other)
	{
		return (*this = *this * other);
	}

	constexpr matrix& operator*=(T const v)
	{
		_impl::vec::mul(*this, v, row_indices);
		return *this;
	}

	constexpr matrix& operator/=(T const v)
	{
		_impl::vec::div(*this, v, row_indices);
		return *this;
	}

	template<typename Func>
	constexpr void for_each_column(Func func)
	{
		_impl::mat::for_each_column(*this, func, column_indices);
	}

	template<typename Func>
	constexpr void for_each_row(Func func)
	{
		_impl::mat::for_each_row(*this, func, row_indices);
	}

	template<typename Func>
	constexpr void for_each(Func func)
	{
		_impl::mat::for_each(*this, func, row_indices);
	}

	constexpr T& get(size_t i, size_t j)
	{
		return rows[i][j];
	}

	constexpr T get(size_t i, size_t j) const
	{
		assert(i < M);
		assert(j < N);

		return rows[i][j];
	}

	constexpr row_type& row(size_t i)
	{
		assert(i < M);
		return rows[i];
	}

	constexpr row_type const& row(size_t i) const
	{
		assert(i < M);
		return rows[i];
	}

	constexpr column_type col(size_t j) const
	{
		return _impl::mat::col(*this, j, row_indices);
	}

	/*!
	 * \{
	 * Access matrix data through a pointer. Indended for interfacing
	 * with C APIs, such as OpenGL.
	 *
	 * Caveat emptor: accessing data beyond first row is
	 * undefined according to C++ standard, but should be OK
	 * on most platforms.
	 */
	constexpr T* data()
	{
		static_assert( sizeof(vector<T,N>) == sizeof(T)*N );
		return rows[0].data();
	}

	constexpr T const* data() const
	{
		static_assert( sizeof(vector<T,N>) == sizeof(T)*N );
		return rows[0].data();
	}
	/* \} */
};

template<size_t I, size_t J, typename T, size_t M, size_t N>
constexpr T& get(matrix<T,M,N>& mat)
{
	return mat.rows[I][J];
}

template<size_t I, size_t J, typename T, size_t M, size_t N>
constexpr T const& get(matrix<T,M,N> const& mat)
{
	return mat.rows[I][J];
}

template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,N>& row(matrix<T,M,N>& mat)
{
	return mat.rows[Index];
}

template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,N> const& row(matrix<T,M,N> const& mat)
{
	return mat.rows[Index];
}

template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,M> col(matrix<T,M,N> const& mat)
{
	return _impl::mat::col(mat, Index, mat.row_indices);
}


namespace _impl {
namespace mat {
template<typename T, size_t M, size_t N, size_t...Is>
constexpr void set_col(matrix<T,M,N> const& mat, vector<T,N> const& col, size_t j, index_sequence<Is...>)
{
	(void(mat[Is][j] = col[Is]), ...);
}
} // namespace mat
} // namespace _impl

template<typename T, size_t M, size_t N>
constexpr void set_column(matrix<T,M,N> const& mat, vector<T,N> const& col, size_t idx)
{
	_impl::mat::set_col(mat, col, idx, mat.row_indices);
}

namespace _impl {
template<size_t Col, size_t... Rows, typename T, size_t M, size_t N>
constexpr matrix<T,N-1,M-1> make_sub(matrix<T,M,N> const& mat, index_sequence<Rows...>)
{
	return { sub<Col>(row<Rows>(mat))... };
}
} // namespace _impl

template<size_t Row, size_t Col, typename T, size_t M, size_t N>
constexpr matrix<T,N-1,M-1> sub_matrix(matrix<T,M,N> const& mat)
{
	auto range = index_cat<
	        make_index_range<0,Row>,
	        make_index_range<Row+1,N>
	>{};

	return _impl::make_sub<Col>(mat,range);
}

//! Transpose a matrix
template<typename T, size_t M, size_t N>
constexpr matrix<T,N,M> transpose(matrix<T,M,N> const& mat)
{
	return _impl::mat::transpose(mat, mat.column_indices);
}

template<typename T, size_t M, size_t N>
constexpr vector<T,M> operator*(matrix<T,M,N> const& m, vector<T,N> const& v)
{
	return _impl::mat::mul(m, v, m.row_indices);
}

template<typename T, size_t M, size_t N>
constexpr vector<T,N> operator*(vector<T,M> const& v, matrix<T,M,N> const& m)
{
	return _impl::mat::mul(v, m, m.column_indices);
}

template<typename T, size_t M, size_t N, size_t P>
constexpr matrix<T,M,P> operator*(matrix<T,M,N> const& A, matrix<T,N,P> const& B)
{
	return _impl::mat::mul(A, B, A.row_indices);
}

template<typename T, size_t M, size_t N>
constexpr matrix<T,M,N> operator+(matrix<T,M,N> A, matrix<T,M,N> const& B)
{
	return A += B;
}

template<typename T, size_t M, size_t N>
constexpr matrix<T,M,N> operator-(matrix<T,M,N> A, matrix<T,M,N> const& B)
{
	return A -= B;
}

template<typename T, size_t M, size_t N>
constexpr matrix<T,M,N> operator*(matrix<T,N,M> mat, T const v)
{
	mat *= v;
	return mat;
}

template<typename T, size_t M, size_t N>
constexpr matrix<T,M,N> operator*(T const v, matrix<T,N,M> mat)
{
	mat *= v;
	return mat;
}

template<typename T, size_t M, size_t N>
constexpr matrix<T,M,N> operator/(matrix<T,N,M> mat, T const v)
{
	mat /= v;
	return mat;
}

template<typename T, size_t M, size_t N>
constexpr matrix<T,M,N> operator+(matrix<T,N,M> mat)
{
	return mat;
}

template<typename T, size_t M, size_t N>
constexpr matrix<T,M,N> operator-(matrix<T,N,M> mat)
{
	return mat *= T(-1);
}

template<typename T, size_t M, size_t N>
void fill(matrix<T,M,N>& mat, T const value)
{
	vector<T,N> row = {};
	fill(row, value);
	std::fill(std::begin(mat.rows), std::end(mat.rows), row);
}
} // namespace aw::math

#include "bits/square_matrix.h"
#endif//aw_math_matrix_h
