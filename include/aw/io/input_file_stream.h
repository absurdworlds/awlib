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
	constexpr static size_t buffer_size = 4096 * 2;
	input_file_buffer(fs::path const& path, size_t size)
		: _file(path, file_mode::read),
		  size(size)
	{
		buf = new char[size];
		auto nend = buf + size;
		set_ptr(buf,nend,nend);
	}

	input_file_buffer(fs::path const& path)
		: input_file_buffer{path, buffer_size}
	{ }


	~input_file_buffer() override
	{
		delete[] buf;
	}

	bool is_open() const
	{
		return _file.is_open();
	}

	void seekpos(size_t offset) override
	{
		_file.seek(offset, seek_mode::set);
		read_more();
	}

	void seekend(size_t offset) override
	{
		_file.seek(offset, seek_mode::end);
		read_more();
	}

	void seekoff(ptrdiff_t offset) override
	{
		auto newpos = ptr() + offset;
		if ( newpos < begin() || newpos >= end() ) {
			_file.seek(offset, seek_mode::cur);
			read_more();
		} else {
			set_ptr(begin(), newpos, end());
		}
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

		if (ptr() == end())
			return read_more();

		return true;
	}

private:
	bool read_more()
	{
		auto count = _file.read(buf, size);

		// end of file reached
		if (count == 0) {
			set_ptr(0, 0, 0);
			return false;
		}

		char* beg  = buf;
		char* nend = buf + count;
		set_ptr(beg, beg, nend);
		return true;
	}

	file _file;
	char* buf;
	size_t size;
};

/*!
 * Provides high-level interface for reading files.
 */
struct input_file_stream : input_stream {
	input_file_stream(fs::path const& path)
		: buffer{path}
	{
		input_stream::init_buffer(buffer);
	}

	virtual ~input_file_stream() = default;

	bool is_open() const
	{
		return buffer.is_open();
	}

private:
	input_file_buffer buffer;
};
} // namespace io
} // namespace aw
#endif//aw_input_file_stream_h
