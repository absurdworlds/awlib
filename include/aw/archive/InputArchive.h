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
namespace arc {
inline namespace v2 {
template<class T, class A> using member_load = decltype(std::declval<T>().load(std::declval<A&>()));
template<class T, class A> using non_member_load = decltype(load(std::declval<A&>(),std::declval<T&>()));
template<class T> constexpr auto has_member_load = is_detected<member_load, T, class InputArchive>;
template<class T> constexpr auto has_non_member_load = is_detected<non_member_load, T, class InputArchive>;

/*!
 * Base class for Input Archive.
 * TODO: description
 */
struct InputArchive {
	template<class T>
	auto operator()(char const* name, T& value) -> void_if<!is_pointer<T>>
	{
		start(kind_of<T>, name);
		process(value);
		end(kind_of<T>, name);
	}

	template<class T, typename... Args>
	void operator()(char const* name, T*& value, std::tuple<Args...>&& args)
	{
		using Tuple = std::tuple<Args...>;
		constexpr auto size = sizeof...(Args);
		constexpr auto index = std::make_index_sequence<size>{};
		unpack(name, value, std::forward<Tuple>(args), index);
	}

	template<class T, typename... Args>
	void operator()(char const* name, T*& value, Args&&... args)
	{
		polymorphic(name, value, std::forward<Args>(args)...);
	}

public:
	virtual bool at_end() = 0;

private:

	/* Polymorphic */
	virtual char const* read_type() = 0;

	template<class T, typename Tuple, std::size_t... I>
	void unpack(char const* n, T*& v, Tuple&& a, std::index_sequence<I...>)
	{
		polymorphic(n, v, std::get<I>(std::forward<Tuple>(a))...);
	}

	template<typename T, typename... Args>
	void polymorphic(char const* name, T*& value, Args&&... args)
	{
		static_assert(is_polymorphic<T>, "Pointer must be of polymorphic type!");

		start(kind_of<T*>, name);

		auto type = read_type();

		auto classDef = T::ClassDef::findClassDef(type);

		assert(classDef && "Could not find classdef! Forgot to register class?");

		if (classDef->isAbstract())
			return;

		value = classDef->create(std::forward<Args>(args)...);

		process(value);

		end(kind_of<T>, name);
	}

	template<typename T>
	auto process(T& value) -> void_if<has_member_load<T>>
	{
		value.load(*this);
	}

	template<typename T>
	auto process(T& value) -> void_if<has_non_member_load<T>>
	{
		load(*this, value);
	}

	template<class T>
	void process(T*& value)
	{
		value->load(*this);
	}

	/* Objects */
	virtual void start(ObjectKind kind, char const* name) = 0;
	virtual void end(ObjectKind kind, char const* name) = 0;

	/* Primitive types */
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
