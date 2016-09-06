/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_unique_ptr_to_string_h
#define aw_unique_ptr_to_string_h
#include <memory>
#include <aw/utility/to_string.h>
namespace aw {
/*!
 * Convert unique_ptr to string
 * \return
 *    Underlying pointer converted to string
 */
template <typename T>
struct string_converter<std::unique_ptr<T>> {
	std::string operator()( std::unique_ptr<T> const& ptr ) const
	{
		return to_string(ptr.get());
	}
};

} // namespace aw
#endif//aw_unique_ptr_to_string_h
