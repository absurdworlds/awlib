/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CCharacterStream_
#define _hrengin_CCharacterStream_

#include <hrengin/common/types.h>
#include <hrengin/io/ICharacterStream.h>

namespace hrengin {
namespace io {

class IReadFile;

class CCharacterStream : public ICharacterStream {
public:
	CCharacterStream(char const* source)
		: source_(source), pos_(0)
	{

	}
	~CCharacterStream()
	{
	}

	virtual bool getCurrent(u8& c)
	{
		if(pos_ == 0xFFFFFFF) {
			c = 0;
			return false;
		}
		c = source_[pos_];
		return true;
	}
	virtual bool getNext(u8& c)
	{
		++ pos_;
		if(source_[pos_] == 0) {
			c = 0;
			pos_ = 0xFFFFFFF;
			return false;
		}
		c = source_[pos_];
		return true;
	}
	virtual u32 getPos() const
	{
		return pos_;
	}

private:
	char const* source_;
	u32 pos_;
};

} //namespace io
} //namespace hrengin
#endif//_hrengin_CCharacterStream_
