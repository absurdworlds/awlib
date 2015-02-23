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

#include "impl/compose.h"

namespace hrengin {
namespace string {
/*!
 * Compose parametrized string (parameter substitution).
 */
template<typename... Args>
std::string compose(std::string const& fmt, Args const&... args)
{
	std::vector<std::string> bits{args...};

	return compose_::Composed(fmt, bits);
}
} // namespace string
} // namespace hrengin
#endif// (header guard)
