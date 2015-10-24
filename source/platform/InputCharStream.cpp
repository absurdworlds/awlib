/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awengine/io/InputCharStream.h>

namespace awrts {
namespace io {
bool InputCharStream::peek(char& c)
{
	if(source[pos] == 0) {
		c = 0;
		return false;
	}
	c = source[pos];
	return true;
}

bool InputCharStream::get(char& c)
{
	auto ret = peek(c);

	if(source[pos] != 0)
		++pos;
	return ret;
}
} //namespace io
} //namespace awrts
