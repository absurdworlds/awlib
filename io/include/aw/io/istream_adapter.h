/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_istream_adapter_h
#define aw_istream_adapter_h
#include <aw/io/input_stream.h>
#include <istream>
#include <aw/io/bits/istream.h>
namespace aw {
namespace io {
/*! Adapter for std::streambuf */
struct istream_buffer : input_buffer {
	istream_buffer(std::streambuf* buf)
		: adapt{buf}
	{ }

	~istream_buffer() override
	{
		// tell underlying buffer that we read some characters from it
		adapt.advance(ptr() - begin());
	}

	void seekpos(size_t offset) override
	{
		adapt.buf->pubseekoff(offset, std::ios_base::beg, std::ios_base::in);
	}

	void seekend(size_t offset) override
	{
		adapt.buf->pubseekoff(offset, std::ios_base::end, std::ios_base::in);
	}

	void seekoff(ptrdiff_t offset) override
	{
		adapt.buf->pubseekoff(offset, std::ios_base::cur, std::ios_base::in);
	}

protected:
	bool fill_buffer() override
	{
		if (!adapt)
			return false;
		if (ptr() < end())
			return true;

		adapt.advance(ptr() - begin());

		if (!adapt.fill_buffer())
			return false;
		set_ptr(adapt.begin(), adapt.ptr(), adapt.end());
		return true;
	}

private:
	streambuf_adapt adapt;
};

/*! Adapter for istream */
struct istream_adapter : input_stream {
	/*!
	 * Construct istream_adapter from std::istream.
	 * \note
	 *    For duration of istream_adapter existance,
	 *    it takes full control of underlying buffer.
	 */
	istream_adapter(std::istream& parent)
		: parent{parent}, sb{parent.rdbuf()}, buffer{sb}
	{
		input_stream::init_buffer(buffer);
		static streambuf_dummy dummy;
		parent.rdbuf(&dummy);
	}

	virtual ~istream_adapter()
	{
		parent.rdbuf(sb);
	}

private:
	std::istream& parent;
	std::streambuf* sb;
	istream_buffer buffer;
};
} // namespace io
} // namespace aw
#endif//aw_istream_adapter_h
