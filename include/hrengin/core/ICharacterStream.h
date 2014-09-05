#ifndef _hrengin_ICharacterStream_
#define _hrengin_ICharacterStream_

#include <hrengin/common/api.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace io {

class ICharacterStream {
public:
	virtual bool getCurrent(u8& c) = 0;
	virtual bool getNext(u8& c) = 0;
	virtual u32 getPos() const = 0;
};

HR_CORE_API ICharacterStream* createCharacterStream(char* source);

} // namespace io
} // namespace hrengin

#endif//_hrengin_ICharacterStream_
