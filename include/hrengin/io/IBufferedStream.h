/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IBufferedStream_
#define _hrengin_IBufferedStream_

#include <hrengin/io/ICharacterStream.h>

namespace hrengin {
namespace io {
class IReadFile;

//! Class defines an interface for buffered file stream
class IBufferedStream : public ICharacterStream {
public:
	virtual ~IBufferedStream ()
	{
	}
};

//! Create a buffered file stream
HR_SYS_EXP IBufferedStream* createBufferedStream(IReadFile* source);

} //namespace io
} //namespace hrengin
#endif//_hrengin_IBufferedStream_
