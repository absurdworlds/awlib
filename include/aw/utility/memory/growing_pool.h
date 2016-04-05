/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_memory_growing_pool_h
#define aw_memory_growing_pool_h
#include <cassert>
#include <new>
#include <vector>
#include <aw/types/types.h>
#include <aw/utility/ranges/value_range.h>
namespace aw {
namespace memory {
/*!
 * Simple memory pool implementation.
 * Behaves similarly to \c aw::memory::pool,
 * but grows itself by allocating more chunks of memory,
 * instead of returning nullptr when no more space is left.
 */
template<size_t Size>
struct growing_pool {
	/*!
	 * Pool stores freelist inside beginning of each block,
	 * so each block must be big enough to hold a pointer.
	 */
	static constexpr size_t block_size = std::max(Size, sizeof(void*));

	/*!
	 * Create bool with num_objects blocks of memory
	 */
	growing_pool(size_t num_objects) noexcept
		: num_blocks(num_objects)
	{
		auto size = block_size*num_blocks;
	}


	growing_pool(growing_pool const&) = delete;
	growing_pool& operator=(growing_pool const&) = delete;


	~growing_pool() noexcept
	{
		for (auto start : pools)
			::operator delete(start, std::nothrow);
	}

	/*!
	 * Allocate memory from pool.
	 * \return
	 *    Pointer to allocated memory, or nullptr
	 *    on allocation failure (i.e. system is out of memory).
	 */
	void* alloc() noexcept
	{
		if (next == nullptr)
			next = add_pool();

		if (next == nullptr)
			return nullptr;


		auto ret = next;

		next = *static_cast<void**>(next);

		return ret;
	}

	/*!
	 * Return memory, pointed by \a ptr to the pool.
	 * Result of passing \a ptr that wasn't returned by alloc()
	 * is undefined.
	 */
	void* dealloc(void* ptr) noexcept
	{
		next_of(ptr) = next;
		next = ptr;
	}

#if 0
	void print()
	{
		std::cout << "next: " << next;

		auto list = next;
		while (list) {
			list = next_of(list);
			std::cout << ", " << list;
		}

		std::cout << "\n";

		for (auto pool : pools) {
			std::cout << "{" << pool << ":" << next_of(pool);
			for (auto i : range(1ul, num_blocks))
				std::cout << ", " << index_to_ptr(pool,i) << ":" << next_of(index_to_ptr(pool, i));
			std::cout <<"}\n";
		}
	}
#endif

private:
	static void*& next_of(void* ptr)
	{
		return *static_cast<void**>(ptr);
	}

	void* index_to_ptr(void* begin, size_t idx) const
	{
		assert(idx < num_blocks);
		return static_cast<char*>(begin) + block_size*idx;
	}

	void* add_pool() noexcept
	{
		size_t size = num_blocks*block_size;
		void* start  = ::operator new(size, std::nothrow);
		
		if (!start)
			return nullptr;

		for (auto i : range(0ul, num_blocks-1))
			next_of(index_to_ptr(start, i)) = index_to_ptr(start, i+1);

		next_of(index_to_ptr(start, num_blocks-1)) = nullptr;

		pools.push_back(start);

		return start;
	}

	size_t num_blocks;

	std::vector<void*> pools;

	void* next = nullptr;
};
} // namespace memory
} // namespace aw
#endif//aw_memory_growing_pool_h
