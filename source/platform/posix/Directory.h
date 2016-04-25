/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_Directory_impl
#define _aw_Directory_impl

#include <stdio.h>
#include <dirent.h>

#include <string>
#include <vector>

#include <aw/io/Directory.h>

namespace aw {
namespace io {
namespace impl_ {

class Directory : public io::Directory {
public:
	Directory(std::string const& path);
	virtual ~Directory();

	virtual i32 read(Dirent& result);
	virtual void seek(u32 offset);
	virtual void rewind();
	virtual u32 tell() const;

	virtual bool isOpen() const
	{
		return dir_ != 0;
	}

	virtual const std::string& getPath() const;

private:
	void open ();

	DIR* dir_;
	std::string path_;
};
} // namespace impl_
} // namespace io
} // namespace aw
#endif// (header guard)
