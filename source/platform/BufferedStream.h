/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_BufferedStream_
#define _hrengin_BufferedStream_
#include <hrengin/io/BufferedStream.h>

namespace hrengin {
namespace io {
class ReadFile;

namespace impl_ {
class BufferedStream : public io::BufferedStream {
public:
	BufferedStream(ReadFile* source);
	virtual ~BufferedStream();

	virtual bool getCurrent(char& c);
	virtual bool getNext(char& c);
	virtual u32 getPos() const;

private:
	ReadFile* source_;
	char cur_;
	u32 pos_;
};
} // namespace impl_
} // namespace io
} // namespace hrengin
#endif//_hrengin_BufferedStream_
