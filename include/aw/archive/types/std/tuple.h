/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_std_tuple
#define aw_archive_std_tuple
#include <aw/types/tuple.h>
#include <aw/archive/archive_base.h>
namespace aw {
namespace arc {
inline namespace v3 {
template<typename Archive, typename...Ts>
void save( Archive& arc, std::tuple<Ts...> const& tuple)
{
	for_each(arc, tuple);
}

template<typename Archive, typename...Ts>
void load( Archive& arc, std::tuple<Ts...> & tuple)
{
	for_each(arc, tuple);
}
} // inline namespace v3
} // namespace arc
} // namespace aw
#endif//aw_archive_std_tuple
