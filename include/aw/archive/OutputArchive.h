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
	auto process(T const& value) -> void_if<has_member_save<T,OutputArchive>>
	{
		value.save(*this);
	}

	template<typename T>
	auto process(T const& value) -> void_if<has_non_member_save<OutputArchive,T>>
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
