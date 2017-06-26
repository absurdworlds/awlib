/*
 * Copyright (C) 2017  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_base_h
#define aw_archive_base_h
#include <aw/archive/class_info.h>

namespace aw {
namespace arc {
inline namespace v3 {

template<typename Derived>
struct output_archive {
	static constexpr bool can_save = true;

	template<typename T>
	void operator()(string_view name, T const& value)
	{
		archive(name, value);
	}

	template<typename T>
	void operator()(T const& value)
	{
		using namespace std::string_view_literals;
		archive(""sv, value);
	}

	template<typename T>
	void archive(string_view name, T const& value)
	{
		if constexpr(is_pointer_type<T>) {
			using object_type = typename pointer_traits<T>::element_type;
			if constexpr(is_polymorphic<object_type>)
				polymorphic_save(name, *value);
		} else {
			constexpr auto kind = kind_of<T>;
			derived().start_save(kind, name);
			do_save(value);
			derived().end_save(kind, name);
		}
	}

private:
	template<typename T>
	void polymorphic_save(string_view name, T const& value)
	{
		auto type = value.class_name();
		auto save = save_registry<Derived>::find_class(type);
		auto ptr  = reinterpret_cast<void const*>(&value);

		derived().start_save_virtual(type, name);
		save( derived(), ptr );
		derived().end_save_virtual(type, name);
	}

	template<typename T>
	void do_save(T const& value)
	{
		if constexpr( Derived::template is_directly_serializable<T> )
			derived().save(value);
		else if constexpr( has_non_member_save<T,Derived> )
			save(derived(), value);
		else if constexpr( has_member_save<T,Derived> )
			value.save(derived());
	}

	Derived& derived() { return *static_cast<Derived*>(this); }
};

template<typename Derived>
struct input_archive {
	static constexpr bool can_load = true;

	template<typename T>
	void operator()(string_view name, T& value)
	{
		unarchive(name, value);
	}

	template<typename T>
	void operator()(T& value)
	{
		using namespace std::string_view_literals;
		unarchive(""sv, value);
	}

	template<typename T>
	void unarchive(string_view name, T& value)
	{
		if constexpr(is_pointer_type<T>) {
			using object_type = typename pointer_traits<T>::element_type;
			if constexpr(is_polymorphic<object_type>)
				value = polymorphic_load<object_type>(name);
		} else {
			constexpr auto kind = kind_of<T>;
			derived().start_load(kind, name);
			do_load(value);
			derived().end_load(kind, name);
		}
	}

private:
	template<typename T>
	T* polymorphic_load(string_view name)
	{
		auto type = derived().start_load_virtual(name);
		auto load = load_registry<Derived>::find_class(type, typename T::create_parameters{});
		auto ptr  = load( derived() );
		derived().end_load_virtual(name);
		return reinterpret_cast<T*>(ptr);
	}

	template<typename T>
	void do_load(T& value)
	{
		if constexpr( Derived::template is_directly_serializable<T> )
			derived().load(value);
		else if constexpr( has_non_member_load<T,Derived> )
			load(derived(), value);
		else if constexpr( has_member_load<T,Derived> )
			value.load(derived());
	}

	Derived& derived() { return *static_cast<Derived*>(this); }
};



} // inline namespace v3
} // namespace arc
} // namespace aw
#endif//aw_archive_base_h
