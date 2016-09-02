/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_containers_flat_map
#define aw_containers_flat_map
#include <cassert>
#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>
#include <aw/utility/exceptions.h>
#include <aw/types/traits/iterator.h>
#include <aw/types/traits/conditional.h>
#include <aw/types/containers/bits/shared.h>

namespace aw {
namespace _impl {
// Empty-base optimization
template<typename Compare>
struct flat_map_base : Compare {
	flat_map_base( Compare const& comp )
		: Compare(comp)
	{ }

	flat_map_base& operator=(flat_map_base const& other) = default;
	flat_map_base& operator=(flat_map_base&& other) = default;

	Compare key_comp() const
	{
		return *this;
	}
};
}
/*!
 * flat_map (sorted_vector) is a sorted associative container,
 * that contains key-value pairs with unqiue keys. Keys are sorted
 * using \a Compare.
 * Key-value pairs are placed contiguously in memory.
 * Search operation has logarithmic complexity/
 * Insertion and removal operations are O(log n) search time plus O(n)
 * in amount of elements with keys bigger than inserted element.
 */
template<typename Key,
         typename T,
         typename Compare = std::less<Key>,
         typename Allocator = std::allocator<std::pair<Key const, T>>
        >
struct flat_map : private _impl::flat_map_base<Compare> {
	using key_type    = Key;
	using mapped_type = T;
	//need to solve this somehow
	//using value_type  = std::pair<Key const, T>;
	using value_type  = std::pair<Key, T>;

	using base_container   = std::vector<value_type, Allocator>;

	using allocator_type   = Allocator;
	using allocator_traits = std::allocator_traits<Allocator>;
	using reference        = typename base_container::reference;
	using const_reference  = typename base_container::const_reference;
	using size_type        = typename base_container::size_type;
	using difference_type  = typename base_container::difference_type;
	using pointer          = typename base_container::pointer;
	using const_pointer    = typename base_container::const_pointer;

	using iterator               = typename base_container::iterator;
	using const_iterator         = typename base_container::const_iterator;
	using reverse_iterator       = typename base_container::reverse_iterator;
	using const_reverse_iterator = typename base_container::const_reverse_iterator;

private:
	base_container base;

	// TODO: get rid of comp_storage, use special pair type
	using comp_storage = _impl::flat_map_base<Compare>;
	bool compare_key(key_type const& a, key_type const& b)
	{
		return comp_storage::operator()(a, b);
	}

public:
	using key_compare = Compare;
	struct value_compare {
		friend class flat_map;
	protected:
		Compare comp;

		value_compare(Compare comp)
			: comp(comp)
		{ }
	
	public:
		bool operator()(value_type const& a, value_type const& b)
		{
			return comp(a.first, b.first);
		}
	};

	key_compare key_comp() const
	{
		return comp_storage::key_comp();
	}

	value_compare value_comp() const
	{
		return {key_comp()};
	}

	/*! Get the allocator associated with the container. */
	allocator_type get_allocator() const noexcept
	{
		return base.get_allocator();
	}

	/*! Get the maximum number of elements that map is able to hold. */
	size_type max_size() const noexcept
	{
		return base.max_size();
	}

	/*! Create empty map */
	flat_map()
		: base{}, comp_storage( Compare() )
	{ }

	explicit
	flat_map(Compare const& comp,
	         Allocator const& alloc = Allocator())
		: base(alloc), comp_storage( comp )
	{ }

	explicit
	flat_map(Allocator const& alloc)
		: base(alloc), comp_storage( Compare() )
	{ }

	/*!
	 * Copy constructor.
	 * All ellements in \a other are copied into newly created map.
	 * Extra space is not copied.
	 */
	flat_map(flat_map const& other)
		: base(other.base), comp_storage(other)
	{ }

	flat_map(flat_map const& other, Allocator const& alloc) noexcept
		: base(other.base, alloc), comp_storage(other)
	{ }

	/*!
	 * Move constructor.
	 * Newly-created map receives contents of \a other,
	 * \a other is left in a valid (but unspecified) state.
	 */
	flat_map(flat_map&& other) noexcept
		: base(std::move(other.base)), comp_storage(other)
	{ }

	/*!
	 * Move constructor with alternative allocator.
	 * \note
	 * If `!(alloc == q.get_allocator())`, then operation is O(n).
	 */
	flat_map(flat_map&& other, Allocator const& alloc) noexcept
		: base(std::move(other), alloc), comp_storage(other)
	{ }


	/*!
	 * Construct map from a (possibly unsorted) range.
	 */
	template<typename Iterator>
	flat_map(Iterator first, Iterator last,
	         Compare const& comp = Compare(),
	         Allocator const& alloc = Allocator())
		: base(first, last, alloc), comp_storage(comp)
	{
		normalize();
	}

	/*!
	 * Create map from an initializer list.
	 */
	flat_map(std::initializer_list<value_type> list,
	         Compare const& comp = Compare(),
	         Allocator const& alloc = Allocator())
		: base(list, alloc), comp_storage(comp)
	{
		normalize();
	}

	/*!
	 * Create map from an initializer list.
	 */
	flat_map(std::initializer_list<value_type> list,
	         Allocator const& alloc)
		: base(list, alloc), comp_storage( Compare() )
	{
		normalize();
	}

	~flat_map() = default;

	/*!
	 * Replaces contents with copy of \a other's contents.
	 */
	flat_map& operator=(flat_map const& other)
	{
		base = other.base;
		comp_storage::operator=(other);
		return *this;
	}

	/*!
	 * Moves contents of \a other's into *this;
	 */
	flat_map& operator=(flat_map&& other)
	{
		base = std::move(other.base);
		comp_storage::operator=(std::move(other));
		return *this;
	}

	/*!
	 * Replaces the contents with those identified by initializer list \a ilist.
	 */
	flat_map& operator=(std::initializer_list<value_type> ilist)
	{
		clear();
		base.reserve(ilist.size());
		std::copy(std::begin(ilist), std::end(ilist), std::back_inserter(base));
		normalize();
		return *this;
	}

	/*! Iterator to the front of map */
	iterator begin()
	{
		return base.begin();
	}

	/*! Iterator to the front of map */
	const_iterator begin() const
	{
		return base.begin();
	}

	/*! Iterator to the front of map */
	const_iterator cbegin() const
	{
		return {begin()};
	}

	/*! Iterator to element past the end of map */
	iterator end()
	{
		return base.end();
	}

	/*! Iterator to element past the end of map */
	const_iterator end() const
	{
		return base.end();
	}

	/*! Iterator to element past the end of map */
	const_iterator cend() const
	{
		return {end()};
	}

	/*! Reverse iterator to the end of map */
	reverse_iterator rbegin()
	{
		return {end()};
	}


	/*! Reverse iterator to the end of map */
	const_reverse_iterator rbegin() const
	{
		return {end()};
	}

	/*! Reverse iterator to the end of map */
	const_reverse_iterator crbegin() const
	{
		return {cend()};
	}

	/*! Reverse iterator to start of map */
	reverse_iterator rend()
	{
		return {begin()};
	}

	/*! Reverse iterator to start of map */
	const_reverse_iterator rend() const
	{
		return {begin()};
	}

	/*! Reverse iterator to start of map */
	const_reverse_iterator crend() const
	{
		return {cbegin()};
	}

	/*! Get number of elements in map */
	size_type size() const noexcept
	{
		return base.size();
	}

	/*! Get map capacity */
	size_type capacity() const noexcept
	{
		return base.capacity();
	}

	/*!
	 * Check if map is empty
	 */
	bool empty() const noexcept
	{
		base.empty();
	}

	/*!
	 * Reserve space for n elements.
	 * Invalidates all iterators and refreneces if reallocation occurs.
	 */
	void reserve(size_type n)
	{
		base.reserve(n);
	}

	/*!
	 * Free up extra capacity.
	 * Invalidates all iterators and refreneces.
	 */
	bool shrink_to_fit()
	{
		return base.shrink_to_fit();
	}

	/*!
	 * Erases all elements in map.
	 *
	 * \note
	 * It does not free allocated memory.
	 * If elements are pointers, memory pointed-to by them is not freed.
	 */
	void clear()
	{
		base.clear();
	}

	/*!
	 * Find first element that with key not less than \a key.
	 */
	iterator lower_bound(key_type const& key)
	{
		auto compare =
		[this] (value_type const& v, key_type const& k)
		{
			return this->compare_key(v.first, k);
		};
		return std::lower_bound(begin(), end(), key, compare);
	}

	/*!
	 * Find first element that with key not less than \a key.
	 */
	const_iterator lower_bound(key_type const& key) const
	{
		// ugly, but DRY
		return const_cast<flat_map*>(this)->lower_bound(key);
	}

	/*!
	 * Find element with key equivalent to \a key.
	 */
	iterator find(key_type const& key)
	{
		iterator pos = lower_bound(key);
		if (pos == end() || compare_key(key, pos->first))
			return end();
		return pos;
	}

	/*!
	 * Find element with key equivalent to \a key.
	 */
	const_iterator find(key_type const& key) const
	{
		return const_cast<flat_map*>(this)->find(key);
	}

	/*!
	 * Insert element into the map,
	 * if map doesn't already contain element with equivalent key
	 * \return
	 *    pair consisting of bool denoting whether insertion took place,
	 *    and iterator pointing to inserted element, or an element which
	 *    prevented insertion.
	 */
	std::pair<iterator,bool> insert(value_type const& pair)
	{
		iterator pos = lower_bound(pair.first);
		if (pos == end()) {
			base.push_back( pair );
			return {end() - 1, true};
		}

		if (compare_key(pair.first, pos->first)) {
			pos = base.insert( pos, pair );
			return {pos, true};
		}

		return {pos, false};
	}

	/*!
	 * Insert elements from range [first, last) into map.
	 */
	template<typename InputIt>
	void insert( InputIt first, InputIt last )
	{
		size_t len = size();
		/*
		if constexpr(is_forward_iterator<InputIt>)
			base.reserve(len + std::distance(first, last));
		 */
		std::copy(first, last, std::back_inserter(base));

		auto a_begin  = begin();
		auto a_middle = begin() + len;
		auto a_end    = end();

		std::inplace_merge(a_begin, a_middle, a_end, value_comp());
		remove_duplicates();
	}

	/*!
	 * Insert elements denoted by \a ilist into the map.
	 */
	void insert( std::initializer_list<value_type> ilist )
	{
		insert(begin(ilist), end(ilist));
	}

	/*!
	 * Construct element from \a args, and insert into the map.
	 */
	template<typename... Args>
	void emplace( Args&&... args )
	{
		// No idea how to optimize it.
		insert( value_type{ std::forward<Args>... } );
	}

	template<typename M>
	std::pair<iterator,bool> insert_or_assign(key_type const& key, M&& obj)
	{
		iterator pos = lower_bound(key);
		bool inserted = false;
		if (pos == end()) {
			base.push_back( value_type{key, std::forward<M>(obj)} );
			return {end() - 1, true};
		}

		if (compare_key(key, pos->first)) {
			pos = base.insert( pos, value_type{key, std::forward<M>(obj)} );
			return {pos, true};
		}

		*pos->second = std::forward<M>(obj);
		return {pos, false};
	}

	/*!
	 * Erase element pointed-to by interator \a pos.
	 */
	iterator erase(const_iterator pos)
	{
		return base.erase(pos);
	}

	/*!
	 * Erases element with \a key, if such exists
	 */
	iterator erase(key_type const& key)
	{
		auto pos = find(key);
		if (pos != end())
			return erase(pos);
		return pos;
	}

	/*!
	 * Returns reference to element with \a key.
	 * If element doesn't exist, it is created.
	 */
	mapped_type& operator[](key_type const& key)
	{
		iterator pos = lower_bound(key);
		if (pos == end())
#if __cpluspls >= 201700L // TODO: correct value
			return base.emplace_back( value_type{key, T{}} ).second;
#else
		{
			base.emplace_back( value_type{key, T{}} );
			return base.back().second;
		}
#endif

		if (compare_key(key, pos->first))
			pos = base.emplace( pos, value_type{key, T{}} );

		return pos->second;
	}

private:
	void remove_duplicates()
	{
		auto compare =
		[this] (value_type const& a, value_type const& b)
		{
			return !compare_key(a.first, b.first) &&
			       !compare_key(b.first, a.first);
		};
		base.erase( std::unique( begin(), end(), compare ), end() );
	}

	void sort()
	{
		std::sort( begin(), end(), value_comp() );
	}

	void normalize()
	{
		sort();
		remove_duplicates();
	}
};
} // namespace aw
#endif//aw_containers_flat_map
