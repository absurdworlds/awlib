
#include <hrengin/core/ILogger.h>

#include "CReadFile.h"


namespace hrengin {
namespace io {

CReadFile::CReadFile(const std::string& path)
: file_(0), size_(0), path_(path)
{
	TRACE("Opening file:", path)

	open();
}


CReadFile::~CReadFile()
{
	TRACE("Closing file:", path_)

	if(isOpen()) {
		fclose(file_);
	}
}


void CReadFile::open()
{
	if (path_.size() == 0) {
		TRACE("invalid filename (empty)")
		file_ = 0;
		return;
	}

	file_ = fopen(path_.c_str(), "rb");

	if (file_) {
		fseek(file_, 0, SEEK_END);
		size_ = tell();
		fseek(file_, 0, SEEK_SET);
	}
}

i32 CReadFile::read(void* buffer, u32 size)
{
	if (!isOpen()) {
		return -1;
	}

	return (i32)fread(buffer, 1, size, file_);
}

i32 CReadFile::seek(i32 offset, bool relative)
{
	if (!isOpen()) {
		return -1;
	}

	return fseek(file_, offset, relative ? SEEK_CUR : SEEK_SET);
}

u32 CReadFile::tell() const
{
	return ftell(file_);
}

u32 CReadFile::getSize() const
{
	return size_;
}

const std::string& CReadFile::getPath() const
{
	return path_;
}

IReadFile* openReadFile(std::string path)
{
	IReadFile* readFile = new CReadFile(path);
	
	if (readFile->isOpen()) {
		return readFile;
	}	

	return 0;
}

}
}