/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <hrengin/io/IReadFile.h>

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
		return false;
	}

	c = buffer_[pos_ % STREAM_BUFFER_SIZE];
	return true;
}

bool CBufferedStream::getNext(u8& c)
{
	pos_++;
	
	if(pos_ > source_->getSize()) {
		c = 0;
		return false;
	}

	if(pos_ % STREAM_BUFFER_SIZE == 0) {
		source_->read(buffer_, STREAM_BUFFER_SIZE);
	}

	c = buffer_[pos_ % STREAM_BUFFER_SIZE];

	return true;
}

u32 CBufferedStream::getPos() const 
{
	return pos_;
}

} //namespace io
} //namespace hrg
