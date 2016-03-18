/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_stringutils_
#define _aw_stringutils_
#include <cstring>

#include <string>
#include <vector>
#include <algorithm>

#include <aw/core/core.h>

namespace aw {
//! Generic strlen
template<typename char_type>
size_t strlen_g(char_type const* str)
{
	char_type const* s = str;
	while(*s++)
		++s;

	return s - str;
}

//! Get file extension from string
inline std::string getFileExtension(std::string& dest, std::string const& path)
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
} // namespace string
} // namespace aw
#endif //_aw_stringutils_