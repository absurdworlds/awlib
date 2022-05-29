/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_pair_h
#define aw_archive_pair_h
#include <utility>
namespace aw {
namespace arc {
inline namespace v3 {
template<typename OutputArchive, typename A, typename B>
void save(OutputArchive& arc, std::pair<A, B> const& pair)
{
	arc(pair.first,  "first");
	arc(pair.second, "second");
}

template<typename InputArchive, typename A, typename B>
void load(InputArchive& arc, std::pair<A, B>& pair)
{
	arc(pair.first,  "first");
	arc(pair.second, "second");
}
} // inline namespace v3
} // namespace arc
} // namespace aw
#endif//aw_archive_pair_h
