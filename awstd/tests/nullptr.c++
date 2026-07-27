/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awstd/nullptr>

#include "awstd_test.h"

namespace {
struct test {
	int x;
	void func() {}
};

void f(test* p)            { Check(p == 0); }
void g(void (*p)())        { Check(p == 0); }
void h(int test::* p)      { Check(p == 0); }
void i(void (test::* p)()) { Check(p == 0); }
} // namespace

int main()
{
	// since C++11 nullptr is a keyword, and the fallback is not used
	f(nullptr);
	g(nullptr);
	h(nullptr);
	i(nullptr);

	test* p = nullptr;
	Check(p == nullptr);
	Check(!(p != nullptr));

	// the fallback also redefines NULL, so that it is type-safe as well
	test* q = NULL;
	Check(q == nullptr);

	return awstd_test::result();
}
