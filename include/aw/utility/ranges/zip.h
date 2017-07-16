/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_ranges_zip_h
#define aw_utility_ranges_zid_h
#include <aw/utility/index_sequence.h>
#include <iterator>
#include <tuple>
namespace aw {
template <typename...Iters>
class zip_iterator {
	static constexpr make_index_sequence< sizeof...(Iters) > indices{};
public:
	zip_iterator(Iters...iters)
		: iters{iters...}
	{}

	auto operator*()
	{
		return deref( indices );
	}

	zip_iterator& operator++()
	{
		increment( indices );
		return *this;
	}

	std::tuple<Iters...> iters;

private:
	template <size_t...I>
	void increment( index_sequence<I...> )
	{
		( ++std::get<I>(iters), ... );
	}

	template <size_t...I>
	auto deref( index_sequence<I...> )
	{
		return std::tuple{ *std::get<I>(iters) ... };
	}

	template <typename...A, typename...B>
	friend bool operator==(zip_iterator<A...> const&, zip_iterator<B...> const&);
	template <typename...A, typename...B>
	friend bool operator!=(zip_iterator<A...> const&, zip_iterator<B...> const&);
	template <typename...A, typename...B>
	friend bool operator<(zip_iterator<A...> const&, zip_iterator<B...> const&);
};

template <typename...Is, typename...Js>
bool operator==(zip_iterator<Is...> const& a, zip_iterator<Js...> const& b)
{
	return a.iters == b.iters;
}

template <typename...Is, typename...Js>
bool operator!=(zip_iterator<Is...> const& a, zip_iterator<Js...> const& b)
{
	return a.iters != b.iters;
}

template <typename...Is, typename...Js>
bool operator<(zip_iterator<Is...> const& a, zip_iterator<Js...> const& b)
{
	return a.iters < b.iters;
}

/*!
 * Provides a way to iterate over multiple ranges
 */
template<typename...Ranges>
class zip {
	static constexpr make_index_sequence< sizeof...(Ranges) > indices{};

	template <size_t...I>
	auto begin( index_sequence<I...> )
	{
		using std::begin;
		return zip_iterator{ begin( std::get<I>(ranges) )... };
	}

	template <size_t...I>
	auto end( index_sequence<I...> )
	{
		using std::end;
		return zip_iterator{ end( std::get<I>(ranges) )... };
	}
public:

	zip(Ranges&&... ranges)
		: ranges{ranges...}
	{}

	auto begin()
	{
		return begin( indices );
	}

	auto end()
	{
		return end( indices );
	}


	std::tuple<Ranges&&...> ranges;

	using iterator = decltype(std::declval<zip>().begin());
};

template<typename...Ranges>
zip( Ranges&& ... ) -> zip<Ranges...>;
} // namespace aw
#endif//aw_utility_ranges_zip_h
