/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <hrengin/core/ILogger.h>

#include "CWriteFile.h"

namespace hrengin {
namespace io {

IWriteFile* openWriteFile (std::string path, IWriteFile::Mode mode)
{
	IWriteFile* readFile = new C/WriteFile(path);
	
	if (readFile->isOpen()) {
		return readFile;
	}

	return 0;
}

CWriteFile::CWriteFile (std::string const& path, IWriteFile::Mode mode)
: file_(0), size_(0), path_(path)
{
	if (path_.size() == 0) {
		return;
	}
	
	switch(mode) {
	case IWriteFile::Mode::Overwrite:
		file_ = fopen(path_.c_str(), "w");
		break;
	case IWriteFile::Mode::Append:
		file_ = fopen(path_.c_str(), "a");
		break;
	default:
		return;
	}

	if (file_) {
		fseek(file_, 0, SEEK_END);
		size_ = tell();
		fseek(file_, 0, SEEK_SET);
	} else {
	}
}

CWriteFile::~CWriteFile ()
{
	if(isOpen()) {
		fclose(file_);
	}
}

i32 CWriteFile::write (void* buffer, u32 size)
{
	if (!isOpen()) {
		return -1;
	}

	return i32(fwrite(buffer, 1, size, file_));
}

i32 CWriteFile::seek (i32 offset, bool relative)
{
	if (!isOpen()) {
		return -1;
	}

	return fseek(file_, offset, relative ? SEEK_CUR : SEEK_SET);
}

u32 CWriteFile::tell () const
{
	return ftell(file_);
}

u32 CWriteFile::getSize () const
{
	return size_;
}

std::string const& CWriteFile::getPath () const
{
	return path_;
}

} // namespace io
} // namespace hrengin
