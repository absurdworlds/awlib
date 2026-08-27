/*
 * Copyright (C) 2016-2017  absurdworlds
 * Copyright (C) 2016-2017  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_parser_helpers_h
#define aw_string_parser_helpers_h
#include <aw/types/string_view.h>
namespace aw {
/*
 * Search for char \a c, not prepended with \a escape.
 *
 * An escape applies to the character right after it, so an escaped
 * escape does not escape the character which follows it. For example,
 * in '\'' the '\' escapes the '\', but in '\\' the '\' escapes the '\'
 * that follows it.
 */
template<typename Iter, typename CharT>
Iter find_non_escaped_char(Iter begin, Iter end, CharT c, CharT escape)
{
	for (; begin != end; ++begin) {
		if (*begin == escape) {
			// the escaped character is taken as it is
			if (++begin == end)
				break;
			continue;
		}

		if (*begin == c)
			return begin;
	}

	return end;
}

template<typename CharT>
size_t find_non_escaped_char(basic_string_view<CharT> s, CharT c, CharT escape)
{
	for (size_t pos = 0; pos < s.size(); ++pos) {
		if (s[pos] == escape) {
			++pos;
			continue;
		}

		if (s[pos] == c)
			return pos;
	}

	return s.npos;
}
} // namespace aw
#endif//aw_string_parser_helpers_h
