#include <aw/utility/memory/pool.h>
#include <aw/test/test.h>
#include <new>
#include <cstdint>

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
using memory::align_up;

static_assert(align_up(0, 8)  == 0);
static_assert(align_up(1, 8)  == 8);
static_assert(align_up(8, 8)  == 8);
static_assert(align_up(9, 8)  == 16);
static_assert(align_up(12, 8) == 16);
static_assert(align_up(12, 4) == 12);
static_assert(align_up(64, 32) == 64);
static_assert(align_up(65, 32) == 96);
// an alignment of one is a no-op
static_assert(align_up(1, 1)  == 1);
static_assert(align_up(7, 1)  == 7);

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

/*!
 * Blocks are suitably aligned for the type they hold.
 */
Test(pool_blocks_are_aligned)
{
	// a size which is not a multiple of the alignment
	memory::pool<12, 8> p(4);

	void* blocks[4] = {};
	for (auto& block : blocks) {
		block = p.alloc();
		TestAssert(block != nullptr);
		TestAssert(reinterpret_cast<uintptr_t>(block) % alignof(void*) == 0);
	}

	for (auto block : blocks)
		p.dealloc(block);
}

/*!
 * A pool asked for no blocks still hands out usable memory.
 */
Test(pool_with_no_blocks)
{
	memory::pool<64, 8> p(0);

	void* a = p.alloc();
	TestAssert(a != nullptr);

	void* b = p.alloc();
	TestAssert(b != nullptr);
	TestAssert(a != b);

	p.dealloc(a);
	p.dealloc(b);
}
} // namespace aw
