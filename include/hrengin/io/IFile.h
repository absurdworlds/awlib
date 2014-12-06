/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IFile_
#define _hrengin_IFile_

#include <string>

#include <hrengin/io/io.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace io {
//! Base class for file streams
class IFile {
	virtual ~IFile ()
	{
	}

	/*! Set position indicator in file stream.
	 * \param offset Number of bytes to move.
	 * \param relative If true, offset will be added to current position,
	 * otherwise to the beginning of gile.
	 * \return 0 if seek was successful, \a -error_code otherwise
	 */ 
	virtual i32 seek (i32 offset, bool relative = false) = 0;
	/* Get current position in file stream. */
	virtual u32 tell () const = 0;

	/*! Get size of file in bytes */
	virtual u32 getSize () const = 0;

	/*! \return \a true if file is open. */
	virtual bool isOpen () const = 0;

	/*! Get full path to file */
	virtual std::string const& getPath () const = 0;
}
} // namespace io
} // namespace hrengin
#endif//_hrengin_IFile_
