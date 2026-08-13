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
static_assert(false, "Do not include this file directly.");
#endif

namespace aw::io {
/*! Hack to access protected members of std::streambuf */
struct streambuf_adapt : private std::streambuf {
	streambuf_adapt(std::streambuf* buf)
		: buf{buf}
	{}

	explicit operator bool() const
	{
		return bool(buf);
	}

	void advance(ptrdiff_t dist)
	{
		(buf->*(&streambuf_adapt::gbump))(dist);
	}

	char* begin()
	{
		return (buf->*(&streambuf_adapt::eback))();
	}

	char* ptr()
	{
		return (buf->*(&streambuf_adapt::gptr))();
	}

	char* end()
	{
		return (buf->*(&streambuf_adapt::egptr))();
	}

	bool fill_buffer()
	{
		using traits = std::streambuf::traits_type;
		return (buf->*(&streambuf_adapt::underflow))() != traits::eof();
	}

	std::streambuf* buf;
};

/*!
 * A placeholder streambuf that holds no characters.
 *
 * istream_adapter parks one of these in the wrapped stream while it
 * owns the real buffer, to guard against potential reads into the
 * wrapped stream.
 */
struct streambuf_dummy : std::streambuf {
	using std::streambuf::traits_type;
	using int_type = traits_type::int_type;

	int_type overflow( int_type ) override { return traits_type::eof(); }
	int_type underflow( ) override { return traits_type::eof(); }
};
} // namespace aw::io
