/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_boolean_h
#define aw_traits_boolean_h
#include <type_traits>
namespace aw {
using std::true_type;
using std::false_type;

template<typename... Bool>
struct bool_and {
	static constexpr bool value = (Bool::value && ...);
};

template<typename... Bool>
struct bool_or {
	static constexpr bool value = (Bool::value || ...);
};
} // namespace aw
#endif//aw_traits_boolean_h
