#ifndef aw_string_compose_h
#define aw_string_compose_h
#include <aw/types/array_view.h>
#include <aw/types/string_view.h>

#include <aw/string/export.h>
#include <aw/utility/to_string.h>

namespace aw::string {
/*!
 * Compose parametrized string (parameter substitution).
 */
AW_STRING_EXP
std::string compose_v(string_view fmt, array_view<string_view> args);
AW_STRING_EXP
std::string compose_v(string_view fmt, array_view<std::string> args);

namespace _impl {
inline std::string compose(string_view fmt, std::initializer_list<string_view> args)
{
	return compose_v(fmt, array_view<string_view>(args));
}
} // namespace _impl

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
	return _impl::compose(fmt, { to_string(args)... });
}
} // namespace aw::string
#endif//aw_string_compose_h
