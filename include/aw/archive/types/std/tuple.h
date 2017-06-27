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
#include <tuple>
#include <aw/archive/archive_base.h>
namespace aw {
namespace arc {
inline namespace v3 {
namespace _impl {
template<typename Archive, typename Tuple, size_t...Is>
void tuple_save( Archive& arc, Tuple const& tuple, index_sequence<Is...> )
{
	(arc(std::to_string(Is), std::get<Is>(tuple)), ...);
}
template<typename Archive, typename Tuple, size_t...Is>
void tuple_load( Archive& arc, Tuple& tuple, index_sequence<Is...> )
{
	(arc(std::to_string(Is), std::get<Is>(tuple)), ...);
}
} // namespace _impl

template<typename Archive, typename...Ts>
void save( Archive& arc, std::tuple<Ts...> const& tuple)
{
	_impl::tuple_save( arc, tuple, make_index_sequence<sizeof...(Ts)>() );
}

template<typename Archive, typename...Ts>
void load( Archive& arc, std::tuple<Ts...> & tuple)
{
	_impl::tuple_load( arc, tuple, make_index_sequence<sizeof...(Ts)>() );
}
} // inline namespace v3
} // namespace arc
} // namespace aw
#endif//aw_archive_std_tuple
