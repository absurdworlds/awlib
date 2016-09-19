/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_input_memory_stream_h
#define aw_input_memory_stream_h
#include <aw/io/input_stream.h>
#include <aw/io/file.h>

namespace aw {
namespace io {
/*! Buffer for input_memory_stream */
struct input_memory_buffer : input_buffer {
	input_memory_buffer(char const* _begin, char const* _end)
		: buf(_begin), size(_end - _begin)
	{
		set_ptr(_begin,_begin,_end);
	}

	size_t position() const override
	{
		return ptr() - begin();
	}

protected:
	bool fill_buffer() override
	{
		if (ptr() == end())
			return false;
		return true;
	}

private:
	char const* buf;
	size_t size;
};

/*!
 * Provides access to memory buffer as an input stream.
 */
struct input_memory_stream : input_stream {
	input_memory_stream(char const* begin, char const* end)
		: buffer{begin, end}
	{
		input_stream::init_buffer(buffer);
	}

	virtual ~input_memory_stream() = default;

private:
	input_memory_buffer buffer;
};
} // namespace io
} // namespace aw
#endif//aw_input_memory_stream_h
