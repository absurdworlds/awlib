/*
 * Copyright (C) 2017  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_map_shared_h
#define aw_archive_map_shared_h
#include <utility>
#include <aw/meta/substitute.h>
#include <aw/utility/iterators/wrapper.h>
#include <aw/archive/types/std/pair.h>
namespace aw {
namespace arc {
inline namespace v3 {
/*!
 * Allows archive implementations to overload for this type,
 * if different structure/syntax for dictionaries is preferred.
 */
template<typename Key, typename Value>
struct key_value_pair : std::pair<Key,Value> {
	using std::pair<Key,Value>::pair;
	key_value_pair(std::pair<Key,Value> const& pair)
		: std::pair<Key,Value>{pair}
	{}
};

template<typename Iterator>
using to_kv_pair  = meta::substitute<
	key_value_pair,
	typename Iterator::value_type
>;

template<typename T>
auto kv_begin(T const& range)
{
	using iter = typename T::const_iterator;
	return aw::iter::wrapper<iter, to_kv_pair<iter>>{ range.begin() };
}

template<typename T>
auto kv_end(T const& range)
{
	using iter = typename T::const_iterator;
	return aw::iter::wrapper<iter, to_kv_pair<iter>>{ range.end() };
}

} // inline namespace v3
} // namespace arc
} // namespace aw
#endif//aw_archive_map_shared_h
