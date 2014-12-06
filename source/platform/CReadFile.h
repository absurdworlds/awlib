/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CReadFile_
#define _hrengin_CReadFile_

#include <stdio.h>

#include <hrengin/io/IReadFile.h>

namespace hrengin {
namespace io {

class CReadFile : public IReadFile {
public:
	CReadFile (std::string const& path);

	virtual ~CReadFile();
	
	virtual i32 read (void* buffer, u32 size);
	virtual i32 seek (i32 offset, bool relative = false);
	virtual u32 tell () const;
	virtual u32 getSize () const;

	virtual bool isOpen () const
	{
		return file_ != 0;
	}

	virtual std::string const& getPath () const;

private:
	void open ();

	FILE* file_;
	u32 size_;
	std::string path_;
};

} // namespace io
} // namespace hrengin
#endif//_hrengin_CReadFile_
