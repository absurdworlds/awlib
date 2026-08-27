/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_functional_wrapper_h
#define aw_utility_functional_wrapper_h
#include <utility>
#include <functional>
namespace aw {
/*!
 * Wrap a function in a functor, so that it can be passed around as a template
 * parameter.
 */
// Inspired by
// https://dev.krzaq.cc/post/you-dont-need-a-stateful-deleter-in-your-unique_ptr-usually/
template<auto Function>
struct function_wrapper {
	template<typename...Args>
	constexpr void operator()(Args&&... args)
	{
		std::invoke(Function, std::forward<Args>(args)...);
	}
};
}
#endif//aw_utility_functional_wrapper_h
