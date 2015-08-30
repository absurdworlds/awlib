/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_CharacterStream_impl_
#define _awrts_CharacterStream_impl_
#include <awrts/io/CharacterStream.h>

namespace awrts {
namespace io {
class ReadFile;

namespace impl_ {
class CharacterStream : public io::CharacterStream {
public:
	CharacterStream(char const* source)
		: source_(source), pos_(0)
	{
	}

	~CharacterStream()
	{
	}

	virtual bool getCurrent(char& c);

	virtual bool getNext(char& c);

	virtual u32 getPos() const
	{
		return pos_;
	}

private:
	char const* source_;
	u32 pos_;
};
} // namespace impl_
} // namespace io
} // namespace awrts
#endif// (header guard)
