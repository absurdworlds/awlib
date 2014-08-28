#ifndef _hrengin_IReadFile_
#define _hrengin_IReadFile_

#include <string>

#include <hrengin/common/api.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace io {

class IReadFile {
public:
	virtual ~IReadFile() {};

	virtual i32 read(void* buffer, u32 size) = 0;
	virtual i32 seek(i32 offset, bool relative = false) = 0;
	virtual u32 tell() const = 0;

	virtual u32 getSize() const = 0;

	virtual bool isOpen() const = 0;

	virtual const std::string& getPath() const = 0;
};

HRENGINFILESYSTEM_API IReadFile* openReadFile(std::string path);

} // namespace io
} // namespace hrengin


#endif//_hrengin_IReadFile_