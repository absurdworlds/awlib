/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CBufferedStream_
#define _hrengin_CBufferedStream_

#include <hrengin/common/types.h>
#include <hrengin/io/IBufferedStream.h>

namespace hrengin {
namespace io {

class IReadFile;

class CBufferedStream : public IBufferedStream {
public:
	CBufferedStream(IReadFile* source);
	virtual ~CBufferedStream();

	virtual bool getCurrent(u8& c);
	virtual bool getNext(u8& c);
	virtual u32 getPos() const;

private:
	IReadFile* source_;
	char cur_;
	u32 pos_;
};

} //namespace io
} //namespace hrengin

#endif//_hrengin_CBufferedStream_
