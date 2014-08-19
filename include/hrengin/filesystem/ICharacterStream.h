#ifndef __hrengin_ICharacterStream__
#define __hrengin_ICharacterStream__

//#include <hrengin/common/hrengintypes.h>

namespace hrengin {
namespace io {

class ICharacterStream 
{
public:
	virtual bool getCurrent(char& c) = 0;
	virtual bool getNext(char& c) = 0;
};


}
}


#endif//__HRENGIN_ICharacterStream__