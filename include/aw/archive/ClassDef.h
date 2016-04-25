/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_archive_ClassDef_base
#define aw_archive_ClassDef_base
#include <map>
#include <string>
#include <functional>
#include <aw/types/traits/basic_traits.h>
#include <aw/utility/static_object.h>

namespace aw {
namespace arc {
inline namespace v2 {
template <class>
struct ClassDef;

template <class Base, typename...Args>
struct ClassDef<Base*(Args...)> {
private:
	using CreatorSignature = Base*(Args...);
	using Creator = std::function<CreatorSignature>;

	Creator     const creator;
	std::string const  name;

public:
	/*!
	 * Create classdef. It is necessary in order
	 * to load polymorphic classes with aw archiver.
	 */
	template<class Class>
	static ClassDef create(std::string name)
	{
		static_assert(is_polymorphic<Class>,
		              "Class must be polymorphic.");
		static_assert(is_base_of<Base, Class>,
		              "Class must be derived from Base.");

		// using meta_class = reflexpr(Class);
		// std::string name = std::meta::get_name_v<meta_class>;

		auto create = [] (Args...args) -> Base*
		{
			return new Class(std::forward<Args>(args)...);
		};

		Creator creator = std::is_abstract<Class>::value ?
			nullptr : create;


		return ClassDef(name, creator);
	}

	char const* className() const
	{
		return name.c_str();
	}

	Base* create(Args... args) const
	{
		return creator(args...);
	}

	bool isAbstract() const
	{
		return !creator;
	}

	using ClassDefMapType = std::map<std::string, ClassDef*>;
	using ClassDefMap = static_object<ClassDefMapType>;

	static ClassDef* findClassDef(std::string const& name)
	{
		auto map = ClassDefMap::instance();
		auto iter = map.find(name);
		if (iter == std::end(map))
			return nullptr;
		return iter->second;
	}

private:
	ClassDef(std::string name, Creator creator)
		: name(name), creator(creator)
	{
		ClassDefMap::instance().insert({name, this});
	}
};
} // inline namespace v2
} // namespace arc
} // namespace aw
#endif//aw_archive_ClassDef_base
