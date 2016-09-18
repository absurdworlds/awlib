/*
 * Copyright (C) 2014       absurdworlds
 * Copyright (C) 2015-2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_File_h
#define aw_io_File_h
#include <algorithm>

#include <aw/types/types.h>
#include <aw/utility/filesystem.h>
#include <aw/io/file_mode.h>

#include <cstdio>

namespace aw {
namespace io {
/*! Wrapper for C file streams */
struct buffered_file {
	/*!
	 * Construct object not representing a file.
	 */
	buffered_file() = default;

	/*! Construct file from existing C file */
	buffered_file(FILE* _file) : _file(_file) { }
	
	/*!
	 * Open file identified by \a path.
	 * Not all file_mode flags are supported.
	 */
	buffered_file(fs::path const& path, file_mode mode)
		: _path(path)
	{
		using fm = file_mode;

		char const* oflag;
		switch (mode) {
		case fm::read:
		case fm::read|fm::append:
			oflag = "rb";      break;
		case fm::write:
		case fm::write|fm::truncate:
		case fm::write|fm::truncate|fm::create:
			oflag = "wb";      break;
		case fm::append:
		case fm::write|fm::append:
		case fm::write|fm::append|fm::create:
			oflag = "ab";     break;
		case fm::read|fm::write:
			oflag = "r+b";     break;
		case fm::read|fm::write|fm::truncate:
			oflag = "w+b";     break;
		case fm::read|fm::write|fm::append:
		case fm::read|fm::write|fm::append|fm::create:
			oflag = "a+b";     break;
		default:
			oflag = "?";
		}

		// TODO: _wfopen on win32
		_file = std::fopen(path.u8string().data(), oflag);
	}

	~buffered_file()
	{
		if (is_open())
			close();
	}
	
	buffered_file(buffered_file&& other) noexcept
	{
		swap(other);
	}

	buffered_file& operator=(buffered_file&& other) noexcept
	{
		swap(other);
		return *this;
	}

	void swap(buffered_file& other) noexcept
	{
		//std::swap(_path, other._path);
		auto tmp = _file;
		_file = other._file;
		other._file=tmp;
		//std::swap(_file, other._file);
	}

	void swap(buffered_file&& other) noexcept
	{
		swap(static_cast<buffered_file&>(other));
	}

	void close()
	{
		std::fclose(_file);
		_file = nullptr;
	}

	/*!
	 * Check if file is open
	 */
	bool is_open() const noexcept { return _file != nullptr; }

	/*!
	 * Read specified number of bytes from file to buffer
	 */
	intmax_t read(char* buffer, uintmax_t count)
	{
		return std::fread(buffer, 1, long(count), _file);
	}

	/*!
	 * Write specified number of bytes to file from buffer.
	 */
	intmax_t write(char const* buffer, uintmax_t count)
	{
		return std::fwrite(buffer, 1, long(count), _file);
	}

	/*! Set pointer position */
	intmax_t seek(intmax_t count, seek_mode mode)
	{
		int whence;
		switch (mode) {
		case seek_mode::set: whence = SEEK_SET; break;
		case seek_mode::end: whence = SEEK_END; break;
		case seek_mode::cur: whence = SEEK_CUR; break;
		}
		return std::fseek(_file, count, whence);
	}

	/*! Get pointer position */
	intmax_t tell() { return std::ftell(_file); }

	/*! Flush file buffer */
	int flush()     { return std::fflush(_file); }

	/*!
	 * Get size of file in bytes
	 */
	intmax_t size() const
	{
#if (AW_FILESYSTEM == AW_NO_FILESYSTEM)
		auto pos = tell();
		seek(0, seek_mode::end);
		auto pos2 = tell();
		seek(pos, seek_mode::set);
		return pos2;
#else
		return fs::file_size(_path);
#endif
	}

	/*!
	 * Get full path to file
	 */
	fs::path const& path() const noexcept { return _path; }

private:
	fs::path _path;
	FILE*    _file = nullptr;
};
} // namespace io
} // namespace aw
#endif//aw_io_File_h
