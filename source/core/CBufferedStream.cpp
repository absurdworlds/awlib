
#include <hrengin/core/IReadFile.h>

#include "CBufferedStream.h"

namespace hrengin {
namespace io {

const u32 STREAM_BUFFER_SIZE = 1024;


IBufferedStream* createBufferedStream(IReadFile* source)
{
	return new CBufferedStream(source);
}

CBufferedStream::CBufferedStream(IReadFile* source)
: pos_(0), source_(source), buffer_(new char[STREAM_BUFFER_SIZE])
{
	source_->read(buffer_, STREAM_BUFFER_SIZE);
}

CBufferedStream::~CBufferedStream()
{
	delete[] buffer_;
}

bool CBufferedStream::getCurrent(u8& c)
{
	if(pos_+1 > source_->getSize()) {
		c = 0;
		return 0;
	}

	c = buffer_[pos_ % STREAM_BUFFER_SIZE];
	return true;
}

bool CBufferedStream::getNext(u8& c)
{
	pos_++;
	
	if(pos_ > source_->getSize()) {
		c = 0;
		return 0;
	}

	if(pos_ % STREAM_BUFFER_SIZE == 0) {
		source_->read(buffer_, STREAM_BUFFER_SIZE);
	}

	c = buffer_[pos_ % STREAM_BUFFER_SIZE];

	return 1;
}

u32 CBufferedStream::getPos() const 
{
	return pos_;
}

} //namespace io
} //namespace hrg
