/*
 * Copyright (C) 2014-2016  absurdworlds
 * Copyright (C) 2015-2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_split_h
#define aw_string_split_h
#include <vector>
#include <algorithm>
#include <aw/types/string_view.h>
namespace aw {
namespace string {
/*!
 * Split string into tokens, separated by delimiters \a delim.
 *
 * Example:
 * `split("/ab/cde//fgh/", "/")` -> `{"ab", "cde", "fgh"}`
 * `split("ab\\cde/fgh/\\", "/\\")` -> `{"ab", "cde", "fgh"}`
 */
inline std::vector<string_view>
split_by(string_view source, string_view delim)
{
	std::vector<string_view> holder;
	size_t delim_pos = 0;
	size_t pos;

	do {
		pos = source.find_first_not_of(delim, delim_pos);
		if (pos == source.npos)
			break;

		delim_pos = source.find_first_of(delim, pos);
		holder.push_back(source.substr(pos, delim_pos - pos));
	} while (true);

	return holder;
}

namespace _impl {
// TODO: move out of _impl?
template<typename Store>
void split(string_view source, string_view delim, Store store)
{
	size_t pos1 = 0;
	size_t pos2;

	do {
		pos2 = source.find(delim, pos1);

		store( source.substr(pos1, pos2 - pos1) );

		if (pos2 == source.npos)
			break;

		pos1 = pos2 + delim.size();
	} while (true);
}
} // namespace _impl

/*!
 * Split delimited string into substrings,
 * discarding empty substrings.
 * Delimiter may consist of multiple characters.
 *
 * Examples:
 * `slice("x==y==z", "==")` -> `{"x", "y", "z"}`
 * `slice("/path/", "/", true)`  -> `{"path"}`
 */
inline std::vector<string_view>
split(string_view source, string_view delim)
{
	std::vector<string_view> holder;
	auto insert = [&] (string_view s) {
		if (!s.empty())
			holder.push_back(s);
	};
	_impl::split(source, delim, insert);
	return holder;
}

/*!
 * Split delimited string into substrings, including
 * empty substrings.
 * Delimiter may consist of multiple characters.
 *
 * Examples:
 * `explode("x==y==z", "==")` -> `{"x", "y", "z"}`
 * `explode("/path/", "/", false)` -> `{"", "path", ""}`
 */
inline std::vector<string_view>
cut(string_view source, string_view delim)
{
	std::vector<string_view> holder;
	auto insert = [&] (string_view s) {
		holder.push_back(s);
	};
	_impl::split(source, delim, insert);
	return holder;
}
} // namespace string
} // namespace aw
#endif//aw_string_split_h
