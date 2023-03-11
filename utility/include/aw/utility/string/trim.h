/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_trim_h
#define aw_string_trim_h
#include <algorithm>
#include <string>
#include <aw/types/string_view.h>
namespace aw {
namespace string {
/*!
 * Remove characters matching predicate \a pred
 * from the *beginning* of the string \a str.
 */
template <typename Predicate>
std::string& ltrim(std::string& str, Predicate pred)
{
	auto first_not = std::find_if_not(begin(str), end(str), pred);
	str.erase(begin(str), first_not);
	return str;
}

/*!
 * Remove characters matching predicate \a pred
 * from the *end* of the string \a str.
 */
template <typename Predicate>
std::string& rtrim(std::string& str, Predicate pred)
{
	auto last_not = std::find_if_not(rbegin(str), rend(str), pred);
	str.erase(last_not.base(), end(str));
	return str;
}

/*!
 * Remove characters matching predicate \a pred
 * from both end of the string \a str.
 */
template <typename Predicate>
std::string& trim(std::string& str, Predicate pred)
{
	return ltrim(rtrim(str, pred), pred);
}

/*!
 * Create a l-trimmed copy of a string \a str
 */
template <typename Predicate>
std::string ltrimmed(std::string str, Predicate pred)
{
	return ltrim(str, pred);
}

/*!
 * Create a r-trimmed copy of a string \a str
 */
template <typename Predicate>
std::string rtrimmed(std::string str, Predicate pred)
{
	return rtrim(str, pred);
}

/*!
 * Create a trimmed copy of a string \a str
 */
template <typename Predicate>
std::string trimmed(std::string str, Predicate pred)
{
	auto first = std::find_if_not(begin(str), end(str), pred);
	auto last = std::find_if_not(rbegin(str), rend(str), pred);
	return str.substr(first - begin(str), last.base() - first);
}

/*!
 * Remove characters matching predicate \a pred
 * from the *beginning* of the string \a str.
 */
template <typename Predicate>
string_view ltrim_if(string_view str, Predicate pred)
{
	auto first_not = std::find_if_not(begin(str), end(str), pred);
	str.remove_prefix(first_not - begin(str));
	return str;
}

/*!
 * Remove characters matching predicate \a pred
 * from the *end* of the string \a str.
 */
template <typename Predicate>
string_view rtrim_if(string_view str, Predicate pred)
{
	auto last_not = std::find_if_not(rbegin(str), rend(str), pred);
	str.remove_suffix(last_not - rbegin(str));
	return str;
}

/*!
 * Remove characters matching predicate \a pred
 * from both end of the string \a str.
 */
template <typename Predicate>
string_view trim_if(string_view str, Predicate pred)
{
	auto first = std::find_if_not(begin(str), end(str), pred);
	auto last = std::find_if_not(rbegin(str), rend(str), pred);
	return str.substr(first - begin(str), last.base() - first);
}


/*!
 * Remove characters in set \a chars
 * from the *beginning* of the string \a str.
 */
constexpr inline string_view ltrim(string_view str, string_view chars)
{
	auto first_not = str.find_first_not_of( chars );
	if (first_not == str.npos) return {};
	str.remove_prefix(first_not);
	return str;
}

/*!
 * Remove characters in set \a chars
 * from the *end* of the string \a str.
 */
constexpr inline string_view rtrim(string_view str, string_view chars)
{
	auto last_not = str.find_last_not_of( chars );
	if (last_not == str.npos) return {};
	str.remove_suffix(str.size() - last_not - 1);
	return str;
}

/*!
 * Remove characters in set \a chars
 * from both end of the string \a str.
 */
constexpr inline string_view trim(string_view str, string_view chars)
{
	auto first = str.find_first_not_of( chars );
	auto last  = str.find_last_not_of( chars );
	if (first == str.npos) return {};
	return str.substr(first, last - first + 1);
}
} // namespace string
} // namespace aw
#endif//aw_string_trim_h
