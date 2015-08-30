/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "compose.h"

namespace awrts {
namespace string {
HR_CORE_EXP std::string compose(std::string const& fmt,
		std::vector<std::string> const& args)
{
	return compose_::Composed(fmt, args);
}

namespace compose_ {
void Composed::compose()
{
	result.reserve(fmt.size());

	size_t pos = 0;
	
	while (pos != std::string::npos)
		pos = compose_arg(pos);
}

size_t Composed::compose_arg(size_t pos)
{
	size_t pos1 = fmt.find(delim, pos);
	
	result += fmt.substr(pos, pos1 - pos);
	if (pos1 == std::string::npos)
		return pos1;

	++pos1;

	if(!isdigit(fmt[pos1]))
		return compose_special(pos1);

	return paste_arg(pos1);
}

size_t Composed::compose_special(size_t pos)
{
	if(fmt[pos] == delim) {
		result += delim;
		return pos + 1;
	}

	switch(fmt[pos]) {
	default:
		result += delim;
		return pos;
	}
}

size_t Composed::paste_arg(size_t pos)
{
	size_t pos2 = pos;

	while(isdigit(fmt[pos2]))
		++pos2;

	size_t arg_no = stoull(fmt.substr(pos, pos2 - pos));
	if(arg_no < bits.size())
		result += bits[arg_no];

	return pos2;
}
} // namespace compose_
} // namespace string
} // namespace awrts
