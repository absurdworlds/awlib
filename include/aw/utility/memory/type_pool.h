/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_memory_type_pool_h
#define aw_memory_type_pool_h
#include <aw/utility/memory/pool.h>
#include <aw/utility/memory/growing_pool.h>
namespace aw {
namespace memory {
/*!
 * Pool of objects of single type.
 */
template<class T, template <size_t> class Base = pool>
struct type_pool : Base<std::max(sizeof(T), alignof(T))>{
	using base_type = Base<std::max(sizeof(T), alignof(T))>;
	using base_type::block_size;

	type_pool(size_t num_objects)
		: base_type(num_objects)
	{}
};

template<class T>
using growing_type_pool = type_pool<T,growing_pool>;
} // namespace memory
} // namespace aw
#endif//aw_memory_type_pool_h
