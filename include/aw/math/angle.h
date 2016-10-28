/*
 * Copyright (C) 2014-2016 absurdworlds
 * Copyright (C) 2014-2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_angle_h
#define aw_math_angle_h
#include <ratio>
#include <aw/math/math.h>
#include <aw/math/constants.h>
#include <aw/math/equals.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/types/traits/common_type.h>

namespace aw::math {

template<typename T>
constexpr double extract_unit = T::value;

template<intmax_t Num, intmax_t Den>
constexpr double extract_unit<std::ratio<Num,Den>> = double(Num)/Den;

struct radian_unit { static constexpr double value = 2*pi; };

template<typename Rep, typename Period>
class angle;

namespace _impl {
template<typename T>
constexpr bool is_angle = false;
template<typename Rep, typename Period>
constexpr bool is_angle<angle<Rep,Period>> = true;
}

template<typename Rep, typename Period = radian_unit>
class angle {
	Rep value;
public:
	// TODO: support integers
	// Currently, I don't need integer angles (or any other type),
	// but they should be supported for completeness sake.
	// However, it is more complicated with angles than with other units,
	// because of irratinal pi.
	static_assert( is_floating_point<Rep> );

	using rep = Rep;
	using period_type = Period;
	static constexpr auto period = extract_unit<Period>;

	// TODO: proper cast
	template<typename Rep2, typename = enable_if< is_convertible<Rep2, rep> >>
	constexpr explicit angle( Rep2 value ) : value(value) {}

	template<typename Ang2, typename = enable_if< _impl::is_angle<Ang2> >>
	constexpr angle( Ang2 const& other )
		: value( other.count() / other.period * period )
	{ }

	constexpr Rep count() const { return value; }

	/*!
	 * Normalize angle to be in range (-period/2; period/2].
	 * For example, radians will be normalized to (-π; π], and degrees
	 * to (-180; 180] range. E.g. 189° will become 9°.
	 */
	angle& normalize()
	{
		// TODO: guaranteed to be in (-period/2; period/2] range?
		value = std::remainder(value, period);
		return *this;
	}

	angle normalized() const { return angle{*this}.normalize(); }

	constexpr angle operator-() const { return angle{ -value }; };
	constexpr angle operator+() const { return *this; };

	constexpr angle& operator++()    { ++value; return *this; };
	constexpr angle  operator++(int) { return angle{value++}; };

	constexpr angle& operator--()    { --value; return *this; };
	constexpr angle  operator--(int) { return angle{value--}; };

	constexpr angle& operator+=(angle const& r) { value += r.value; return *this; };
	constexpr angle& operator-=(angle const& r) { value -= r.value; return *this; };
	constexpr angle& operator/=(rep const& r) { value /= r; return *this; };
	constexpr angle& operator*=(rep const& r) { value *= r; return *this; };
};

template <typename T>
using radians = angle<T, radian_unit>;
template <typename T>
using turns   = angle<T, std::ratio<1>>;
template <typename T>
using degrees = angle<T, std::ratio<360>>;


template <typename R1, typename P1, typename R2, typename P2>
auto operator+(angle<R1,P1> const& a, angle<R2,P2> const& b) ->
	angle< common_type<R1, R2>, P1 >
{
	using result = angle< common_type<R1, R2>, P1 >;
	result r{ a };
	return r += result{ b };
}

template <typename R1, typename P1, typename R2, typename P2>
auto operator-(angle<R1,P1> const& a, angle<R2,P2> const& b) ->
	angle< common_type<R1, R2>, P1 >
{
	using result = angle< common_type<R1, R2>, P1 >;
	result r{ a };
	return r -= result{ b };
}

template <typename R1, typename P1, typename R2, typename P2>
auto operator/(angle<R1,P1> const& a, angle<R2,P2> const& b) -> common_type<R1, R2>
{
	using result = angle< common_type<R1, R2>, P2 >;
	return result{ result{ a }.count() / result{ b }.count() };
}

template <typename R1, typename R2, typename P2>
auto operator*(R1 const& a, angle<R2,P2> const& b) ->
	angle< common_type<R1, R2>, P2 >
{
	using result = angle< common_type<R1, R2>, P2 >;
	result r{ b };
	return r *= a;
}

template <typename R1, typename R2, typename P2>
auto operator*(angle<R2,P2> const& b, R1 const& a) { return a*b; }

template <typename R1, typename R2, typename P2>
auto operator/(R1 const& a, angle<R2,P2> const& b) ->
	angle< common_type<R1, R2>, P2 >
{
	using result = angle< common_type<R1, R2>, P2 >;
	result r{ b };
	return r /= a;
}

template <typename R1, typename P1, typename R2, typename P2>
bool operator==(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	using result = angle< common_type<R1, R2>, P2 >;
	return result{ a }.count() == result{ b }.count();
}


template <typename R1, typename P1, typename R2, typename P2>
bool operator<(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	using result = angle< common_type<R1, R2>, P2 >;
	return result{ a }.count() < result{ b }.count();
}

template <typename R1, typename P1, typename R2, typename P2>
bool operator>(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	return b < a;
}

template <typename R1, typename P1, typename R2, typename P2>
bool operator<=(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	return !(a > b);
}

template <typename R1, typename P1, typename R2, typename P2>
bool operator>=(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	return !(a < b);
}

template <typename R1, typename P1, typename R2, typename P2>
bool operator!=(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	return !(a == b);
}

template <typename R1, typename P1, typename R2, typename P2>
bool equals(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	using result = angle< common_type<R1, R2>, P2 >;
	return equals(result{ a }.count(), result{ b }.count());
}

} //namespace aw::math
#endif //aw_math_angle_h
