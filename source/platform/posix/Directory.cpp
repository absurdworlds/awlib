/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <iostream>
#include <sys/stat.h>

#include <hrengin/core/ILogger.h>

#include "CDirectory.h"

namespace hrengin {
namespace io {

IDirectory* openDirectory (std::string path)
{
	IDirectory* dir = new CDirectory(path);

	if (dir->isOpen()) {
		return dir;
	}

	return 0;
}

CDirectory::CDirectory (const std::string& path)
: dir_(0), path_(path)
{
	this->open();
}


CDirectory::~CDirectory ()
{
	if(isOpen()) {
		closedir(dir_);
	}
}

void CDirectory::open ()
{
	if (path_.size() == 0) {
		dir_ = 0;
		return;
	}

	dir_ = opendir(path_.c_str());
#if 0
	if (dir_) {
		seekdir(dir_, 0);
		size_ = telldir();
		seekdir(dir_, 0);
	} else {
	}
#endif
}

i32 CDirectory::read (Dirent& result)
{
	if (!isOpen()) {
		return -1;
	}

	dirent* entry = readdir(dir_);

	if(entry == 0) {
		return 0;
	}

	std::string dname = path_ + "/" + entry->d_name;
	struct stat dstat;

	int err = stat(dname.c_str(), &dstat);
	if(err < 0) {
		return -1;
	}

	//Dirent dent;
	switch(dstat.st_mode & S_IFMT) {
	case S_IFREG:
		result.type = FileType::File;
		break;
	case S_IFDIR:
		result.type = FileType::Dir;
		break;
	default:
		result.type = FileType::Unknown;
	}

	result.name = entry->d_name;

	return 1;
}

void CDirectory::seek (u32 offset)
{
	seekdir(dir_, offset);
}

void CDirectory::rewind ()
{
	rewinddir(dir_);
}

u32 CDirectory::tell () const
{
	return telldir(dir_);
}
/*
u32 CDirectory::getSize() const
{
	return size_;
}
*/
const std::string& CDirectory::getPath () const
{
	return path_;
}

} // namespace io
} // namespace hrengin
