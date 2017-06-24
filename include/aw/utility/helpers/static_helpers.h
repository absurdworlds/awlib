/*
 * Copyright (C) 2017  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_on_static_helpers_h
#define aw_on_static_helpers_h
#include <utility>
#include <aw/types/non_copyable.h>
#include <aw/utility/static_object.h>
namespace aw {
/*!
 * Calls the Function when object of this calss is instantiated.
 *
 * Use-case: see aw::archive
 */
template<auto Function>
struct call_in_ctor {
	template<typename...Args>
	call_in_ctor(Args&&... args)
	{
		Function(std::forward<Args>(args)...);
	}
};

/*!
 * Calls function during static variable initialization,
 * i.e. before main is called.
 */
template<auto Function>
class call_on_init {
	static const int dummy;
};

/* TODO: replace int with void (p0146r1)*/
template<auto Function>
const int call_on_init<function>::dummy = (static_object<call_in_ctor<function>>::instance(), 1);

} // namespace aw
#endif//aw_on_static_helpers_h
