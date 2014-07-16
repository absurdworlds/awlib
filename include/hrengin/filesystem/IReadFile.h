#ifndef __HRENGIN_FILESYSTEM_IReadFile_H__
#define __HRENGIN_FILESYSTEM_IReadFile_H__

#include <hrengin/common/hrengintypes.h>

namespace hrengin {
namespace io {

class IReadFile 
{
public:
	virtual i32 read(void* buffer, u32 size) = 0;
	virtual i32 seek(i32 offset, bool relative = false) = 0;
	virtual u32 tell() const = 0;

	virtual u32 getSize() const = 0;

	virtual bool isOpen() const = 0;

	virtual const std::string& getPath() const = 0;
};

IReadFile* openReadFile(std::string path);

}
}


#endif//__HRENGIN_FILESYSTEM_IReadFile_H__