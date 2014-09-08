/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IFileSystem_
#define _hrengin_IFileSystem_

#include <hrengin/common/api.h>

namespace hrengin {
namespace io {

class IFileParser;
class IReadFile;
class IWriteFile;

class IFileSystem {
public:
	IReadFile& openFileRead(char * path);
	IWriteFile& openFileWrite(char * path);
};


HRENGINFILESYSTEM_API IFileSystem& getFileSystem();


}
}


#endif//__HRENGIN_FILESYSTEM_IFileSystem_H__