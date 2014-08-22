#ifndef __hrengin_ICharacterStream__
#define __hrengin_ICharacterStream__

//#include <hrengin/common/hrengintypes.h>

namespace hrengin {
namespace io {

class ICharacterStream 
{
public:
	virtual bool getCurrent(u8& c) = 0;
	virtual bool getNext(u8& c) = 0;
	virtual u32 getPos() const = 0;
};


}
}


#endif//__HRENGIN_ICharacterStream__