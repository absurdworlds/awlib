/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_types_map_h
#define aw_archive_types_map_h
#include <map>
#include <algorithm>
#include <aw/archive/types/std/vector.h>
#include <aw/archive/types/map_shared.h>
namespace aw {
namespace arc {
inline namespace v3 {

template<typename OutputArchive, typename Key, typename Value>
void save(OutputArchive& arc, std::map<Key,Value> const& map)
{
	arc.archive(map.size(), "size");
	arc( const_iterator_pair{kv_begin(map), kv_end(map)}, "elements" );
}

template<typename InputArchive, typename Key, typename Value>
void load(InputArchive& arc, std::map<Key,Value>& map)
{
	std::vector<key_value_pair<Key,Value>> vec;
	arc( vec );

	/*
	 * Because map can't be resize()d, I can't read the map same way
	 * as other containers (by reading the size, resizing containers,
	 * and passing that range to archive).
	 *
	 * This way is easier than implementing a special case for maps,
	 * and additionally, this is more efficient (at least with libstdc++)
	 */
	map.clear();
	std::move( begin(vec), end(vec), std::inserter(map,end(map)) );
}
} // inline namespace v3
} // namespace arc
} // namespace aw
#endif//aw_archive_types_map_j
