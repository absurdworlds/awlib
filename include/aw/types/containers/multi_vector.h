/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_containers_multi_vector
#define aw_containers_multi_vector
#include <tuple>



namespace aw {

namespace _impl {


} // namespace _impl

/*
 * Stores a vector of tuples of types Ts... as separate vectors of each type
 * (useful for implementing struct-of-arrays)
 * No allocator support.
 */
template<typename... Ts>
struct multi_vector {
	using size_type = size_t;

	size_type _size;
	size_type _capacity;
	using ptr_tuple = std::tuple<Ts*...>;
	ptr_tuple _data;

	template<typename T>
	static void allocate(T*& ptr, size_type size)
	{
		if (size == 0)
			return;
		ptr = (T*)operator new(size * sizeof(T));
	}

	template<typename T>
	static void deallocate(T*& ptr)
	{
		operator delete(ptr);
		ptr = nullptr;
	}

	void push_back(std::tuple<Ts...> const& tuple)
	{
		check_capacity();
	}

	void create_storage(size_type size)
	{
		_capacity = size;
		auto visitor = [size] (auto*&... ptrs)
		{
			( allocate(ptrs, size), ... );
		};
		std::apply(visitor, _data);
	}

	void destroy_storage()
	{
		// assert(_capacity > 0);
		auto visitor = [] (auto*&... ptrs)
		{
			( deallocate(ptrs), ... );
		};
		std::apply(visitor, _data);
	}

	void reallocate(size_type new_size)
	{
		ptr_tuple new_begin{};
	}

	void check_capacity()
	{
		if (size() == capacity())
			reallocate(next_size());
	}
};
} // namespace aw

#endif//aw_containers_multi_vector
