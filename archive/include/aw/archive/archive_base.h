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
#include <aw/types/optional.h>
#include <aw/archive/class_info.h>
#include <aw/archive/types/range_shared.h>

namespace aw {
namespace arc {
inline namespace v3 {
using opt_string = optional<string_view>;

template<typename Derived>
struct output_archive {
	static constexpr bool can_save = true;

	template<typename T>
	void operator()(T const& value, opt_string name = nullopt)
	{
		archive(value, name);
	}

	template<typename Iterator, typename Sentinel>
	void operator()(const_iterator_pair<Iterator,Sentinel> range, opt_string name = nullopt)
	{
		start_save_array(derived(), name);
		while (range.begin != range.end)
			archive( *range.begin++ );
		end_save_array(derived(), name);
	}

	template<typename T>
	void archive(T const& value, opt_string name = nullopt)
	{
		if constexpr(is_pointer_type<T>)
			save_pointer( value, name );
		else if constexpr( is_directly_serializable<T,Derived> )
			derived().save( value, name );
		else
			save_object( value, name );
	}

private:
	template<typename T>
	void save_pointer(T const& value, opt_string name = nullopt)
	{
		using object_type = typename pointer_traits<T>::element_type;
		if constexpr(is_polymorphic<object_type>)
			save_virtual(*value, name);
	}

	template<typename T>
	void save_virtual(T const& value, opt_string name = nullopt)
	{
		auto type = value.class_name();
		auto save = save_registry<Derived>::find_class(type);
		auto ptr  = reinterpret_cast<void const*>(&value);

		start_save_virtual(derived(), type, name);
		save( derived(), ptr );
		end_save_virtual(derived(), name);
	}

	template<typename T>
	void save_object(T const& value, opt_string name = nullopt)
	{
		start_save_object(derived(), name);
		call_save( derived(), value );
		end_save_object(derived(), name);
	}


	Derived& derived() { return *static_cast<Derived*>(this); }
};

template<typename Derived>
struct input_archive {
	static constexpr bool can_load = true;

	template<typename T>
	explicit operator T()
	{
		using namespace std::string_view_literals;
		T temp; unarchive(temp);
		return temp;
	}

	template<typename T>
	void operator()(T& value, opt_string name = nullopt)
	{
		unarchive(value, name);
	}

	template<typename Iterator, typename Sentinel>
	void operator()(iterator_pair<Iterator,Sentinel> range, opt_string name = nullopt)
	{
		start_load_array(derived(), name);
		while (range.begin != range.end)
			unarchive( *range.begin++ );
		end_load_array(derived(), name);
	}

	template<typename T>
	void unarchive(T& value, opt_string name = nullopt)
	{
		if constexpr(is_pointer_type<T>)
			load_pointer(value, name);
		else if constexpr( is_directly_serializable<T,Derived> )
			derived().load(value, name);
		else
			load_object(value, name);
	}

private:
	template<typename T>
	void load_pointer(T& value, opt_string name = nullopt)
	{
		using object_type = typename pointer_traits<T>::element_type;
		if constexpr(is_polymorphic<object_type>)
			value = load_virtual<object_type>(name);
	}

	template<typename T>
	T* load_virtual(opt_string name = nullopt)
	{
		auto params = typename T::create_parameters{};
		auto type = start_load_virtual(derived(), name);
		auto load = load_registry<Derived>::find_class(type, params);
		auto ptr  = load( derived() );
		end_load_virtual(derived(), name);
		return reinterpret_cast<T*>(ptr);
	}

	template<typename T>
	void load_object(T& value, opt_string name = nullopt)
	{
		start_load_object(derived(), name);
		call_load(derived(), value);
		end_load_object(derived(), name);
	}

	Derived& derived() { return *static_cast<Derived*>(this); }
};

template<typename Archive>
void start_save_virtual(Archive& arc, string_view type, opt_string name = nullopt) { }
template<typename Archive>
void end_save_virtual(Archive& arc, opt_string name = nullopt) { }

template<typename Archive>
std::string start_load_virtual(Archive& arc, opt_string name = nullopt) { return {}; }
template<typename Archive>
void end_load_virtual(Archive& arc, opt_string name = nullopt) { }

template<typename Archive>
void start_save_object(Archive& arc, opt_string name = nullopt) { }
template<typename Archive>
void end_save_object(Archive& arc, opt_string name = nullopt) { }

template<typename Archive>
void start_load_object(Archive& arc, opt_string name = nullopt) { }
template<typename Archive>
void end_load_object(Archive& arc, opt_string name = nullopt) { }

template<typename Archive>
void start_save_array(Archive& arc, opt_string name = nullopt) { }
template<typename Archive>
void end_save_array(Archive& arc, opt_string name = nullopt) { }

template<typename Archive>
void start_load_array(Archive& arc, opt_string name = nullopt) { }
template<typename Archive>
void end_load_array(Archive& arc, opt_string name = nullopt) { }

} // inline namespace v3
} // namespace arc
} // namespace aw
#endif//aw_archive_base_h
