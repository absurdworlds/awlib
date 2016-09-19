/*
 * Copyright (C) 2014       absurdworlds
 * Copyright (C) 2015-2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_file_h
#define aw_io_file_h
#include <mutex>
#include <algorithm>

#include <aw/types/types.h>
#include <aw/utility/filesystem.h>
#include <aw/io/file_mode.h>

/* internal */
#include <aw/io/bits/file.h>

namespace aw {
namespace io {
/*! Platform-dependent file descriptor */
using file_descriptor = _impl::file_descriptor;

/*!
 * Provides raw unbuffered file IO.
 */
struct file {
	/*! Construct object not representing a file.  */
	file() = default;

	/*! Construct a file from a system file descriptor. */
	file(file_descriptor fd)
		: data(fd)
	{ }

	/*! Open file identified by \a path. */
	file(fs::path const& path, file_mode fm)
		: _path(path), data(path, fm)
	{ }

	~file() { close(); }

	file(file&& other) noexcept
		: data(other.data)
	{
		other.data = _impl::file{};
	}

	file& operator=(file&& other) noexcept
	{
		swap(other);
		return *this;
	}

	void swap(file& other) noexcept
	{
		std::lock_guard<std::mutex> guard{mutex};
		std::swap(_path, other._path);
		data.swap(other.data);
	}

	void swap(file&& other) noexcept
	{
		std::lock_guard<std::mutex> guard{mutex};
		std::swap(_path, other._path);
		data.swap(other.data);
	}

	void close()
	{
		std::lock_guard<std::mutex> guard{mutex};
		if (data.is_open())
			data.close();
	}

	/*!
	 * Check if file is open
	 */
	bool is_open() const noexcept
	{
		std::lock_guard<std::mutex> guard{mutex};
		return data.is_open();
	}

	/*!
	 * Read specified number of bytes from file to buffer
	 * \return
	 *     number of bytes read, or -1 on failure.
	 */
	intmax_t read(char* buffer, uintmax_t count)
	{
		std::lock_guard<std::mutex> guard{mutex};
		return data.read(buffer, count);
	}

	/*!
	 * Write specified number of bytes to file from buffer.
	 * \return
	 *     number of bytes written, negative on failure
	 */
	intmax_t write(char const* buffer, uintmax_t count)
	{
		std::lock_guard<std::mutex> guard{mutex};
		return data.write(buffer, count);
	}

	/*!
	 * Set pointer position
	 */
	intmax_t seek(intmax_t count, seek_mode mode)
	{
		std::lock_guard<std::mutex> guard{mutex};
		return data.seek(count, mode);
	}

	/*!
	 * Get pointer position
	 */
	intmax_t tell()
	{
		std::lock_guard<std::mutex> guard{mutex};
		return data.tell();
	}

	/*!
	 * Get size of file in bytes
	 */
	uintmax_t size() const noexcept { return data.size(); }

	/*!
	 * Get full path to file
	 */
	fs::path const& path() const noexcept { return _path; }

private:
	mutable std::mutex mutex;
	fs::path _path;
	_impl::file data;
};
} // namespace io
} // namespace aw
#endif//aw_io_file_h
