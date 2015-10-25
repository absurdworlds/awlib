/*
 * Copyright (C) 2014-2105  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awengine/io/ReadFile.h>
#include <awengine/io/InputFileStream.h>

#include <cstdio>

namespace awrts {
namespace io {
InputFileStream::InputFileStream(ReadFile& source)
	: pos(0), source(source), size(source.getSize())
{
	if (size > 0) {
		source.read(&cur, 1);
	}
}

bool InputFileStream::peek(char& c)
{
	if (pos == size) {
		c = 0;
		return false;
	}

	c = cur;
	return true;
}

bool InputFileStream::get(char& c)
{
	bool ret = peek(c);
	if (pos < size) {
		++pos;
		source.read(&cur, 1);
	}

	return ret;
}

bool InputFileStream::next(char& c)
{
	if (pos < size) {
		++pos;
		source.read(&cur, 1);
	}

	return peek(c);
}

size_t InputFileStream::getPos() const
{
	return pos;
}
} //namespace io
} //namespace awrts
