/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_containers_circular_buffer_h
#define aw_containers_circular_buffer_h
#include <cassert>
#include <memory>
#include <iterator>
#include <algorithm>
#include <aw/types/containers/bits/cbuffer.h>
#include <aw/types/containers/bits/traits.h>
namespace aw {
/*!
 * circular_buffer is a fixed-size buffer, which overwrites itself
 * when it is full.
 *
 * Does not support allocators.
 * TODO: do we need allocator support?
 */
template<typename T>
class circular_buffer {
public:
	using value_type       = T;
	using reference        = T&;
	using const_reference  = T const&;
	using size_type        = size_t;
	using difference_type  = ptrdiff_t;
	using pointer          = T*;
	using const_pointer    = T const*;
	using iterator         = _impl::circular_iterator<_impl::traits<circular_buffer>>;
	using const_iterator   = _impl::circular_iterator<_impl::const_traits<circular_buffer>>;
	using reverse_iterator       = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
	_impl::cbuffer_data<T> data;

	void create_storage(size_type size)
	{
		++size; // for null element
		data.begin = (pointer)operator new(size);
		data.end   = data.begin + size;
		data.head  = data.tail = data.begin;
	}

	void destroy_storage()
	{
		delete[] data.begin;
	}

public:

	/*! Create buffer with specified capacity */
	explicit circular_buffer(size_type size)
	{
		create_storage( size );
	}

	/*!
	 * Copy constructor.
	 * Creates buffer of the same size and copies all elements.
	 */
	circular_buffer(circular_buffer const& q)
		: circular_buffer( q.size() )
	{
		std::uninitialized_copy(q.begin(), q.end(), begin());
	}

	/*! TODO: move constructor */


	~circular_buffer()
	{
		destroy(begin(), end());
		destroy_storage();
	}


	/*! Iterator to the front of queue */
	iterator begin()
	{
		return {data.head, data};
	}

	/*! Iterator to the front of queue */
	const_iterator begin() const
	{
		return {data.head, data};
	}

	/*! Iterator to the front of queue */
	const_iterator cbegin() const
	{
		return {begin()};
	}

	/*! Iterator to element past the end of queue */
	iterator end()
	{
		return {data.tail, data};
	}

	/*! Iterator to element past the end of queue */
	const_iterator end() const
	{
		return {data.tail, data};
	}

	/*! Iterator to element past the end of queue */
	const_iterator cend() const
	{
		return {end()};
	}

	/*! Reverse iterator to the end of queue */
	reverse_iterator rbegin()
	{
		return {end()};
	}


	/*! Reverse iterator to the end of queue */
	const_reverse_iterator rbegin() const
	{
		return {end()};
	}

	/*! Reverse iterator to the end of queue */
	const_reverse_iterator crbegin() const
	{
		return {cend()};
	}

	/*! Reverse iterator to start of queue */
	reverse_iterator rend()
	{
		return {begin()};
	}

	/*! Reverse iterator to start of queue */
	const_reverse_iterator rend() const
	{
		return {begin()};
	}

	/*! Reverse iterator to start of queue */
	const_reverse_iterator crend() const
	{
		return {cbegin()};
	}

	/*! Get number of elements in queue */
	size_type size() const noexcept
	{
		auto dist = end() - begin();
		return dist - 1;
	}

	/*! Get buffer capacity */
	size_type capacity() const noexcept
	{
		auto dist = data.end - data.begin;
		return dist - 1;
	}

	/*!
	 * Erases all elements in queue.
	 *
	 * \note
	 * It does not free allocated memory.
	 * If elements are pointers, memory pointed-to by them
	 * is not freed.
	 */
	void clear()
	{
		destroy(begin(), end());
		data.tail = data.head;
	}

	/*!
	 * Check if queue is empty
	 */
	bool empty() const noexcept
	{
		return begin() == end();
	}

	/*!
	 * Destroy element at the front of queue
	 */
	void pop_front()
	{
		assert(!empty() && "pop_front() on empty queue.");
		data.head->~T();
		data.head = data.next_p(data.head);
	}

	/*!
	 * Destroy element at the back of queue
	 */
	void pop_back()
	{
		assert(!empty() && "pop_back() on empty queue.");
		data.tail = data.prev_p(data.tail);
		data.tail->~T();
	}

	/*!
	 * Insert element at the front of queue
	 */
	void push_front(const_reference val)
	{
		emplace_front(val);
	}

	/*!
	 * Insert element at the end of queue
	 */
	void push_back(const_reference val)
	{
		emplace_back(val);
	}

	/*!
	 * Insert element at the front of queue
	 */
	void push_front(value_type&& val)
	{
		emplace_front(std::move(val));
	}

	/*!
	 * Insert element at the end of queue
	 */
	void push_back(value_type&& val)
	{
		emplace_back(std::move(val));
	}

	/*!
	 * Construct element at the front of queue
	 */
	template <typename... Args>
	void emplace_front(Args&&... args)
	{
		auto head = data.prev_p(data.head);
		if (head == data.tail)
			pop_back();
		data.head = head;
		construct(data.head, std::forward<Args>(args)...);
	}

	/*!
	 * Construct element at the end of queue
	 */
	template <typename... Args>
	void emplace_back(Args&&... args)
	{
		construct(data.tail, std::forward<Args>(args)...);
		auto tail = data.next_p(data.tail);
		if (tail == data.head)
			pop_front();
		data.tail = tail;
	}

	/*! Get element at the head of queue */
	const_reference front() const noexcept
	{
		assert(!empty() && "front() on empty queue.");
		return *begin();
	}

	/*! Get element at the head of queue */
	reference front() noexcept
	{
		assert(!empty() && "front() on empty queue.");
		return *begin();
	}

	/*! Get element at the tail of queue */
	const_reference back() const noexcept
	{
		assert(!empty() && "back() on empty queue.");
		return *(end() - 1);
	}

	/*! Get element at the tail of queue */
	reference back() noexcept
	{
		assert(!empty() && "back() on empty queue.");
		return *(end() - 1);
	}

	const_reference operator[](size_type n) const noexcept
	{
		assert(n < size() && "Index out of bounds.");
		return begin()[n];
	}

	reference operator[](size_type n) noexcept
	{
		assert(n < size() && "Index out of bounds.");
		return begin()[n];
	}

private:
	template <typename... Args>
	void construct(pointer p, Args&&... args)
	{
		new (p) T( std::forward<Args>(args)... );
	}

	void destroy(iterator head, iterator tail)
	{
		for (; head != tail; ++head)
			head->~T();
	}


	template<typename Iterator, typename Sentinel>
	void range_init(Iterator first, Sentinel last, std::input_iterator_tag)
	{
		for (; first != last; ++first)
			emplace_back(*first);
	}

	template<typename Iterator, typename Sentinel>
	void range_init(Iterator first, Sentinel last, std::forward_iterator_tag)
	{
		data.tail = std::uninitialized_copy(first, last, data.head);
	}
};
} // namespace aw
#endif//aw_containers_circular_buffer_h
