/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IFileSystem_
#define _hrengin_IFileSystem_

#include <hrengin/core/core.h>

namespace hrengin {
namespace io {
class IFileParser;
class IReadFile;
class IWriteFile;

//! Vitual filesystem, for transparent access to hrengin archives
class IFileSystem {
public:
	IReadFile& openFileRead(char* path);
	IWriteFile& openFileWrite(char* path);
};

HR_CORE_EXP IFileSystem* initFilesystem();

} // namespace io
} // namespace hrengin
#endif//_hrengin_IFileSystem_
