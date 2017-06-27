/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_std_vector_h
#define aw_archive_std_vector_h
#include <vector>
#include <aw/archive/archve_base.h>
namespace aw {
namespace arc {
inline namespace v3 {
template<typename Archive, typename T>
void save(Archive& arc, std::vector<T> const& vec)
{
	arc("size", vec.size());
	for (auto const& v : vec)
		arc( v );
}

template<typename Archive, typename T>
void load(Archive& arc, std::vector<T>& vec)
{
	size_t size;
	arc("size", size);

	vec.clear();
	vec.resize(size);
	for (auto& v : vec)
		arc( v );
}
} // inline namespace v3
} // namespace arc
} // namespace aw
#endif//aw_archive_std_vector_h
