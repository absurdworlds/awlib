/*
 * Copyright (C) 2026  Hedede <dev@hedede.me>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_unsafe_move_h
#define aw_test_unsafe_move_h
namespace aw::test {
/*!
 * Movable type whose move operations aren't `noexcept`.
 * Intended for testing behavior of containers and wrappers, that
 * must not advertise themselves as `noexcept` if a wrapped type
 * can throw.
 *
 * \note Does not actually throw.
 */
struct unsafe_move {
	unsafe_move() = default;
	// NOLINTBEGIN(performance-noexcept-move-constructor): not being noexcept is the point
	unsafe_move(unsafe_move&&) {}
	unsafe_move& operator=(unsafe_move&&) { return *this; }
	// NOLINTEND(performance-noexcept-move-constructor)
};
} // namespace aw::test
#endif//aw_test_unsafe_move_h
