#ifndef __HRENGIN_FILESYSTEM_IFileSystem_H__
#define __HRENGIN_FILESYSTEM_IFileSystem_H__

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
	IReadFile* openFileRead(char * path);
	IWriteFile* openFileWrite(char * path);
}


}
}


#endif//__HRENGIN_FILESYSTEM_IFileSystem_H__