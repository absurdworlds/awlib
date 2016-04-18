/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_Vector_h
#define aw_math_Vector_h
#include <array>
#include <tuple>
#include <utility>

#include <aw/math/math.h>
#include <aw/math/angle.h>
#include <aw/types/support/array.h>
#include <aw/types/traits/enable_if.h>
#include <aw/utility/index_sequence.h>

namespace aw {
template <typename T, size_t N>
struct Vector;

template<size_t I, typename T, size_t N>
T& get(Vector<T,N>& vec);

template<size_t I, typename T, size_t N>
T const& get(Vector<T,N> const& vec);


namespace Vec {
enum Coordinate {
	X, Y, Z, W
};
} // namespace Vec

template <class VectorT, class = typename VectorT::indices>
struct VectorOps;

template <class T, size_t N, size_t...Is>
struct VectorOps<Vector<T,N>,index_sequence<Is...>>
{
	using VectorT = Vector<T,N>;

	static void set(VectorT& vec, VectorT const& other)
	{
		int dummy[] = { ((vec[Is] = other[Is]), 0)...  };
	}

	static void add(VectorT& vec, VectorT const& other)
	{
		int dummy[] = { ((vec[Is] += other[Is]), 0)...  };
	}

	static void sub(VectorT& vec, VectorT const& other)
	{
		int dummy[] = { ((vec[Is] -= other[Is]), 0)...  };
	}

	static void mul(VectorT& vec, T const& val)
	{
		int dummy[] = { ((vec[Is] *= val), 0)...  };
	}

	static void div(VectorT& vec, T const& val)
	{
		int dummy[] = { ((vec[Is] /= val), 0)...  };
	}

	static T dot(VectorT const& vec1, VectorT const& vec2)
	{
		T product = {};
		int dummy[] = {
			((product += vec1[Is] * vec2[Is]), 0)...
		};
		return product;
	}

	template<typename Func>
	static void for_each(VectorT& vec, Func func)
	{
		int dummy[] = {
			(func(vec[Is]), 0)...
		};
	}
};

template <typename T, size_t N>
struct Vector {
	static_assert(N > 0, "Vector must have non-zero number of dimensions");

	constexpr static size_t vector_size = N;

	using value_type = T;
	using array_type = std::array<T,N>;
	using tuple_type = decltype(aw::to_tuple(std::declval<array_type>()));

	using indices = std::make_index_sequence<N>;

	value_type elems[N];

	Vector<T,N>& operator=(Vector<T,N> const& other)
	{
		VectorOps<Vector<T,N>>::set(*this, other);
		return *this;
	}

	Vector<T,N>& operator +=(Vector<T,N> const& other)
	{
		VectorOps<Vector<T,N>>::add(*this, other);
		return *this;
	}

	Vector<T,N>& operator -=(Vector<T,N> const& other)
	{
		VectorOps<Vector<T,N>>::sub(*this, other);
		return *this;
	}

	Vector<T,N>& operator *=(T const v)
	{
		VectorOps<Vector<T,N>>::mul(*this, v);
		return *this;
	}

	Vector<T,N>& operator /=(T const v)
	{
		VectorOps<Vector<T,N>>::div(*this, v);
		return *this;
	}

	Vector<T,N>& negate()
	{
		return (*this *= -1);
	}

	T dot(Vector<T,N> const& other) const
	{
		return VectorOps<Vector<T,N>>::dot(*this, other);
	}

	T lengthSq() const
	{
		return dot(*this);
	}

	T length() const
	{
		return math::sqrt(lengthSq());
	}

	//! Normalize the vector
	Vector<T,N>& normalize()
	{
		T length = lengthSq();
		if (length == 0)
			return *this;

		length = math::invSqrt(length);

		return (*this *= length);
	}

	T& operator[](size_t idx)
	{
		return elems[idx];
	}

	T const& operator[](size_t idx) const
	{
		return elems[idx];
	}

	array_type to_array() const
	{
		return elems;
	}

	tuple_type to_tuple() const
	{
		return aw::to_tuple(elems);
	}

	template<typename Func>
	void for_each(Func func/*void(func)(T)*/)
	{
		VectorOps<Vector<T,N>>::for_each(*this, func);
	}

	T& x()
	{
		return get<Vec::X>(*this);
	}

	T& y()
	{
		return get<Vec::Y>(*this);
	}

	T& z()
	{
		return get<Vec::Z>(*this);
	}

	T& w()
	{
		return get<Vec::W>(*this);
	}

	T x() const
	{
		return get<Vec::X>(*this);
	}

	T y() const
	{
		return get<Vec::Y>(*this);
	}

	T z() const
	{
		return get<Vec::Z>(*this);
	}

	T w() const
	{
		return get<Vec::W>(*this);
	}
};

template<typename T, size_t N>
T dot(Vector<T,N> const& vec1, Vector<T,N> const& vec2)
{
	return vec1.dot(vec2);
}

template<size_t I, typename T, size_t N>
T& get(Vector<T,N>& vec)
{
	static_assert(I < N, "Index out of bounds.");
	return vec[I];
}

template<size_t I, typename T, size_t N>
T const& get(Vector<T,N> const& vec)
{
	static_assert(I < N, "Index out of bounds.");
	return vec[I];
}

namespace detail {
template<size_t... Is, typename T, size_t N>
Vector<T,N-1> make_sub(Vector<T,N> const& vec, index_sequence<Is...>)
{
	return {get<Is>(vec)...};
}
} // namespace detail

template<size_t Index, typename T, size_t N>
Vector<T,N-1> sub(Vector<T,N> const& vec)
{
	auto range = index_cat<
	        make_index_range<0,Index>,
	        make_index_range<Index+1,N>
	>{};

	return detail::make_sub(vec, range);
}

//! Negate vector (reverse direction)
template<typename T, size_t N>
Vector<T,N> operator - (Vector<T,N> vec)
{
	return vec.negate();
}

//! Identity
template<typename T, size_t N>
Vector<T,N> operator + (Vector<T,N> vec)
{
	return vec;
}

//! Sum of two vectors
template<typename T, size_t N>
Vector<T,N> operator + (Vector<T,N> v1, Vector<T,N> const& v2)
{
	v1 += v2;
	return v1;
}

//! Difference of two vectors
template<typename T, size_t N>
Vector<T,N> operator - (Vector<T,N> v1, Vector<T,N> const& v2)
{
	v1 -= v2;
	return v1;
}

//! Scalar-vector product
template<typename T, size_t N>
Vector<T,N> operator * (Vector<T,N> vec, T const v)
{
	vec *= v;
	return vec;
}

//! Scalar-vector product
template<typename T, size_t N>
Vector<T,N> operator / (Vector<T,N> vec, T const v)
{
	vec /= v;
	return vec;
}

//! Scalar-vector product
template<typename T, size_t N>
Vector<T,N> operator * (T const v, Vector<T,N> vec)
{
	vec *= v;
	return vec;
}

//! Get a normalized version of a vector
template<typename T, size_t N>
Vector<T,N> normalize(Vector<T,N> vec)
{
	return vec.normalize();
}

//! Get distance between two points
template<typename T, size_t N>
T distance(Vector<T,N> vec1, Vector<T,N> const& vec2)
{
	return (vec1 - vec2).length();
}

//! Get squared distance between two points
template<typename T, size_t N>
T distanceSq(Vector<T,N> vec1, Vector<T,N> const& vec2)
{
	return (vec1 - vec2).lengthSq();
}

template<typename T, size_t N>
void fill(Vector<T,N>& vec, T const value)
{
	std::fill(std::begin(vec.elems), std::end(vec.elems), value);
}
} // namespace aw
#endif//aw_math_Vector_h
