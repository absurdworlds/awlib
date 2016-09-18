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
/*
 * This header chooses appropriate header and aliases for std::filesystem,
 * and provides minimal fallback (*very* minimal) for cases when no
 * implementation is available.
 */
//------------------------------------------------------------------------------
// fallback and boost implementations can be disabled by commenting them out
#define AW_NO_FILESYSTEM       0
#define AW_FALLBACK_FILESYSTEM 1
/*
#define AW_BOOST_FILESYSTEM    2
*/
#define AW_EXP_FILESYSTEM      3
#define AW_STD_FILESYSTEM      4

//------------------------------------------------------------------------------
#if __has_include(<filesystem>)
#include <filesystem>
#ifdef __cpp_lib_experimental_filesystem
#define AW_FILESYSTEM AW_EXP_FILESYSTEM
#else
#define AW_FILESYSTEM AW_STD_FILESYSTEM
#endif
//-----------------------------------------------
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
#define AW_FILESYSTEM AW_EXP_FILESYSTEM
//-----------------------------------------------
#elif __has_include(<boost/filesystem.hpp>) && defined(AW_BOOST_FILESYSTEM)
#include <boost/filesystem.hpp>
#define AW_FILESYSTEM AW_BOOST_FILESYSTEM
//-----------------------------------------------
#elif defined(AW_FALLBACK_FILESYSTEM)
#include <aw/utility/fallback/filesystem.h>
#define AW_FILESYSTEM AW_FALLBACK_FILESYSTEM
//-----------------------------------------------
#else
#define AW_FILESYSTEM AW_NO_FILESYSTEM
#endif

//------------------------------------------------------------------------------
#ifndef AW_NO_FILESYSTEM
#include <aw/config.h>
namespace aw {
namespace filesystem {
//-----------------------------------------------
#if (AW_FILESYSTEM == AW_STD_FILESYSTEM)
using namespace std::filesystem;
//-----------------------------------------------
#elif (AW_FILESYSTEM == AW_EXP_FILESYSTEM)
#if (AW_COMPILER == AW_COMPILER_MSVC)
using namespace std::tr2::filesystem;
#else
using namespace std::experimental::filesystem;
#endif
//-----------------------------------------------
#elif defined(AW_BOOST_FILESYSTEM)    && (AW_FILESYSTEM == AW_BOOST_FILESYSTEM)
using namespace boost::filesystem;
//-----------------------------------------------
#elif defined(AW_FALLBACK_FILESYSTEM) && (AW_FILESYSTEM == AW_FALLBACK_FILESYSTEM)
using namespace aw::filesystem::fallback;
#endif
} // namespace filesystem
namespace fs = filesystem;
} // namespace aw
#endif//AW_NO_FILESYSTEM
#endif//aw_utility_filesystem_h
