/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_string_compose_impl_
#define _hrengin_string_compose_impl_
#include <vector>
#include <string>

namespace hrengin {
namespace string {
namespace impl_ {

char const CompositionChar = '$';

size_t compose_special(std::string const& fmt, std::string& out,
		size_t pos)
{
	switch(fmt[pos]) {
	case CompositionChar:
		out += CompositionChar;
		return pos + 1;
	default:
		out += CompositionChar;
		return pos;
	}
}

size_t compose_paste(std::string const& fmt, std::string& out,
		std::vector<std::string> const& bits, size_t pos)
{
	return pos;
}

size_t compose_arg(std::string const& fmt, std::string& out,
		std::vector<std::string> const& bits, size_t pos)
{
	size_t pos1 = fmt.find('%', pos);
	
	out += fmt.substr(pos, pos1 - pos);
	if (pos1 == std::string::npos)
		return pos1;

	size_t pos2 = ++pos1;

	if(!isdigit(fmt[pos2])) {
		return compose_special(fmt, out, pos2);
	}

	while(isdigit(fmt[pos2]))
		++pos2;

	size_t arg_no = stoull(fmt.substr(pos1, pos2 - pos1));
	if(arg_no < bits.size())
		out += bits[arg_no];

	return pos2;
}
} // namespace impl_
} // namespace string
} // namespace hrengin
#endif// (header guard)
