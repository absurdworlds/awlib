/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <unistd.h>
#include <sys/stat.h>

#include <awengine/io/filesystem.h>

namespace awrts {
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
		result.type = FileType::Directory;
		break;
	default:
		result.type = FileType::Unknown;
	}

	result.size = size_t(file_stat.st_size);

	return 0;
}

i32 checkFile(std::string const& path, FileAccess fmode)
{
#if 0
	// Can't find any mention of exact values in the standard
	// so just in case I leave this snippet here.
	int mode = F_OK;
	mode |= fmode & FileMode::Exec  ? E_OK : 0;
	mode |= fmode & FileMode::Write ? W_OK : 0;
	mode |= fmode & FileMode::Read  ? R_OK : 0;
#endif
	i32 status = access(path.c_str(), int(fmode));

	return status;
}
} // namespace io
} // namespace awrts
