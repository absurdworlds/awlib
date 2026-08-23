/*
 * Copyright (C) 2017  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_tuple_h
#define aw_types_tuple_h
#include <tuple>
#include <functional>
namespace aw {
template<typename F, typename Tuple>
constexpr auto for_each(F&& f, Tuple&& tuple)
{
	auto visitor = [&] (auto&&... args) {
		( std::invoke(
			std::forward<F>(f),
			std::forward<decltype(args)>(args)
			),
		... );
	};
	return std::apply( visitor, std::forward<Tuple>(tuple) );
}

} // namespace aw
#endif//aw_types_tuple_h
