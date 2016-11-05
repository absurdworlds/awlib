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
#include <vector>
#include <numeric>
#include <aw/types/string_view.h>
#include <aw/algorithm/join.h>
namespace aw {
namespace string {
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
inline std::string
join(std::vector<string_view> const& source, string_view delim = "")
{
	auto begin = source.begin();
	auto end   = source.end();

	if (begin == end)
		return {};

	size_t size = 0;
	for (string_view s : source)
		size += s.size();

	/* TODO: wait for C++17 */
	auto append = [] (std::string& s, string_view sv)
	{
		s.append(sv.data(), sv.size());
	};

	std::string sink;
	sink.reserve(size);
	//sink += *begin++;
	append(sink, *begin++);
	return aw::join(begin, end, sink, delim, append);
}
} // namespace string
} // namespace aw
#endif//aw_string_join_h
