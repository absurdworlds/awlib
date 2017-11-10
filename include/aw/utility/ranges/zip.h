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
#define aw_utility_ranges_zip_h
#include <aw/utility/functional/forward.h>
#include <iterator>
#include <tuple>
namespace aw {
template <typename...Iters>
struct zip_iterator {
	constexpr zip_iterator(Iters...iters)
		: iters{iters...}
	{}

	constexpr auto operator*()
	{
		auto dereference = [] (auto&&... ps)
		{
			return std::tuple{ (*forward<decltype(ps)>(ps)) ... };
		};
		return std::apply( dereference, iters );
	}

	constexpr zip_iterator& operator++()
	{
		auto increment = [] (auto&&... ps)
		{
			return std::tuple{ (++forward<decltype(ps)>(ps)) ... };
		};
		std::apply( increment, iters );
		return *this;
	}

	template <typename...Is, typename...Js> friend constexpr
	bool operator==(zip_iterator<Is...> const& a, zip_iterator<Js...> const& b);
	template <typename...Is, typename...Js> friend constexpr
	bool operator!=(zip_iterator<Is...> const& a, zip_iterator<Js...> const& b);
	template <typename...Is, typename...Js> friend constexpr
	bool operator<(zip_iterator<Is...>  const& a, zip_iterator<Js...> const& b);

private:
	std::tuple<Iters...> iters;
};

template <typename...Is, typename...Js>
constexpr bool operator==(zip_iterator<Is...> const& a, zip_iterator<Js...> const& b)
{
	return a.iters == b.iters;
}

template <typename...Is, typename...Js>
constexpr bool operator!=(zip_iterator<Is...> const& a, zip_iterator<Js...> const& b)
{
	return a.iters != b.iters;
}

template <typename...Is, typename...Js>
constexpr bool operator<(zip_iterator<Is...> const& a, zip_iterator<Js...> const& b)
{
	return a.iters < b.iters;
}

/*!
 * Provides a way to iterate over multiple ranges
 */
template<typename...Ranges>
struct zip {
	constexpr zip(Ranges&&... ranges)
		: ranges{ranges...}
	{}

	constexpr auto begin()
	{
		auto _begin = [] (auto&&... ps)
		{
			using std::begin;
			return zip_iterator{ begin( forward<decltype(ps)>(ps) ) ... };
		};
		return std::apply( _begin, ranges );
	}

	constexpr auto end()
	{
		auto _end = [] (auto&&... ps)
		{
			using std::end;
			return zip_iterator{ end( forward<decltype(ps)>(ps) ) ... };
		};
		return std::apply( _end, ranges );
	}

	std::tuple<Ranges&&...> ranges;

	using iterator = decltype(std::declval<zip>().begin());
};

template<typename...Ranges>
zip( Ranges&& ... ) -> zip<Ranges...>;
} // namespace aw
#endif//aw_utility_ranges_zip_h
