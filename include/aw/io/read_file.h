/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_read_file_h
#define aw_io_read_file_h
#include <aw/io/file_mode.h>
#include <aw/utility/filesystem.h>
namespace aw {
namespace io {
/*! Provides interface for reading files */
template<typename File>
struct read_file : private File {
	read_file(fs::path const& _path)
		: File(_path, file_mode::read)
	{ }

	~read_file() = default;

	using File::is_open;
	using File::close;
	using File::read;
	using File::seek;
	using File::tell;
	using File::size;
	using File::path;
};
} // namespace io
} // namespace aw
#endif//aw_io_read_file_h
