/*
 * Copyright (C) 2018  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_tempflag_h
#define aw_utility_tempflag_h
#include <chrono>
namespace aw {
/*!
 * Temporal flag — a flag that is set only for specified
 * period of time (i.e. resets itself after duration passes).
 */
struct tmpflag {
	using clock_type = std::chrono::steady_clock;
	using duration   = clock_type::duration;
	using time_point = clock_type::time_point;

	/*! Flag is constructed in an "off" state */
	tmpflag() = default;
	/*! Flag is constructed in an "on" state */
	tmpflag( duration dur )
	{
		set(dur);
	}

	tmpflag(tmpflag const&) = default;

	/*!
	 * Flag is set to true.
	 * It will stay true for specified duration.
	 */
	void set( duration dur ) noexcept
	{
		_expires = clock_type::now() + dur;
	}

	/*!
	 * Reset the flag to the false state.
	 */
	void reset( ) noexcept
	{
		_expires = time_point{};
	}

	/*!
	 * Returns true if flag was set and duration hasn't expired yet.
	 */
	explicit operator bool() const noexcept
	{
		return _expires > clock_type::now();
	}

private:
	time_point _expires;
};

inline bool operator==(tmpflag const& f, bool b) { return bool(f) == b; }
inline bool operator==(bool b, tmpflag const& f) { return b == bool(f); }

inline bool operator!=(tmpflag const& f, bool b) { return bool(f) != b; }
inline bool operator!=(bool b, tmpflag const& f) { return b != bool(f); }
} // namespace aw
#endif//aw_utility_tempflag_h
