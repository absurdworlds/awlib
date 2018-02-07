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

#if defined(AW_IO_ADAPT_USE_STEAL)
#include <aw/meta/steal.h>
namespace aw {
namespace steal {
struct gbump_tag {
	using type = void (std::streambuf::*)(std::streambuf::int_type);
	friend constexpr type member(gbump_tag);
};

struct underflow_tag {
	using type = int (std::streambuf::*)();
	friend constexpr type member(underflow_tag);
};

struct egptr_tag {
	using type = char* (std::streambuf::*)() const;
	friend constexpr type member(egptr_tag);
};

struct gback_tag {
	using type = char* (std::streambuf::*)() const;
	friend constexpr type member(gback_tag);
};

struct gptr_tag {
	using type = char* (std::streambuf::*)() const;
	friend constexpr type member(gptr_tag);
};

template struct steal<gbump_tag,     &std::streambuf::gbump>;
template struct steal<underflow_tag, &std::streambuf::underflow>;
template struct steal<gback_tag,     &std::streambuf::eback>;
template struct steal<gptr_tag,      &std::streambuf::gptr>;
template struct steal<egptr_tag,     &std::streambuf::egptr>;
} // namespace steal
namespace io::_impl {
steal::gbump_tag     gbump;
steal::underflow_tag underflow;
steal::egptr_tag     egptr;
steal::gback_tag     gback;
steal::gptr_tag      gptr;
} // namespace io::_impl
} // namespace aw
#endif//AW_IO_ADAPT_USE_STEAL

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
#if defined(AW_IO_ADAPT_USE_STEAL)
		(buf->*member(_impl::gbump))(dist);
#else
		(buf->*(&streambuf_adapt::gbump))(dist);
#endif
	}

	char* begin()
	{
#if defined(AW_IO_ADAPT_USE_STEAL)
		return (buf->*member(_impl::gback))();
#else
		return (buf->*(&streambuf_adapt::eback))();
#endif
	}

	char* ptr()
	{
#if defined(AW_IO_ADAPT_USE_STEAL)
		return (buf->*member(_impl::gptr))();
#else
		return (buf->*(&streambuf_adapt::gptr))();
#endif
	}

	char* end()
	{
#if defined(AW_IO_ADAPT_USE_STEAL)
		return (buf->*member(_impl::egptr))();
#else
		return (buf->*(&streambuf_adapt::egptr))();
#endif
	}

	bool fill_buffer()
	{
		using traits = std::streambuf::traits_type;
#if defined(AW_IO_ADAPT_USE_STEAL)
		return (buf->*member(_impl::underflow))() != traits::eof();
#else
		return (buf->*(&streambuf_adapt::underflow))() != traits::eof();
#endif
	}

	std::streambuf* buf;
};

/*! A dummy streambuf that does nothing */
struct streambuf_dummy : std::streambuf {
	using std::streambuf::traits_type;
	using int_type = traits_type::int_type;

	int_type overflow( int_type c ) override { return c; }
	int_type underflow( ) override { return traits_type::to_int_type(' '); }
};
} // namespace aw::io
