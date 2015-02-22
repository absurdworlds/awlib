/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CharacterStream_
#define _hrengin_CharacterStream_

#include <hrengin/platform/platform.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace io {

//! Class defines an interface for character streams
class CharacterStream {
public:
	virtual ~CharacterStream ()
	{
	}

	virtual bool getCurrent (u8& c) = 0;
	virtual bool getNext (u8& c) = 0;
	virtual u32 getPos () const = 0;
};

//! Create a character stream
HR_SYS_EXP CharacterStream* createCharacterStream (char const* source);

} // namespace io
} // namespace hrengin
#endif//_hrengin_CharacterStream_
