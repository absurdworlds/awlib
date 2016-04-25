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
	ClassDef    const* parent;
	std::string const  name;

public:
	/*!
	 * Create classdef. It is necessary in order
	 * to load polymorphic classes with aw archiver.
	 *
	 * \param Parent
	 *    Parent class of \a Class. If \a Class is Base,
	 *    then \a Parent must also be Base.
	 */
	template<class Parent, class Class>
	static ClassDef create(std::string name)
	{
		static_assert(std::is_polymorphic<Class>,
		              "Class must by polymorphic.");
		static_assert(std::is_base_of<Base, Parent>,
		              "Parent must be derived from Base.")
		static_assert(std::is_base_of<Parent, Class>,
		              "Class must be derived from Parent.")
		static_assert(std::is_same<Base,Class> || !is_same<Parent,Class>,
		              "Parent can't be same as Class");
		static_assert(!std::is_same<Base,Class> || is_same<Parent,Base>,
		              "Base class can't have Parent.");

		// using meta_class = reflexpr(Class);
		// std::string name = std::meta::get_name_v<meta_class>;

		ClassDef const* parent = std::is_same<Base,Class>::value ?
			nullptr : &Parent::classdef;

		Create const creator = std::is_abstract<Class>::value ?
			nullptr : [] (Args...args) -> Base*
			{
				return new Class(std::forward<Args>(args)...);
			}


		return ClassDef(parent, name, creator);
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
	ClassDef(ClassDef* parent, std::string name, Creator creator)
		: parent(parent), name(name), creator(creator)
	{
		ClassDefMap::instance().insert({name, this});
	}
};

#if 0
#define AW_CLASSDEF_BASE_HEADER(Base, Signature)      \
	using ClassDef = ::ClassDef<Base, Signature>; \
	static ClassDef& classdef;                    \
	virtual ClassDef& classDef() const            \
	{                                             \
		return classdef;                      \
	}

#define AW_CLASSDEF_ABSTRACT_BASE(Base, Signature) \
	AW_CLASSDEF_BASE_HEADER(Base, Signature)   \
	static ClassDef& classDef_()               \
	{                                          \
		static auto cd = ClassDef::base(#base, nullptr); \
		return cd; \
	}

#define AW_CLASSDEF_BASE(Base, Signature) \
	AW_CLASSDEF_BASE_HEADER(Base, Signature)   \
	static ClassDef& classDef_()               \
	{                                          \
		static auto cd = ClassDef::base(#base, [] ); \
		return cd; \
	}
#endif
} // inline namespace v2
} // namespace arc
} // namespace aw
#endif//aw_archive_ClassDef_base
