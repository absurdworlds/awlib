/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_FileSystem_
#define _awrts_FileSystem_

#include <awrts/core/core.h>

namespace awrts {
namespace io {
class FileParser;
class ReadFile;
class WriteFile;

//! Vitual filesystem, for transparent access to awrts archives
class FileSystem {
public:
	ReadFile& openFileRead(char* path);
	WriteFile& openFileWrite(char* path);
};

HR_CORE_EXP FileSystem* initFilesystem();

} // namespace io
} // namespace awrts
#endif//_awrts_FileSystem_
