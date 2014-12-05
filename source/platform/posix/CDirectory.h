/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CDirectory_
#define _hrengin_CDirectory_

#include <stdio.h>
#include <dirent.h>

#include <string>
#include <vector>

#include <hrengin/io/IDirectory.h>

namespace hrengin {
namespace io {

class CDirectory : public IDirectory {
public:
	CDirectory (std::string const& path);
	virtual ~CDirectory ();
	
	virtual i32 read (Dirent& result);
	virtual void seek (u32 offset);
	virtual void rewind ();
	virtual u32 tell () const;

	virtual bool isOpen () const
	{
		return dir_ != 0;
	}

	virtual const std::string& getPath () const;

private:
	void open ();

	DIR* dir_;
	std::string path_;
};

} // namespace io
} // namespace hrengin
#endif//_hrengin_CDirectory_
