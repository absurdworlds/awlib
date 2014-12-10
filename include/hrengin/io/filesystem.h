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

namespace hrengin {
namespace io {
  
enum class FileType {
	File,
	Dir,
	Unknown
};

struct FileInfo {
	FileType type;
};

HR_SYS_EXP FileInfo file_stat (std::string const& path);
} //namespace io
} //namespace hrengin
#endif//_hrengin_filesystem_
