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
AW_DECLARE_HAS_MEMBER(save);
AW_DECLARE_HAS_NON_MEMBER(save);
namespace arc {
inline namespace v2 {
/*!
 * Base class for Output archive.
 * TODO: proper description
 */
struct OutputArchive {
	template<class T, EnableIf<IsPrimitive<T>> = dummy>
	void operator()(char const* name, T const& value)
	{
		value_start(name);
		write(value);
		value_end(name);
	}

	template<class T, EnableIf<IsObject<T>> = dummy>
	void operator()(char const* name, T const& value)
	{
		object_start(name);
		object_write(value);
		object_end(name);
	}

	template<class T, EnableIf<IsContainer<T>> = dummy>
	void operator()(char const* name, T const& value)
	{
		list_start(name);
		object_write(value);
		list_end(name);
	}

	template<class T>
	void operator()(char const* name, T const* value)
	{
		if (!value)
			return;

		if (value->classDef().isAbstract())
			return;

		auto type = value->classDef().className();
		object_start(name, type);

		polymorphic_write(value);

		object_end(name);
	}

private:
	virtual void object_start(char const* name) = 0;
	virtual void object_start(char const* name, char const* type) = 0;
	virtual void object_end(char const* name) = 0;

	virtual void list_start(char const* name) = 0;
	virtual void list_end(char const* name) = 0;

	/* Polymorphic */
	template<typename T, EnableIf<has_member_save<T,OutputArchive>> = dummy>
	void object_write(T const& value)
	{
		value.save(*this);
	}

	template<typename T, EnableIf<has_non_member_save<OutputArchive,T>> = dummy>
	void object_write(T const& value)
	{
		save(*this, value);
	}

	template<typename T>
	void polymorphic_write(T const* value)
	{
		value->save(*this);
	}

	/* Basic types */
	virtual void value_start(char const* name) = 0;
	virtual void value_end(char const* name)   = 0;

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
	friend void load(OutputArchive& arc, T& value);

	friend void save(OutputArchive& arc, char const value) { arc.write(value); }
	friend void save(OutputArchive& arc, std::string const& value) { arc.write(value); }

	friend void save(OutputArchive& arc, i8& value) { arc.write(value); }
	friend void save(OutputArchive& arc, u8& value) { arc.write(value); }

	friend void save(OutputArchive& arc, i16& value) { arc.write(value); }
	friend void save(OutputArchive& arc, u16& value) { arc.write(value); }

	friend void save(OutputArchive& arc, i32& value) { arc.write(value); }
	friend void save(OutputArchive& arc, u32& value) { arc.write(value); }

	friend void save(OutputArchive& arc, i64& value) { arc.write(value); }
	friend void save(OutputArchive& arc, u64& value) { arc.write(value); }

	friend void save(OutputArchive& arc, f32& value) { arc.write(value); }
	friend void save(OutputArchive& arc, f64& value) { arc.write(value); }
};
} // inline namespace v2
} // namespace arc
} // namespace aw
#endif//aw_OutputArchive_base
