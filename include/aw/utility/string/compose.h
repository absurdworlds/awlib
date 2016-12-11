/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_compose_h
#define aw_string_compose_h
#include <vector>

#include <aw/types/string_view.h>
#include <aw/types/array_view.h>
#include <aw/utility/string/string.h>
#include <aw/utility/to_string.h>

namespace aw {
namespace string {
/*!
 * Compose parametrized string (parameter substitution).
 */
AW_STRING_EXP
std::string compose(string_view fmt, array_view<std::string> args);

/*!
 * Compose parametrized string (parameter substitution).
 *
 * Takes string as input, all characters of which are returned
 * unchanged, with exception for '%'. Tokens, starting with '%'
 * are replacement fields, and have following format:
 *
 * 	ref ::= '%' [0-9]+
 *
 * These refer to an argument number, and substituted by respective
 * arguments, passed into this function.
 *
 * For example:
 * 	compose("%1 %0", " a string", "this is");
 *
 * Will return std::string("this is a string").
 *
 * Use '%%' to write '%' symbol. Do not use '%' (single '%') with
 * characters, other than [0-9] digits, as their behavior will
 * change in the future.
 * 
 * \param fmt
 * 	Format string, containing regular text and parameters
 * 	starting with '%'.
 * \param args
 * 	Arguments, which will be used to substitute parameters in
 * 	the string \a fmt.
 */
template<typename... Args>
std::string compose(string_view fmt, Args const&... args)
{
	std::vector<std::string> bits{to_string(args)...};

	return compose(fmt, bits);
}
} // namespace string
} // namespace aw
#endif//aw_string_compose_h
