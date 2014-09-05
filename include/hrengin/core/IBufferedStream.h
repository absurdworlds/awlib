#ifndef _hrengin_IBufferedStream_
#define _hrengin_IBufferedStream_

#include <hrengin/core/ICharacterStream.h>

namespace hrengin {
namespace io {

class IReadFile;

class IBufferedStream : public ICharacterStream {
public:
};

HR_CORE_API IBufferedStream* createBufferedStream(IReadFile* source);

} //namespace io
} //namespace hrengin

#endif//_hrengin_IBufferedStream_
