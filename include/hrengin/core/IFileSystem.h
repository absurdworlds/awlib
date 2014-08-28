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