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
#include <aw/utility/string/lazy_split.h>
#include <aw/utility/string/split.h>
#include <aw/utility/string/trim.h>

namespace aw::obj {
constexpr auto ws = string::whitespace;
using string::cut_behavior;

template<typename T>
bool parse1(string_view line, T& v)
{
	return string::try_parse(line, v);
}

namespace _impl {
template<typename Fields, typename T>
size_t parse_fields(Fields fields, T& _1, T& _2, T& _3)
{
	_1 = _2 = _3 = T{0};

	T*     values[] = { &_1, &_2, &_3 };
	size_t num      = 0;

	for (string_view field : fields) {
		if (num == 3)
			break;

		if (!field.empty() && !string::try_parse(field, *values[num]))
			return num;

		++num;
	}

	return num;
}
} // namespace _impl

/*!
 * Read up to three delimited values out of \a line.
 *
 * An empty field the value of zero, e.g. `1//3`, a normal with no texture coordinate.
 *
 * \return
 *     How many values were read. Scanning stops at the first field that is
 *     not a number. Zero means nothing usable was found.
 */
template<typename T>
size_t parse3(string_view line, T& _1, T& _2, T& _3,
              string_view delim = ws, cut_behavior behavior = cut_behavior::discard_empty)
{
	if (behavior == cut_behavior::keep_empty)
		return _impl::parse_fields( string::lazy::cut(line, delim), _1, _2, _3 );

	return _impl::parse_fields( string::lazy::split_by(line, delim), _1, _2, _3 );
}

template<typename T>
size_t parse3(string_view line, T(&arr)[3], string_view delim = ws)
{
	return parse3(line, arr[0], arr[1], arr[2], delim);
}
} // namespace aw::obj

#endif//aw_internal_obj_shared_h
