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
#include <aw/types/string_view.h>
namespace aw {
namespace string {

constexpr string_view whitespace (" \t\v\f\r", 5);

/*!
 * Remove characters in set \a chars
 * from the *beginning* of the string \a str.
 */
constexpr string_view ltrim(string_view str, string_view chars = whitespace)
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
constexpr string_view rtrim(string_view str, string_view chars = whitespace)
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
constexpr string_view trim(string_view str, string_view chars = whitespace)
{
	auto first = str.find_first_not_of( chars );
	auto last  = str.find_last_not_of( chars );
	if (first == str.npos) return {};
	return str.substr(first, last - first + 1);
}
} // namespace string
} // namespace aw
#endif//aw_string_trim_h
