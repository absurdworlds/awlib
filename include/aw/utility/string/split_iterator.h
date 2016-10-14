/*
 * Copyright (C) 2014-2016  absurdworlds
 * Copyright (C) 2015-2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_split_h
#define aw_string_split_h
#include <aw/types/string_view.h>
namespace aw {
namespace string {
struct substring_iterator_base {
	string_view operator*() const
	{
		return source.substr(pos1, pos2 - pos1);
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

struct split_iterator : substring_iterator_base {
	split_iterator() = default;
	split_iterator(string_view source, string_view delim)
		: substring_iterator_base{source, delim}
	{
		pos1 = source.find_first_not_of(delim);
		pos2 = source.find_first_of(delim, pos1);
	}

	split_iterator& begin()
	{
		return *this;
	}

	split_iterator end() const
	{
		return {};
	}

	split_iterator& operator++()
	{
		if (pos1 != npos) {
			pos1 = source.find_first_not_of(delim, pos2);
			pos2 = source.find_first_of(delim, pos1);
		}
		return *this;
	}

	split_iterator operator++(int)
	{
		split_iterator copy = *this;
		++*this;
		return copy;
	}
};

struct slice_iterator : substring_iterator_base{
	slice_iterator() = default;
	slice_iterator(string_view source, string_view delim)
		: substring_iterator_base{source, delim}
	{
		pos1 = 0;
		pos2 = source.find_first_of(delim, pos1);
	}

	slice_iterator& begin()
	{
		return *this;
	}

	slice_iterator end() const
	{
		return {};
	}

	slice_iterator& operator++()
	{
		if (pos2 != npos) {
			pos1 = pos2 + 1;
			pos2 = source.find_first_of(delim, pos1);
		} else {
			pos1 = npos;
		}
		return *this;
	}

	slice_iterator operator++(int)
	{
		slice_iterator copy = *this;
		++*this;
		return copy;
	}
};

/*
#include <iostream>
int main()
{
	using namespace aw::string;
	for (auto s : split_iterator("a/b/c/d", "/"))
		std::cout << s << '\n';
	for (auto s : split_iterator("//aa//bb/cc///dd///", "/"))
		std::cout << s << '\n';

	for (auto s : slice_iterator("a/b/c/d", "/"))
		std::cout << s << '\n';
	for (auto s : slice_iterator("//aa//bb/cc///dd///", "/"))
		std::cout << s << '/';
	std::cout << "\b \n";
}
*/
} // namespace string
} // namespace aw
#endif//aw_string_split_h
