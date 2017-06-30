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
#include <algorithm>
#include <aw/types/string_view.h>
namespace aw {
/*
 * Search for char \a c, not predended with \a escape.
 */
template<typename Iter, typename CharT>
Iter find_non_escaped_char(Iter begin, Iter end, CharT c, CharT escape)
{
	Iter pos;
        while (true) {
		pos = std::find(begin, end, c);
		if (pos == begin || pos == end)
                        break;
                if (*(pos-1) != escape)
                        break;
        }
        return pos;
}

template<typename CharT>
size_t find_non_escaped_char(basic_string_view<CharT> s, CharT c, CharT escape)
{
	size_t pos;
        while (true) {
		pos = s.find(c);
		if (pos == 0 || pos == s.npos)
                        break;
                if (s[pos-1] != escape)
                        break;
        }
        return pos;
}
} // namespace aw
#endif//aw_string_parser_helpers_h
