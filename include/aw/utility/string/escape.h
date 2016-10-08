/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_escape_h
#define aw_string_escape_h
#include <string>
namespace aw {
namespace string {
inline std::string& escape_quotes(std::string const& src, std::string& dest)
{
	dest.reserve(dest.size() + src.size());
	for (char c : src) switch (c) {
	case '\\':
	case '"':
		dest.push_back('\\');
		[[fallthrough]];
	default:
		dest.push_back(c);
	}
	return dest;
}

inline std::string escape_quotes(std::string const& src)
{
	std::string dest;
	escape_quotes(src, dest);
	return dest;
}
} // namespace string
} // namespace aw
#endif//aw_string_escape_h
