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
#include <aw/io/file_descriptor.h>

#include <aw/io/native_file.h>

namespace aw {
namespace io {
/*!
 * Provides raw unbuffered file IO.
 *
 * Methods not marked as noexcept throw fs::filesystem_error
 * with error code supplied by the operating system.
 */
struct file {
	/*! Construct object not representing a file.  */
	file() noexcept = default;

	/*! Construct a file from a system file descriptor. */
	file(file_descriptor fd)
		: data{fd}
	{ }

	/*! Open file identified by \a path. */
	file(fs::path const& path, file_mode fm)
		: _path{path}, data{path, fm}
	{
	}

	/*! Destructor automatically closes the file */
	~file() noexcept
	try
	{
		close();
	}
	catch(...)
	{
		//log.warning("aw::io", "could not close file " + path.u8string());
	}

	file(file&& other) noexcept
		: data{std::move(other.data)},
		 _path{std::move(other._path)}
	{
	}

	file& operator=(file&& other) noexcept
	{
		swap(other);
		return *this;
	}

	void swap(file& other) noexcept
	{
		std::lock_guard<std::mutex> guard{mutex};
		_path.swap(other._path);
		data.swap(other.data);
	}

	void close()
	{
		std::error_code ec;
		std::lock_guard<std::mutex> guard{mutex};

		data.close(ec);

		check_error(ec, "cannot close file");
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
	uintmax_t read(char* buffer, uintmax_t count)
	{
		std::error_code ec;
		std::lock_guard<std::mutex> guard{mutex};

		auto ret = data.read(buffer, count, ec);

		check_error(ec, "cannot read from file");

		return uintmax_t(ret);
	}

	/*!
	 * Write specified number of bytes to file from buffer.
	 * \return
	 *     number of bytes written, negative on failure
	 */
	uintmax_t write(char const* buffer, uintmax_t count)
	{
		std::error_code ec;
		std::lock_guard<std::mutex> guard{mutex};

		auto ret = data.write(buffer, count, ec);

		check_error(ec, "cannot write to file");

		return uintmax_t(ret);
	}

	/*!
	 * Set pointer position
	 */
	uintmax_t seek(intmax_t count, seek_mode mode)
	{
		std::error_code ec;
		std::lock_guard<std::mutex> guard{mutex};

		auto ret = data.seek(count, mode, ec);

		check_error(ec, "cannot set file position");

		return uintmax_t(ret);
	}

	/*!
	 * Get pointer position
	 */
	uintmax_t tell() const
	{
		std::error_code ec;
		std::lock_guard<std::mutex> guard{mutex};

		auto ret = data.tell(ec);

		check_error(ec, "cannot get file position");

		return uintmax_t(ret);
	}

	/*!
	 * Get size of file in bytes
	 */
	uintmax_t size() const
	{
		std::error_code ec;
		std::lock_guard<std::mutex> guard{mutex};

		auto ret = data.size();

		check_error(ec, "cannot get file size");

		return uintmax_t(ret);
	}

	/*!
	 * Get full path to file
	 */
	fs::path const& path() const noexcept { return _path; }

#if 0
protected:
	native::file& get_native() { return data; }
#endif

private:
	void check_error(std::error_code& ec, char const* what) const
	{
		std::error_condition ok{0, ec.category()};
		if (ec.default_error_condition() != ok)
			throw fs::filesystem_error{what, path(), ec};
	}

	mutable std::mutex mutex;
	fs::path _path;
	native::file data;
};
} // namespace io
} // namespace aw
#endif//aw_io_file_h
