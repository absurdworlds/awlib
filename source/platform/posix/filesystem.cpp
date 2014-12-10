/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <sys/stat.h>

#include <hrengin/io/filesystem.h>

namespace hrengin {
namespace io {

i32 fileStat (std::string const& path, FileInfo& result)
{
	struct stat file_stat;

	int err = stat(path.c_str(), &file_stat);
	if(err < 0) {
		return -1;
	}

	switch(file_stat.st_mode & S_IFMT) {
	case S_IFREG:
		result.type = FileType::File;
		break;
	case S_IFDIR:
		result.type = FileType::Dir;
		break;
	default:
		result.type = FileType::Unknown;
	}

	return 0;
}
} // namespace io
} // namespace hrengin
