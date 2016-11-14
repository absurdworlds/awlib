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
#include <aw/math/math.h>
#include <aw/math/constants.h>
#include <aw/math/equals.h>
#include <aw/math/units.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/types/traits/common_type.h>

namespace aw {
namespace math {
// TODO: currently unused
template<typename T>
struct treat_as_floating_point_t : is_floating_point_t<T> {};
template<typename T>
constexpr bool treat_as_floating_point = treat_as_floating_point_t<T>::value;


template<typename Rep, typename Period>
class angle;

template<typename T>
constexpr bool is_angle = false;
template<typename Rep, typename Period>
constexpr bool is_angle<angle<Rep,Period>> = true;

struct radian_unit { static constexpr double value = 2*pi; };

template<typename Rep, typename Period = radian_unit>
class angle {
	Rep value;
public:
	using rep = Rep;
	using period_type = Period;

	// TODO: proper cast
	template<typename Rep2, typename = enable_if< is_convertible<Rep2, rep> >>
	constexpr explicit angle( Rep2 value ) : value(value) {}

	template<typename Ang2, typename = enable_if< is_angle<Ang2> >>
	constexpr angle( Ang2 const& other )
		: value{ units::convert(
			Rep( other.count() ),
			typename Ang2::period_type{},
			Period{}
		)}
	{ }

	constexpr Rep count() const { return value; }


	void normalize_impl( std::false_type )
	{
		// TODO: guaranteed to be in (-period/2; period/2] range?
		constexpr auto period = units::extract< double, Period >;
		value = remainder(value, period);
	}

	constexpr void normalize_impl( std::true_type )
	{
		constexpr intmax_t num = numerator<Period>;
		value -= divround(value, num) * num;
	}

	/*!
	 * Normalize angle to be in range (-period/2; period/2].
	 * For example, radians will be normalized to (-π; π], and degrees
	 * to (-180; 180] range. E.g. 189° will become 9°.
	 */
	constexpr angle& normalize()
	{
		constexpr bool not_float   = !treat_as_floating_point<Rep>;
		constexpr bool valid_ratio = is_ratio<Period> && denominator<Period> == 1;
		normalize_impl( std::integral_constant<bool, valid_ratio>{} );
		return *this;
	}

	constexpr angle normalized() const { return angle{*this}.normalize(); }

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
} // namespace math

using math::angle;
using math::radians;
using math::degrees;
using math::turns;
} // namespace aw


namespace std {

template<typename R1, typename P1, typename R2, typename P2>
struct common_type<aw::angle<R1, P1>, aw::angle<R2, P2> >
{
	using type = aw::angle<common_type_t<R1,R2>, aw::units::common<P1,P2>>;
};

} // namespace std

#include <iostream>
namespace aw::math {

template <typename R1, typename P1, typename R2, typename P2>
constexpr auto operator+(angle<R1,P1> const& a, angle<R2,P2> const& b) ->
	common_type< angle<R1,P1>, angle<R2,P2> >
{
	using result = common_type< angle<R1,P1>, angle<R2,P2> >;
	result r{ a };
	return r += result{ b };
}

template <typename R1, typename P1, typename R2, typename P2>
constexpr auto operator-(angle<R1,P1> const& a, angle<R2,P2> const& b) ->
	common_type< angle<R1,P1>, angle<R2,P2> >
{
	using result = common_type< angle<R1,P1>, angle<R2,P2> >;
	result r{ a };
	return r -= result{ b };
}

template <typename R1, typename P1, typename R2, typename P2>
constexpr auto operator/(angle<R1,P1> const& a, angle<R2,P2> const& b)
	-> common_type<R1,R2>
{
	using result = common_type< angle<R1,P1>, angle<R2,P2> >;
	return result{ result{ a }.count() / result{ b }.count() };
}

template <typename R1, typename R2, typename P2>
constexpr auto operator*(R1 const& a, angle<R2,P2> const& b) ->
	angle< common_type<R1, R2>, P2 >
{
	using result = angle< common_type<R1, R2>, P2 >;
	result r{ b };
	return r *= a;
}

template <typename R1, typename R2, typename P2>
constexpr auto operator*(angle<R2,P2> const& b, R1 const& a) { return a*b; }

template <typename R1, typename P1, typename R2>
constexpr auto operator/(angle<R1,P1> const& a, R2 const& b) ->
	angle< common_type<R1, R2>, P1 >
{
	using result = angle< common_type<R1, R2>, P1 >;
	result r{ a };
	return r /= b;
}

template <typename R1, typename P1, typename R2, typename P2>
constexpr bool operator==(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	using result = common_type< angle<R1,P1>, angle<R2,P2> >;
	return result{ a }.count() == result{ b }.count();
}


template <typename R1, typename P1, typename R2, typename P2>
constexpr bool operator<(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	using result = common_type< angle<R1,P1>, angle<R2, P2> >;
	return result{ a }.count() < result{ b }.count();
}

template <typename R1, typename P1, typename R2, typename P2>
constexpr bool operator>(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	return b < a;
}

template <typename R1, typename P1, typename R2, typename P2>
constexpr bool operator<=(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	return !(a > b);
}

template <typename R1, typename P1, typename R2, typename P2>
constexpr bool operator>=(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	return !(a < b);
}

template <typename R1, typename P1, typename R2, typename P2>
constexpr bool operator!=(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	return !(a == b);
}

template <typename R1, typename P1, typename R2, typename P2>
bool equals(angle<R1,P1> const& a, angle<R2,P2> const& b)
{
	using result = common_type< angle<R1,P1>, angle<R2, P2> >;
	return equals(result{ a }.count(), result{ b }.count());
}

} // namespace aw::math
#endif //aw_math_angle_h
