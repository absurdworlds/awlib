/*
 * Copyright (C) 2016  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/utility/static_object.h>
#include <map>
#include <iostream>
using namespace aw;
struct Test1 {
	Test1()
	{
		std::cout << "test1\n";
	}

	int val { 1 };
};
using static_test1 = static_object<Test1>;

struct Test2 {
	Test2()
	{
		std::cout << static_test1::instance().val << "\n";

		std::cout << "test2\n";
	}

	int val { 2 };
};
using static_test2 = static_object<Test2>;

struct Test3 {
	Test3()
	{
		std::cout << static_test2::instance().val << "\n";

		std::cout << "test3\n";
	}

	int val { 3 };
};
using static_test3 = static_object<Test3>;

int main()
{
	std::cout << static_test3::instance().val << "\n";
}
