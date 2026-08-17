#include <aw/utility/on_scope_exit.h>
#include <aw/test/test.h>
#include <type_traits>

TestFile( "on_scope_exit" );

namespace aw {
namespace {
struct throwing_move {
	throwing_move() = default;
	throwing_move(throwing_move&&) noexcept(false) {}
	void operator()() const noexcept {}
};
struct nothrow_move {
	nothrow_move() = default;
	nothrow_move(nothrow_move&&) noexcept {}
	void operator()() const noexcept {}
};
} // namespace

static_assert(!std::is_nothrow_move_constructible_v<on_scope_exit<throwing_move>>);
static_assert( std::is_nothrow_move_constructible_v<on_scope_exit<nothrow_move>>);

Test(scope_basic_test)
{
	int x = 100;
	auto on_exit1 = aw::call_on_exit([&] {x = 0;});
	{
		decltype(on_exit1) on_exit2(std::move(on_exit1));

		TestAssert(x == 100);
	}
	TestAssert(x == 0);
}

Test(throw_in_dtor)
{
	struct ex {};
	auto func = [] {
		auto on_exit = aw::call_on_exit([] { throw ex{}; });
	};

	TestCatch( ex, func() );
}
} // namespace aw
