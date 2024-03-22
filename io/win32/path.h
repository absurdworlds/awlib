/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_internal_path_helpers_h
#define aw_internal_path_helpers_h
#include <aw/io/filesystem.h>
namespace aw::io::win32 {
// workaround: (actually run into this problem)
// wchar_t is 2 bytes on windows, and 4 bytes in linux
// when using native libstdc++, this causes problems
struct winapi_path {
#if defined(AW_WINELIB)
	winapi_path( fs::path const& path )
		: path{ path.u16string() }
	{}
	std::u16string path;
#else
	winapi_path( fs::path const& path )
		: path{ path.wstring() }
	{}
	winapi_path( const std::wstring& path )
		: path{ path }
	{}
	std::wstring path;
#endif
	operator wchar_t*() const { return (wchar_t*)path.data(); }
};
} // namespace aw::io::win32
#endif//aw_internal_path_helpers_h
