/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_FileSystem_
#define _aw_FileSystem_

#include <aw/core/core.h>

namespace aw {
namespace io {
class FileParser;
class ReadFile;
class WriteFile;

//! Vitual filesystem, for transparent access to aw archives
class FileSystem {
public:
	ReadFile& openFileRead(char* path);
	WriteFile& openFileWrite(char* path);
};

HR_CORE_EXP FileSystem* initFilesystem();

} // namespace io
} // namespace aw
#endif//_aw_FileSystem_
