#ifndef aw_string_case_h
#define aw_string_case_h
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>

namespace aw::string {
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
} // namespace aw::string

#endif//aw_string_case_h
