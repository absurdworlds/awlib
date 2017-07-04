/*
 * Copyright (C) 2017  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_range_shared_h
#define aw_archive_range_shared_h
namespace aw {
namespace arc {
inline namespace v3 {
/*
 * These are needed to select correct overload.
 * I think this solution is a lot nicer than SFINAE,
 * and it is better than renaming operator() to some "archive_range".
 */
template<typename Begin, typename End>
struct iterator_pair {
	Begin begin;
	End   end;
};


template<typename Begin, typename End>
struct const_iterator_pair {
	// static_assert( is_const_iterator<Begin> )
	Begin begin;
	End   end;
};

template<typename Begin, typename End>
iterator_pair(Begin, End)       -> iterator_pair<Begin, End>;
template<typename Begin, typename End>
const_iterator_pair(Begin, End) -> const_iterator_pair<Begin, End>;
} // inline namespace v3
} // namespace arc
} // namespace aw
#endif//aw_archive_range_shared_h
