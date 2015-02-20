/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_stringutils_
#define _hrengin_stringutils_

#include <hrengin/common/compiler_setup.h>

#include <cstring>

#include <string>
#include <vector>
#include <algorithm>

#include <hrengin/core/core.h>

namespace hrengin {
//! Generic strlen
template<typename char_type>
size_t strlen_g (char_type const* str)
{
	char_type const* s = str;
	while(*s++)
		++s;

	return s - str;
}

//! Get file extension from string
inline std::string getFileExtension (std::string& dest, std::string const& path)
{
	size_t extpos = path.find_last_of(".");

	if(extpos == std::string::npos) {
		dest = "";
	}

	dest = path.substr(extpos+1);

	std::transform(dest.begin(), dest.end(), dest.begin(), ::tolower);

	return dest;
}


namespace string {
/*!
 * \brief
 * 	join strings together
 * \param source
 * 	vector of strings to be joined
 * \param delim 
 * 	delimiting sequence which will be inserted between 
 * 	joined strings
 * \return
 * 	resulting string concatenated together
 */
inline std::string join (std::vector<std::string>& source, 
		std::string const& delim)
{
	std::string result;
	for(auto const& str : source) {
		result.append(delim + str);
	}

	return result;
}

/*!
 * \brief 
 * 	Split string into tokens. Ignores empty tokens.
 * 	For example, `splitString("/ab/cde//fgh/", "/")` will produce 
 * 	three tokens: {"ab", "cde", "fgh}
 * \param source
 * 	Source string to split
 * \param delim
 * 	Delimiting sequence
 * \return
 * 	Vector with found tokens.
 */
inline std::vector<std::string>
split (std::string const& source, std::string const& delim)
{
	std::vector<std::string> holder;
	size_t num_tokens = 0;

	size_t pos = source.find_first_not_of(delim);
	size_t delim_pos = source.find_first_of(delim, pos);

	while(pos != std::string::npos) {
		holder.push_back(source.substr(pos, delim_pos - pos));
		++num_tokens;

		pos = source.find_first_not_of(delim, delim_pos);
		delim_pos = source.find_first_of(delim, pos);
	}

	return holder;
}

/*!
 * \brief 
 * 	Split string into tokens, bearing in mind empty tokens.
 * \param source
 * 	Source string to split
 * \param delim
 * 	Delimiting sequence
 * \return
 * 	Vector of found tokens.
 */
inline std::vector<std::string>
explode (std::string const& source, std::string const& delim)
{
	std::vector<std::string> holder;
	size_t pos1 = 0;
	size_t pos2;

	do {
		pos2 = source.find(delim, pos1);
		holder.push_back(source.substr(pos1, pos2 - pos1));

		// I really hate duplicate code, so I have to do this.
		if (pos2 == std::string::npos)
			break;

		pos1 = pos2 + delim.size();
	} while(true);

	return holder;
}
} // namespace string
} // namespace hrengin
#endif //_hrengin_stringutils_
