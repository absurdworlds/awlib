/*
 * Copyright (C) 2015-2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_string_strto_h
#define aw_utility_string_strto_h
#include <limits>
#include <cstdlib>
namespace aw {
/*!
 * Thin wrapper around std::strto*() for use in template code.
 * Additionally provides specializations for `short int` and `int`,
 * and unsigned counterparts.
 */
template<typename T>
T strto(char const* begin, char** end, int base = 0);

template<>
inline float strto(char const* begin, char** end, int)
{
	return std::strtof(begin, end);
}
template<>
inline double strto(char const* begin, char** end, int)
{
	return std::strtod(begin, end);
}
template<>
inline long double strto(char const* begin, char** end, int)
{
	return std::strtold(begin, end);
}

namespace _impl {
template<typename T, typename L>
T _strto(char const* begin, char** end, int base)
{
	L val = aw::strto<L>(begin, end, base);
	if (end && (begin == *end))
		return T(val);
	constexpr auto min = std::numeric_limits<T>::min();
	constexpr auto max = std::numeric_limits<T>::max();
	constexpr auto minl = std::numeric_limits<L>::min();
	constexpr auto maxl = std::numeric_limits<L>::max();
	if (errno == ERANGE) {
		if (val == maxl)
			return max;
		if (val == minl)
			return min;
	}
	if (val > max) {
		errno = ERANGE;
		return max;
	}
	if (val < min) {
		errno = ERANGE;
		return min;
	}
	return T(val);
}
} // namespace _impl

template<>
inline unsigned short strto(char const* begin, char** end, int base)
{
	return _impl::_strto<unsigned short, unsigned long>(begin, end, base);
}

template<>
inline unsigned strto(char const* begin, char** end, int base)
{
	return _impl::_strto<unsigned, unsigned long>(begin, end, base);
}

template<>
inline unsigned long strto(char const* begin, char** end, int base)
{
	return std::strtoul(begin, end, base);
}

template<>
inline unsigned long long strto(char const* begin, char** end, int base)
{
	return std::strtoull(begin, end, base);
}

template<>
inline short strto(char const* begin, char** end, int base)
{
	return _impl::_strto<short, long>(begin, end, base);
}

template<>
inline int strto(char const* begin, char** end, int base)
{
	return _impl::_strto<int, long>(begin, end, base);
}

template<>
inline long strto(char const* begin, char** end, int base)
{
	return std::strtol(begin, end, base);
}

template<>
inline long long strto(char const* begin, char** end, int base)
{
	return std::strtoll(begin, end, base);
}

} // namespace aw
#endif//aw_utility_string_strto_h
