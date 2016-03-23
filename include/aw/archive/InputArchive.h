/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_InputArchive_base
#define aw_InputArchive_base
#include <tuple>
#include <aw/archive/Archive.h>
namespace aw {
AW_DECLARE_HAS_MEMBER(load);
AW_DECLARE_HAS_NON_MEMBER(load);
namespace arc {
inline namespace v2 {
/*!
 * Base class for Input Archive.
 * TODO: description
 */
struct InputArchive {
	template<class T, EnableIf<IsPrimitive<T>> = dummy>
	void operator()(char const* name, T& value)
	{
		value_start(name);
		read(value);
		value_end(name);
	}

	template<class T, EnableIf<IsObject<T>> = dummy>
	void operator()(char const* name, T& value)
	{
		object_start(name);
		object_read(value);
		object_end(name);
	}

	template<class T, EnableIf<IsContainer<T>> = dummy>
	void operator()(char const* name, T& value)
	{
		list_start(name);
		object_read(value);
		list_end(name);
	}

	template<class T>
	void operator()(char const* name, T*& value)
	{
		auto classDef = polymorphic_start(name, value);
		if (classDef.isAbstract())
			return;

		value = classDef.create();

		polymorphic_read(value);
		object_end(name);
	}

	template<class T, typename... Args>
	void operator()(char const* name, T*& value, std::tuple<Args...>&& args)
	{
		auto classDef = polymorphic_start(name, value);
		if (classDef.isAbstract())
			return;

		using Tuple = std::tuple<Args...>;
		constexpr auto size  = sizeof...(Args);
		constexpr auto index = std::make_index_sequence<size>{};

		construct(value, classDef, std::forward<Tuple&&>(args), index);

		polymorphic_read(value);
		object_end(name);
	}

public:
	virtual bool list_atend() = 0;
private:
	/* Objects */
	virtual void object_start(char const* name) = 0;
	virtual void object_end(char const* name) = 0;

	virtual void list_start(char const* name) = 0;
	virtual void list_end(char const* name) = 0;

	template<typename T, EnableIf<has_member_load<T,InputArchive>> = dummy>
	void object_read(T& value) { value.load(*this); }

	template<typename T, EnableIf<has_non_member_load<InputArchive,T>> = dummy>
	void object_read(T& value) { load(*this, value); }

	/* Polymorphic */
	virtual char const* polymorphic_type() = 0;

	template<class T, typename ClassDef, typename Tuple, std::size_t... I>
	void construct(T*& v, ClassDef& c, Tuple&& a, std::index_sequence<I...>)
	{
		v = c.create(std::get<I>(std::forward<Tuple&&>(a))...);
	}

	template<class T>
	auto polymorphic_start(char const* name, T*) -> typename T::ClassDef&
	{
		static_assert(is_polymorphic<T>, "Pointer must be of polymorphic type!");

		object_start(name);
		auto type = polymorphic_type();

		auto classDef = T::ClassDef::findClassDef(type);

		assert(classDef && "Could not find classdef!");

		return *classDef;
	}

	template<class T>
	void polymorphic_read(T* value) { value->load(*this); }

	/* Primitive types */
	virtual void value_start(char const* name) = 0;
	virtual void value_end(char const* name)   = 0;

	virtual void read(char& value) = 0;
	virtual void read(std::string& value) = 0;

	virtual void read(i8& value) = 0;
	virtual void read(u8& value) = 0;

	virtual void read(i16& value) = 0;
	virtual void read(u16& value) = 0;

	virtual void read(i32& value) = 0;
	virtual void read(u32& value) = 0;

	virtual void read(i64& value) = 0;
	virtual void read(u64& value) = 0;

	virtual void read(f32& value) = 0;
	virtual void read(f64& value) = 0;


	/* load() declarations */
	template<class T>
	friend void load(InputArchive& arc, T&);

	friend void load(InputArchive& arc, char& value)        { arc.read(value); }
	friend void load(InputArchive& arc, std::string& value) { arc.read(value); }

	friend void load(InputArchive& arc, i8& value) { arc.read(value); }
	friend void load(InputArchive& arc, u8& value) { arc.read(value); }

	friend void load(InputArchive& arc, i16& value) { arc.read(value); }
	friend void load(InputArchive& arc, u16& value) { arc.read(value); }

	friend void load(InputArchive& arc, i32& value) { arc.read(value); }
	friend void load(InputArchive& arc, u32& value) { arc.read(value); }

	friend void load(InputArchive& arc, i64& value) { arc.read(value); }
	friend void load(InputArchive& arc, u64& value) { arc.read(value); }

	friend void load(InputArchive& arc, f32& value) { arc.read(value); }
	friend void load(InputArchive& arc, f64& value) { arc.read(value); }
};
} // inline namespace v2
} // namespace arc
} // namespace aw
#endif//aw_InputArchive_base
