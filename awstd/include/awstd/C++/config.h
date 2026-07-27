/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awstd_config_h
#define awstd_config_h
#include <aw/config.h>

#if __cplusplus >= 201103L
#define aw_constexpr constexpr
#define aw_noexcept  noexcept
#else
#define aw_constexpr const
#define aw_noexcept  throw()
#endif

//! For functions: aw_constexpr would qualify the return type, and
//! C++11 constexpr is too restrictive to express most of them
#if __cplusplus >= 201402L
#define aw_constexpr_fn constexpr
#else
#define aw_constexpr_fn
#endif

#endif//awstd_config_h
