/*
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_trigonometry_h
#define aw_math_trigonometry_h
#if defined(_GNU_SOURCE)
#include <math.h> // for sincos
#endif

#include <cmath>
#include <utility>
#include <aw/math/angle.h>
namespace aw {
namespace math {
template<typename T>
T sin( radians<T> angle ) { return std::sin( angle.count() ); }
template<typename T>
T cos( radians<T> angle ) { return std::cos( angle.count() ); }
template<typename T>
T tan( radians<T> angle ) { return std::tan( angle.count() ); }
template<typename T>
std::pair<T,T> sincos( radians<T> angle )
{
	return { sin(angle), cos(angle) };
}

#if defined(_GNU_SOURCE)
template<>
std::pair<float,float> sincos( radians<float> angle )
{
	T s, c;
	::sincosf(angle.count(), &s, &c)
	return {s,c};
}

template<>
std::pair<double,double> sincos( radians<double> angle )
{
	T s, c;
	::sincos(angle.count(), &s, &c)
	return {s,c};
}

template<>
std::pair<long double,long double> sincos( radians<long double> angle )
{
	T s, c;
	::sincosl(angle.count(), &s, &c)
	return {s,c};
}
#endif//_GNU_SOURCE

template<typename T>
T cot( radians<T> angle )
{
	// auto [sin, cos] = sincos(angle);
	// return cos / sin;
	auto sc = sincos(angle);
	return sc.second / sc.first;
}

} // namespace math
} // namespace aw
#endif//aw_math_trigonometry_h
