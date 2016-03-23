/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_OutputArchive_base
#define aw_OutputArchive_base
#include <aw/archive/Archive.h>
namespace aw {
namespace arc {
inline namespace v2 {
template<class T, class A> using member_save = decltype(std::declval<T const&>().save(std::declval<A&>()));
template<class T, class A> using non_member_save = decltype(save(std::declval<A&>(),std::declval<T const&>()));
template<class T> constexpr auto has_member_save = is_detected<member_save, T, class OutputArchive>;
template<class T> constexpr auto has_non_member_save = is_detected<non_member_save, T, class OutputArchive>;
/*!
 * Base class for Output archive.
 * TODO: proper description
 */
struct OutputArchive {
	template<class T>
	auto operator()(char const* name, T const& value) -> void_if<!is_pointer<T>>
	{
		start(kind_of<T>, name);
		process(value);
		end(kind_of<T>, name);
	}

	template<class T>
	void operator()(char const* name, T const* value)
	{
		if (!value)
			return;

		if (value->classDef().isAbstract())
			return;

		auto type = value->classDef().className();
		start(kind_of<T*>, name, type);

		process(value);

		end(kind_of<T*>, name);
	}

private:
	virtual void start(ObjectKind kind, char const* name) = 0;
	virtual void start(ObjectKind kind, char const* name, char const* type) = 0;
	virtual void end(ObjectKind kind, char const* name) = 0;

	template<typename T>
	auto process(T const& value) -> void_if<has_member_save<T>>
	{
		value.save(*this);
	}

	template<typename T>
	auto process(T const& value) -> void_if<has_non_member_save<T>>
	{
		save(*this, value);
	}

	template<typename T>
	void process(T const*& value)
	{
		value->save(*this);
	}

	/* Basic types */
	virtual void write(char const& value)        = 0;
	virtual void write(std::string const& value) = 0;

	virtual void write(i8 const& value) = 0;
	virtual void write(u8 const& value) = 0;

	virtual void write(i16 const& value) = 0;
	virtual void write(u16 const& value) = 0;

	virtual void write(i32 const& value) = 0;
	virtual void write(u32 const& value) = 0;

	virtual void write(i64 const& value) = 0;
	virtual void write(u64 const& value) = 0;

	virtual void write(f32 const& value) = 0;
	virtual void write(f64 const& value) = 0;

	/* save() declarations */
	template<class T>
	friend void save(OutputArchive& arc, T const& value);

	friend void save(OutputArchive& arc, char const value) { arc.write(value); }
	friend void save(OutputArchive& arc, std::string const& value) { arc.write(value); }

	friend void save(OutputArchive& arc, i8 const& value) { arc.write(value); }
	friend void save(OutputArchive& arc, u8 const& value) { arc.write(value); }

	friend void save(OutputArchive& arc, i16 const& value) { arc.write(value); }
	friend void save(OutputArchive& arc, u16 const& value) { arc.write(value); }

	friend void save(OutputArchive& arc, i32 const& value) { arc.write(value); }
	friend void save(OutputArchive& arc, u32 const& value) { arc.write(value); }

	friend void save(OutputArchive& arc, i64 const& value) { arc.write(value); }
	friend void save(OutputArchive& arc, u64 const& value) { arc.write(value); }

	friend void save(OutputArchive& arc, f32 const& value) { arc.write(value); }
	friend void save(OutputArchive& arc, f64 const& value) { arc.write(value); }
};
} // inline namespace v2
} // namespace arc
} // namespace aw
#endif//aw_OutputArchive_base
