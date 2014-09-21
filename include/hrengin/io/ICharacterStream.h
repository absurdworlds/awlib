/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ICharacterStream_
#define _hrengin_ICharacterStream_

#include <hrengin/platform/api.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace io {

class ICharacterStream {
public:
	virtual bool getCurrent(u8& c) = 0;
	virtual bool getNext(u8& c) = 0;
	virtual u32 getPos() const = 0;
};

HR_PLATFORM_API ICharacterStream* createCharacterStream(const char* source);

} // namespace io
} // namespace hrengin

#endif//_hrengin_ICharacterStream_
