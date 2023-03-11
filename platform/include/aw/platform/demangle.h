/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_platform_demangle_h
#define aw_platform_demangle_h
#include <aw/platform/export.h>
#include <string>
namespace aw {
//! Demangle symbol name. Returns unmodified mangled name on failure.
AW_PLATFORM_EXP std::string demangle( char const* name );
inline std::string demangle(std::string const& name)
{
	return demangle(name.data());
}
} // namespace aw

#if (__cpp_rtti)
#include <typeinfo>
namespace aw {
//! Produces demangled type name from type_info.
AW_PLATFORM_EXP std::string demangle( std::type_info const& info );
} // namespace aw
#endif// __cpp_rtti
#endif//aw_platform_demangle_h
