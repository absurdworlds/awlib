/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_string_compose_impl_
#define _aw_string_compose_impl_
#include <aw/string/compose.h>

#include <vector>
#include <string>
namespace aw {
namespace string {
// Implementation details, do not use directly
namespace compose_ {
char const CompositionChar = '%';
class Composed {
public:
	Composed(std::string const& fmt,
			std::vector<std::string> const& tokens,
			char delim = CompositionChar)
		: fmt(fmt), bits(tokens), delim(delim)
	{
		compose();
	}

	operator std::string() const
	{
		return result;
	}
private:
	void compose();
	size_t compose_arg(size_t pos);
	size_t compose_special(size_t pos);
	size_t paste_arg(size_t pos);

	char const delim;
	std::string const& fmt;
	std::vector<std::string> const& bits;

	std::string result;
};
} // namespace compose_
} // namespace string
} // namespace aw
#endif// (header guard)
