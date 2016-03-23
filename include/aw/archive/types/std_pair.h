/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_pair
#define aw_archive_pair
#include <utility>
#include <aw/archive/InputArchive.h>
#include <aw/archive/OutputArchive.h>
namespace aw {
namespace arc {
inline namespace v2 {
template<typename A, typename B>
void save(OutputArchive& arc, std::pair<A, B> const& pair)
{
	arc("first",  pair.first);
	arc("second", pair.second);
}

template<typename A, typename B>
void load(InputArchive& arc, std::pair<A, B>& pair)
{
	arc("first",  pair.first);
	arc("second", pair.second);
}
} // inline namespace v2
} // namespace arc
} // namespace aw
#endif//aw_archive_pair
