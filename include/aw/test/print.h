/*
 * Copyright (C) 2016-2020 Hedede <haddayn@gmail.com>
 * License LGPLv3 or later: <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_print_h
#define aw_test_print_h

#include <aw/test/test_case.h>
#include <iostream>

namespace aw::test {

// TODO: move these out of test
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

#endif aw_test_print_h
