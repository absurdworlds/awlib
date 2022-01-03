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

#include <aw/utility/string/trim.h>
#include <aw/utility/string/split.h>
#include <aw/utility/string/strto.h>

//#include <aw/types/promote.h>
#include <limits>
#include <cassert>

namespace aw {
namespace obj {
constexpr string_view ws (" \t\v\f\r", 5);


template<typename T>
bool parse1(string_view line, T& v)
{
	char* end;
	std::string tmp(line);
	// unfortunately, strto* requires string to be null-terminated

	v = strto<T>( tmp.data(), &end );
	return (end != tmp.data());
}

using split_func = std::vector<string_view>(string_view, string_view);
template<typename T>
size_t parse3(string_view line, T& _1, T& _2, T& _3, string_view delim = ws, split_func* split = string::split_by)
{
	auto is_delim = [&] (char c) {
		return delim.find(c) != delim.npos;
	};
	char* end;
	errno = 0;
	_1 = strto<T>( line.data(), &end );
	if (errno) return 0;
	while (is_delim(*end)) ++end;
	errno = 0;
	_2 = strto<T>( end+1, &end );
	if (errno) return 1;
	while (is_delim(*end)) ++end;
	errno = 0;
	_3 = strto<T>( end+1, &end );
	if (errno) return 2;
	return 3;
}

template<typename T>
size_t parse3(string_view line, T(&arr)[3], string_view delim = ws)
{
	return parse3(line, arr[0], arr[1], arr[2], delim);
}
} // namespace obj
} // namespace aw
#endif//aw_internal_obj_shared_h
