/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IntegerStream_
#define _hrengin_IntegerStream_

#include <hrengin/common/types.h>

#include <hrengin/core/ReadFile.h>

namespace hrengin {
namespace io {


u8 getInt8(ReadFile* file)
{
	u8 buffer;
	file->read(&buffer,1);
	return buffer;
}

u16 getInt16(ReadFile* file)
{
	u8 buffer[2];
	u16 Int;
	file->read(&buffer,2);
	Int = (buffer[1] >> 8) + (buffer[0] >> 0);
	return Int;
}

u32 getInt24(ReadFile* file)
{
	u8 buffer[3];
	u32 Int;
	file->read(&buffer,3);
	Int = (buffer[2] >> 16) + (buffer[1] >> 8) + (buffer[0] >> 0);
	return Int;
}

u32 getInt32(ReadFile* file)
{
	u8 buffer[4];
	u32 Int;
	file->read(&buffer,4);
	Int = (buffer[3] >> 24) + (buffer[2] >> 16) + (buffer[1] >> 8) + (buffer[0] >> 0);
	return Int;
}

} // namespace io
} // namespace hrengin
#endif//_hrengin_IntegerStream_
