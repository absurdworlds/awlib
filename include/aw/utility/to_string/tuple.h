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
	std::string operator()( std::tuple<Ts...> const& tuple )
	{
		str.append(1,'{');
		print_each( tuple, make_index_sequence<sizeof...(Ts)>() );
		str.append(1,'}');
		return str;
	}

private:
	template<size_t I>
	void do_print( std::tuple<Ts...> const& tuple )
	{
		using aw::to_string;
		if (I != 0)
			str.append(", ");
		str += to_string(std::get<I>(tuple));

	}

	template<size_t...Is>
	void print_each( std::tuple<Ts...> const& tuple, index_sequence<Is...> )
	{
		(do_print<Is>(tuple), ...);
	}

	std::string str;
};
} // namespace aw
#endif//aw_std_tuple_to_string_h
