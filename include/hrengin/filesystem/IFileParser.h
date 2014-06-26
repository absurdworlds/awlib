#ifndef __HRENGIN_FILESYSTEM_IFileParser_H__
#define __HRENGIN_FILESYSTEM_IFileParser_H__

namespace hrengin {
namespace filesystem {

class IReadFile;

class IFileParser
{
public:
	bool validate(IReadFile& file);
	bool parse(IReadFile& file);

};


}
}


#endif//__HRENGIN_FILESYSTEM_IFileParser_H__