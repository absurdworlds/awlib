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
#include <aw/utility/to_string.h>
namespace aw {
namespace _impl {
template<typename Formatter>
struct variant_to_string_visitor {
	using return_type = std::string;

	template<typename T>
	std::string operator()(T const& data)
	{
		return fmt.value(data);
	}

	Formatter&& fmt;
};

} // namespace _impl

/*!
 * Convert variant to string
 * \return
 *    Contained value, converted to string,
 *    or empty string if optional is empty.
 */
template<typename... Args, typename Formatter = format::pretty_print>
std::string to_string(variant<Args...> const& var, Formatter&& fmt = Formatter{})
{
	if (var.empty())
		return fmt.empty_value();
	auto&& vis = _impl::variant_to_string_visitor{std::forward<Formatter>(fmt)};
	return var.apply(vis);
}
} // namespace aw
#endif//aw_variant_to_string_h
