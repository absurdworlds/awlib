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

#include <hrengin/io/IFile.h>

namespace hrengin {
namespace io {
/*!
 * Class provides interface for writing into files
 */
class HR_IO_EXP CWriteFile : public IFile {
public:
	/*! Open file for reading
	 * \paran path Full path to file
	 * \param mode File access mode, \see io;:FileMode
	 */
	CWriteFile (std::string const& path, bool append);

	/*!
	 * Destructor automatically closes the file
	 */
	virtual ~CWriteFile ();

	/*! Write \a size bytes into file stream from \a buffer.
	 * \param buffer Pointer to first object of source buffer.
	 * \param size Number of bytes to read.
	 * \return >0 if write was successful, \a -error_code otherwise.
	 */ 
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
	void open (bool append);
};

} // namespace io
} // namespace hrengin
#endif//_hrengin_CWriteFile_
