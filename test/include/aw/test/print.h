/*
 * Copyright (C) 2016-2022  Hudd <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_print_h
#define aw_test_print_h

#include <iostream>

// TODO: make a generic pretty-printer

namespace aw::test {
#if (AW_PLATFORM != AW_PLATFORM_WIN32)
char const _bold[]  = "\033[1m";
char const _red[]   = "\033[31m";
char const _green[] = "\033[32m";
char const _white[] = "\033[37m";
char const _reset[] = "\033[0m";
inline std::ostream& bold(std::ostream& os)  { if (isatty(1)) os << _bold;  return os;}
inline std::ostream& red(std::ostream& os)   { if (isatty(1)) os << _red;   return os;}
inline std::ostream& green(std::ostream& os) { if (isatty(1)) os << _green; return os;}
inline std::ostream& white(std::ostream& os) { if (isatty(1)) os << _white; return os;}
inline std::ostream& reset(std::ostream& os) { if (isatty(1)) os << _reset; return os;}
#else
char const bold[]  = "";
char const red[]   = "";
char const green[] = "";
char const white[] = "";
char const reset[] = "";
#endif

template<typename...Args>
void print(Args&&...args)
{
	( std::cout << ... << std::forward<Args>(args) );
}

template<typename...Args>
void println(Args&&...args)
{
	( std::cout << ... << std::forward<Args>(args) ) << '\n';
}
} // namespace aw::test

#endif // aw_test_print_h
