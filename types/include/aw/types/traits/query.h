/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_query_h
#define aw_traits_query_h
#include <aw/meta/void_t.h>

namespace aw {
#define aw_define_member_exists(name) \
namespace class_member::name { \
template<typename T, typename = void> \
constexpr bool exists = false; \
template<typename T> \
constexpr bool exists<T, void_t<decltype(T::name)>> = true; \
}

#define aw_define_member_get(name) \
namespace class_member::name { \
template<typename T> \
constexpr auto get_value = [] (auto default_value) \
{ \
	if constexpr(exists<T>) \
		return T::name; \
	return default_value; \
}; \
}

// #define aw_member_exists(class,name) ::aw::class_member::name::exists<class>;
} // namespace aw
#endif//aw_traits_query_h
