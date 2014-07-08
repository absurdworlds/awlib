#ifndef __HRENGIN_FILESYSTEM_IFileSystem_H__
#define __HRENGIN_FILESYSTEM_IFileSystem_H__

#include <hrengin/common/hrenginapi.h>

namespace hrengin
{
namespace filesystem
{

class IFileParser;
class IReadFile;
class IWriteFile;

class IFileSystem
{
public:
	IReadFile& openFileRead(char * path);
	IWriteFile& openFileWrite(char * path);
};


HRENGINFILESYSTEM_API IFileSystem& getFileSystem();


}
}


#endif//__HRENGIN_FILESYSTEM_IFileSystem_H__