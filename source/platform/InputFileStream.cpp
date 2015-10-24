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

namespace awrts {
namespace io {
InputFileStream::InputFileStream(ReadFile& source)
	: pos_(0), source(source)
{
	//TODO: may crash on file of zero length
	source.read(&cur_, 1);
}

InputFileStream::~InputFileStream()
{
}

bool InputFileStream::peek(char& c)
{
	if(pos > source.getSize()) {
		c = 0;
		return false;
	}

	c = next;
	return true;
}

bool InputFileStream::get(char& c)
{
	++pos;

	if(pos > source.getSize()) {
		c = 0;
		return false;
	}

	source_->read(&next, 1);
	c = next;

	return true;
}

u32 InputFileStream::getPos() const
{
	return pos;
}

} //namespace io
} //namespace awrts
