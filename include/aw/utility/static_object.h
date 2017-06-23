/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_static_object_h
#define aw_static_object_h
//#include <aw/utility/tags/EmptyTag.h>
//struct EmptyTag {};
namespace aw {
/*!
 * Creates a single static instance of class T.
 * T must be DefaultConstructible.
 *
 * Purpose of this class is to avoid "static initialization
 * order fiasco" when creating a static object.
 */
template <class T> //, class Tag = EmptyTag>
class static_object {
	static T& ref;

	static void use(T const&) {}

	static T& create()
	{
		static T object;
		use(ref);
		return object;
	}

public:
	static T& instance()
	{
		return create();
	}

	static T const& const_instance()
	{
		return create();
	}
};

template <class T>
T& static_object<T>::ref = static_object<T>::create();
} // namespace aw
#endif//aw_static_object_h
