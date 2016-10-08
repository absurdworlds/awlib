/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_pair_to_string_h
#define aw_pair_to_string_h
#include <memory>
#include <aw/utility/to_string.h>
namespace aw {
/*!
 * Convert pair to string
 * \return
 *    String in format "{pair.first, pair.second}".
 */
template <typename T1, typename T2>
struct string_converter<std::pair<T1, T2>> {
	std::pair<T1, T2> const& pair;

	template<typename Formatter>
	std::string operator()( Formatter& fmt ) const
	{
		fmt.compound_start();
		fmt.value(pair.first);
		fmt.value(pair.second);
		fmt.compound_end();
		return fmt;
	}
};
} // namespace aw
#endif//aw_pair_to_string_h
