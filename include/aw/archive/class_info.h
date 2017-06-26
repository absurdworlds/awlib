/*
 * Copyright (C) 2017  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_class_info_h
#define aw_archive_class_info_h
#include <map>
#include <aw/types/string_view.h>
#include <aw/archive/traits.h>
#include <aw/utility/helpers/static_helpers.h>

namespace aw {
namespace arc {
inline namespace v3 {
template<typename Archive>
struct save_registry {
	using class_save = void(Archive&, void const*);
	using map = std::map<string_view, class_save*>;
	using class_map = static_object<map>;

	template<typename T>
	static void register_class()
	{
		auto& map_ref = class_map::instance();

		map_ref[T::type_name] = +[] (Archive& arc, void const* ptr) {
			auto tptr = reinterpret_cast<T const*>( ptr );
			if constexpr( has_member_save<T,Archive> )
				tptr->save( arc );
			else if constexpr( has_non_member_save<T,Archive> )
				save( arc, *tptr );
		};
	}

	static class_save* find_class(string_view name)
	{
		auto& map_ref = class_map::instance();
		auto it = map_ref.find(name);
		if (it == end(map_ref))
			return nullptr;
		return it->second;
	}
};

template<typename Archive>
struct load_registry {
	template<typename...Args>
	using class_load = void*(Archive&, Args...);
	template<typename...Args>
	using map = std::map<string_view, class_load<Args...>*>;
	template<typename...Args>
	using class_map = static_object<map<Args...>>;

	template<typename T, typename...Args>
	static void register_class_with_args(meta::list<Args...>)
	{
		auto& map_ref = class_map<Args...>::instance();
		map_ref[T::type_name] = +[] (Archive& arc, Args... args) {
			auto* tptr = new T(args...);
			if constexpr( has_member_load<T,Archive> )
				tptr->load( arc );
			else if constexpr( has_non_member_load<T,Archive> )
				load( arc, *tptr );
			return reinterpret_cast<void*>( tptr );
		};
	}

	template<typename T>
	static void register_class()
	{
		register_class_with_args<T>(get_create_parameters<T>{});
	}

	template<typename...Args>
	static class_load<Args...>* find_class(string_view name, meta::list<Args...>)
	{
		auto& map_ref = class_map<Args...>::instance();
		auto it = map_ref.find(name);
		if (it == end(map_ref))
			return nullptr;
		return it->second;
	}
};

namespace _impl {
template<typename Archive, typename T>
void register_class_info()
{
	//if constexpr( has_save<T,Archive> )
	if constexpr( archive_traits<Archive>::can_save )
		save_registry<Archive>::template register_class<T>();
	//if constexpr( has_load<T,Archive> )
	if constexpr( archive_traits<Archive>::can_load )
		load_registry<Archive>::template register_class<T>();
}
} // namespace _impl

template<typename Archive, typename T>
using register_class_info = call_in_ctor<_impl::register_class_info<Archive,T>>;


/*! Required to ensure that ADL finds all overloads of adl_magic */
struct adl_tag {};

#define aw_register_archive( Archive ) \
template<typename T> \
force_instantiation<register_class_info<Archive, T>> adl_magic(T*, Archive*, adl_tag);

template<typename T> void adl_magic(T*, int, adl_tag) {}
template<typename T>
void invoke_register_class()
{
	adl_magic(static_cast<T*>(nullptr), 0, adl_tag{});
}

/*!
 * Polymorphic classes must be registered to enable them to be serialized by archives.
 *
 * Class must have members
 * `constexpr string_view type_name = <fully qualified class name>`, and
 * `virtual string_view class_name() const`, which returns `type_name`.
 *
 * TODO: remove type_name when C++ finally gets an official way to get fully qualified
 * name of a type.
 */
#define aw_register_class( T ) \
template struct call_on_init<invoke_register_class<T>>;
} // inline namespace v3
} // namespace arc
} // namespace aw
#endif//aw_archive_class_info_h
