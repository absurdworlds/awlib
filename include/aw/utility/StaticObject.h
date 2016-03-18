/*
 * Copyright (C) 2016       Hedede <haddayn@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_StaticObject_
#define aw_StaticObject_
//#include <aw/utility/tags/EmptyTag.h>
namespace aw {
//struct EmptyTag {};

template <class T> //, class Tag = EmptyTag>
class StaticObject {
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
T& StaticObject<T>::ref = StaticObject<T>::create();

} // namespace aw
#endif//aw_StaticObject_
