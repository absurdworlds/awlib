/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_variant_to_string_h
#define aw_variant_to_string_h
#include <aw/types/variant.h>
namespace aw {
namespace _impl {
struct variant_to_string_visitor {
	using return_type = std::string;

	template<typename T>
	std::string operator()(T const& data)
	{
		using aw::to_string;
		return to_string(data);
	}
};

} // namespace _impl

/*!
 * Convert variant to string
 * \return
 *    Contained value, converted to string,
 *    or empty string if optional is empty.
 */
template<typename... Args>
std::string to_string(variant<Args...> const& var)
{
	if (var.empty())
		return {};
	return var.apply(_impl::variant_to_string_visitor{});
}
} // namespace aw
#endif//aw_variant_to_string_h
