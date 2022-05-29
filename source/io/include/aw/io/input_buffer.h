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
#include <string>
#include <cstring>
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
			if (!check_length())
				break;

			size_t len = end() - ptr();
			size_t req = size - count;

			len = std::min(len, req);

			std::copy(ptr(), ptr() + len, out);

			count += len;
			out   += len;

			move_ptr(len);
		}
		return count;
	}

	bool scan(std::string& s, char delim);

	size_t skip(size_t count)
	{
		size_t skipped = 0;
		while (skipped < count) {
			if (!check_length())
				break;

			size_t len = end() - ptr();
			size_t req = count - skipped;

			len = std::min(len, req);

			skipped += len;
			move_ptr(len);
		}

		return skipped;
	}

	/*
	 * Read single character from buffer
	 * \return
	 *    true if a character was extracted, false on end of stream
	 */
	bool peek(char& out)
	{
		if (!check_length()) {
			out = 0;
			return false;
		}
		out = *ptr();
		return true;
	}

	/*
	 * Read single character from buffer
	 * \return
	 *    true if a character was extracted, false on end of stream
	 */
	bool get(char& out)
	{
		if (peek(out)) {
			move_ptr(1);
			return true;
		}
		return false;
	}

	bool eof() const
	{
		return !ptr();
	}

	virtual void seekpos(size_t offset) {}
	virtual void seekend(size_t offset) {}
	virtual void seekoff(ptrdiff_t offset) {}

	virtual size_t position() const { return size_t(-1); }

protected:
	bool check_length()
	{
		if (ptr() != end())
			return true;
		return fill_buffer();
	}
	virtual bool fill_buffer() = 0;

	char const* begin() const { return _beg; };
	char const* ptr()   const { return _ptr; };
	char const* end()   const { return _end; };

	void move_ptr(ptrdiff_t offset) { _ptr += offset; }
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

inline bool input_buffer::scan(std::string& s, char delim)
{
	while (true) {
		if (!check_length())
			return false;

		/*
		 * I did a bit of benchmarking, and found out
		 * that the old implementation of read_until
		 * while (c != delim) { s += c; c = get() }
		 * on input_file_stream was a 3 times slower than
		 * std::getline() on std::fstream!
		 *
		 * I made several attempts to make it faster
		 * than std::getline, but succeded only with
		 * std::memchr
		 *
		 * baseline (std::getline)         1.0s
		 * std::find                       1.5s
		 * std::char_traits::find          1.2s
		 * std::memchr                     0.9s
		 */
		size_t l = end() - ptr();
		if (auto p = std::memchr(ptr(), delim, l)) {
			auto iter = static_cast<const char*>(p);
			s.append(ptr(), iter);
			move_ptr(iter - ptr());
			break;
		}

		s.append( ptr(), end() );
		move_ptr( l );
	}

	skip(1);
	return true;
}
} // namespace io
} // namespace aw
#endif//aw_io_input_buffer_h
