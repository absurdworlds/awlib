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
#include <aw/types/traits/basic_traits.h>

namespace aw {
namespace math {
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
};

template <typename T>
using radians = angle<T, radian_unit>;
template <typename T>
using turns   = angle<T, std::ratio<1>>;
template <typename T>
using degrees = angle<T, std::ratio<360>>;

} //namespace math
} //namespace aw
#endif //aw_math_angle_h
