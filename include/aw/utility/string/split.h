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
#include <vector>
#include <algorithm>
#include <aw/types/string_view.h>
namespace aw {
namespace string {
/*!
 * \brief
 *      Split string into tokens. Ignores empty tokens.
 *      For example, `split("/ab/cde//fgh/", "/")` will produce 
 *      three tokens: {"ab", "cde", "fgh"}
 * \param source
 *      Source string to split
 * \param delim
 *      String containing possible delimiters.
 * \return
 *      Vector with found tokens.
 */
inline std::vector<std::string>
split(string_view source, string_view delim)
{
	std::vector<std::string> holder;
	size_t num_tokens = 0;

	size_t pos = source.find_first_not_of(delim);
	size_t delim_pos = source.find_first_of(delim, pos);

	while (pos != std::string::npos) {
		holder.push_back((std::string)source.substr(pos, delim_pos - pos));
		++num_tokens;

		pos = source.find_first_not_of(delim, delim_pos);
		delim_pos = source.find_first_of(delim, pos);
	}

	return holder;
}

/*!
 * Split delimited string into substrings, including
 * empty substrings.
 * Delimiter may consist of multiple characters.
 *
 * Examples:
 * `explode("x==y==z", "==")` -> `{"x", "y", "z"}`
 * `explode("/path/", "/", false)` -> `{"", "path", ""}`
 */
inline std::vector<std::string>
cut(string_view source, string_view delim)
{
	std::vector<std::string> holder;
	size_t pos1 = 0;
	size_t pos2;

	do {
		pos2 = source.find(delim, pos1);
		holder.push_back((std::string)source.substr(pos1, pos2 - pos1));

		if (pos2 == std::string::npos)
			break;

		pos1 = pos2 + delim.size();
	} while (true);

	return holder;
}
} // namespace string
} // namespace aw
#endif//aw_string_split_h
