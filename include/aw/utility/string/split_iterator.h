/*
 * Copyright (C) 2014-2016  absurdworlds
 * Copyright (C) 2015-2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_substr_iterator_h
#define aw_string_substr_iterator_h
#include <cassert>
#include <aw/types/string_view.h>
#include <aw/utility/iterators/proxy.h>
namespace aw {
namespace string {
struct substring_iterator_base {
	string_view operator*() const
	{
		return source.substr(pos1, pos2 - pos1);
	}

	iter::proxy<string_view> operator->() const
	{
		return {*(*this)};
	}

	/*
	 * Compares two iterators.
	 * Result of comparing iterators constructed from
	 * inequal string_views is undefined.
	 */
	bool operator==(substring_iterator_base const& other) const
	{
		return pos1 == other.pos1 && pos2 == other.pos2;
	}

	/*
	 * Compares two iterators.
	 * Result of comparing iterators constructed from
	 * inequal string_views is undefined.
	 */
	bool operator!=(substring_iterator_base const& other) const
	{
		return pos1 != other.pos1 || pos2 != other.pos2;
	}

protected:
	static constexpr size_t npos = string_view::npos;

	substring_iterator_base() = default;
	substring_iterator_base(string_view source, string_view delim)
		: source{source}, delim{delim}
	{}

	string_view source;
	string_view delim;
	size_t pos1 = string_view::npos;
	size_t pos2 = string_view::npos;
};

struct split_by_iterator : substring_iterator_base {
	split_by_iterator() = default;
	split_by_iterator(string_view source, string_view delim)
		: substring_iterator_base{source, delim}
	{
		pos1 = source.find_first_not_of(delim);
		pos2 = source.find_first_of(delim, pos1);
	}

	split_by_iterator& begin()
	{
		return *this;
	}

	split_by_iterator end() const
	{
		return {};
	}

	split_by_iterator& operator++()
	{
		if (pos1 != npos) {
			pos1 = source.find_first_not_of(delim, pos2);
			pos2 = source.find_first_of(delim, pos1);
		}
		return *this;
	}

	split_by_iterator operator++(int)
	{
		split_by_iterator copy = *this;
		++*this;
		return copy;
	}
};

template<bool DiscardEmpty>
struct cut_iterator_base : substring_iterator_base {
	cut_iterator_base() = default;
	cut_iterator_base(string_view source, string_view delim)
		: substring_iterator_base{source, delim}
	{
		assert(!delim.empty());
		pos1 = 0;
		pos2 = source.find(delim, pos1);

		if /*constexpr*/ (DiscardEmpty)
			discard_empty();
	}

	cut_iterator_base& begin()
	{
		return *this;
	}

	cut_iterator_base end() const
	{
		return {};
	}

	cut_iterator_base& operator++()
	{
		if (pos2 == npos) {
			pos1 = npos;
			return *this;
		}

		advance();

		if /*constexpr*/ (DiscardEmpty)
			discard_empty();

		return *this;
	}

	cut_iterator_base operator++(int)
	{
		cut_iterator_base copy = *this;
		++*this;
		return copy;
	}

private:
	void advance()
	{
		pos1 = pos2 + delim.size();
		pos2 = source.find(delim, pos1);
	}

	void discard_empty()
	{
		while ( (*this)->empty() ) {
			if (pos2 != npos) {
				advance();
			} else {
				pos1 = npos;
				break;
			}
		}
	}
};

using split_iterator = cut_iterator_base<true>;
using cut_iterator   = cut_iterator_base<false>;
} // namespace string
} // namespace aw
#endif//aw_string_substr_iterator_h
