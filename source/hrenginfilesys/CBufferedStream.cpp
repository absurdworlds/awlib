
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
: source_(source), buffer_(new char(STREAM_BUFFER_SIZE))
{
	source_->read(buffer_, STREAM_BUFFER_SIZE);
}

CBufferedStream::~CBufferedStream()
{
	delete[] buffer_;
}

bool CBufferedStream::getCurrent(char& c)
{
	c = buffer_[pos_ % STREAM_BUFFER_SIZE];
	return true;
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

	return 1;
}


} //namespace io
} //namespace hrg
