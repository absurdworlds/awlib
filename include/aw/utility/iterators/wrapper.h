/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_iterators_wrapper_h
#define aw_iterators_wrapper_h
#include <aw/utility/iterators/proxy.h>
namespace aw {
namespace iter {

template<typename T>
struct default_converter {
	template<typename F>
	constexpr T operator()(F&& val) const
	{
		return { val };
	}
};

/*!
 * Helper class to use iterator as though it has `value type = T`
 *
 * For example, to iterate through `vector<unique_ptr<V>>` as
 * though it is `vector<V*>`.
 */
template <typename Iterator, typename T, typename Convert = default_converter<T>>
struct wrapper : Iterator, protected Convert {
	using base_type = Iterator;

	using difference_type = std::ptrdiff_t;

	// TODO: should I write *actual* types in here?
	using value_type = T;
	using reference  = T&;
	using pointer    = T*;

	using iterator_category = typename Iterator::iterator_category;

	constexpr wrapper(Iterator base)
		: Iterator{base}
	{}

	constexpr value_type operator*() const
	{
		return operator()( Iterator::operator*() );
	}

	constexpr proxy<value_type> operator->() const
	{
		return { operator*() };
	}

	constexpr wrapper& operator++()
	{
		Iterator::operator++();
		return *this;
	}

	constexpr wrapper operator++(int)
	{
		wrapper copy = *this;
		Iterator::operator++();
		return copy;
	}

	constexpr wrapper& operator--()
	{
		Iterator::operator--();
		return *this;
	}

	constexpr wrapper operator--(int)
	{
		wrapper copy = *this;
		Iterator::operator--();
		return copy;
	}

private:
	using Convert::operator();
};
} // namespace iter
} // namespace aw
#endif//aw_iterators_wrapper_h
