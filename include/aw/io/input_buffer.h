/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_input_buffer_h
#define aw_io_input_buffer_h
#include <algorithm>
#include <aw/types/types.h>
namespace aw {
namespace io {
/*! Input stream buffer */
struct input_buffer {
	input_buffer() = default;
	virtual ~input_buffer() = default;

	/*!
	 * Read a sequence of characters from buffer.
	 * \return
	 *    Number of characters read.
	 *    If end of sorce reached, return value is always 0.
	 */
	size_t read(char* out, size_t size)
	{
		size_t count = 0;
		while (count < size) {
			if (ptr() == end() && !fill_buffer())
				break;

			size_t len = end() - ptr();
			size_t req = size - count;

			len = std::min(len, req);

			std::copy(ptr(), ptr() + len, out);

			count += len;
			out   += len;

			bump_ptr(len);
		}
		return count;
	}

	/*
	 * Read single character from buffer
	 * \return
	 *    true if a character was extracted, false on end of stream
	 */
	bool get(char& out)
	{
		if (ptr() == end() && !fill_buffer()) {
			out = 0;
			return false;
		}
		out = *begin();
		bump_ptr(1);
		return true;
	}

	bool eof() const
	{
		return !ptr();
	}

	virtual size_t position() const = 0;

protected:
	virtual bool fill_buffer() = 0;

	char const* begin() const { return _beg; };
	char const* ptr()   const { return _ptr; };
	char const* end()   const { return _end; };

	void bump_ptr(size_t len) { _ptr += len; }
	void set_ptr(char const* new_b, char const* new_p, char const* new_e)
	{
		_beg = new_b;
		_ptr = new_p;
		_end = new_e;
	}

private:
	char const* _beg = nullptr;
	char const* _ptr = nullptr;
	char const* _end = nullptr;
};
} // namespace io
} // namespace aw
#endif//aw_io_input_buffer_h
