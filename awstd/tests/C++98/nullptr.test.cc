#include "nullptr.h"

struct test {
	int x;
	void func();
};

void f(test*);
void g(void (*) ());
void h(int test::*);
void i(void (test::*) ());

void j()
{
	f(nullptr);
	g(nullptr);
	h(nullptr);
	i(nullptr);
}
