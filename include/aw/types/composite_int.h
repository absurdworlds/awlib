/*
 * Copyright (C) 2016 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_composite_int_h
#define aw_types_composite_int_h
#include <aw/meta/conditional.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/types/promote.h>
#include <aw/math/numeric.h>
#include <aw/math/bitmath.h>
namespace aw {
/*!
 * Synthesizes bigger integer type from two smaller ints.
 */
template<typename T>
class composite_int {
	using U = make_unsigned<T>;
	using S = make_signed<T>;

public:
	using unsigned_type = U;
	using signed_type = S;
	using opposite_type = conditional<is_signed<T>, U, S>;
	static constexpr auto digits = num_digits<T> + num_digits<U>;

	constexpr composite_int() = default;
	constexpr composite_int(T hi, U lo)
		: hi{hi}, lo{lo}
	{ }

	constexpr composite_int(composite_int const& other) = default;
	constexpr composite_int& operator=(composite_int const& other) = default;

	/*!
	 * Construct from basic type.
	 * \note
	 *    enable_if<> is needed to avoid ambiguity caused by
	 *    implicit conversion to bool.
	 */
	template<typename I, typename = enable_if<is_same<I,T>>>
	constexpr explicit composite_int(I value)
		: lo{U(value)}
	{
		if (value < 0)
			hi = -1;
	}

	constexpr operator composite_int<opposite_type>() const
	{
		return {opposite_type(hi), lo};
	}

	constexpr auto& operator++()
	{
		// If anyone reading this gets annoyed that
		// I compute (lo + 1) twice: I don't care about that,
		// that should be optimized away by compiler.
		hi += (lo + 1) < lo;
		++lo;
		return *this;
	}

	constexpr auto& operator--()
	{
		hi -= (lo - 1) > lo;
		--lo;
		return *this;
	}

	constexpr auto& operator+=(composite_int const& other)
	{
		U carry = (lo + other.lo) < lo;
		lo += other.lo;
		hi += other.hi + carry;
		return *this;
	}

	constexpr auto& operator+=(U val)
	{
		U carry = (lo + val) < lo;
		lo += val;
		hi += carry;
		return *this;
	}

	constexpr auto& operator-=(composite_int const& other)
	{
		U carry = (lo - other.lo) > lo;
		lo -= other.lo;
		hi -= other.hi + carry;
		return *this;
	}


	constexpr auto& operator^=(composite_int const& other)
	{
		lo ^= other.lo;
		hi ^= other.hi;
		return *this;
	}

	constexpr auto& operator|=(composite_int const& other)
	{
		lo |= other.lo;
		hi |= other.hi;
		return *this;
	}

	constexpr auto& operator|=(U val)
	{
		lo |= val;
		return *this;
	}

	constexpr auto& operator&=(composite_int const& other)
	{
		lo &= other.lo;
		hi &= other.hi;
		return *this;
	}

	constexpr auto& operator<<=(size_t n)
	{
		if (n == 0)
			return *this;
		if (n == num_digits<T>) {
			hi = lo;
			lo = 0;
		} else if (n > num_digits<T>) {
			hi = lo << (n - num_digits<T>);
			lo = 0;
		} else if (n < num_digits<T>) {
			hi <<= n;
			hi |= lo >> (num_digits<T> - n);
			lo <<= n;
		}
		return *this;
	}

	constexpr auto& operator>>=(size_t n)
	{
		if (n == 0)
			return *this;
		if (n == num_digits<T>) {
			lo = hi;
			hi = 0;
		} else if (n > num_digits<T>) {
			lo = hi >> (n - num_digits<T>);
			hi = 0;
		} else if (n < num_digits<T>) {
			lo >>= n;
			lo |= hi << (num_digits<T> - n);
			hi >>= n;
		}
		return *this;
	}

	static auto mul(U a, U b) -> composite_int;
	static auto div(composite_int<T> const& a, composite_int<T> const& b)
	        -> std::pair<composite_int<T>, composite_int<T>>;

	auto operator*(composite_int const& other) const
	{
		auto tmp = mul(lo, other.lo);
		tmp.hi += (other.lo * hi) + (lo * other.hi);
		return tmp;
	}

	auto operator/(composite_int const& other) const
	{
		return div(*this, other).first;
	}

	auto operator%(composite_int const& other) const
	{
		return div(*this, other).second;
	}

	auto& operator*=(composite_int const& other)
	{
		return *this = *this * other;
	}

	auto& operator/=(composite_int const& other)
	{
		return *this = *this / other;
	}

	auto& operator%=(composite_int const& other)
	{
		return *this = *this % other;
	}

	size_t leading_zeros() const
	{
		if (hi == 0)
			return num_digits<T> + math::leading_zeros(lo);
		return math::leading_zeros(hi);
	}

	size_t trailing_zeros() const
	{
		if (lo == 0)
			return num_digits<T> + math::trailing_zeros(hi);
		return math::trailing_zeros(lo);
	}

	constexpr T high() const
	{
		return hi;
	}

	constexpr U low() const
	{
		return lo;
	}

	constexpr explicit operator T() const
	{
		return T(lo);
	}

	constexpr operator bool() const
	{
		return lo || hi;
	}

	constexpr bool operator!() const
	{
		return !(lo && hi);
	}

	constexpr auto operator+() const -> composite_int<T>
	{
		return *this;
	}

	constexpr auto operator~() const -> composite_int<T>
	{
		return {~a.hi, ~a.lo};
	}

	constexpr auto operator-() const -> composite_int<T>
	{
		composite_int<S> result = ~a;
		return composite_int<T>{++result};
	}

	constexpr auto operator++(int) const -> composite_int<T>
	{
		composite_int<T> tmp = *this;
		return ++tmp;
	}

	constexpr auto operator--(int) const -> composite_int<T>
	{
		composite_int<T> tmp = *this;
		return --tmp;
	}

	constexpr T sign() const
	{
		return sign(std::integral_constant<bool,is_signed<T>>{});
	}

private:
	constexpr T sign(std::true_type is_signed) const
	{
		if (hi < 0)
			return -1;
		return bool(*this);
	}

	constexpr T sign(std::false_type is_signed) const
	{
		return (hi > 0);
	}

private:
	U lo {};
	T hi {};
};

template<typename T>
composite_int<T> make_composite_int(T hi, make_unsigned<T> lo)
{
	if (hi < 0)
		return -composite_int<T>{-hi, lo};
	return {hi, lo};
}

template<typename T>
constexpr composite_int<T> operator+(composite_int<T> a, composite_int<T> const& b)
{
	return a += b;
}

template<typename T>
constexpr composite_int<T> operator-(composite_int<T> a, composite_int<T> const& b)
{
	return a -= b;
}

template<typename T>
constexpr composite_int<T> operator>>(composite_int<T> a, size_t n)
{
	return a >>= n;
}

template<typename T>
constexpr composite_int<T> operator<<(composite_int<T> a, size_t n)
{
	return a <<= n;
}

template<typename T>
constexpr composite_int<T> operator^(composite_int<T> a, composite_int<T> const& b)
{
	return a ^= b;
}

template<typename T>
constexpr composite_int<T> operator|(composite_int<T> a, composite_int<T> const& b)
{
	return a |= b;
}

template<typename T>
constexpr composite_int<T> operator&(composite_int<T> a, composite_int<T> const& b)
{
	return a &= b;
}

template<typename T>
constexpr bool operator<(composite_int<T> const& a, composite_int<T> const& b)
{
	if (a.high() == b.high())
		return a.low() < b.low();
	return a.high() < b.high();
}

template<typename T>
constexpr bool operator>(composite_int<T> const& a, composite_int<T> const& b)
{
	if (a.high() == b.high())
		return a.low() > b.low();
	return a.high() > b.high();
}

template<typename T>
constexpr bool operator==(composite_int<T> const& a, composite_int<T> const& b)
{
	return a.high() == b.high() && a.low() == b.low();
}

template<typename T>
constexpr bool operator!=(composite_int<T> const& a, composite_int<T> const& b)
{
	return !(a == b);
}

template<typename T>
constexpr bool operator<=(composite_int<T> const& a, composite_int<T> const& b)
{
	return !(a > b);
}

template<typename T>
constexpr bool operator>=(composite_int<T> const& a, composite_int<T> const& b)
{
	return !(a < b);
}



//template<typename T>
//std::string to_string(composite_int<T> val);
} // namespace aw

#include "bits/composite_int.h"
#endif //aw_types_composite_int_h
