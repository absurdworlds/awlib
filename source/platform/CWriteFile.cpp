/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <stdio.h>

#include <hrengin/core/ILogger.h>

#include "CWriteFile.h"

namespace hrengin {
namespace io {

IWriteFile* openWriteFile (std::string path, IWriteFile::Mode mode)
{
	IWriteFile* writeFile = new CWriteFile(path, mode);
	
	if (writeFile->isOpen()) {
		return writeFile;
	}

	delete writeFile;
	return 0;
}

CWriteFile::CWriteFile (std::string const& path, IWriteFile::Mode mode)
: file_(0), size_(0), path_(path), mode_(mode)
{
	this->open();
}

CWriteFile::~CWriteFile ()
{
	if(isOpen()) {
		fclose(file_);
	}
}

void CWriteFile::open ()
{
	if (path_.size() == 0) {
		return;
	}
	
	switch(mode_) {
	case IWriteFile::Mode::Overwrite:
		file_ = fopen(path_.c_str(), "wb");
		break;
	case IWriteFile::Mode::Append:
		file_ = fopen(path_.c_str(), "ab");
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

i32 CWriteFile::write (void const* buffer, u32 size)
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
