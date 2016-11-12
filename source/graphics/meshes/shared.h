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
#include <limits>

#include <aw/utility/string/trim.h>
#include <aw/utility/string/split.h>
#include <aw/utility/string/strto.h>

#include <aw/types/promote.h>

namespace aw {
namespace obj {
constexpr string_view ws (" \t\v\f\r", 4);


template<typename T>
bool parse1(string_view line, T& v)
{
	char* end;
	std::string tmp(line);
	// unfortunately, strto* requires string to be null-terminated

	v = strto<T>( tmp.data(), &end );
	return (end != tmp.data());
}

template<typename T>
bool parse3(string_view line, T& _1, T& _2, T& _3, string_view delim = ws)
{
	auto substrs = string::split_by(line.substr(1), delim);
	if (substrs.empty())
		return false;

	_1 = _2 = _3 = T{0};

	switch ( substrs.size() ) {
	default:
	case 3:
		if ( !parse1(substrs[2], _3) ) return false;
	case 2:
		if ( !parse1(substrs[1], _2) ) return false;
	case 1:
		if ( !parse1(substrs[0], _1) ) return false;
		return true;
	case 0:
		return false;
	};
}

template<typename T>
bool parse3(string_view line, T(&arr)[3], string_view delim = ws)
{
	return parse3(line, arr[0], arr[1], arr[2], delim);
}
} // namespace obj
} // namespace aw
#endif//aw_internal_obj_shared_h
