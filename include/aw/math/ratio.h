/*
 * Copyright (C) 2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_ratio_h
#define aw_math_ratio_h
#include <ratio>
#include <aw/math/numeric.h>
namespace aw {
namespace math {
using std::ratio;

template <typename R1, typename R2>
using ratio_multiply_t = std::ratio_multiply<R1,R2>;
template <typename R1, typename R2>
using ratio_divide_t   = std::ratio_divide<R1,R2>;
template <typename R1, typename R2>
struct ratio_gcd_t {
	using type = ratio< gcd( R1::num, R2::num ), lcm( R1::den, R2::den )>;
};

// class instead of typename, because they were blending together
// making declarations harder to read
template <class R1, class R2>
using ratio_multiply = typename ratio_multiply_t<R1,R2>::type;
template <class R1, class R2>
using ratio_divide   = typename ratio_divide_t<R1,R2>::type;
template <class R1, class R2>
using ratio_gcd      = typename ratio_gcd_t<R1,R2>::type;


template<typename T>
constexpr bool is_ratio = false;
template<intmax_t Num, intmax_t Den>
constexpr bool is_ratio< ratio<Num, Den> > = true;

template<typename T>
struct numerator_t;
template<intmax_t Num, intmax_t Den>
struct numerator_t< ratio<Num, Den> > { static constexpr auto value = Num; };

template<typename T>
constexpr intmax_t numerator = numerator_t<T>::value;

template<typename T>
struct denominator_t;
template<intmax_t Num, intmax_t Den>
struct denominator_t< ratio<Num, Den> > { static constexpr auto value = Den; };

template<typename T>
constexpr intmax_t denominator = denominator_t<T>::value;
} // namespace math
} // namespace aw
#endif //aw_math_ratio_h
