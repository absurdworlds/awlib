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

// TODO: insert and remove
// TODO: assign
// TODO: cleanup (allocation)

namespace aw {
namespace _impl {
template<typename InputIt, typename ForwardIt>
ForwardIt try_uninit_move(InputIt begin, InputIt end, ForwardIt output)
{
	using T = typename std::iterator_traits<InputIt>::value_type;
	static_assert(std::is_nothrow_move_constructible<T>::value ||
	              std::is_copy_constructible<T>::value,
	              "Remove throw from your move constructor, you doofus!");

	constexpr bool do_move = std::is_nothrow_move_constructible<T>::value;

	using Iter = conditional<do_move, InputIt, std::move_iterator<InputIt>>;

	auto beg_it = Iter{begin};
	auto end_it = Iter{end};

	return std::uninitialized_copy(beg_it, end_it, output);
}

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

template<typename T, typename Allocator>
struct queue_base {
	using allocator_type   = Allocator;
	using allocator_traits = std::allocator_traits<Allocator>;
	using reference        = typename allocator_type::reference;
	using size_type        = typename allocator_type::size_type;
	using difference_type  = typename allocator_type::difference_type;
	using pointer          = typename allocator_type::pointer;

	allocator_type get_allocator() const noexcept
	{
		return {alloc()};
	}

protected:
	allocator_type& alloc() noexcept
	{
		return *static_cast<allocator_type*>(&impl);
	}

	allocator_type const& alloc() const noexcept
	{
		return *static_cast<allocator_type*>(&impl);
	}

	pointer allocate(size_type len)
	{
		if (len == 0)
			return nullptr;
		return allocator_traits::allocate(alloc(), len);
	}

	void deallocate(pointer p, size_type n)
	{
		if (p)
			allocator_traits::deallocate(alloc(), p, n);
	}

	queue_base() noexcept = default;
	queue_base(allocator_type const& a) noexcept
		: impl(a)
	{}

	queue_base(allocator_type&& a) noexcept
		: impl(std::move(a))
	{}

	queue_base(queue_base&& other)
		: impl(std::move(other.alloc()))
	{
		impl.swap(other.impl);
	}

	queue_base(queue_base&& other, allocator_type const a)
		: impl(a)
	{
		impl.swap(other.impl);
	}

	~queue_base() noexcept
	{
		deallocate(impl.begin, impl.end - impl.begin + 1);
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

private:
	using Base::impl;
	using Base::alloc;
	using Base::allocate;
	using Base::deallocate;

	template<typename Iterator, typename Sentinel>
	void range_init(Iterator first, Sentinel last, std::input_iterator_tag)
	{
		for (; first != last; ++first)
			emplace_back(*first);
	}

	template<typename Iterator, typename Sentinel>
	void range_init(Iterator first, Sentinel last, std::forward_iterator_tag)
	{
		size_type const size = std::distance(first, last);
		impl.begin = allocate(size);
		impl.end   = impl.begin + size;
		impl.head  = impl.begin;
		impl.end   = std::uninitialized_copy(first, last, impl.head);
	}

	size_type allocated_size() const noexcept
	{
		return static_cast<size_type>(impl.end - impl.begin);
	}

public:
	/*! Create empty queue */
	queue() /*noexcept(noexcept(Allocator()))*/ = default;

	explicit queue(Allocator const& a)
	noexcept(std::is_nothrow_copy_constructible<Allocator>::value)
		: Base(a)
	{ }

	queue(queue const& q)
		: Base(q.impl)
	{
		reallocate(q.size());
		std::uninitialized_copy(q.begin(), q.end(), begin());
	}

	queue(queue&& q) noexcept
		: Base(q)
	{ }

	queue(std::initializer_list<value_type> l,
	      Allocator const& a = Allocator())
		: Base(a)
	{
		for (auto& val : l)
			emplace_back(val);
	}

	template<typename Iterator, typename Sentinel>
	queue(Iterator first, Sentinel last,
	      Allocator const& a = Allocator())
		: Base(a)
	{
		using iter_cat = typename std::iterator_traits<Iterator>::iterator_category;
		range_init(first, last, iter_cat{});
	}

	~queue()
	{
		destroy(impl.head, impl.tail);
	}

	// TODO: assignment operators

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
			reallocate(n);
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
		if (!empty()) {
			allocator_traits::destroy(alloc(), impl.head);
			impl.head = next_p(impl.head);
		}

	}
	/*!
	 * Destroy element at the back of queue
	 */
	void pop_back()
	{
		if (!empty()) {
			impl.tail = prev_p(impl.tail);
			allocator_traits::destroy(alloc(), impl.tail);
		}
	}

	/*!
	 * Insert element at the front of queue
	 */
	void push_front(const_reference val)
	{
		check_capacity();

		impl.head = prev_p(impl.head);
		allocator_traits::construct(alloc(), impl.head, val);
	}

	/*!
	 * Insert element at the end of queue
	 */
	void push_back(const_reference val)
	{
		check_capacity();

		allocator_traits::construct(alloc(), impl.tail, val);
		impl.tail = next_p(impl.tail);
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
	void emplace_front(Args... args)
	{
		check_capacity();

		impl.head = prev_p(impl.head);
		allocator_traits::construct(alloc(), impl.head, std::forward<Args>(args)...);
	}

	/*!
	 * Construct element at the end of queue
	 */
	template <typename... Args>
	void emplace_back(Args... args)
	{
		check_capacity();

		allocator_traits::construct(alloc(), impl.tail, std::forward<Args>(args)...);
		impl.tail = next_p(impl.tail);
	}

	/*! Get element at the head of queue */
	value_type front() const
	{
		return *begin();
	}

	/*! Get element at the head of queue */
	value_type& front() noexcept
	{
		return *begin();
	}

	/*! Get element at the tail of queue */
	value_type back() const
	{
		return *(end() - 1);
	}

	/*! Get element at the tail of queue */
	value_type& back() noexcept
	{
		return *(end() - 1);
	}

	value_type operator[](size_type n) const
	{
		return begin()[n];
	}

	value_type& operator[](size_type n) noexcept
	{
		return begin()[n];
	}

private:
	void destroy(pointer head, pointer tail)
	{
		for (; head != tail; head = next_p(head))
			allocator_traits::destroy(alloc(), head);
	}

	template<typename P>
	P next_p(P p) const noexcept
	{
		// [h===========t|  ] => [h============t| ]
		// [h=============t|] => [H==============t]
		// [=====t|  h======] => [======t| h======]
		// [=======t|h======] => [========tH======]
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
		// [=========|++++ ]
		if (n < impl.end - p)
			return p + n;

		// [xx|=========|++]xx
		return p + n - allocated_size(); // == begin + n - (end - p)
	}

	template<typename P>
	P sub_p(P p, difference_type n) const noexcept
	{
		if (n <= p - impl.begin)
			return p - n;
		return p - n + allocated_size(); // == end - n + (p - begin)
	}

	//! Map pointer from circular to linear space
	template<typename P>
	P map_p(P p) const noexcept
	{
		// [----p==t      h++++] => [----++++p
		if (p < impl.head)
			return p + (impl.end - impl.head);
		// [  h---------p==t   ] => [--------p
		return impl.begin + (p - impl.head);
	}

	size_type next_size() const noexcept
	{
		constexpr size_type min_size = 16;
		size_type const old_size = allocated_size();
		return old_size + std::max(old_size, min_size);
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

	void check_capacity()
	{
		if (size() == capacity())
			reallocate(next_size());
	}
};
} // namespace aw
#endif//aw_containers_queue
