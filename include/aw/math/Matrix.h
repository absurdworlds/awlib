#include <iostream>
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

template<typename T, size_t N, size_t M>
struct Matrix {
	constexpr static size_t matrix_width = N;
	constexpr static size_t matrix_height = M;

	using value_type = T;
	using column_type = Vector<T, M>;
	using base_type = std::array<column_type,N>;
	//using base_type = column_type[N];

	column_type columns[N];

/*	Matrix()
		: columns{}
	{ }

	/*
	Matrix(base_type const& array)
		: columns(array)
	{ }* /

	template<typename...Args>
	Matrix(Vector<Args,M> const&... args)
		: columns{args...}
	{
	}

	Matrix(Matrix<T,N,M> const& other)
		: columns(other.columns)
	{ }

	template<typename U>
	Matrix(Matrix<U,N,M> const& other)
		: columns(convert_array<Vector<T,M>>(other.columns))
	{}*/

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

	Matrix<T,N,M>& operator += (Matrix<T,N,M> const& other)
	{
		for_all([&] (size_t i) {columns[i] += other[i];});
		return *this;
	}

	Matrix<T,N,M>& operator -= (Matrix<T,N,M> const& other)
	{
		for_all([&] (size_t i) {columns[i] -= other[i];});
		return *this;
	}

	Matrix<T,N,M>& operator *= (T const v)
	{
		for_all([&] (size_t i) {columns[i] *= v;});
		return *this;
	}

	Matrix<T,N,M>& operator /= (T const v)
	{
		for_all([&] (size_t i) {columns[i] /= v;});
		return *this;
	}

	bool operator == (Matrix<T,N,M> const& other) const
	{
		bool equal = true;
		for_all([&] (size_t i) {equal = equal && columns[i] == other[i];});
		return equal;
	}

#if 0
	template<size_t... Cols, size_t Row>
	Matrix<T,N-1,M-1> subMatrix(index_sequence<Cols...>c, index_sequence<Rows...>r)
	{
		/* Matrix<T,N-1,M-1> sub;
		size_t cols[] = {Cols...};
		size_t rows[] = {Rows...};
		eval([&] (size_t i) {
			eval([&] (size_t j) {
				sub[i][j] = columns[cols[i]][rows[j]];
			}, make_index_sequence<M-1>{});
		}, make_index_sequence<N-1>{});

		return sub;*/
		// return { get<Rows>(get<Cols>(*this)) ...};
		return { columns[cols].sub(Row) };
	};
#endif


	template<typename Func>
	void for_each_column(Func func/*void(func)(T)*/)
	{
		for_all([&] (size_t i) { func(columns[i]); });
	}

	template<typename Func>
	void for_each(Func func/*void(func)(T)*/)
	{
		for_all([&] (size_t i) { columns[i].for_each(func); });
	}

	template <typename Func>
	static void for_all(Func func)
	{
		eval(func, make_index_sequence<N>{});
	}

	template <typename Func, size_t... I>
	static void eval(Func func, std::index_sequence<I...>)
	{
		int dummy[] = { (func(I), 0) ... };
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
		//std::cout << "xyzw"[I] << " += ";
		//std::cout << "xyzw"[J] << "×" << "abcpqruvw"[J + I*3];
		//std::cout << "\n";
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

template<typename Func, typename T, size_t N, size_t M, size_t...Is>
void for_each_row(Func func, Matrix<T,N,M> const& mat,index_sequence<Is...>)
{
	eat( (func(row<Is>(mat)), 0)...);
}

template<typename Func, typename T, size_t N, size_t M>
void for_each_row(Matrix<T,N,M> const& mat, Func func)
{
	for_each_row(func, mat, make_index_sequence<M>{});
}

template<typename T, size_t N, size_t M>
void fill(Matrix<T,N,M>& mat, T const value)
{
	Vector<T,M> column = {};
	fill(column, value);
	std::fill(std::begin(mat.columns), std::end(mat.columns), column);
}
} // namespace aw

#include "SquareMatrix.h"
