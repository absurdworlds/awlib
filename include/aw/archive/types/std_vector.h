/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_vector
#define aw_archive_vector
#include <vector>
#include <aw/archive/InputArchive.h>
#include <aw/archive/OutputArchive.h>
namespace aw {
namespace arc {
inline namespace v2 {
namespace _impl {
template <typename...Args> struct IsContainer<std::vector<Args...>> : std::true_type{};
} // namespace _impl

template<typename T>
void save(OutputArchive& arc, std::vector<T> const& vec)
{
	for (auto const& v : vec)
		arc("value", v);
}

template<typename T>
void load(InputArchive& arc, std::vector<T>& vec)
{
	vec.clear();
	while (!arc.at_end())
		vec.push_back([&arc] {T v; arc("value", v); return v;} ());
}
} // inline namespace v2
} // namespace arc
} // namespace aw
#endif//aw_archive_vector
