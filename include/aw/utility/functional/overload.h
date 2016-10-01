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
template<typename Func, typename...Fs>
struct overloaded : overloaded<Func>, overloaded<Fs...> {
	overloaded(Func&& func, Fs&&... fs)
		: overloaded<Func>{std::forward<F>(func)},
		  overloaded<Fs...>{std::forward<Fs>(fs)...}
	{}

	using overloaded<Func>::operator();
	using overloaded<Fs...>::operator();
};

template<typename Func>
struct overloaded<Func> : Func {
	overloaded(Func&& func)
		: Func{std::forward<Func>(func)}
	{}
};

/*!
 * Allows to combine multiple functors into
 * overloaded set of functors.
 */
template<typename...Fs>
overloaded<Fs> overload(Fs&&...fs)
{
	return {std::forward<Fs>(fs)...};
}
}
#endif//aw_utility_functional_overload_h
