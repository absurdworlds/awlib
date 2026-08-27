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
#if __cpp_variadic_using >= 201611
/*!
 * Allows to combine multiple functors into overloaded set.
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
#else
template<typename Func, typename...Fs>
struct overload : overload<Func>, overload<Fs...> {
	overload(Func func, Fs... fs)
		: overload<Func>{std::forward<F>(func)},
		  overload<Fs...>{std::forward<Fs>(fs)...}
	{}

	using overload<Func>::operator();
	using overload<Fs...>::operator();
};

template<typename Func>
struct overload<Func> : Func {
	overload(Func func)
		: Func{std::forward<Func>(func)}
	{}
};
#endif

template<typename...Fs>
[[deprecated]]
overload<Fs...> make_overload(Fs&&...fs)
{
	return {std::forward<Fs>(fs)...};
}
} // namespace aw
#endif//aw_utility_functional_overload_h
