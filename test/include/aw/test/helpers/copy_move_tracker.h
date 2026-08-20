/*
 * Copyright (C) 2026  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_copy_move_tracker_h
#define aw_test_copy_move_tracker_h
#include <cstddef>
#include <type_traits>
#include <utility>

namespace aw::test {
/*!
 * A helper type which keeps track of how it was passed around. Intended for
 * testing copy and move constructors/assignment operators of container types.
 *
 * The counters travel with the value: copying bumps \a n_copies, moving bumps
 * \a n_moves and resets the counters of the source, which also records how
 * many times it was moved from in \a n_moved_from.
 *
 * \note
 * Has the same `noexcept` specifier as \a T, so tests would pick the same
 * code path as for \a T itself.
 */
template<typename T>
struct copy_move_tracker {
	T value;
	size_t n_copies = 0;
	size_t n_moves  = 0;
	size_t n_moved_from = 0;

	copy_move_tracker(T value)
		noexcept(std::is_nothrow_move_constructible_v<T>)
		: value(std::move(value))
	{}

	copy_move_tracker(const copy_move_tracker& other)
		noexcept(std::is_nothrow_copy_constructible_v<T>)
		: value(other.value)
		, n_copies(other.n_copies + 1)
		, n_moves(other.n_moves)
	{
	}

	copy_move_tracker(copy_move_tracker&& other)
		noexcept(std::is_nothrow_move_constructible_v<T>)
		: value(std::move(other.value))
		, n_copies(std::exchange(other.n_copies, 0))
		, n_moves(std::exchange(other.n_moves, 0) + 1)
	{
		++other.n_moved_from;
	}

	copy_move_tracker& operator=(const copy_move_tracker& other)
		noexcept(std::is_nothrow_copy_assignable_v<T>)
	{
		value = other.value;
		n_copies = other.n_copies + 1;
		n_moves = other.n_moves;
		return *this;
	}

	copy_move_tracker& operator=(copy_move_tracker&& other)
		noexcept(std::is_nothrow_move_assignable_v<T>)
	{
		value = std::move(other.value);
		n_copies = std::exchange(other.n_copies, 0);
		n_moves = std::exchange(other.n_moves, 0) + 1;
		++other.n_moved_from;
		return *this;
	}

	// silences the clang-tidy warning
	[[clang::reinitializes]]
	void unmove() {}
};
} // namespace aw::test
#endif//aw_test_copy_move_tracker_h
