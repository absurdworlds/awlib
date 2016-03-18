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
#include <string>
#include <vector>
#include <algorithm>
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
inline std::string join(std::vector<std::string>& source,
                        std::string const& delim = "")
{
	std::string result;
	for (auto const& str : source)
		result.append(delim + str);

	return result;
}
} // namespace string
} // namespace aw
#endif//aw_string_join_h
