/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/platform/demangle.h>
#include <aw/types/byte_buffer.h>

#if (AW_COMPILER == AW_COMPILER_GCC) || (AW_COMPILER == AW_COMPILER_CLANG)
#include <memory>
#include <cxxabi.h>
namespace aw {
std::string demangle(const char* name)
{
	static thread_local char_buffer buf;
	int status;
	// renounce memory ownership, __cxa_demangle might call realloc()
	char* memory = buf.memory.release();
	auto demangled = abi::__cxa_demangle(name, memory, &buf.size, &status);
	if (demangled) {
		// reclaim ownership
		buf.memory.reset( demangled );
		return demangled;
	}
	// is old buffer untouched on failure?
	buf.memory.reset( memory );
	return name;
}
} // namespace aw
#elif (AW_COMPILER == AW_COMPILER_MSVC) || (AW_COMPILER == AW_COMPILER_CLANG_CL)
#include <vector>
#include <aw/platform/windows.h>
#include <dbghelp.h>
#undef UnDecorateSymbolName
namespace aw {
namespace {
size_t undecorate(const char* name, char* out, size_t len)
{
	return UnDecorateSymbolName(name, out, len, UNDNAME_COMPLETE);
}
} // namespace

std::string demangle(const char* name)
{
	static thread_local std::vector<char> buf(1024);
	size_t size = undecorate(name, buf.data(), buf.size());
	if (size > buf.size()) {
		buf.resize(size);
		size = undecorate(name, buf.data(), buf.size());
	}

	if (size == 0)
		return name;

	return std::string(buf.data(), buf.size());
}
} // namespace aw
#else
namespace aw {
std::string demangle(const char* name) { return name; }
} // namespace aw
#endif

//------------------------------------------------------------------------------
#if (__cpp_rtti)
namespace aw {
#if (AW_COMPILER == AW_COMPILER_GCC) || (AW_COMPILER == AW_COMPILER_CLANG)
std::string demangle(std::type_info const& info)
{
	return demangle( info.name() );
}
#else
// No need to demangle:
// — MSVC
// Not supported:
// ???
std::string demangle(std::type_info const& info)
{
	return info.name();
}
#endif
} // namespace aw
#endif // __cpp_rtti
