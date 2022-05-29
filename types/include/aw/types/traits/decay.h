/*
 * The code in this file is placed in public domain.
 * Contact: Hedede <Haddayn@gmail.com>
 */
#ifndef aw_traits_decay_h
#define aw_traits_decay_h
#include <type_traits>
namespace aw {
template<typename T>
using decay = typename std::decay<T>::type;
template<typename T>
using decay_t = std::decay<T>;
} // namespace aw
#endif//aw_traits_decay_h
