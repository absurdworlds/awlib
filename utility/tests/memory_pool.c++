#include <aw/utility/memory/pool.h>
#include <aw/test/test.h>
#include <new>

TestFile("memory::pool");

namespace {
bool force_oom = false;
} // namespace


// TODO: isolate memory pool tests? give memory pool a customisation point?
void* operator new(std::size_t n, std::nothrow_t const&) noexcept
{
	if (force_oom)
		return nullptr;
	try {
		return ::operator new(n);
	} catch (...) {
		return nullptr;
	}
}

namespace aw {
Test(pool_hands_out_distinct_reusable_blocks)
{
	memory::pool<64, 8> p(4);

	void* a = p.alloc();
	void* b = p.alloc();

	TestAssert(a != nullptr);
	TestAssert(b != nullptr);
	TestAssert(a != b);

	// a freed block is the next one handed back out
	p.dealloc(a);
	void* c = p.alloc();
	TestAssert(c == a);

	p.dealloc(b);
	p.dealloc(c);
}

Test(pool_returns_null_when_out_of_memory)
{
	memory::pool<64, 8> p(4);

	force_oom = true;
	void* a = p.alloc();
	force_oom = false;

	TestAssert(a == nullptr);
}
} // namespace aw
