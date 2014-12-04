/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IReadFile_
#define _hrengin_IReadFile_

#include <string>

#include <hrengin/io/io.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace io {

//! Interface to access files for reading
class IReadFile {
public:
	virtual ~IReadFile()
	{
	}

	/*! Read \a size bytes into \a buffer.
	 * \param buffer Pointer to first object of target buffer.
	 * \param size Number of bytes to read.
	 * \return 0 if read was successful, \a -error_code otherwise.
	 */ 
	virtual i32 read(void* buffer, u32 size) = 0;
	/*! Set position indicator in file stream.
	 * \param offset Number of bytes to move.
	 * \param relative If true, offset will be added to current position,
	 * otherwise to the beginning of gile.
	 * \return 0 if seek was successful, \a -error_code otherwise
	 */ 
	virtual i32 seek(i32 offset, bool relative = false) = 0;
	/* Get current position in file stream. */
	virtual u32 tell() const = 0;

	/*! Get size of file in bytes */
	virtual u32 getSize() const = 0;

	/*! \return \a true if file is open. */
	virtual bool isOpen() const = 0;

	/*! Get full path to file */
	virtual std::string const& getPath() const = 0;
};

HR_IO_EXP IReadFile* openReadFile(std::string path);

} // namespace io
} // namespace hrengin

#endif//_hrengin_IReadFile_
