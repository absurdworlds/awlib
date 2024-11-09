/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_internal_obj_shared_h
#define aw_internal_obj_shared_h
#include <aw/fileformat/obj/loader.h>

#include <aw/io/input_stream_utils.h>

#include <aw/string/parse.h>
#include <aw/utility/string/split.h>
#include <aw/utility/string/trim.h>

namespace aw::obj {
constexpr auto ws = string::whitespace;

template<typename T>
bool parse1(string_view line, T& v)
{
	return string::try_parse(line, v);
}

using split_func = std::vector<string_view>(string_view, string_view);
template<typename T>
size_t parse3(string_view line, T& _1, T& _2, T& _3, string_view delim = ws, split_func* split = string::split_by)
{
	auto get_val = [] (string_view str, T& out) {
		if (str.empty())
			return true;
		return parse1(str, out);
	};

	auto substrs = split(line, delim);
	if (substrs.empty())
		return false;

	_1 = _2 = _3 = T{0};

	size_t num = 0;
	switch ( substrs.size() ) {
	default:
	case 3:
		if ( !get_val(substrs[2], _3) ) return num;
		++num;
	case 2:
		if ( !get_val(substrs[1], _2) ) return num;
		++num;
	case 1:
		if ( !get_val(substrs[0], _1) ) return num;
		++num;
	case 0:
		return num;
	}
}

template<typename T>
size_t parse3(string_view line, T(&arr)[3], string_view delim = ws)
{
	return parse3(line, arr[0], arr[1], arr[2], delim);
}
} // namespace aw::obj

#endif//aw_internal_obj_shared_h
