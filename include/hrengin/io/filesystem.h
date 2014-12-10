/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_filesystem_
#define _hrengin_filesystem_
#include <string>

#include <hrengin/common/types.h>
#include <hrengin/io/io.h>

namespace hrengin {
namespace io {
  
enum class FileType {
	Unknown,
	File,
	Dir
};

struct FileInfo {
	FileType type;
};

/*!
 * Get information about file
 */
HR_IO_EXP i32 fileStat (std::string const& path, FileInfo& result);
} //namespace io
} //namespace hrengin
#endif//_hrengin_filesystem_
