/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_containers_queue
#define aw_containers_queue
#include <cassert>
#include <memory>
#include <iterator>
#include <algorithm>
#include <aw/utility/exceptions.h>
#include <aw/meta/conditional.h>
#include <aw/types/traits/iterator.h>
#include <aw/types/containers/bits/shared.h>
#include <aw/types/containers/bits/traits.h>
#include <aw/types/containers/bits/cbuffer.h>

// TODO: insert and remove
// TODO: assign & assignment operators
// TODO: cleanup (allocation)

namespace aw {
namespace _impl {
template <typename Traits>
using queue_iterator = circular_iterator<Traits>;

struct queue_base_common {
	void length_error() const
	{
#if __cpp_exceptions
		throw std::length_error("aw::queue");
#else
		assert(!"length_error");
#endif
	}
};

template<typename T, typename Allocator>
struct queue_base : protected queue_base_common {
	using allocator_type   = Allocator;
	using allocator_traits = std::allocator_traits<Allocator>;
	using reference        = typename allocator_type::reference;
	using size_type        = typename allocator_type::size_type;
	using difference_type  = typename allocator_type::difference_type;
	using pointer          = typename allocator_type::pointer;

	/*! Get the allocator associated with the container. */
	allocator_type get_allocator() const noexcept
	{
		return {alloc()};
	}

	/*! Get the maximum number of elements that queue is able to hold. */
	size_type max_size() const noexcept
	{
		return allocator_traits::max_size(alloc());
	}

protected:
	queue_base() noexcept = default;
	queue_base(allocator_type const& a) noexcept
		: impl(a)
	{}

	queue_base(allocator_type const& a, size_type n)
	noexcept(std::is_nothrow_copy_constructible<Allocator>::value)
		: impl(a)
	{
		create_storage(n);
	}

	queue_base(allocator_type&& a)
	noexcept(std::is_nothrow_copy_constructible<Allocator>::value)
		: impl(std::move(a))
	{}

	queue_base(queue_base&& other) noexcept
		: impl(std::move(other.alloc()))
	{
		impl.swap(other.impl);
	}

	/*
	 * Move-construct with alternative allocator.
	 *
	 * If alloc != other.alloc, derived class must
	 * move other's data into new storage.
	 *
	 */
	queue_base(queue_base&& other, Allocator const& alloc) noexcept
		: impl(alloc)
	{
		if (alloc == other.alloc)
			impl.swap(other.impl);
		else
			create_storage(other.allocated_size());
	}

	template<typename Iterator>
	queue_base(Iterator first, Iterator last, Allocator const& alloc) noexcept
		: impl(alloc)
	{
		if (is_forward_iterator<Iterator>)
			create_storage(std::distance(first, last) + 1);
	}

	~queue_base() noexcept
	{
		deallocate(impl.begin, allocated_size());
	}

	allocator_type& alloc() noexcept
	{
		return *static_cast<Allocator*>(&impl);
	}

	allocator_type const& alloc() const noexcept
	{
		return *static_cast<Allocator const*>(&impl);
	}

	pointer allocate(size_type len)
	{
		if (len == 0)
			return nullptr;

		if (len > max_size())
			length_error();

		return allocator_traits::allocate(alloc(), len);
	}

	void deallocate(pointer p, size_type n)
	{
		if (p)
			allocator_traits::deallocate(alloc(), p, n);
	}

	size_type allocated_size() const noexcept
	{
		return static_cast<size_type>(impl.end - impl.begin);
	}

	struct impl : Allocator, cbuffer_data<T> {
		impl() noexcept = default;

		impl(Allocator const& a) noexcept
			: Allocator(a)
		{}

		impl(Allocator&& a) noexcept
			: Allocator(std::move(a))
		{ }

		void swap(impl& other) noexcept
		{
			cbuffer_data<T>::swap(other);
		}
	} impl;

private:
	void create_storage(size_type size)
	{
		impl.begin = allocate(size);
		impl.end   = impl.begin + size;
		impl.head  = impl.tail = impl.begin;
	}
};
} // namespace _impl

/*!
 * Queue allows efficient insertion and removal at * its both ends,
 * and constant-time access to elements in any order.
 *
 * Elements of queue are allocated within contiguous chunk of memory,
 * but aren't guaranteed to be contiguous withing that chunk (at maximum
 * elements are separated into two parts).
 */
template<typename T, typename Allocator = std::allocator<T>>
class queue : _impl::queue_base<T,Allocator> {
	using Base = _impl::queue_base<T,Allocator>;
public:
	using value_type       = T;
	using allocator_type   = Allocator;
	using allocator_traits = std::allocator_traits<Allocator>;
	using reference        = typename allocator_type::reference;
	using const_reference  = typename allocator_type::const_reference;
	using size_type        = typename allocator_type::size_type;
	using difference_type  = typename allocator_type::difference_type;
	using pointer          = typename allocator_type::pointer;
	using const_pointer    = typename allocator_type::const_pointer;
	using iterator         = _impl::queue_iterator<Allocator>;
	using const_iterator   = _impl::queue_iterator<_impl::const_traits<Allocator>>;
	using reverse_iterator       = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	friend iterator;
	friend const_iterator;

	using Base::get_allocator;
	using Base::max_size;

private:
	using Base::impl;
	using Base::alloc;
	using Base::allocate;
	using Base::deallocate;
	using Base::allocated_size;

public:
	/*! Create empty queue */
	queue() /*noexcept(noexcept(Allocator()))*/ = default;

	explicit queue(Allocator const& a)
	noexcept(std::is_nothrow_copy_constructible<Allocator>::value)
		: Base(a)
	{ }

	/*!
	 * Copy constructor.
	 * All ellements in \a q are copied into newly created queue.
	 * Extra space is not copied.
	 */
	queue(queue const& q)
		: Base(q.impl, q.size() + 1)
	{
		std::uninitialized_copy(q.begin(), q.end(), begin());
	}

	/*!
	 * Move constructor.
	 * Newly-created queue receives contents of \a q,
	 * \a q is left in a valid state.
	 */
	queue(queue&& q) noexcept
		: Base(std::move(q))
	{ }

	/*!
	 * Move constructor with alternative allocator.
	 * \note
	 * If `!(alloc == q.get_allocator())`, then operation is O(n).
	 */
	queue(queue&& q, Allocator const& alloc) noexcept
		: Base(q, alloc)
	{
		if (alloc != q.get_allocator()) {
			// If memory can't be managed with new allocator,
			// queue_base allocates new memory, but doesn't
			// move its contents.
			impl.tail = try_uninit_move(q.begin(), q.end(), impl.head);
		}
	}

	/*!
	 * Create queue with \a n copies of prototype \a val.
	 */
	queue(size_type n, const_reference val,
	      Allocator const& alloc = Allocator())
		: Base(alloc, n + 1)
	{
		impl.tail = std::uninitialized_fill_n(impl.begin, n, val);
	}

	/*!
	 * Create queue with \a n default-constructed elements
	 */
	queue(size_type n, Allocator const& alloc = Allocator())
		: queue(n, T{}, alloc)
	{ }


	/*!
	 * Construct queue from range
	 */
	template<typename Iterator,
	         typename = require_input_iterator<Iterator>>
	queue(Iterator first, Iterator last, Allocator const& alloc = Allocator())
		: Base(first, last, alloc)
	{
		using iter_traits = std::iterator_traits<Iterator>;
		using iter_cat    = typename iter_traits::iterator_category;
		range_init(first, last, iter_cat{});
	}

	/*!
	 * Create queue from an initializer list.
	 */
	queue(std::initializer_list<T> list, Allocator const& alloc = Allocator())
		: Base(alloc, list.size() + 1)
	{
		auto first = std::begin(list);
		auto last  = std::end(list);
		impl.tail  = std::uninitialized_copy(first, last, impl.head);
	}

	/*!
	 * Destructor.
	 * Destroys queue and all elements in it.
	 */
	~queue()
	{
		destroy(impl.head, impl.tail);
	}

	/*! Iterator to the front of queue */
	iterator begin()
	{
		return {impl.head, impl};
	}

	/*! Iterator to the front of queue */
	const_iterator begin() const
	{
		return {impl.head, impl};
	}

	/*! Iterator to the front of queue */
	const_iterator cbegin() const
	{
		return {begin()};
	}

	/*! Iterator to element past the end of queue */
	iterator end()
	{
		return {impl.tail, impl};
	}

	/*! Iterator to element past the end of queue */
	const_iterator end() const
	{
		return {impl.tail, impl};
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
		return end() - begin();
	}

	/*! Get queue capacity */
	size_type capacity() const noexcept
	{
		size_type cap = allocated_size();
		// need to keep one element free, so that
		// head doesn't step on its tail
		return cap ? cap - 1 : 0;
	}

	/*!
	 * Reserve space for n elements.
	 * Invalidates all iterators and refreneces if
	 * reallocation occurs.
	 */
	void reserve(size_type n)
	{
		if (n < capacity())
			reallocate(n + 1);
	}

	/*!
	 * Free up extra capacity.
	 *
	 * Invalidates all iterators and refreneces.
	 */
	bool shrink_to_fit()
	{
		if (capacity() > size())
			reallocate(size() + 1);
		return true;
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
		destroy(impl.head, impl.tail);
		impl.tail = impl.head;
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
		allocator_traits::destroy(alloc(), impl.head);
		impl.head = impl.next_p(impl.head);
	}

	/*!
	 * Destroy element at the back of queue
	 */
	void pop_back()
	{
		assert(!empty() && "pop_back() on empty queue.");
		impl.tail = impl.prev_p(impl.tail);
		allocator_traits::destroy(alloc(), impl.tail);
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
		check_capacity();

		impl.head = impl.prev_p(impl.head);
		construct(impl.head, std::forward<Args>(args)...);
	}

	/*!
	 * Construct element at the end of queue
	 */
	template <typename... Args>
	void emplace_back(Args&&... args)
	{
		check_capacity();

		construct(impl.tail, std::forward<Args>(args)...);
		impl.tail = impl.next_p(impl.tail);
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
		allocator_traits::construct(alloc(), p, std::forward<Args>(args)...);
	}

	void destroy(pointer head, pointer tail)
	{
		for (; head != tail; head = impl.next_p(head))
			allocator_traits::destroy(alloc(), head);
	}

	size_type next_size() const noexcept
	{
		constexpr size_type min_size = 16;
		size_type const old_size = allocated_size();
		return old_size + std::max(old_size, min_size);
	}

	void set_storage(pointer begin, pointer end)
	{
		destroy(impl.head, impl.tail);
		deallocate(impl.begin, allocated_size());

		impl.begin = begin;
		impl.end   = end;
	}

	void do_emplace_back()
	{

	}

	void reallocate(size_type new_size)
	{
		pointer new_begin{ allocate(new_size) };
		pointer new_tail = nullptr;

		aw_try {
			new_tail = _impl::try_uninit_move(begin(), end(), new_begin);
		} aw_catch(...) {
			if (new_tail)
				destroy(new_begin, new_tail);

			deallocate(new_begin, new_size);
			aw_rethrow;
		}

		set_storage(new_begin, new_begin + new_size);

		impl.head = new_begin;
		impl.tail = new_tail;
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
		impl.tail = std::uninitialized_copy(first, last, impl.head);
	}

	void check_capacity()
	{
		if (size() == capacity())
			reallocate(next_size());
	}
};

/*!
 * Compare queues.
 * Queues are considered equal if all elemets within are equal.
 */
template<typename T, typename Alloc>
bool operator==(const queue<T, Alloc>& q1, const queue<T, Alloc>& q2)
{
	return (q1.size() == q2.size()) &&
	        std::equal(q1.begin(), q1.end(), q2.begin());
}

/*!
 * Compare queues lexicographically.
 */
template<typename T, typename Alloc>
bool operator<(const queue<T, Alloc>& q1, const queue<T, Alloc>& q2)
{
	return std::lexicographical_compare(q1.begin(), q1.end(), q2.begin(), q2.end());
}

/*! Based on operator== */
template<typename T, typename Alloc>
bool operator!=(const queue<T, Alloc>& q1, const queue<T, Alloc>& q2)
{
	return !(q1 == q2);
}
/*! Based on operator< */
template<typename T, typename Alloc>
bool operator>(const queue<T, Alloc>& q1, const queue<T, Alloc>& q2)
{
	return q2 < q1;
}
/*! Based on operator< */
template<typename T, typename Alloc>
bool operator<=(const queue<T, Alloc>& q1, const queue<T, Alloc>& q2)
{
	return !(q2 < q1);
}
/*! Based on operator< */
template<typename T, typename Alloc>
bool operator>=(const queue<T, Alloc>& q1, const queue<T, Alloc>& q2)
{
	return !(q1 < q2);
}

} // namespace aw
#endif//aw_containers_queue
