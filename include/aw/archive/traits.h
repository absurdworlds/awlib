/*
 * Copyright (C) 2017  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_traits_h
#define aw_archive_traits_h
#include <aw/meta/detect.h>
#include <aw/meta/list.h>
#include <aw/meta/substitute.h>
#include <aw/types/traits/is_container.h>
#include <aw/types/traits/pointer_traits.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/types/traits/query.h>

namespace aw {
namespace arc {
inline namespace v3 {

aw_define_member_exists( can_save )
aw_define_member_get( can_save )
aw_define_member_exists( can_load )
aw_define_member_get( can_load )

/*!
 * Provides a common way to query archive properties.
 */
template<typename Archive>
struct archive_traits {
	static constexpr bool can_save = class_member::can_save::get_value<Archive>( false );
	static constexpr bool can_load = class_member::can_load::get_value<Archive>( false );
};


enum class object_kind {
	unknown,
	arithmetic,
	string,
	structure,
	container,
};

template<typename T>
constexpr object_kind kind_of = [] {
	if constexpr(is_string<T>)
		return object_kind::string;
	if constexpr(is_basic_container<T>)
		return object_kind::container;
	if constexpr(is_class<T>)
		return object_kind::structure;
	if constexpr(is_arithmetic<T>)
		return object_kind::arithmetic;
	return object_kind::unknown;
}();




namespace _impl {
template<typename T, typename A>
using member_save     = decltype( declval<T const&>().save(declval<A&>()) );
template<typename T, typename A>
using member_load     = decltype( declval<T>().load(declval<A&>()) );
template<typename T, typename A>
using non_member_save = decltype( save(declval<A&>(),declval<T const&>()) );
template<typename T, typename A>
using non_member_load = decltype( load(declval<A&>(),declval<T&>()) );

template<typename T, typename = void>
struct get_create_parameter_list {
	using type = meta::list<>;
};

template<typename T>
struct get_create_parameter_list<
	T,
	void_t<typename T::create_parameters>
> {
	using type = meta::substitute<meta::list,typename T::create_parameters>;
};
} // namespace _impl

template<typename T, typename A>
constexpr bool has_member_save = is_detected<_impl::member_save, T, A>;
template<typename T, typename A>
constexpr bool has_member_load = is_detected<_impl::member_load, T, A>;

template<typename T, typename A>
constexpr bool has_non_member_save = is_detected<_impl::non_member_save, T, A>;
template<typename T, typename A>
constexpr bool has_non_member_load = is_detected<_impl::non_member_load, T, A>;

template<typename T>
using get_create_parameters = typename _impl::get_create_parameter_list<T>::type;
} // inline namespace v3
} // namespace arc
} // namespace aw
#endif//aw_archive_traits_h
