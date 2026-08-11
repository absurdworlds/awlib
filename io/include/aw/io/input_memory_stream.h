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
		: b_begin(_begin), b_end(_end)
	{
		set_ptr(_begin, _begin, _end);
	}

	void seekpos(size_t offset) override
	{
		if (offset > b_size()) {
			set_ptr(b_begin, b_end, b_end);
		} else {
			set_ptr(b_begin, b_begin + offset, b_end);
		}
	}

	void seekend(size_t offset) override
	{
		if (offset > b_size()) {
			set_ptr(b_begin, b_end, b_end);
		} else {
			set_ptr(b_begin, b_end - offset, b_end);
		}
	}

	void seekoff(ptrdiff_t offset) override
	{
		// ptr() is null at eof, so seek from the end of the source
		auto newpos = (eof() ? b_end : ptr()) + offset;
		if ((newpos < b_begin) || (newpos > b_end)) {
			set_ptr(b_begin, b_end, b_end);
		} else {
			set_ptr(b_begin, newpos, b_end);
		}
	}

	size_t position() const override
	{
		return eof() ? b_size() : ptr() - begin();
	}

protected:
	bool fill_buffer() override
	{
		// ptr() is null at eof, so it must be checked separately,
		// because ptr() is no longer equal to b_end
		if (eof() || ptr() == b_end) {
			set_ptr(0, 0, 0);
			return false;
		}
		return true;
	}

	/*! Size of the source buffer */
	size_t b_size() const
	{
		return b_end - b_begin;
	}

private:
	char const* b_begin;
	char const* b_end;
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

	template<size_t N>
	explicit input_memory_stream(char const (&buf)[N])
		: buffer{buf, buf+N}
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
