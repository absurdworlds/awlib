#ifndef __H_INCLUDED__HRENGIN_IFileReader
#define __H_INCLUDED__HRENGIN_IFileReader

namespace hrengin
{
namespace filesystem
{

class IFileParser;
class IReadFile;
class IOpenFile;

class IFileReader
{
public:
	void addParser(IFileParser parser);
	IReadFile* openReadFile(char * path);
	IWriteFile* openWriteFile(char * path);
}


}
}


#endif