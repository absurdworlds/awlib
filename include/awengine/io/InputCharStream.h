/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_InputCharStream_impl_
#define _awrts_InputCharStream_impl_
#include <awengine/io/InputStream.h>

namespace awrts {
namespace io {
class InputCharStream : public io::InputStream {
public:
	InputCharStream(char const* source)
		: source(source), pos(0)
	{
	}

	virtual ~InputCharStream() = default;

	virtual bool peek(char& c);
	virtual bool get(char& c);

	/*!
	 * Skip current character and peek a next.
	 * Equivalent to
	 * 	get(c) && peek(c);
	 */
	virtual bool next(char& c);

	virtual size_t getPos() const
	{
		return pos;
	}

private:
	char const* source;
	size_t pos;
};
} // namespace io
} // namespace awrts
#endif// (header guard)
