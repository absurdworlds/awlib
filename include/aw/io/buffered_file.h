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

#include <aw/io/file_mode.h>
#include <aw/io/filesystem.h>
#include <aw/types/types.h>

#include <cstdio>

namespace aw {
namespace io {

inline const char* make_fopen_flag(file_mode mode)
{
	using fm = file_mode;

	switch (mode) {
	case fm::read:
	case fm::read | fm::append:
		return "rb";
	case fm::write:
	case fm::write | fm::truncate:
	case fm::write | fm::truncate | fm::create:
		return "wb";
	case fm::append:
	case fm::write | fm::append:
	case fm::write | fm::append | fm::create:
		return "ab";
	case fm::read | fm::write:
		return "r+b";
	case fm::read | fm::write | fm::truncate:
		return "w+b";
	case fm::read | fm::write | fm::append:
	case fm::read | fm::write | fm::append | fm::create:
		return "a+b";
	default:
		return "?";
	}
}

inline const wchar_t* make_wopen_flag(file_mode mode)
{
	using fm = file_mode;

	switch (mode) {
	case fm::read:
	case fm::read | fm::append:
		return L"rb";
	case fm::write:
	case fm::write | fm::truncate:
	case fm::write | fm::truncate | fm::create:
		return L"wb";
	case fm::append:
	case fm::write | fm::append:
	case fm::write | fm::append | fm::create:
		return L"ab";
	case fm::read | fm::write:
		return L"r+b";
	case fm::read | fm::write | fm::truncate:
		return L"w+b";
	case fm::read | fm::write | fm::append:
	case fm::read | fm::write | fm::append | fm::create:
		return L"a+b";
	default:
		return L"?";
	}
}

/*! Wrapper for C file streams */
struct buffered_file {
	/*!
	 * Construct object not representing a file.
	 */
	buffered_file() = default;

	/*! Construct file from existing C file */
	buffered_file(FILE* _file) : _file(_file) {}

	/*!
	 * Open file identified by \a path.
	 * Not all file_mode flags are supported.
	 */
	buffered_file(fs::path const& path, file_mode mode)
	    : _path(path)
	{
#if (AW_PLATFORM == AW_PLATFORM_WIN32)
		auto err = ::_wfopen_s(&_file, path.native().data(), make_wopen_flag(mode));
		(void)err; // TODO
#else
		_file = std::fopen(path.u8string().data(), make_fopen_flag(mode));
#endif
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
