/*
 * The code in this file is placed in public domain.
 * Contact: Hedede <Haddayn@gmail.com>
 */
#ifndef aw_traits_void_t
#define aw_traits_void_t
#include <type_traits>
namespace aw {
using std::declval;
template<typename... Ts> struct make_void { using type = void; };
template<typename... Ts> using void_t = typename make_void<Ts...>::type;
} // namespace aw
#endif//aw_traits_void_t
