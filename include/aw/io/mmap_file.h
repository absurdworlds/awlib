/*
 * Copyright (C) 2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_mmap_file_h
#define aw_io_mmap_file_h
#include <aw/io/native_file.h>
namespace aw {
namespace io {

enum class map_perms : unsigned {
	none    = 0x0,
	read    = 0x1,
	write   = 0x2,
	execute = 0x4,
	// shorthands
	exec    = execute,
	rdwr    = read|write,
};

constexpr map_perms operator|(map_perms a, map_perms b)
{
	return map_perms(unsigned(a) | unsigned(b));
}

constexpr map_perms operator&(map_perms a, map_perms b)
{
	return map_perms(unsigned(a) & unsigned(b));
}

constexpr bool operator!(map_perms a)
{
	return !bool(a);
}


#if defined(AW_SUPPORT_PLATFORM_POSIX)
namespace posix {
struct file_mapping {
	constexpr bool valid() const { return address != nullptr; }
	void* address = nullptr;
	size_t length = 0;
};

AW_IO_EXP
file_mapping map_file( file_descriptor fd, map_perms perms, std::error_code& ec );
AW_IO_EXP int unmap_file( file_mapping& map, std::error_code& ec );
} // namespace posix
#endif

#if defined(AW_SUPPORT_PLATFORM_WIN32)
namespace win32 {
constexpr uintptr_t invalid_mapping = -1;
struct file_mapping {
	constexpr bool valid() const { return handle != invalid_mapping; }
	uintptr_t handle = invalid_mapping;
	void* address = nullptr;
	size_t length = 0;
};

AW_IO_EXP
file_mapping map_file( file_descriptor fd, map_perms perms, std::error_code& ec );
AW_IO_EXP bool unmap_file( file_mapping& map );
} // namespace win32
#endif

namespace native {
#if   (AW_PLATFORM == AW_PLATFORM_POSIX)
using posix::map_file;
using posix::unmap_file;
using posix::file_mapping;
#elif (AW_PLATFORM == AW_PLATFORM_WIN32)
using win32::map_file;
using win32::unmap_file;
using win32::file_mapping;
#endif
} // namespace native

inline file_mode get_file_mode(map_perms perms)
{
	using mp = map_perms;
	switch (perms) {
	case mp::none:
		return file_mode::none;
	case mp::read:
	case mp::read|mp::exec:
		return file_mode::read;
	case mp::write:
		return file_mode::write;
	case mp::write|mp::exec:
	case mp::rdwr:
	case mp::rdwr|mp::exec:
		return file_mode::read|file_mode::write;
	};
}


/*!
 * Map a file into memory. Allows access a file like a regular array.
 */
struct mmap_file {
	/*!
	 * @param perms
	 *    Should be used with care, as incorrect use will lead to
	 *    protection faults. E.g. setting map_perms::write and
	 *    attempting to read from file may crash the program.
	 */
	mmap_file(file_descriptor fd, map_perms perms = map_perms::rdwr)
		: _file{fd}
	{
		std::error_code ec;
		create_mapping( ec, perms );
	}

	mmap_file(file_descriptor fd, std::error_code& ec, map_perms perms = map_perms::rdwr)
		: _file{fd}
	{
		create_mapping( ec, perms );
	}

	mmap_file(fs::path const& path, map_perms perms = map_perms::rdwr)
		: _file{path, get_file_mode(perms)}
	{
		std::error_code ec;
		create_mapping( ec, perms );
	}

	mmap_file(fs::path const& path, std::error_code& ec, map_perms perms = map_perms::rdwr)
		: _file{path, get_file_mode(perms)}
	{
		create_mapping( ec, perms );
	}

	~mmap_file()
	{
		std::error_code ec;
		if ( _map.valid()) native::unmap_file( _map, ec );
	}

	using iterator       = char*;
	using const_iterator = char const*;

	bool is_open() { return _file.is_open() && _map.valid(); }

	char*       data()       { return (char*)_map.address; }
	char const* data() const { return (char const*)_map.address; }

	size_t size() const { return _map.length; }

	char* begin() { return data(); }
	char* end()   { return data() + size(); }

	char const* begin() const { return data(); }
	char const* end()   const { return data() + size(); }

	char const* cbegin() const { return begin(); }
	char const* cend()   const { return end(); }

private:
	void create_mapping( std::error_code& ec, map_perms perms )
	{
		_map = native::map_file( _file.descriptor(), perms, ec );
	}

	native::file _file;
	native::file_mapping _map;
};

struct mmap_view : private mmap_file {
	using mmap_file::const_iterator;
	using iterator = const_iterator;

	mmap_view(file_descriptor fd)
		: mmap_file( fd, map_perms::read )
	{}

	mmap_view(file_descriptor fd, std::error_code& ec)
		: mmap_file( fd, ec, map_perms::read )
	{}

	mmap_view(fs::path const& path)
		: mmap_file( path, map_perms::read )
	{}

	mmap_view(fs::path const& path, std::error_code& ec)
		: mmap_file( path, ec, map_perms::read )
	{}

	using mmap_file::is_open;
	using mmap_file::size;

	char const* begin() const { return mmap_file::begin(); }
	char const* end()   const { return mmap_file::end(); }
};
} // namespace io
} // namespace aw
#endif//aw_io_native_file_h
