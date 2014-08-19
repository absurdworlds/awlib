#ifndef __hrengin_IBufferedStream__
#define __hrengin_IBufferedStream__

#include <hrengin/filesystem/ICharacterStream.h>

namespace hrengin {
namespace io {

class IReadFile;

class IBufferedStream : public ICharacterStream
{
public:
//	virtual bool getCurrent(char& c) = 0;
//	virtual bool getNext(char& c) = 0;
};


IBufferedStream* createBufferedStream(IReadFile* source);

} //namespace io
} //namespace hrg



#endif//__HRENGIN_IBufferedStream__