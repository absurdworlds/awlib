/*
 * Copyright (C) 2026  Hedede <dev@hedede.me>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_throwing_h
#define aw_test_throwing_h
namespace aw::test {
/*!
 * Element type which throws on demand, so that it can interrupt an
 * operation completed part-way through, for testing expection safety.
 *
 * Construction throws \a error while \a armed, which lets a test arm the
 * type around the single operation it wants to interrupt. Moving never
 * throws, so a container may still rely on a nothrow move.
 *
 * \a live counts instances which were actually constructed, so that
 * it's possible to detect a value being destroyed twice.
 *
 * \note \a live and \a armed are shared, so a test has to reset them
 *       before use.
 */
struct throwing {
	static inline int  live  = 0;
	static inline bool armed = false;

	//! Thrown by a construction which was armed to fail
	struct error {};

	throwing(int id = 0)
		: id{id}
	{
		if (armed)
			throw error{};
		++live;
	}

	throwing(throwing const& other)
	{
		if (armed)
			throw error{};
		id = other.id;
		++live;
	}

	throwing(throwing&& other) noexcept
	{
		id = other.id;
		++live;
	}

	// assignment neither creates nor destroys an instance
	throwing& operator=(throwing const&) = default;
	throwing& operator=(throwing&&) noexcept = default;

	~throwing()
	{
		--live;
	}

	int id;
};
} // namespace aw::test
#endif//aw_test_throwing_h
