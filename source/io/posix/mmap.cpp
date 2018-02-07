/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/io/mmap_file.h>
#include "helpers.h"

#include <sys/mman.h>
namespace aw {
namespace io {
namespace posix {
namespace {
int get_protection( map_perms perms )
{
	using mp = map_perms;
	int result = 0;
	if (bool(perms & mp::read))
		result |= PROT_READ;
	if (bool(perms & mp::write))
		result |= PROT_WRITE;
	if (bool(perms & mp::exec))
		result |= PROT_EXEC;
	return result;
}

struct map_flags {
	int protection;
	int flags;
};
map_flags get_map_flags( map_perms perms )
{
	using mp = map_perms;

	int prot = get_protection( perms );
	int flags = MAP_PRIVATE;

	// mmapping large files with MAP_PRIVATE will fail
	// use MAP_SHARED to enable writeback
	if (bool(perms & mp::write))
		flags = MAP_SHARED;

	return {prot, flags};
}
} // namespace

file_mapping map_file( file_descriptor fd, map_perms perms, std::error_code& ec )
{
	if (fd == invalid_fd) {
		ec = std::make_error_code( std::errc::invalid_argument );
		return { };
	}

	auto length = size( fd, ec );
	if (length == -1)
		return { };

	auto [prot,flags] = get_map_flags( perms );
	void* map = ::mmap( nullptr, length, prot, flags, fd, 0 );
	if (map == MAP_FAILED) {
		set_error( ec );
		return { };
	}
	return { map, length };
}

int unmap_file( file_mapping& map, std::error_code& ec )
{
	int result = munmap( map.address, map.length );
	set_error_if( result == -1, ec );
	return result == 0;
}
} // namespace posix
} // namespace io
} // namespace aw
