/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef Daedalus_string
#define Daedalus_string
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
namespace aw {
namespace string {
/*!
 * Transform the string to lower case.
 */
inline std::string& tolower(std::string& str)
{
	std::transform(std::begin(str), std::end(str),
	               std::begin(str), ::tolower);
	return str;
}

/*!
 * Transform the string to upper case.
 */
inline std::string& toupper(std::string& str)
{
	std::transform(std::begin(str), std::end(str),
	               std::begin(str), ::toupper);
	return str;
}

/*!
 * Make first letter upper case and lower rest.
 */
inline std::string& capitalize(std::string& str)
{
	if (!str.empty())
		str.front() = std::toupper(str.front());
	if (str.size() < 2)
		return str;
	auto begin = std::next(std::begin(str));
	std::transform(begin, std::end(str), begin, ::tolower);
	return str;
}

inline std::string tolower( std::string_view str )
{
	std::string tmp(str);
	tolower(tmp);
	return tmp;
}

inline std::string toupper( std::string_view str )
{
	std::string tmp(str);
	toupper(tmp);
	return tmp;
}
} // namespace string
} // namespace aw
#endif//aw_string_case_h
