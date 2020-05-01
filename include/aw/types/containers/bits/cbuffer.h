/*
 * Copyright (C) 2018  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_containers_cbuffer_h
#define aw_containers_cbuffer_h
namespace aw {
namespace _impl {
template<typename T>
struct cbuffer_data {
	using pointer = T*;
	using const_pointer = T const*;
	using difference_type = ptrdiff_t;

	pointer begin = nullptr;
	pointer end   = nullptr;
	pointer head  = nullptr;
	pointer tail  = nullptr;

	void swap(cbuffer_data& other) noexcept
	{
		std::swap(begin, other.begin);
		std::swap(end,   other.end);
		std::swap(head,  other.head);
		std::swap(tail,  other.tail);
	}

	pointer next_p(pointer p) const noexcept
	{
		if (p + 1 == end)
			return begin;
		return p + 1;
	}

	pointer prev_p(pointer p) const noexcept
	{
		if (p == begin)
			return end - 1;
		return p - 1;
	}

	pointer add_p(pointer p, difference_type n) const noexcept
	{
		if (n < end - p)
			return p + n;

		return (p + n) - end + begin;
	}

	pointer sub_p(pointer p, difference_type n) const noexcept
	{
		if (n <= p - begin)
			return p - n;
		return (p - n) + (end - begin);
	}

	pointer map_p(pointer p) const noexcept
	{
		if (p < head)
			return p + (end - head);
		return begin + (p - head);
	}

	const_pointer next_p(const_pointer p) const noexcept
	{
		return next_p( const_cast<pointer>(p) );
	}
	const_pointer prev_p(const_pointer p) const noexcept
	{
		return prev_p( const_cast<pointer>(p) );
	}
	const_pointer add_p(const_pointer p, difference_type n) const noexcept
	{
		return add_p( const_cast<pointer>(p), n );
	}
	const_pointer sub_p(const_pointer p, difference_type n) const noexcept
	{
		return sub_p( const_cast<pointer>(p), n );
	}
	const_pointer map_p(const_pointer p) const noexcept
	{
		return map_p( const_cast<pointer>(p) );
	}
};

template<typename Traits>
struct circular_iterator {
	using value_type        = typename Traits::value_type;
	using pointer           = typename Traits::pointer;
	using reference         = typename Traits::reference;
	using difference_type   = typename Traits::difference_type;
	using iterator_category = std::random_access_iterator_tag;

	using iterator = circular_iterator;

	circular_iterator() noexcept = default;

	circular_iterator(pointer p, cbuffer_data<value_type> data) noexcept
		: data{data}, p{p}
	{
	}

	circular_iterator(iterator const& other) noexcept
		: data{other.data}, p{other.p}
	{
	}

	iterator& operator=(iterator const& other) noexcept
	{
		data = other.data;
		p = other.p;
		return *this;
	}

	//----------------------------------------------------------------
	reference operator*() const noexcept
	{
		return *p;
	}

	pointer operator->() const noexcept
	{
		return &(operator*());
	}

	reference operator[](difference_type n) const noexcept
	{
		return *(*this + n);
	}

	//----------------------------------------------------------------
	iterator& operator--() noexcept
	{
		p = data.prev_p(p);
		return *this;
	}

	iterator operator--(int) noexcept
	{
		iterator tmp{*this};
		--(*this);
		return tmp;
	}

	iterator& operator++() noexcept
	{
		p = data.next_p(p);
		return *this;
	}

	iterator operator++(int) noexcept
	{
		iterator tmp{*this};
		++(*this);
		return tmp;
	}

	//----------------------------------------------------------------
	iterator& operator+=(difference_type n) noexcept
	{
		p = data.add_p(p, n);
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

	//----------------------------------------------------------------
	iterator& operator-=(difference_type n) noexcept
	{
		p = data.sub_p(p, n);
		return *this;
	}

	friend iterator operator-(iterator i, difference_type n) noexcept
	{
		return i -= n;
	}

	//----------------------------------------------------------------
	friend difference_type
	operator-(iterator const& a, iterator const& b) noexcept
	{
		return a.map() - b.map();
	}

	//----------------------------------------------------------------
	bool operator==(iterator const& other) const noexcept
	{
		return p == other.p;
	}

	bool operator!=(iterator const& other) const noexcept
	{
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

	friend bool operator>=(iterator const& a, iterator const& b) noexcept
	{
		return !(a < b);
	}

	friend bool operator<=(iterator const& a, iterator const& b) noexcept
	{
		return !(a > b);
	}

protected:
	pointer map() const
	{
		return data.map_p( p );
	}

private:
	cbuffer_data<value_type> data;
	pointer p = nullptr;
};

} // namespace _impl
} // namespace aw
#endif//aw_containers_cbuffer_h
