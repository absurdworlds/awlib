/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_memory_pool_h
#define aw_memory_pool_h
#include <cassert>
#include <new>
#include <aw/types/types.h>
#include <aw/utility/ranges/value_range.h>
namespace aw {
namespace memory {
/*!
 * Simplest memory pool implementation.
 * Allocates fixed-size chunks of memory, up to specified limit.
 */
template<size_t Size>
struct pool {
	/*!
	 * Pool stores freelist inside beginning of each block,
	 * so each block must be big enough to hold a pointer.
	 */
	static constexpr size_t block_size = std::max(Size, sizeof(void*));

	/*!
	 * Create bool with num_objects blocks of memory
	 */
	pool(size_t num_objects)
		: num_blocks(num_objects)
	{
		auto size = block_size*num_blocks;

		start  = ::operator new(size, std::nothrow);
		next   = start;


		// almost forgot this part
		for (auto i : range(0ul, num_blocks-1))
			next_of(index_to_ptr(i)) = index_to_ptr(i+1);

		next_of(index_to_ptr(num_blocks-1)) = nullptr;
	}

	~pool()
	{
		::operator delete(start, std::nothrow);
	}

	/*
	 * Pointer to the first byte of pool
	 */
	char* begin() const
	{
		return static_cast<char*>(start);
	}

	/*
	 * Pointer past the last byte of the pool
	 */
	char* end() const
	{
		return static_cast<char*>(start) + num_blocks*block_size;
	}

	/*!
	 * Allocate memory from pool.
	 * \return
	 *    Pointer to allocated memory, or nullptr if
	 *    no more space is left in the pool.
	 */
	void* alloc()
	{
		auto ret = next;

		if (next != nullptr)
			next = *static_cast<void**>(next);

		return ret;
	}

	/*!
	 * Return memory, pointed by \a ptr to the pool.
	 * \a ptr must point to memory, returned by alloc().
	 */
	void* dealloc(void* ptr)
	{
		assert(belongs_to(ptr));
		next_of(ptr) = next;
		next = ptr;
	}

private:
	static void*& next_of(void* ptr)
	{
		return *static_cast<void**>(ptr);
	}

	void* index_to_ptr(size_t idx) const
	{
		assert(idx < num_blocks);
		return begin() + block_size*idx;
	}


	bool belongs_to(void* ptr) const
	{
		return static_cast<char*>(ptr) >= begin() &&
		       static_cast<char*>(ptr) < end();
	}

	size_t num_blocks;

	void* start;
	void* next;
};
} // namespace memory
} // namespace aw
#endif//aw_memory_pool_h
