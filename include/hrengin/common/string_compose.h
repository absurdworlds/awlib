/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_string_compose_
#define _hrengin_string_compose_
#include <vector>
#include <string>

#include "impl/string_compose.h"

namespace hrengin {
namespace string {
/*!
 * Compose string via token substitution.
 */
template<typename... Args>
std::string compose(std::string const& fmt, Args const&... args)
{
	std::string out;
	out.reserve(fmt.size());

	std::vector<std::string> bits{ args... };

	size_t pos = 0;
	
	while (pos != std::string::npos)
		pos = impl_::compose_arg(fmt, out, bits, pos);


	return out;
}

} // namespace string
} // namespace hrengin
#endif// (header guard)
