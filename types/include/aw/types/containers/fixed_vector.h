/*
 * Copyright (C) 2023  Hudd <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_containers_fixed_vector_h
#define aw_containers_fixed_vector_h

#include <aw/types/types.h>

namespace aw {

/**
 * Fixed-capacity vector.
 *
 * Can be resized manually.
 */
template<typename T>
class fixed_vector {
public:
	using size_type = std::size_t;
	using pointer = T*;

private:
	pointer data;
	size_type size;
	size_type capacity;
};

} // namespace aw

#endif // aw_containers_fixed_vector_h
