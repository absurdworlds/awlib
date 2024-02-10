/*
 * Copyright (C) 2017  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_freelist_vector_h
#define aw_freelist_vector_h
#include <cassert>
#include <cstddef>
#include <string>
#include <algorithm>
#include <aw/meta/conditional.h>
#include <aw/types/traits/is_flat_container.h>

namespace aw {
template<typename Integer>
constexpr Integer clear_top_bits(Integer i, unsigned n)
{
	return ((i << n) >> n);
}

/*!
 *
 */
template<typename T>
struct freelist_vector {
	using size_type  = std::size_t;
	using value_type = T;
	using pointer    = T*;
	using reference  = T&;

	using iterator   = T*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_iterator = T const*;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	constexpr size_type sz = clear_top_bits(std::numeric_limits<size_t>::max(), 1);


	pointer begin;
	pointer end;
	pointer last;

	size_t first_free;
	std::vector<size_t> freelist;

	struct item2 {
		item1 info;
		T value;
	};


	array_ref() = default;

	template<size_t N>
	constexpr array_ref(T (&array)[N])
		: _data{array}, _size{N}
	{}

	constexpr array_ref(T* ptr, size_t length)
		: _data{ptr}, _size{length}
	{ }

	template<typename C, typename = enable_if<is_flat_container<C>>>
	constexpr array_ref( C& cont )
		: array_ref{cont.data(), cont.size()}
	{ }

	array_ref& operator=(array_ref const&) = default;
	//array_ref& operator=(array_ref&&) = default;

	constexpr void swap(array_ref& other)
	{
		std::swap(_data, other._data);
		std::swap(_size, other._size);
	}

	constexpr iterator begin() { return _data; }
	constexpr iterator end()   { return _data + _size; }

	constexpr const_iterator begin()  const { return _data; }
	constexpr const_iterator end()    const { return _data + _size; }
	constexpr const_iterator cbegin() const { return begin(); }
	constexpr const_iterator cend()   const { return end(); }

	constexpr auto rbegin() { return reverse_iterator{end()}; }
	constexpr auto rend()   { return reverse_iterator{begin()}; }

	constexpr auto rbegin()  const { return const_reverse_iterator{end()}; }
	constexpr auto rend()    const { return const_reverse_iterator{begin()}; }
	constexpr auto crbegin() const { return rbegin(); }
	constexpr auto crend()   const { return rend(); }

	constexpr size_t size() const { return _size; }
	constexpr bool  empty() const { return begin() == end(); }

	constexpr T& operator[](size_t idx) { return _data[idx]; }
	constexpr T* data()  { return _data; }
	constexpr T& front() { return _data[0]; }
	constexpr T& back()  { return _data[_size]; }

	constexpr T const& operator[](size_t idx) const { return _data[idx]; }
	constexpr T const* data()  const { return _data; }
	constexpr T const& front() const { return _data[0]; }
	constexpr T const& back()  const { return _data[_size]; }

	constexpr array_ref slice(size_t pos, size_t end) const
	{
		assert(end <= size());
		assert(pos <= end);

		return {data() + pos, end - pos};
	}

	constexpr void remove_prefix(size_t n)
	{
		assert(n <= _size);
		_data += n;
		_size -= n;
	}

	constexpr void remove_suffix(size_t n)
	{
		assert(n <= _size);
		_size -= n;
	}

};
} // namespace aw
#endif//aw_freelist_vector_h
