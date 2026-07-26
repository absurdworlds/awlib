/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/io/mmap_file.h>
#include <aw/types/support/narrow.h>
#include "winapi_helpers.h"
namespace aw {
namespace io {
namespace win32 {
namespace {
unsigned get_protection( map_perms perms )
{
	using mp = map_perms;
	switch (perms) {
	default:
	case mp::none:
		return 0;
	case mp::read:
		return PAGE_READONLY;
	case mp::write:
	case mp::rdwr:
		return PAGE_READWRITE;
	case mp::read|mp::execute:
		return PAGE_EXECUTE_READ;
	case mp::write|mp::execute:
	case mp::rdwr|mp::execute:
		return PAGE_EXECUTE_READWRITE;
	}
}

unsigned get_access( map_perms perms )
{
	using mp = map_perms;

	unsigned result = 0;

	if (!(perms & mp::rdwr)) // MapViewOfFile doesn't have execute-only mode
		return result;

	if (bool(perms & mp::write))
		result |= FILE_MAP_WRITE;
	if (bool(perms & mp::read))
		result |= FILE_MAP_READ;
	if (bool(perms & mp::execute))
		result |= FILE_MAP_EXECUTE;

	// TODO: add a flag for FILE_MAP_ALL_ACCESS ?

	return result;
}
} // namespace

file_mapping map_file( file_descriptor fd, map_perms perms, std::error_code& ec )
{
	if (fd == invalid_fd) {
		ec.assign( ERROR_INVALID_HANDLE, winapi_error_category() );
		return { invalid_mapping };
	}

	const auto length = size( fd, ec );
	if (ec)
		return { invalid_mapping };

	if (length == 0)
		return {};

	const unsigned prot = get_protection( perms );
	const HANDLE mapping = CreateFileMappingW( HANDLE(fd), nullptr, prot, 0, 0, nullptr);
	if (!mapping) {
		set_error( ec );
		return { invalid_mapping };
	}

	const unsigned access = get_access( perms );
	void* view = MapViewOfFile( mapping, access, 0, 0, 0 );
	if (!view) {
		set_error( ec );
		std::error_code close_ec;
		close_handle( uintptr_t(mapping), close_ec );
		return { invalid_mapping };
	}

	ec.clear();
	return {
		.handle = uintptr_t(mapping),
		.address = view,
		.length = narrow_cast<size_t>(length)
	};
}

bool unmap_file( file_mapping& map, std::error_code& ec )
{
	if (!UnmapViewOfFile( map.address )) {
		set_error( ec );
		return false;
	}

	return close_handle( map.handle, ec );
}
} // namespace win32
} // namespace io
} // namespace aw
