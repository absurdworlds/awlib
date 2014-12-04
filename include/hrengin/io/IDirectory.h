/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IDirectory
#define _hrengin_IDirectory

#include <string>

#include <hrengin/io/io.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace io {

struct Dirent {
	enum class Type {
		File,
		Dir
	} type;
	std::string name;
}

//! Interface for directory listing
class IDirectory {
public:
	virtual ~IDirectory ()
	{
	}

	/*! Read directory entry at current position
	 * \param result Pointer to struct, which will store information about
	 * directory entry.
	 * \return 0 if successful, otherwise \a -error_code.
	 */
	virtual i32 read (Dirent* result) = 0;
	/*! Reset position to beginning of directory */
	virtual i32 rewind () = 0;
	/*! Set position indicator in directory stream. */
	virtual i32 seek (u32 loc) = 0;
	/*! Get current position in directory stream. */
	virtual u32 tell () = 0;

	/* \return true if directory is open */
	bool isOpen() = 0;
}
} // namespace io
} // namespace hrengin
