/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Directory_
#define _hrengin_Directory_

#include <string>

#include <hrengin/io/io.h>
#include <hrengin/io/filesystem.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace io {
/*!
 * Struct, which represents directory entry.
 */
struct Dirent {
	FileType type;
	std::string name;
};

//! Interface for directory listing
class Directory {
public:
	virtual ~Directory ()
	{
	}

	/*!
	 * Read directory entry at current position
	 * \param result Reference to struct, which will hold directory
	 * entry information. 
	 * \return 0 on success, \a -error_code otherwise. 
	 */
	virtual i32 read(Dirent& result) = 0;
	/*! Reset position to beginning of directory */
	virtual void rewind() = 0;
	/*! Set position indicator in directory stream. */
	virtual void seek(u32 loc) = 0;
	/*! Get current position in directory stream. */
	virtual u32 tell() const = 0;

	/* \return true if directory is open */
	virtual bool isOpen() const = 0;

	/*! Get absolute path of the directory */	
	virtual std::string const& getPath() const = 0;
};

HR_IO_EXP Directory* openDirectory(std::string path);
} // namespace io
} // namespace hrengin
#endif //_hrengin_Directory_
