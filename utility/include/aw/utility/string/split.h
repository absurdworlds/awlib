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
 * Split string into tokens, separated by one of delimiters
 * contained in the string \a delim.
 * Empty tokens are skipped.
 *
 * Example:
 * `split_by("/ab/cde//fgh/", "/")` -> `{"ab", "cde", "fgh"}`
 * `split_by("ab, cde;fgh", " ,;")` -> `{"ab", "cde", "fgh"}`
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

/*!
 * Split off first substring from a string.
 */
inline std::pair<string_view, string_view>
split_off(string_view source, string_view delim)
{
	size_t pos1 = source.find_first_not_of(delim);
	if (pos1 == source.npos)
		return {};
	size_t pos2 = source.find_first_of(delim, pos1);
	auto first = source.substr(pos1, pos2 - pos1);

	size_t pos3 = source.find_first_not_of(delim, pos2);
	return {first, source.substr( std::min(pos3, source.size()) )};
}

constexpr enum class keep_empty_t {} keep_empty = {};
constexpr enum class discard_empty_t {} discard_empty = {};

namespace _impl {

inline size_t delim_size(char)
{
	return 1;
}

inline size_t delim_size(std::string_view str)
{
	return str.size();
}

inline bool keep(std::string_view substr, keep_empty_t)
{
	return true;
}

inline bool keep(std::string_view substr, discard_empty_t)
{
	return !substr.empty();
}

// TODO: move out of _impl?
template<typename Delimiter, typename Container, typename Behavior>
void split(string_view source, Delimiter delim, Container& store, Behavior behavior)
{
	size_t pos1 = 0;

	do {
		const auto pos2 = source.find(delim, pos1);

		const auto substr = source.substr(pos1, pos2 - pos1);
		if (keep(substr, behavior))
			store.push_back( substr );

		if (pos2 == source.npos)
			break;

		pos1 = pos2 + delim_size(delim);
	} while (true);
}
} // namespace _impl

/*!
 * Split delimited string into substrings,
 * discarding empty substrings.
 * Delimiter may consist of multiple characters.
 *
 * Examples:
 * `split("x==y==z", "==", discard_empty)` -> `{"x", "y", "z"}`
 * `split("/path/", "/", discard_empty)`  -> `{"path"}`
 */
inline auto split(string_view source, string_view delim, discard_empty_t behavior)
	-> std::vector<string_view>
{
	std::vector<string_view> holder;
	_impl::split(source, delim, holder, behavior);
	return holder;
}

inline auto split(string_view source, char delim, discard_empty_t behavior)
	-> std::vector<string_view>
{
	std::vector<string_view> holder;
	_impl::split(source, delim, holder, behavior);
	return holder;
}

/*!
 * Split delimited string into substrings, including
 * empty substrings.
 * Delimiter may consist of multiple characters.
 *
 * Examples:
 * `split("x==y==z", "==", keep_empty)` -> `{"x", "y", "z"}`
 * `split("/path/", "/", keep_empty)` -> `{"", "path", ""}`
 */
inline auto split(string_view source, string_view delim, keep_empty_t behavior)
	-> std::vector<string_view>
{
	std::vector<string_view> holder;
	_impl::split(source, delim, holder, behavior);
	return holder;
}

inline auto split(string_view source, char delim, keep_empty_t behavior)
	-> std::vector<string_view>
{
	std::vector<string_view> holder;
	_impl::split(source, delim, holder, behavior);
	return holder;
}

enum class split_behavior {
	keep_empty,
	discard_empty,
};

/*!
 * Same as previous split, but allows to control behavior at run-time.
 */
template<typename Delimiter>
auto split(string_view source, Delimiter delim, split_behavior behavior)
	-> std::vector<string_view>
{
	if (behavior == split_behavior::discard_empty)
		return split(source, delim, discard_empty);
	if (behavior == split_behavior::keep_empty)
		return split(source, delim, keep_empty);
	// unreachable
	return {};
}

template<typename Delimiter>
std::vector<string_view> split(string_view source, Delimiter delim)
{
	return split(source, delim, discard_empty);
}

[[deprecated("use aw::string::split(source, delim, aw::string::keep_empty)")]]
inline std::vector<string_view> cut(string_view source, string_view delim)
{
	return split(source, delim, keep_empty);
}

} // namespace string
} // namespace aw
#endif//aw_string_split_h
