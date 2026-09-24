/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_functional_overload_h
#define aw_utility_functional_overload_h
#include <utility>
namespace aw {
/*!
 * Allow to build an overload set from multiple lambdas or functors.
 */
template<typename...Fs>
struct overload : Fs... {
	overload() = default;
	overload(Fs... fs) : Fs{ std::move(fs) }...  {}
	using Fs::operator()...;

	// Enables use in transparent containers
	// (std::map, std::unordered_map, etc)
	using is_transparent = void;
};
} // namespace aw
#endif//aw_utility_functional_overload_h
