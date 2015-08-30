/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_filesystem_
#define _awrts_filesystem_
#include <string>

#include <awrts/common/types.h>
#include <awrts/platform/platform.h>

namespace awrts {
namespace io {
/*!
 * File type on a filesystem
 */
enum class FileType {
	Unknown,
	File,
	Dir,
	Symlink,
};

/*!
 * This structure hold information about file,
 * which is acquired by calling \a fileStat
 */
struct FileInfo {
	FileType type;
	size_t size;
};

/*!
 * Get information about file
 */
HR_SYS_EXP i32 fileStat (std::string const & path, FileInfo& result);

/*!
 * Get type (e.g. regular file or directory) of a file
 */
inline FileType fileType (std::string const & path)
{
	FileInfo info;
	fileStat(path, info);

	return info.type;
}
/*!
 * Get file size in bytes
 */
inline size_t fileSize (std::string const & path)
{
	FileInfo info;
	fileStat(path, info);

	return info.size;
}

/*!
 * File opening mode
 */
enum FileMode {
	//! File exists
	FM_Exists  = 0,
	//! Execute permission
	FM_Exec    = 1,
	//! Write permission
	FM_Write   = 2,
	//! Read permission
	FM_Read    = 4,
};

/*!
 * Test file existence and permissions.
 * \param path
 * 	Path to file.
 * \param mode
 * 	Permissions to test. Can be OR'ed together to check for
 * 	multiple permissions
 * \return 
 * 	Zero (0) on success, or -1 if file not exist
 * 	or one of permissions was denied.
 */
HR_SYS_EXP i32 checkFile(std::string const & path, FileMode mode);

} //namespace io
} //namespace awrts
#endif//_awrts_filesystem_
