#ifndef _hrengin_CBufferedStream_
#define _hrengin_CBufferedStream_

#include <hrengin/common/types.h>
#include <hrengin/core/IBufferedStream.h>

namespace hrengin {
namespace io {

class IReadFile;

class CBufferedStream : public IBufferedStream {
public:
	CBufferedStream(IReadFile* source);
	~CBufferedStream();

	virtual bool getCurrent(u8& c);
	virtual bool getNext(u8& c);
	virtual u32 getPos() const;

private:
	IReadFile* source_;
	char* buffer_;
	u32 pos_;
};

} //namespace io
} //namespace hrengin

#endif//_hrengin_CBufferedStream_
