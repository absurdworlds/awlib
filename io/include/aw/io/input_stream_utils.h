/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_input_stream_utils_h
#define aw_input_stream_utils_h
#include <aw/io/input_stream.h>
#include <aw/types/string_view.h>

namespace aw {
namespace io {
/*!
 * Read from stream until charavter is encountered.
 */
[[gnu::noinline]] inline bool read_until(input_stream& is, char delim, std::string& out)
{
	return is.read_until(out, delim);
	/*out.clear();

	char c;
	while (is.get(c)) {
		if (c == delim)
			return true;
		out += c;
	}
	return false;*/
}

} // namespace io
} // namespace aw
#endif//aw_input_stream_utils_h
