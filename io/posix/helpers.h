/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_posix_internal_helpers_h
#define aw_io_posix_internal_helpers_h
#include <system_error>
namespace aw::io::posix {
// Initialise ec from errno
inline void set_error(std::error_code& ec)
{
	ec.assign(errno, std::generic_category());
}

// Initialise ec from errno if cond is also true
inline void set_error_if(bool cond, std::error_code& ec)
{
	if (cond) {
		set_error( ec );
	} else {
		ec.clear();
	}
}
} // namespace aw::io:posix
#endif//aw_io_posix_internal_helpers_h
