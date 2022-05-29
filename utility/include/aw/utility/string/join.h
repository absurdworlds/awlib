/*
 * Copyright (C) 2014-2016  absurdworlds
 * Copyright (C) 2015-2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_join_h
#define aw_string_join_h
#include <numeric>
#include <aw/types/string_view.h>
#include <aw/algorithm/join.h>
namespace aw {
namespace string {
/*!
 * Concatenate \a strings into one string.
 */
template<typename... Strings>
std::string concatenate(Strings&&... strings)
{
	using std::size;
	std::string result; // TODO: check if memcpy() is faster than append
	// operator += takes const& so forward is unnecesary for now
	result.reserve((size(strings) + ... ));
	return ((result += strings), ...);
}

/*!
 * Create string with enough space reserved for all strings in the range [begin, end)
 */
template<typename Iterator>
std::string reserve_string(Iterator begin, Iterator end)
{
	size_t size = 0;
	while (begin != end)
		size += (begin++)->size();
	std::string tmp;
	tmp.reserve(size);
	return tmp;
}

/*!
 * \brief
 *      join strings together
 * \param source
 *      vector of strings to be joined
 * \param delim
 *      delimiting sequence which will be inserted between 
 *      joined strings
 * \return
 *      resulting string concatenated together
 */
template<typename Iterator>
std::string join(Iterator begin, Iterator end, string_view delim = "")
{
	if (begin == end)
		return {};

	std::string sink = reserve_string(begin, end);
	sink += *begin++;
	return aw::join(begin, end, sink, delim);
}

template<template<typename...> typename Container, typename StringT>
std::string join(Container<StringT> const& source, string_view delim = "")
{
	auto begin = source.begin();
	auto end   = source.end();
	return join(begin, end, delim);
}
} // namespace string
} // namespace aw
#endif//aw_string_join_h
