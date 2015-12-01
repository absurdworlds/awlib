/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_File_
#define _aw_File_
#include <string>
#include <memory>

#include <aw/io/io.h>
#include <aw/common/types.h>

namespace aw {
namespace io {
enum class SeekMode {
	Set,
	Offset,
	Reverse,
};

/*!
 * Base class for file streams
 */
class File {
public:
	//! Flags specifying how to treat the file
	enum Mode {
		//! Open file for reading
		Read     = 1,
		//! Open file for writing
		Write    = 1 << 1,
		//! Append mode - seek to the end of file before each write
		Append   = 1 << 2,
		//! Clear the file contents
		Truncate = 1 << 3
	};

	File(std::string const& path, Mode mode);
	virtual ~File();

	File(File&& other);
	File& operator = (File&& other);

	/*!
	 * Check if file is open
	 */
	bool isOpen() const;

	/*!
	 * Read specified number of bytes from file to buffer
	 */
	diff_t read(void* buffer, diff_t count);

	/*!
	 * Write specified number of bytes to file from buffer.
	 */
	diff_t write(void const* buffer, diff_t count);

	/*!
	 * Set pointer position
	 */
	diff_t seek(diff_t count, SeekMode mode);

	/*!
	 * Get pointer position
	 */
	diff_t tell() const;

	/*!
	 * Get size of file in bytes
	 */
	size_t getSize() const;

	/*!
	 * Get full path to file
	 */
	std::string const& getPath() const;

private:
	/*!
	 * Close the file
	 */
	void close();

	std::string path;

	class Details;
	std::unique_ptr<Details> details;
};
} // namespace io
} // namespace aw
#endif//_aw_File_
