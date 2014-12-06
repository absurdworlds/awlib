/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IWriteFile_
#define _hrengin_IWriteFile_

#include <string>

#include <hrengin/io/IFile.h>

namespace hrengin {
namespace io {
//! Interface to access files for writing 
class IWriteFile : public IFile {
public:
	virtual ~IWriteFile ()
	{
	}

	/*! Write \a size bytes into file stream from \a buffer.
	 * \param buffer Pointer to first object of source buffer.
	 * \param size Number of bytes to read.
	 * \return >0 if write was successful, \a -error_code otherwise.
	 */ 
	virtual i32 write (void const* buffer, u32 size) = 0;

	/*! File access mode
	 * \a Overwrite will destroy file contents upon opening
	 * \a Append will keep file contents and put pointer to the end of file
	 */
	enum class Mode {
		Overwrite,
		Append
	};
};

/*! Open file for reading
 * \paran path Full path to file
 * \param mode File access mode, \see IWriteFile;:Mode
 */
HR_IO_EXP IWriteFile* openWriteFile (std::string path, IWriteFile::Mode mode);

} // namespace io
} // namespace hrengin
#endif//_hrengin_IWriteFile_
