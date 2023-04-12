/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_fallback_filesystem_h
#define aw_utility_fallback_filesystem_h
/*
 * This header chooses appropriate header and aliases for std::filesystem,
 * and provides minimal fallback (*very* minimal) for cases when no
 * implementation is available.
 */
//------------------------------------------------------------------------------
// fallback and boost implementations can be disabled by commenting them out
#define AW_NO_FILESYSTEM 0
#define AW_STD_FILESYSTEM 1
#define AW_FALLBACK_FILESYSTEM 2
#define AW_BOOST_FILESYSTEM 3

//------------------------------------------------------------------------------
#if __has_include(<filesystem>)
#include <filesystem>
#define AW_FILESYSTEM AW_STD_FILESYSTEM
//-----------------------------------------------
#elif defined(AW_BOOST_FILESYSTEM) && __has_include(<boost/filesystem.hpp>)
#include <boost/filesystem.hpp>
#define AW_FILESYSTEM AW_BOOST_FILESYSTEM
//-----------------------------------------------
#elif defined(AW_FALLBACK_FILESYSTEM)
#include "../C++98/bits/fs/path.h"
#if __cplusplus >= 201402L
#include "../C++14/bits/fs/ops.h"
#endif
#define AW_FILESYSTEM AW_FALLBACK_FILESYSTEM
//-----------------------------------------------
#else
#define AW_FILESYSTEM AW_NO_FILESYSTEM
#endif

namespace aw {
namespace filesystem {
//-----------------------------------------------
#if (AW_FILESYSTEM == AW_STD_FILESYSTEM)
using namespace std::filesystem;
//-----------------------------------------------
#elif defined(AW_BOOST_FILESYSTEM) && (AW_FILESYSTEM == AW_BOOST_FILESYSTEM)
using namespace boost::filesystem;
//-----------------------------------------------
#elif defined(AW_FALLBACK_FILESYSTEM) && (AW_FILESYSTEM == AW_FALLBACK_FILESYSTEM)
using namespace awstd::filesystem;
#endif
} // namespace filesystem
namespace fs = filesystem;
} // namespace aw

#endif//aw_utility_fallback_filesystem_h
