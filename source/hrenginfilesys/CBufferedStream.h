#ifndef __hrengin_CBufferedStream__
#define __hrengin_CBufferedStream__

#include <hrengin/common/hrengintypes.h>
#include <hrengin/filesystem/IBufferedStream.h>

namespace hrengin {
namespace io {

class IReadFile;

class CBufferedStream : public IBufferedStream
{
public:
	CBufferedStream(IReadFile* source);
	~CBufferedStream();

	virtual bool getCurrent(char& c);
	virtual bool getNext(char& c);

private:
	IReadFile* source_;
	char* buffer_;
	u32 pos_;
};


} //namespace io
} //namespace hrg



#endif//__hrengin_CBufferedStream__