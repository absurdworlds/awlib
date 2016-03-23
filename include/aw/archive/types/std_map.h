/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_types_map
#define aw_archive_types_map
#include <map>
#include <aw/archive/InputArchive.h>
#include <aw/archive/OutputArchive.h>
#include <aw/archive/types/std_pair.h>
namespace aw {
namespace arc {
namespace detail {
template <typename...Args> struct IsContainer<std::map<Args...>> : std::true_type{};
} // namespace detail

template<typename A, typename B>
void save(OutputArchive& arc, std::map<A,B> const& map)
{
	for (auto const& v : map)
		arc("", v);
}

template<typename A, typename B>
void load(InputArchive& arc, std::map<A,B>& map)
{
	using val_type = typename decltype(map)::value_type;
	map.clear();
	while (!arc.at_end())
		map.insert([&arc] {val_type v; arc("", v); return v;}());
}
} // namespace arc
} // namespace aw
#endif//aw_archive_types_map
