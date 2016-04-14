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
template<typename T, size_t N, size_t M>
struct Matrix;

template<size_t Index, typename T, size_t N, size_t M>
Vector<T,M>& col(Matrix<T,N,M>& mat);
template<size_t Index, typename T, size_t N, size_t M>
Vector<T,M> const& col(Matrix<T,N,M> const& mat);

template<size_t Index, typename T, size_t N, size_t M>
Vector<T,N> row(Matrix<T,N,M> const& mat);

template<size_t I, size_t J, typename T, size_t N, size_t M>
T& get(Matrix<T,N,M>& mat);
template<size_t I, size_t J, typename T, size_t N, size_t M>
T get(Matrix<T,N,M> const& mat);

template<class MatrixT,
         class = typename MatrixT::column_indices,
         class = typename MatrixT::row_indices
>
struct MatrixOps;

template<class T, size_t N, size_t M, size_t...Is, size_t...Js>
struct MatrixOps<Matrix<T,N,M>, index_sequence<Is...>, index_sequence<Js...>>
{
	using MatrixT = Matrix<T,N,M>;

	static void add(MatrixT& a, MatrixT const& b)
	{
		int dummy[] = { 0, ((a[Is] += b[Is]), 0)... };
	}

	static void sub(MatrixT& a, MatrixT const& b)
	{
		int dummy[] = { 0, ((a[Is] -= b[Is]), 0)... };
	}

	static void mul(MatrixT& a, T const v)
	{
		int dummy[] = { 0, ((a[Is] *= v), 0)... };
	}

	static void div(MatrixT& a, T const v)
	{
		int dummy[] = { 0, ((a[Is] /= v), 0)... };
	}

	static Vector<T,N> row(MatrixT const& a, size_t j)
	{
		return { col<Is>(a)[j]... };
	}
};

template<typename T, size_t N, size_t M>
struct Matrix {
	constexpr static size_t matrix_width = N;
	constexpr static size_t matrix_height = M;
	constexpr static size_t num_columns = N;
	constexpr static size_t num_rows = M;
	using indices = make_index_sequence<N>;
	using row_indices = make_index_sequence<N>;
	using column_indices = make_index_sequence<M>;

	using value_type = T;
	using column_type = Vector<T, M>;
	using row_type    = Vector<T, N>;
	//using base_type = std::array<column_type,N>;
	using base_type = column_type[N];

	column_type columns[N];

	Matrix<T,N,M>& operator=(Matrix<T,N,M> const& other)
	{
		columns = other.columns;
		return *this;
	}

	Vector<T,M> const& operator[](size_t idx) const
	{
		return columns[idx];
	}

	Vector<T,M>& operator[](size_t idx)
	{
		return columns[idx];
	}

	Matrix<T,N,M>& operator+=(Matrix<T,N,M> const& other)
	{
		MatrixOps<Matrix,indices>::add(*this, other);
		return *this;
	}


	Matrix<T,N,M>& operator-=(Matrix<T,N,M> const& other)
	{
		MatrixOps<Matrix,indices>::sub(*this, other);
		return *this;
	}

	Matrix<T,N,M>& operator*=(T const v)
	{
		MatrixOps<Matrix,indices>::mul(*this, v);
		return *this;
	}

	Matrix<T,N,M>& operator /= (T const v)
	{
		MatrixOps<Matrix,indices>::div(*this, v);
		return *this;
	}

	template<typename Func>
	void for_each_column(Func func/*void(func)(T)*/)
	{
		eval([&] (size_t i) { func(col(i)); }, indices{});
	}

	template<typename Func>
	void for_each_row(Func func/*void(func)(T)*/)
	{
		eval([&] (size_t i) { func(row(i)); }, indices{});
	}

	template<typename Func>
	void for_each(Func func/*void(func)(T)*/)
	{
		eval([&] (size_t i) { columns[i].for_each(func); }, indices{});
	}

	template <typename Func, size_t... I>
	static void eval(Func func, std::index_sequence<I...>)
	{
		int dummy[] = { (func(I), 0) ... };
	}

	T& get(size_t i, size_t j) const
	{
		assert(i < N);
		assert(j < M);

		return columns[i][j];
	}

	T get(size_t i, size_t j)
	{
		assert(i < N);
		assert(j < M);

		return columns[i][j];
	}

	Vector<T,M>& col(size_t i)
	{
		assert(i < N);
		return columns[i];
	}

	Vector<T,M> const& col(size_t i) const
	{
		assert(i < N);
		return columns[i];
	}

	Vector<T,N> row(size_t j) const
	{
		return MatrixOps<Matrix,indices>::row(*this, j);
	}
};

template<size_t I, size_t J, typename T, size_t N, size_t M>
T get(Matrix<T,N,M> const& mat)
{
	return mat.columns[I][J];
}

template<size_t I, size_t J, typename T, size_t N, size_t M>
T& get(Matrix<T,N,M>& mat)
{
	return mat.columns[I][J];
}

template<size_t Index, typename T, size_t N, size_t M>
Vector<T,M>& col(Matrix<T,N,M>& mat)
{
	return mat.columns[Index];
}

template<size_t Index, typename T, size_t N, size_t M>
Vector<T,M> const& col(Matrix<T,N,M> const& mat)
{
	return mat.columns[Index];
}

namespace detail {
template<size_t Index, size_t... Is, typename T, size_t N, size_t M>
Vector<T,N> row(Matrix<T,N,M> const& mat, index_sequence<Is...>)
{
	return { col<Is>(mat)[Index]... };
}
} // namespace detail

template<size_t Index, typename T, size_t N, size_t M>
Vector<T,N> row(Matrix<T,N,M> const& mat)
{
	return detail::row<Index>(mat, make_index_sequence<N>{});
}

namespace detail {
template<size_t Row, size_t... Cols, typename T, size_t N, size_t M>
Matrix<T,N-1,M-1> make_sub(Matrix<T,N,M> const& mat, index_sequence<Cols...>)
{
	return { sub<Row>(col<Cols>(mat))... };
}
} // namespace detail

template<size_t Col, size_t Row, typename T, size_t N, size_t M>
Matrix<T,N-1,M-1> subMatrix(Matrix<T,N,M> const& mat)
{
	auto range = index_cat<
	        make_index_range<0,Col>,
	        make_index_range<Col+1,N>
	>{};

	return detail::make_sub<Row>(mat,range);
}

namespace detail {
template<size_t... Is, typename T, size_t N, size_t M>
Matrix<T,M,N> transpose(Matrix<T,N,M> const& mat, index_sequence<Is...>)
{
	return { row<Is>(mat)... };
}
} // namespace detail

//! Transpose a matrix
template<typename T, size_t N, size_t M>
Matrix<T,M,N> transpose(Matrix<T,N,M> const& mat)
{
	return detail::transpose(mat, make_index_sequence<M>{});
}

struct eat {
	template<typename...Args>
	eat(Args&&... args) {}
};

namespace detail {
template<typename T, size_t N, size_t M>
struct VecProduct {
	VecProduct(Matrix<T,N,M> const& mat, Vector<T,M> const& vec)
		: mat(mat), vec(vec)
	{
		multiply(make_index_sequence<N>{});
	}

	operator Vector<T,N>()
	{
		return result;
	}

private:
	Matrix<T,N,M> const& mat;
	Vector<T,M>   const& vec;
	Vector<T,N>   result = {};


	template <size_t... Is>
	void multiply(index_sequence<Is...>)
	{
		eat( (multiply1<Is>(make_index_sequence<M>{}), 0)... );
	}

	template <size_t I, size_t... Js>
	void multiply1(index_sequence<Js...>)
	{
		eat( (multiply2<I,Js>(), 0)... );
	}

	template <size_t I, size_t J>
	void multiply2()
	{
		get<I>(result) += get<J,I>(mat) * get<J>(vec);
	}
};
} // namespace detail

template<typename T, size_t N, size_t M>
Vector<T,N> operator * (Matrix<T,N,M> const& A, Vector<T,M> const& B)
{
	return detail::VecProduct<T,N,M>(A,B);
}

namespace detail {
template <size_t... Is, typename T, size_t N, size_t M, size_t P>
Matrix<T,N,P>
multiply(Matrix<T,N,M> const& A, Matrix<T,M,P> const& B, index_sequence<Is...>)
{
	Matrix<T,N,P> result = {};
	eat( (col<Is>(result) += A * col<Is>(B), 0)... );
	return result;
}
} // namespace detail

template<typename T, size_t N, size_t M, size_t P>
Matrix<T,N,P> operator * (Matrix<T,N,M> const& A, Matrix<T,M,P> const& B)
{
	return detail::multiply(A, B, make_index_sequence<N>{});
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M> operator * (Matrix<T,N,M> mat, T const v)
{
	mat *= v;
	return mat;
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M> operator * (T const v, Matrix<T,N,M> mat)
{
	mat *= v;
	return mat;
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M> operator / (Matrix<T,N,M> mat, T const v)
{
	mat /= v;
	return mat;
}

template<typename T, size_t N, size_t M>
void fill(Matrix<T,N,M>& mat, T const value)
{
	Vector<T,M> column = {};
	fill(column, value);
	std::fill(std::begin(mat.columns), std::end(mat.columns), column);
}
} // namespace aw

#include "bits/SquareMatrix.h"
#endif//aw_math_Matrix_h
