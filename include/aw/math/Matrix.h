/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_Matrix_h
#define aw_math_Matrix_h
#include <aw/math/Vector.h>
namespace aw {
template<typename T, size_t M, size_t N>
struct Matrix;

template<size_t Index, typename T, size_t M, size_t N>
Vector<T,N>& row(Matrix<T,M,N>& mat);
template<size_t Index, typename T, size_t M, size_t N>
Vector<T,N> const& row(Matrix<T,M,N> const& mat);

template<size_t Index, typename T, size_t M, size_t N>
Vector<T,M> col(Matrix<T,M,N> const& mat);

template<size_t I, size_t J, typename T, size_t M, size_t N>
T& get(Matrix<T,M,N>& mat);
template<size_t I, size_t J, typename T, size_t M, size_t N>
T get(Matrix<T,M,N> const& mat);

template<class MatrixT,
         class = typename MatrixT::row_indices,
         class = typename MatrixT::column_indices
>
struct MatrixOps;

template<class T, size_t M, size_t N, size_t...Is, size_t...Js>
struct MatrixOps<Matrix<T,M,N>, index_sequence<Is...>, index_sequence<Js...>>
{
	using MatrixT = Matrix<T,M,N>;
	using column_type = typename MatrixT::column_type;

	static void add(MatrixT& a, MatrixT const& b)
	{
#if __cplusplus >= 201500L
		(void(a[Is] += b[Is]), ...);
#else
		(void) fold_dummy { ((a[Is] += b[Is]), 0)...  };
#endif
	}

	static void sub(MatrixT& a, MatrixT const& b)
	{
#if __cplusplus >= 201500L
		(void(a[Is] -= b[Is]), ...);
#else
		(void) fold_dummy { ((a[Is] -= b[Is]), 0)...  };
#endif
	}

	static void mul(MatrixT& a, T const v)
	{
#if __cplusplus >= 201500L
		(void(a[Is] *= v), ...);
#else
		(void) fold_dummy { ((a[Is] *= v), 0)...  };
#endif
	}

	static void div(MatrixT& a, T const v)
	{
#if __cplusplus >= 201500L
		(void(a[Is] /= v), ...);
#else
		(void) fold_dummy { ((a[Is] /= v), 0)...  };
#endif
	}

	static Vector<T,M> mul(MatrixT const& mat, Vector<T,N> const& vec)
	{
		return { dot(mat.row(Is), vec) ... };
	}

	static Vector<T,N> mul(Vector<T,M> const& vec, MatrixT const& mat)
	{
		return { dot(mat.col(Js), vec) ... };
	}

	template <size_t P>
	static Matrix<T,M,P> mul(MatrixT const& A, Matrix<T,N,P> const& B)
	{
		return { A.row(Is) * B ... };
	}

	static column_type col(MatrixT const& a, size_t j)
	{
		return { row<Is>(a)[j]... };
	}

	static MatrixT transpose(Matrix<T,M,N> const& mat)
	{
		return { col<Js>(mat)... };
	}

	template<typename Func>
	static void for_each_column(Matrix<T,M,N>& mat, Func func)
	{
#if __cplusplus >= 201500L
		(func(mat[Js]), ...);
#else
		(void) fold_dummy { (func(mat[Js]), 0)...  };
#endif
	}

	template<typename Func>
	static void for_each_row(Matrix<T,M,N>& mat, Func func)
	{
#if __cplusplus >= 201500L
		(func(mat[Is]), ...);
#else
		(void) fold_dummy { (func(mat[Is]), 0)...  };
#endif
	}

	template<typename Func>
	static void for_each(Matrix<T,M,N>& mat, Func func)
	{
#if __cplusplus >= 201500L
		(mat[Is].for_each(func), ...);
#else
		(void) fold_dummy { (mat[Is].for_each(func), 0)...  };
#endif
	}
};

template<typename T, size_t M, size_t N>
struct Matrix {
	constexpr static size_t num_columns = N;
	constexpr static size_t num_rows = M;

	static_assert(num_columns > 0, "Matrix must have at least one column.");
	static_assert(num_rows > 0, "Matrix must have at least one row.");

	using row_indices    = make_index_sequence<M>;
	using column_indices = make_index_sequence<N>;

	using value_type = T;
	using column_type = Vector<T, M>;
	using row_type    = Vector<T, N>;

	row_type rows[M];

	Matrix<T,M,N>& operator=(Matrix<T,N,M> const& other)
	{
		rows = other.rows;
		return *this;
	}

	row_type const& operator[](size_t idx) const
	{
		return rows[idx];
	}

	row_type& operator[](size_t idx)
	{
		return rows[idx];
	}

	Matrix<T,M,N>& operator+=(Matrix<T,N,M> const& other)
	{
		MatrixOps<Matrix>::add(*this, other);
		return *this;
	}


	Matrix<T,M,N>& operator-=(Matrix<T,N,M> const& other)
	{
		MatrixOps<Matrix>::sub(*this, other);
		return *this;
	}

	Matrix<T,M,N>& operator*=(T const v)
	{
		MatrixOps<Matrix>::mul(*this, v);
		return *this;
	}

	Matrix<T,M,N>& operator /= (T const v)
	{
		MatrixOps<Matrix>::div(*this, v);
		return *this;
	}

	template<typename Func>
	void for_each_column(Func func)
	{
		MatrixOps<Matrix>::for_each_column(*this, func);
	}

	template<typename Func>
	void for_each_row(Func func)
	{
		MatrixOps<Matrix>::for_each_row(*this, func);
	}

	template<typename Func>
	void for_each(Func func)
	{
		MatrixOps<Matrix>::for_each(*this, func);
	}

	T& get(size_t i, size_t j)
	{
		assert(i < M);
		assert(j < N);

		return rows[i][j];
	}

	T get(size_t i, size_t j) const
	{
		assert(i < M);
		assert(j < N);

		return rows[i][j];
	}

	row_type& row(size_t i)
	{
		assert(i < M);
		return rows[i];
	}

	row_type const& row(size_t i) const
	{
		assert(i < M);
		return rows[i];
	}

	column_type col(size_t j) const
	{
		return MatrixOps<Matrix>::col(*this, j);
	}
};

template<size_t I, size_t J, typename T, size_t M, size_t N>
T get(Matrix<T,M,N> const& mat)
{
	return mat.rows[I][J];
}

template<size_t I, size_t J, typename T, size_t M, size_t N>
T& get(Matrix<T,M,N>& mat)
{
	return mat.rows[I][J];
}

template<size_t Index, typename T, size_t M, size_t N>
Vector<T,N>& row(Matrix<T,M,N>& mat)
{
	return mat.rows[Index];
}

template<size_t Index, typename T, size_t M, size_t N>
Vector<T,N> const& row(Matrix<T,M,N> const& mat)
{
	return mat.rows[Index];
}

template<size_t Index, typename T, size_t M, size_t N>
Vector<T,M> col(Matrix<T,M,N> const& mat)
{
	using MatrixT = Matrix<T,M,N>;
	return MatrixOps<MatrixT>::row(mat, Index);
}

namespace _impl {
template<size_t Col, size_t... Rows, typename T, size_t M, size_t N>
Matrix<T,N-1,M-1> make_sub(Matrix<T,M,N> const& mat, index_sequence<Rows...>)
{
	return { sub<Col>(row<Rows>(mat))... };
}
} // namespace _impl

template<size_t Row, size_t Col, typename T, size_t M, size_t N>
Matrix<T,N-1,M-1> subMatrix(Matrix<T,M,N> const& mat)
{
	auto range = index_cat<
	        make_index_range<0,Row>,
	        make_index_range<Row+1,N>
	>{};

	return _impl::make_sub<Col>(mat,range);
}

//! Transpose a matrix
template<typename T, size_t M, size_t N>
Matrix<T,N,M> transpose(Matrix<T,M,N> const& mat)
{
	using MatrixT = Matrix<T,M,N>;
	return MatrixOps<MatrixT>::transpose(mat);
}

template<typename T, size_t M, size_t N>
Vector<T,M> operator * (Matrix<T,M,N> const& A, Vector<T,N> const& B)
{
	using MatrixT = Matrix<T,M,N>;
	return MatrixOps<MatrixT>::mul(A, B);
}

template<typename T, size_t M, size_t N>
Vector<T,N> operator * (Vector<T,M> const& vec, Matrix<T,M,N> const& mat)
{
	using MatrixT = Matrix<T,M,N>;
	return MatrixOps<MatrixT>::mul(vec, mat);
}

template<typename T, size_t M, size_t N, size_t P>
Matrix<T,M,P> operator * (Matrix<T,M,N> const& A, Matrix<T,N,P> const& B)
{
	using MatrixT = Matrix<T,M,N>;
	return MatrixOps<MatrixT>::mul(A, B);
}

template<typename T, size_t M, size_t N>
Matrix<T,M,N> operator * (Matrix<T,N,M> mat, T const v)
{
	mat *= v;
	return mat;
}

template<typename T, size_t M, size_t N>
Matrix<T,M,N> operator * (T const v, Matrix<T,N,M> mat)
{
	mat *= v;
	return mat;
}

template<typename T, size_t M, size_t N>
Matrix<T,M,N> operator / (Matrix<T,N,M> mat, T const v)
{
	mat /= v;
	return mat;
}

template<typename T, size_t M, size_t N>
void fill(Matrix<T,M,N>& mat, T const value)
{
	Vector<T,N> row = {};
	fill(row, value);
	std::fill(std::begin(mat.rows), std::end(mat.rows), row);
}
} // namespace aw

#include "bits/SquareMatrix.h"
#endif//aw_math_Matrix_h
