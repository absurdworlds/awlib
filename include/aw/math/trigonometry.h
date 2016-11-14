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
template<typename T, typename U>
T sin( angle<T,U> angle ) { return std::sin( radians<T>(angle).count() ); }
template<typename T, typename U>
T cos( angle<T,U> angle ) { return std::cos( radians<T>(angle).count() ); }
template<typename T, typename U>
T tan( angle<T,U> angle ) { return std::tan( radians<T>(angle).count() ); }
template<typename T, typename U>
std::pair<T,T> sincos( angle<T,U> angle )
{
	return { sin(angle), cos(angle) };
}

#if defined(_GNU_SOURCE)
template<typename U>
std::pair<float,float> sincos( angle<float, U> angle )
{
	float s, c;
	::sincosf( radians<float>(angle).count(), &s, &c);
	return {s,c};
}

template<typename U>
std::pair<double,double> sincos( angle<double, U> angle )
{
	double s, c;
	::sincos( radians<double>(angle).count(), &s, &c);
	return {s,c};
}

template<typename U>
std::pair<long double,long double> sincos( angle<long double, U> angle )
{
	long double s, c;
	::sincosl( radians<long double>(angle).count(), &s, &c);
	return {s,c};
}
#endif//_GNU_SOURCE

template<typename T, typename U>
T cot( angle<T, U> angle )
{
	// auto [sin, cos] = sincos(angle);
	// return cos / sin;
	auto sc = sincos(angle);
	return sc.second / sc.first;
}

} // namespace math
} // namespace aw
#endif//aw_math_trigonometry_h
