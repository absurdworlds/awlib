/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CWriteFile_
#define _hrengin_CWriteFile_

#include <hrengin/io/IWriteFile.h>

namespace hrengin {
namespace io {

class CWriteFile : public IWriteFile {
public:
	CWriteFile (std::string const& path, IWriteFile::Mode mode);

	virtual ~CWriteFile ();

	virtual i32 write (void const* buffer, u32 size);
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
	
	IWriteFile::Mode mode_;
	FILE* file_;
	u32 size_;
	std::string path_;
};

} // namespace io
} // namespace hrengin
#endif//_hrengin_CWriteFile_
