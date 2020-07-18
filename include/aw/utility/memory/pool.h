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
#include <memory>
#include <aw/types/types.h>
namespace aw {
namespace memory {
struct slab {
	size_t size;
	slab* next;
};

inline void*& next_of(void* ptr)
{
	return *static_cast<void**>(ptr);
}

/*!
 * Memory pool allocates fixed-size chunks of memory
 * from a contiguous memory area, size of which is specified
 * by user.
 */
template<size_t Size, size_t Align>
struct pool {
	/*
	 * Pool stores freelist inside beginning of each block,
	 * so each block must be big enough to hold a pointer.
	 */
	static constexpr size_t size  = std::max(Size,  sizeof(void*));
	static constexpr size_t align = std::max(Align, alignof(void*));
	static constexpr size_t block_size = std::max(size, align);

	/*!
	 * Create pool with blocks allocated in
	 * \a num_blocks sized slabs.
	 */
	pool(size_t num_blocks) noexcept
		: num_blocks(num_blocks)
	{ }

	pool(pool const&) = delete;
	pool& operator=(pool const&) = delete;

	~pool()
	{
		deallocate_slabs();
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
			next = create_slab();

		if (next == nullptr)
			return nullptr;

		auto ret = next;

		next = next_of(next);

		return ret;
	}

	/*!
	 * Return memory, pointed by \a ptr to the pool.
	 * Result of passing \a ptr that wasn't returned by alloc()
	 * is undefined.
	 */
	void dealloc(void* ptr) noexcept
	{
		next_of(ptr) = next;
		next = ptr;
	}

private:
	size_t num_blocks;

	slab* current = nullptr;
	void* next    = nullptr;

	void* get_ptr(void* begin, size_t idx) const
	{
		assert(idx < num_blocks);
		return static_cast<char*>(begin) + block_size*idx;
	}

	void init_blocks(void* ptr)
	{
		for (auto i = 0ul; i < num_blocks-1; ++i)
			next_of(get_ptr(ptr, i)) = get_ptr(ptr, i+1);

		next_of(get_ptr(ptr, num_blocks-1)) = nullptr;
	}

	std::byte* allocate(size_t full_size)
	{
		// TODO: make this a customization point?
		auto raw_memory = ::operator new(full_size, std::nothrow);

		return static_cast<std::byte*>(raw_memory);
	}

	slab* init_slab(void* memory, size_t size, slab* next)
	{
		return new (memory) slab{ size, next };
	}

	void* create_slab()
	{
		static constexpr size_t slab_size {
			std::max(sizeof(slab), alignof(slab))
		};

		auto full_size = slab_size + block_size * (num_blocks + 1);

		std::byte* new_slab = allocate(full_size);
		current = init_slab(new_slab, full_size, current);

		void* memory_begin = new_slab + sizeof(slab);

		std::align(align, size, memory_begin, full_size);

		init_blocks(memory_begin);

		return memory_begin;
	}

	void deallocate_slabs()
	{
		while (current) {
			auto next = current->next;
			::operator delete((void*)current);
			current = next;
		}
	}
};

/*!
 * Memory pool for objects of specific type.
 */
template<typename T>
struct specific_pool : pool<sizeof(T), alignof(T)> {
	using base_type = pool<sizeof(T), alignof(T)>;
	using base_type::block_size;

	specific_pool(size_t num_objects)
		: base_type(num_objects)
	{}
};

} // namespace memory
} // namespace aw
#endif//aw_memory_growing_pool_h
