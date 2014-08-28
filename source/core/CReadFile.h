#ifndef _hrengin_CReadFile_
#define _hrengin_CReadFile_

#include <stdio.h>

#include <string>

#include <hrengin/core/IReadFile.h>

namespace hrengin {
namespace io {

class CReadFile : public IReadFile {
public:
	CReadFile(const std::string& path);

	virtual ~CReadFile();
	
	virtual i32 read(void* buffer, u32 size);

	virtual i32 seek(i32 offset, bool relative = false);
	
	virtual u32 tell() const;

	virtual u32 getSize() const;

	virtual bool isOpen() const
	{
		return file_ != 0;
	}

	virtual const std::string& getPath() const;

private:
	void open();

	FILE* file_;
	u32 size_;
	std::string path_;
};


}
}


#endif//_hrengin_CReadFile_