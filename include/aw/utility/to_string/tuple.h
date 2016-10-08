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
#include <tuple>
#include <aw/utility/index_sequence.h>
#include <aw/utility/to_string.h>
namespace aw {
/*! Converts tuple to string. */
template<typename... Ts>
struct string_converter<std::tuple<Ts...>> {
	std::tuple<Ts...> const& tuple;

	template<typename Formatter>
	std::string operator()( Formatter& fmt ) const
	{
		fmt.compound_start();
		print_each( fmt, make_index_sequence<sizeof...(Ts)>() );
		fmt.compound_end();
		return fmt;
	}

private:
	template<typename Formatter, size_t...Is>
	void print_each( Formatter& fmt, index_sequence<Is...> ) const
	{
		(void(fmt.value(std::get<Is>(tuple))), ...);
	}
};
} // namespace aw
#endif//aw_std_tuple_to_string_h
