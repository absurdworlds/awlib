/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_WriteFile_h
#define aw_io_WriteFile_h
#include <aw/io/File.h>
namespace aw {
namespace io {
/*!
 * Class provides interface for writing into files
 */
class AW_IO_EXP WriteFile : private File {
public:
	/*!
	 * Open file for writing
	 * \param path
	 *     Full path to file
	 * \param append 
	 *     If true, will append to the end instead of overwriting the file.
	 */
	WriteFile(std::string const& path, bool append)
		: File(path, File::Write | append ? File::Append : File::Truncate)
	{
	}

	/*!
	 * Destructor automatically closes the file
	 */
	~WriteFile() = default;

	using File::isOpen;
	using File::write;
	using File::seek;
	using File::tell;
	using File::size;
	using File::path;
};

} // namespace io
} // namespace aw
#endif//aw_io_WriteFile_h
