/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_value_range_h
#define aw_value_range_h
#include <cassert>
#include <type_traits>
#include <aw/types/types.h>
namespace aw {
template <typename T>
struct Range {
	Range(T begin, T end)
		: first(begin), last(end)
	{ }

	struct iterator {
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using reference  = T&;
		using pointer    = T*;
		using iterator_category = std::input_iterator_tag;

		iterator(value_type v)
			: value(v)
		{ }

		reference operator*()
		{
			return value;
		}

		pointer operator->()
		{
			return &value;
		}

		iterator& operator++()
		{
			++value;
			return *this;
		}

		iterator& operator--()
		{
			--value;
			return *this;
		}

		bool operator==(iterator const& other)
		{
			return value == other.value;
		}

		bool operator!=(iterator const& other)
		{
			return value != other.value;
		}

	private:
		value_type value;
	};

	using reverse_iterator = std::reverse_iterator<iterator>;

	iterator begin()
	{
		return iterator(first);
	}

	iterator end()
	{
		return iterator(last);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator{end()};
	}

	reverse_iterator rend()
	{
		return reverse_iterator{begin()};
	}

private:
	T first;
	T last;
};

template<typename T>
Range<T> range(T a, T z)
{
	assert(a < z);
	return Range<T>(a, z);
}

template<typename T>
Range<T> range(T end)
{
	return Range<T>(T{}, end);
}

Range<unsigned char> char_range(unsigned char a, unsigned char z)
{
	assert(a < z);
	return Range<unsigned char>(a, z + 1);
}
} // namespace aw
#endif//aw_value_range_h
