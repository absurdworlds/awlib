/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_std_tuple_to_string_h
#define aw_std_tuple_to_string_h
#include <aw/utility/index_sequence.h>
#include <aw/utility/to_string.h>
#include <aw/types/tuple.h>
namespace aw {
/*! Converts tuple to string. */
template<typename... Ts>
struct string_converter<std::tuple<Ts...>> {
	std::tuple<Ts...> const& tuple;

	template<typename Formatter>
	std::string operator()( Formatter& fmt ) const
	{
		fmt.compound_start();
		auto print = [&] (auto const&... ele) {
			( fmt.value( ele ), ... );
		};
		std::apply( print, tuple );
		fmt.compound_end();
		return fmt;
	}
};
} // namespace aw
#endif//aw_std_tuple_to_string_h
