#ifndef __HRENGIN_FILESYSTEM_IFileParser_H__
#define __HRENGIN_FILESYSTEM_IFileParser_H__

namespace hrengin {
namespace filesystem {

class IReadFile;

class IFileParser
{
public:
	virtual bool validate(IReadFile& file) = 0;
	virtual bool parse(IReadFile& file) = 0;

};


}
}


#endif//__HRENGIN_FILESYSTEM_IFileParser_H__