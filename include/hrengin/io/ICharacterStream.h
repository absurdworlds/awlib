/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ICharacterStream_
#define _hrengin_ICharacterStream_

#include <hrengin/platform/platform.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace io {

//! Class defines an interface for character streams
class ICharacterStream {
public:
	virtual ~ICharacterStream ()
	{
	}

	virtual bool getCurrent (u8& c) = 0;
	virtual bool getNext (u8& c) = 0;
	virtual u32 getPos () const = 0;
};

//! Create a character stream
HR_SYS_EXP ICharacterStream* createCharacterStream (const char* source);

} // namespace io
} // namespace hrengin
#endif//_hrengin_ICharacterStream_
