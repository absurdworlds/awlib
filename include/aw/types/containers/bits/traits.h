/*
 * Copyright (C) 2018  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_containers_traits_h
#define aw_containers_traits_h
#include <aw/types/traits/iterator.h>
namespace aw {
namespace _impl {
// traits wrapper — used to select const or non-const types
template <typename Traits>
struct traits {
	using value_type        = typename Traits::value_type;
	using pointer           = typename Traits::pointer;
	using reference         = typename Traits::reference;
	using difference_type   = typename Traits::difference_type;
};

template <typename Traits>
struct const_traits {
	using value_type        = typename Traits::value_type;
	using pointer           = typename Traits::const_pointer;
	using reference         = typename Traits::const_reference;
	using difference_type   = typename Traits::difference_type;
};
} // namespace _impl
} // namespace aw
#endif//aw_containers_traits_h
