/*
 * Copyright (C) 2014       absurdworlds
 * Copyright (C) 2015-2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_file_mode_h
#define aw_io_file_mode_h
#include <aw/types/types.h>
namespace aw {
namespace io {
/*! File seek direction */
enum class seek_mode {
	set,
	end,
	cur,
};

/*! Specifies how to treat a file */
enum class file_mode : unsigned {
	//! Open file for reading
	read      = 1,
	//! Open file for writing
	write     = 1 << 1,
	//! Causes all writes to happen at the end of file
	append    = 1 << 2,
	//! Create file if it is does not exist
	create    = 1 << 3,
	//! Clear the file contents
	truncate  = 1 << 4,
	//! Fail if file already exists
	exclusive = 1 << 5
};

constexpr file_mode operator|(file_mode a, file_mode b)
{
	return file_mode(unsigned(a) | unsigned(b));
}

constexpr file_mode operator&(file_mode a, file_mode b)
{
	return file_mode(unsigned(a) & unsigned(b));
}

constexpr bool operator!(file_mode a)
{
	return !bool(a);
}
} // namespace io
} // namespace aw
#endif//aw_io_file_mode_h
