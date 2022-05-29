/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_input_stream_h
#define aw_input_stream_h
#include <aw/io/input_buffer.h>
#include <aw/types/traits/basic_traits.h>

namespace aw {
namespace io {
/*!
 * Provides interface for sequential character streams.
 */
struct input_stream {
	virtual ~input_stream() = default;

	bool eof() const
	{
		return buffer->eof();
	}

	/*!
	 * Get byte at current position
	 * Equivalent to: *stream_iter
	 */
	bool peek(char& c) const
	{
		return buffer->peek(c);
	}

	/*!
	 * Get byte at current and advance stream
	 * Equivalent to: *stream_iter++
	 */
	bool get(char& c)
	{
		return buffer->get(c);
	}

	/*!
	 * Advance stream and get byte at next position
	 * Equivalent to: *++stream_iter
	 */
	bool next(char& c)
	{
		buffer->get(c);
		return peek(c);
	}

	/*! Read \a count bytes to buffer \a buf. */
	size_t read(char* buf, size_t count)
	{
		return buffer->read(buf, count);
	}

	/*! Read a trivially copyable object */
	template<typename T>
	bool read(T& object)
	{
		static_assert(aw::is_trivially_copyable<T>,
		              "T must be trivially copyable.");
		size_t cnt = read(reinterpret_cast<char*>(&object), sizeof(object));
		return cnt == sizeof(object);
	}

	bool read_until(std::string& s, char delim)
	{
		s.clear();
		return buffer->scan(s, delim);
	}

	/*! Advance position by \a characters */
	size_t skip(size_t count)
	{
		return buffer->skip(count);
	}

	size_t position() const
	{
		return buffer->position();
	}

protected:
	input_stream() = default;
	void init_buffer(input_buffer& buffer)
	{
		this->buffer = &buffer;
	}

private:
	input_buffer* buffer;
};



struct input_stream_iterator {
	using traits = std::char_traits<char>;

	using iterator_category = std::input_iterator_tag;
	using value_type        = traits::int_type;
	using reference         = value_type&;
	using pointer           = value_type*;

	input_stream_iterator()
	{
		cur = traits::eof();
	}

	input_stream_iterator(input_stream& stream)
		: stream{&stream}
	{
		char c;
		if (stream.peek(c))
			cur = traits::to_int_type(c);
		else
			cur = traits::eof();
	}

	input_stream_iterator(input_stream_iterator const&) = default;

	~input_stream_iterator() = default;

	value_type& operator*()
	{
		return cur;
	}

	value_type const& operator*() const
	{
		return cur;
	}

	value_type* operator->()
	{
		return &cur;
	}

	value_type const* operator->() const
	{
		return &cur;
	}

	input_stream_iterator operator++(int)
	{
		char c;
		if (stream->get(c))
			cur = traits::to_int_type(c);
		else
			cur = traits::eof();
		return *this;
	}

	input_stream_iterator& operator++()
	{
		char c;
		if (stream->next(c))
			cur =  traits::to_int_type(c);
		else
			cur = traits::eof();
		return *this;
	}

	bool is_eof() const
	{
		return cur == traits::eof();
	}

	bool operator==(input_stream_iterator const& iter) const
	{
		return is_eof() == iter.is_eof();
	}

private:
	input_stream* stream;
	value_type cur;
};

} // namespace io
} // namespace aw
#endif//aw_input_stream_h
