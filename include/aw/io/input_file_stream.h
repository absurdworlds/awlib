/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_input_file_stream_h
#define aw_input_file_stream_h
#include <aw/io/input_stream.h>
#include <aw/io/file.h>

namespace aw {
namespace io {
/*! Buffer for input_file_stream */
struct input_file_buffer : input_buffer {
	input_file_buffer(fs::path const& path)
		: _file(path, file_mode::read|file_mode::create)
	{
		size = 4096;
		buf = new char[size];
		auto nend = buf + size;
		set_ptr(buf,nend,nend);
	}

	~input_file_buffer() override
	{
		delete[] buf;
	}

	size_t position() const override
	{
		// TODO
		auto pos = const_cast<file&>(_file).tell();
		return pos;
	}

protected:
	bool fill_buffer() override
	{
		if (!ptr())
			return false;

		if (ptr() == end()) {
			auto count = _file.read(buf, size);

			if (count > 0) {
				char* beg  = buf;
				char* nend = buf + count;
				set_ptr(beg, beg, nend);
				return true;
			}

			if (count == 0) {
				set_ptr(0, 0, 0);
				return false;
			}

			throw std::system_error{
				/* TODO */
				std::make_error_code(std::errc::io_error),
				"error reading from file"
			};
		}
		return true;
	}

private:
	file _file;
	char* buf;
	size_t size;
};

/*!
 * Provides high-level interface for reading files.
 */
struct input_file_stream : input_stream {
	input_file_stream(fs::path const& path)
		: input_stream(buffer), buffer(path)
	{}

	virtual ~input_file_stream() = default;

private:
	input_file_buffer buffer;
};
} // namespace io
} // namespace aw
#endif//aw_input_file_stream_h