#include <aw/utility/memory/pool.h>

// TODO: I had a test for my pool SOMEWHERE, wher eis it?
struct test{
	double    a[4];
	long long b[4];
};
int main()
{
	using namespace aw::memory;
	specific_pool<test> p( 64 );

	for (int i = 0; i < 64*64*5; ++i)
	{
		auto memory = p.alloc();
		auto& t = *new (memory) test;
		t.a[0] = 1.0;
		t.a[1] = 2.0;
		t.a[2] = 4.0;
		t.a[3] = 6.0;

		t.b[0] = 10;
		t.b[1] = 20;
		t.b[2] = 40;
		t.b[3] = 60;
	}
}
