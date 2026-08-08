/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awstd_nullptr_h
#define awstd_nullptr_h
#if __cplusplus < 201103L
#ifdef nullptr
#undef nullptr
#endif

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
// defining something that C++11 made a keyword is the whole point here
#pragma GCC diagnostic ignored "-Wc++11-compat"
#endif

static const struct nullptr_t {
	template<typename T>
	operator T*() const { return 0; }

	template<class C, class T>
	operator T C::*() const { return 0; }

	// for sizeof()
	void const* const _dummy_;

private:
	void operator&() const;
} nullptr = {0};

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#ifdef NULL
#undef NULL
#endif

#define NULL nullptr
#endif//__cplusplus < 201103L
#endif//awstd_nullptr_h
