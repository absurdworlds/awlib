/*
 * Copyright (C) 2026  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_counted_h
#define aw_test_counted_h
#include <string>
#include <utility>

namespace aw::test {
/*!
 * Element type which keeps a count of how many instances are alive, so that
 * a container which loses an element, destroys one twice, or never destroys
 * it at all reports a mismatch instead of corrupting memory quietly.
 *
 * The payload is a heap-allocating string, which makes the failure loud: a
 * destructor run over storage that was never constructed frees a garbage
 * pointer, where a trivially destructible element would pass unnoticed.
 *
 * \note \a live is shared, so a test has to reset it before use.
 */
struct counted {
	static inline int live = 0;

	//! Payload long enough to be heap-allocated rather than stored inline
	static std::string payload(char c = 'x')
	{
		return std::string(64, c);
	}

	counted() : counted{payload()} {}

	explicit counted(std::string val)
		: value{std::move(val)}
	{
		++live;
	}

	counted(counted const& other)
		: value{other.value}
	{
		++live;
	}

	counted(counted&& other) noexcept
		: value{std::move(other.value)}
	{
		++live;
	}

	// assignment neither creates nor destroys an instance
	counted& operator=(counted const&) = default;
	counted& operator=(counted&&) noexcept = default;

	~counted()
	{
		--live;
	}

	std::string value;
};
} // namespace aw::test
#endif//aw_test_counted_h
