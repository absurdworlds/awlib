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
#include <aw/types/types.h>
#include <cassert>
#include <iterator>
#include <type_traits>
namespace aw {
template <typename T>
struct value_range {
	value_range(T begin, T end)
		: first(begin), last(end)
	{ }

	struct iterator {
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using reference  = T;
		using pointer    = void;
		using iterator_category = std::input_iterator_tag;
		using iterator_concept  = std::bidirectional_iterator_tag;

		iterator() = default;

		iterator(value_type v)
			: value(v)
		{ }

		reference operator*() const
		{
			return value;
		}

		iterator& operator++()
		{
			++value;
			return *this;
		}

		iterator operator++(int)
		{
			auto copy = *this;
			++value;
			return copy;
		}

		iterator& operator--()
		{
			--value;
			return *this;
		}

		iterator operator--(int)
		{
			auto copy = *this;
			--value;
			return copy;
		}

		friend std::strong_ordering operator<=>(iterator const& a, iterator const& b) = default;

	private:
		value_type value = value_type{};
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

//! \deprecated Old name for value_range.
template<typename T>
using Range [[deprecated("use value_range")]] = value_range<T>;

template<typename T>
value_range<T> range(T a, T z)
{
	assert(a < z);
	return value_range<T>(a, z);
}

template<typename T>
value_range<T> range(T end)
{
	return value_range<T>(T{}, end);
}

inline value_range<unsigned char> char_range(unsigned char a, unsigned char z)
{
	assert(a < z);
	return value_range<unsigned char>(a, z + 1);
}
} // namespace aw
#endif//aw_value_range_h
