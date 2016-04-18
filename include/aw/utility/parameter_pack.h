/*
 * Copyright (C) 2015-2016  absurdworlds
 * Copyright (C) 2015-2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_parameter_pack_h
#define aw_parameter_pack_h
#include <aw/utility/index_sequence.h>
namespace aw {
using fold_dummy = int[];

template <class Func, class... Args>
void for_each_argument(Func f, Args&&... args) {
	(void) fold_dummy{
		(f(std::forward<Args>(args)), 0)...
	};
}

template<class Func, size_t...Is>
void for_each_index(Func f, index_sequence<Is...>)
{
	for_each_argument(f, Is...);
}
} // namespace aw
#endif//aw_parameter_pack_h
