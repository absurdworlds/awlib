/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_filesystem_h
#define aw_utility_filesystem_h
#if __has_include(<filesystem>)
#include <filesystem>
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
#endif
#include <aw/config.h>
namespace aw {
namespace filesystem {
#ifdef __cpp_lib_experimental_filesystem
#if (AW_COMPILER == AW_COMPILER_MSVC)
using namespace std::tr2::filesystem;
#else
using namespace std::experimental::filesystem;
#endif
#else
using namespace std::filesystem;
#endif
} // namespace filesystem
namespace fs = filesystem;
} // namespace aw
#endif//aw_utility_filesystem_h
