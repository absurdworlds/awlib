#ifndef aw_string_case_h
#define aw_string_case_h
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>

namespace aw::string {
namespace _impl {
/*
 * ::tolower/::toupper take an int which must be representable as an
 * unsigned char; passing a negative char is undefined.
 */
inline char to_lower(char c) { return char(::tolower((unsigned char)c)); }
inline char to_upper(char c) { return char(::toupper((unsigned char)c)); }
} // namespace _impl

/*!
 * Transform the string to lower case.
 */
inline std::string& tolower(std::string& str)
{
	std::transform(std::begin(str), std::end(str),
	               std::begin(str), _impl::to_lower);
	return str;
}

/*!
 * Transform the string to upper case.
 */
inline std::string& toupper(std::string& str)
{
	std::transform(std::begin(str), std::end(str),
	               std::begin(str), _impl::to_upper);
	return str;
}

/*!
 * Make first letter upper case and lower rest.
 */
inline std::string& capitalize(std::string& str)
{
	if (!str.empty())
		str.front() = _impl::to_upper(str.front());
	if (str.size() < 2)
		return str;
	auto begin = std::next(std::begin(str));
	std::transform(begin, std::end(str), begin, _impl::to_lower);
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
} // namespace aw::string

#endif//aw_string_case_h
