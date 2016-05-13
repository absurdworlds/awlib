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
#include <aw/types/traits/conditional.h>
#include <aw/types/containers/bits/shared.h>

// TODO: insert and remove
// TODO: assign & assignment operators
// TODO: cleanup (allocation)

namespace aw {
namespace _impl {
template <typename Traits>
struct const_traits {
	using value_type        = typename Traits::value_type;
	using pointer           = typename Traits::const_pointer;
	using reference         = typename Traits::const_reference;
	using difference_type   = typename Traits::difference_type;
};

template <typename Queue, typename Traits>
class queue_iterator {
public:
	using value_type        = typename Traits::value_type;
	using pointer           = typename Traits::pointer;
	using reference         = typename Traits::reference;
	using difference_type   = typename Traits::difference_type;
	using iterator_category = std::random_access_iterator_tag;

	using iterator = queue_iterator;

private:
	Queue const* q = nullptr;
	pointer p      = nullptr;

	pointer map() const noexcept
	{
		return q->map_p(p);
	}

public:
	queue_iterator() noexcept = default;

	queue_iterator(Queue const& q, pointer p) noexcept
		: q(&q), p(p)
	{}

	queue_iterator(iterator const& other) noexcept
		: q(other.q), p(other.p)
	{
	}

	iterator& operator=(iterator const& other)
	{
		q = other.q;
		p = other.p;
	}

	reference operator*() const noexcept
	{
		return *p;
	}

	pointer operator->() const noexcept
	{
		return &(operator*());
	}

	iterator& operator++() noexcept
	{
		p = q->next_p(p);
		return *this;
	}

	iterator operator++(int) noexcept
	{
		iterator tmp{*this};
		++(*this);
		return tmp;
	}

	iterator& operator+=(difference_type n) noexcept
	{
		p = q->add_p(p, n);
		return *this;
	}

	friend iterator operator+(iterator i, difference_type n) noexcept
	{
		return i += n;
	}

	friend iterator operator+(difference_type n, iterator i) noexcept
	{
		return i += n;
	}

	reference operator[](difference_type n) const noexcept
	{
		return *(*this + n);
	}

	iterator& operator--() noexcept
	{
		p = q->prev_p(p);
		return *this;
	}

	iterator operator--(int) noexcept
	{
		iterator tmp{*this};
		--(*this);
		return tmp;
	}

	iterator& operator-=(difference_type n) noexcept
	{
		p = q->sub_p(p, n);
		return *this;
	}

	friend iterator operator-(iterator i, difference_type n) noexcept
	{
		return i -= n;
	}

	friend difference_type
	operator-(iterator const& a, iterator const& b) noexcept
	{
		return a.map() - b.map();
	}

	bool operator==(iterator const& other) const noexcept
	{
		//return (map() == other.map());
		return p == other.p;
	}

	bool operator!=(iterator const& other) const noexcept
	{
		//return (map() != other.map());
		return p != other.p;
	}

	bool operator<(iterator const& other) const noexcept
	{
		return (map() < other.map());
	}

	bool operator>(iterator const& other) const noexcept
	{
		return (map() > other.map());
	}

	friend bool operator>=(iterator const& a, iterator const b) noexcept
	{
		return !(a < b);
	}

	friend bool operator<=(iterator const& a, iterator const b) noexcept
	{
		return !(a > b);
	}
};

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

	queue_base(allocator_type&& a)
	noexcept(std::is_nothrow_copy_constructible<Allocator>::value)
		: impl(std::move(a))
	{}

	queue_base(queue_base&& other) noexcept
		: impl(std::move(other.alloc()))
	{
		impl.swap(other.impl);
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


	struct impl : Allocator {
		impl() noexcept = default;

		impl(Allocator const& a) noexcept
			: Allocator(a)
		{}

		impl(Allocator&& a) noexcept
			: Allocator(std::move(a))
		{ }

		void swap(impl& other) noexcept
		{
			std::swap(head,  other.head);
			std::swap(tail,  other.tail);
			std::swap(begin, other.begin);
			std::swap(end,   other.end);
		}

		pointer head = nullptr;
		pointer tail = nullptr;
		pointer begin = nullptr;
		pointer end   = nullptr;
	} impl;
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
	using iterator         = _impl::queue_iterator<queue, Allocator>;
	using const_iterator   = _impl::queue_iterator<queue, _impl::const_traits<Allocator>>;
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
		: Base(q.impl)
	{
		create_storage(q.size());
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
		: Base(alloc)
	{
		if (alloc == q.get_allocator()) {
			swap(q);
		} else {
			// Can't use alloc to manage different memory ):
			create_storage(std::distance(q.begin(), q.end()));

			impl.tail = try_uninit_move(q.begin(), q.end(), impl.head);
		}
	}

	/*!
	 * Create queue with \a n default-constructed elements
	 */
	queue(size_type n, Allocator const& alloc = Allocator())
		: Base(alloc)
	{
		create_storage(n);

		for (; n > 0; --n)
			emplace_back();
	}

	/*!
	 * Create queue with \a n copies of prototype \a val.
	 */
	queue(size_type n, const_reference val,
	      Allocator const& alloc = Allocator())
		: Base(alloc)
	{
		create_storage(n);

		for (; n > 0; --n)
			emplace_back(val);
	}

	/*!
	 * Create queue from an initializer list.
	 */
	queue(std::initializer_list<value_type> list,
	      Allocator const& alloc = Allocator())
		: Base(alloc)
	{
		range_init(std::begin(list), std::end(list));
	}

	/*!
	 * Create from range
	 */
	template<typename Iterator, typename = _impl::is_input_iter<Iterator>>
	queue(Iterator first, Iterator last,
	      Allocator const& a = Allocator())
		: Base(a)
	{
		range_init(first, last);
	}

	~queue()
	{
		destroy(impl.head, impl.tail);
	}



	/*! Iterator to the front of queue */
	iterator begin()
	{
		return {*this, impl.head};
	}

	/*! Iterator to the front of queue */
	const_iterator begin() const
	{
		return {*this, impl.head};
	}

	/*! Iterator to the front of queue */
	const_iterator cbegin() const
	{
		return {begin()};
	}

	/*! Iterator to element past the end of queue */
	iterator end()
	{
		return {*this, impl.tail};
	}

	/*! Iterator to element past the end of queue */
	const_iterator end() const
	{
		return {*this, impl.tail};
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
		impl.head = next_p(impl.head);
	}

	/*!
	 * Destroy element at the back of queue
	 */
	void pop_back()
	{
		assert(!empty() && "pop_back() on empty queue.");
		impl.tail = prev_p(impl.tail);
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

		impl.head = prev_p(impl.head);
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
		impl.tail = next_p(impl.tail);
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
		for (; head != tail; head = next_p(head))
			allocator_traits::destroy(alloc(), head);
	}

	template<typename P>
	P next_p(P p) const noexcept
	{
		if (p + 1 == impl.end)
			return impl.begin;
		return p + 1;
	}

	template<typename P>
	P prev_p(P p) const noexcept
	{
		if (p == impl.begin)
			return impl.end - 1;
		return p - 1;
	}

	template<typename P>
	P add_p(P p, difference_type n) const noexcept
	{
		if (n < impl.end - p)
			return p + n;

		return p + n - allocated_size();
	}

	template<typename P>
	P sub_p(P p, difference_type n) const noexcept
	{
		if (n <= p - impl.begin)
			return p - n;
		return p - n + allocated_size();
	}

	//! Map pointer from circular to linear space
	template<typename P>
	P map_p(P p) const noexcept
	{
		if (p < impl.head)
			return p + (impl.end - impl.head);
		return impl.begin + (p - impl.head);
	}

	size_type next_size() const noexcept
	{
		constexpr size_type min_size = 16;
		size_type const old_size = allocated_size();
		return old_size + std::max(old_size, min_size);
	}

	void create_storage(size_type size)
	{
		impl.begin = allocate(size + 1);
		impl.end   = impl.begin + size + 1;
		impl.head  = impl.begin;
		impl.tail  = impl.begin;
	}

	void reallocate(size_type new_size)
	{
		pointer new_begin{ allocate(new_size) };
		pointer new_tail = nullptr;

		AW__try {
			new_tail = _impl::try_uninit_move(begin(), end(), new_begin);
		} AW__catch(...) {
			if (new_tail)
				destroy(new_begin, new_tail);

			deallocate(new_begin, new_size);

			AW__rethrow;
		}

		destroy(impl.head, impl.tail);
		deallocate(impl.begin, allocated_size());

		impl.begin = new_begin;
		impl.end   = new_begin + new_size;

		impl.head = new_begin;
		impl.tail = new_tail;
	}


	template<typename Iterator, typename Sentinel>
	void range_init_a(Iterator first, Sentinel last, std::input_iterator_tag)
	{
		create_storage(std::distance(first, last));

		for (; first != last; ++first)
			emplace_back(*first);
	}

	template<typename Iterator, typename Sentinel>
	void range_init_a(Iterator first, Sentinel last, std::forward_iterator_tag)
	{
		create_storage(std::distance(first, last));

		impl.tail  = std::uninitialized_copy(first, last, impl.head);
	}

	template<typename Iterator, typename Sentinel>
	void range_init(Iterator first, Sentinel last)
	{
		using iter_cat = typename std::iterator_traits<Iterator>::iterator_category;
		range_init_a(first, last, iter_cat{});
	}



	void check_capacity()
	{
		if (size() == capacity())
			reallocate(next_size());
	}
};
} // namespace aw
#endif//aw_containers_queue
