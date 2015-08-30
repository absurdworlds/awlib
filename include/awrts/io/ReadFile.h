/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_ReadFile_
#define _awrts_ReadFile_

#include <awrts/io/File.h>

namespace awrts {
namespace io {
/*!
 * Provides interface for reading files
 */
class HR_IO_EXP ReadFile : public File {
public:
	ReadFile (std::string const& path);

	virtual ~ReadFile();

	/*!
	 * Read \a size bytes into \a buffer.
	 * \param buffer Pointer to first object of target buffer.
	 * \param size Number of bytes to read.
	 * \return >0 if read was successful, \a -error_code otherwise.
	 */ 
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
};

} // namespace io
} // namespace awrts
#endif//_awrts_ReadFile_
