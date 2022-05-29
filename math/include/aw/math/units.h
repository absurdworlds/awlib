/*
 * Copyright (C) 2014-2016 absurdworlds
 * Copyright (C) 2014-2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_units_h
#define aw_math_units_h
#include <aw/math/ratio.h>
#include <aw/meta/conditional.h>

namespace aw {
namespace math {
namespace units {
/* TODO: sfinae
template<typename T, typename A, typename B>
T convert( T value, A from, B to )
{
	return value * to() / from();
}

template<typename T, intmax_t Num1, intmax_t Den1, typename B>
T convert( T value, std::ratio<Num1,Den1>, B to )
{
	return value * to() * Den1 / Num1;
}

template<typename T, typename A, intmax_t Num2, intmax_t Den2>
T convert( T value, A from, std::ratio<Num2,Den2> )
{
	return value * Num2 / Den2 / from();
}
*/

// TODO: overflow-proofing
template<typename T, typename A, typename B>
constexpr T convert( T value, A, B )
{
	return value * A::value / B::value;
}

template<typename T, intmax_t Num1, intmax_t Den1, typename B>
constexpr T convert( T value, ratio<Num1,Den1>, B )
{
	return value * B::value * Den1 / Num1;
}

template<typename T, typename A, intmax_t Num2, intmax_t Den2>
constexpr T convert( T value, A from, ratio<Num2,Den2> )
{
	return value * Num2 / Den2 / A::value;
}

template<typename T, intmax_t Num1, intmax_t Den1, intmax_t Num2, intmax_t Den2>
constexpr T convert( T value, ratio<Num1,Den1>, ratio<Num2,Den2> )
{
	using ratio = ratio_divide< ratio<Num2,Den2>, ratio<Num1,Den1> >;
	return value * ratio::num / ratio::den;
}

template<typename A, typename B>
struct common_t {
	// One of numbers is irrational — select that one,
	// as it cannot be represented as ratio
	// (all floats are rational, but type can be not only float)
	using type = conditional< is_ratio<A>, B, A >;
};

template<intmax_t Num1, intmax_t Den1, intmax_t Num2, intmax_t Den2>
struct common_t< ratio<Num1, Den1>,  ratio<Num2, Den2> > {
	using type = ratio_gcd< ratio<Num1, Den1>, ratio<Num2, Den2> >;
};

template<typename A, typename B>
using common = typename common_t<A,B>::type;

template<typename T, typename U>
constexpr T extract = U::value;
template<typename T, intmax_t Num, intmax_t Den>
constexpr T extract<T, ratio<Num,Den>> = T(Num)/Den;

} // namespace units
} // namespace math

namespace units = math::units;
} // namespace aw
#endif //aw_math_units_h
