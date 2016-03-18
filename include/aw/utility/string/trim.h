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
#include <string>
#include <algorithm>
namespace aw {
namespace string {
/*!
 * Remove characters matching predicate \a pred
 * from the *beginning* of the string \a str.
 */
template <typename Predicate>
std::string& ltrim(std::string& str, Predicate pred)
{
	auto first_not = std::find_if_not(std::begin(str), std::end(str), pred);
	str.erase(std::begin(str), first_not);
	return str;
}

/*!
 * Remove characters matching predicate \a pred
 * from the *end* of the string \a str.
 */
template <typename Predicate>
std::string& rtrim(std::string& str, Predicate pred)
{
	auto last_not = std::find_if_not(std::rbegin(str), std::rend(str), pred);
	str.erase(last_not.base(), std::end(str));
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
std::string ltrimmed(std::string const& str, Predicate pred)
{
	std::string copy = {str};
	return ltrim(copy, pred);
}

/*!
 * Create a r-trimmed copy of a string \a str
 */
template <typename Predicate>
std::string rtrimmed(std::string const& str, Predicate pred)
{
	std::string copy = {str};
	return rtrim(copy, pred);
}

/*!
 * Create a trimmed copy of a string \a str
 */
template <typename Predicate>
std::string trimmed(std::string const& str, Predicate pred)
{
	auto first = std::find_if_not(std::begin(str), std::end(str), pred);
	auto last = std::find_if_not(std::rbegin(str), std::rend(str), pred);
	return str.substr(first - std::begin(str), last.base() - first);
}
} // namespace string
} // namespace aw
#endif//aw_string_trim_h
