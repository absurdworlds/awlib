
#include <hrengin/filesystem/IReadFile.h>

#include "CBufferedStream.h"

namespace hrengin {
namespace io {

const u32 STREAM_BUFFER_SIZE = 1024;


IBufferedStream* createBufferedStream(IReadFile* source)
{
	return new CBufferedStream(source);
}

CBufferedStream::CBufferedStream(IReadFile* source)
: source_(source)
{
	source_->read(buffer_, STREAM_BUFFER_SIZE);
}

CBufferedStream::~CBufferedStream()
{
	delete[] buffer_;
}

bool CBufferedStream::getCurrent(char& c)
{
	return buffer_[pos_ % STREAM_BUFFER_SIZE];
}

bool CBufferedStream::getNext(char& c)
{
	c = buffer_[pos_ % STREAM_BUFFER_SIZE];

	pos_++;
	
	if(pos_ > source_->getSize()) {
		return 0;
	}

	if(pos_ % STREAM_BUFFER_SIZE == 0) {
		source_->read(buffer_, STREAM_BUFFER_SIZE);
	}

	return c;
}


} //namespace io
} //namespace hrg
