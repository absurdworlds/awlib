/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_functional_trivial_h
#define aw_utility_functional_trivial_h
namespace aw {
/*!
 * Functor that takes any number of arguments and always returns true.
 */
struct true_func {
	template<typename...Args>
	constexpr bool operator()(Args&&.../*args*/) const { return true; }
};
/*!
 * Functor that takes any number of arguments and always returns false.
 */
struct false_func {
	template<typename...Args>
	constexpr bool operator()(Args&&.../*args*/) const { return false; }
};
} // namespace aw
#endif//aw_utility_functional_trivial_h
