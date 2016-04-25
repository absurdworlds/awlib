/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_on_scope_exit_h
#define aw_on_scope_exit_h
#include <functional>
#include <utility>
#include <aw/types/non_copyable.h>
namespace aw {
template <class Callable>
class on_scope_exit : non_copyable {
	std::function<void()> func;
public:
	on_scope_exit(Callable func)
		: func(func)
	{}

	on_scope_exit(on_scope_exit&& other)
		: func(std::move(other.func))
	{}

	~on_scope_exit()
	{
		if (func) func();
	}
};

template <class Callable>
on_scope_exit<Callable> call_on_exit(Callable&& func)
{
	return on_scope_exit<Callable>(std::forward<Callable>(func));
}
} // namespace aw
#endif//aw_on_scope_exit_h
