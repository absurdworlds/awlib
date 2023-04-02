#include <aw/algorithm/exchange.h>

#include <aw/test/test.h>

TestFile( "algorithm::exchange" );

template<typename T>
struct copy_move_counter {
	T value;
	size_t n_copies = 0;
	size_t n_moves  = 0;
	size_t n_moved_from = 0;

	copy_move_counter(T value)
		: value(std::move(value))
	{}

	copy_move_counter(const copy_move_counter& other)
		: value(other.value)
		, n_copies(other.n_copies + 1)
		, n_moves(other.n_moves)
	{
	}

	copy_move_counter(copy_move_counter&& other)
		: value(std::move(other.value))
		, n_copies(std::exchange(other.n_copies, 0))
		, n_moves(std::exchange(other.n_moves, 0) + 1)
	{
		++other.n_moved_from;
	}

	copy_move_counter& operator=(const copy_move_counter& other)
	{
		value = other.value;
		n_copies = other.n_copies + 1;
		n_moves = other.n_moves;
		return *this;
	}

	copy_move_counter& operator=(copy_move_counter&& other)
	{
		value = std::move(other.value);
		n_copies = std::exchange(other.n_copies, 0);
		n_moves = std::exchange(other.n_moves, 0) + 1;
		++other.n_moved_from;
		return *this;
	}

	// silences the clang-tidy warning
	[[clang::reinitializes]]
	void unmove() {}
};

namespace aw {
Test(exchange_chain) {
	std::string a = "test1";
	std::string b = "test2";
	std::string c = "test3";
	std::string d = "test4";

	auto x = exchange_chain(a, b, c, std::move(d));

	TestEqual(x, "test1");
	TestEqual(a, "test2");
	TestEqual(b, "test3");
	TestEqual(c, "test4");

	// Don't care about the value of d
}

Test(exchange_copy_move) {
	using namespace std::string_literals;
	{
		copy_move_counter a = "a"s, b = "b"s, c = "c"s, d = "d"s; // NOLINT

		auto x = exchange_chain(a, b, c, std::move(d));
		d.unmove(); // silence clang-tidy

		TestEqual(x.value, "a");
		TestEqualV(x.n_copies, b.n_copies, c.n_copies, d.n_copies, 0u);
		TestEqual(x.n_moves, 1);
		TestEqual(d.n_moved_from, 1);

		// Others depend on optimization levels,
	}
	{
		copy_move_counter a = "a"s, b = "b"s, c = "c"s, d = "d"s; // NOLINT

		auto x = exchange_chain(a, b, c, d);

		TestEqual(x.value, "a");
		TestEqual(x.n_moves, 1);
		TestEqual(c.n_copies, 1);
		TestEqual(d.n_moved_from, 0);
	}
}

Test(rotate_left) {
	std::string a = "test1";
	std::string b = "test2";
	std::string c = "test3";
	std::string d = "test4";

	rotate_left(a, b, c, d);

	TestEqual(a, "test2");
	TestEqual(b, "test3");
	TestEqual(c, "test4");
	TestEqual(d, "test1");

}

Test(rotate_right) {
	std::string a = "test1";
	std::string b = "test2";
	std::string c = "test3";
	std::string d = "test4";

	rotate_right(a, b, c, d);

	TestEqual(a, "test4");
	TestEqual(b, "test1");
	TestEqual(c, "test2");
	TestEqual(d, "test3");
}

Test(rotate_left_copy_count) {
	using namespace std::string_literals;
	copy_move_counter a = "a"s, b = "b"s, c = "c"s, d = "d"s; // NOLINT

	rotate_left(a, b, c, d);

	TestEqualV(b.n_copies, c.n_copies, d.n_copies, 0u);
}

Test(rotate_right_copy_count) {
	using namespace std::string_literals;
	copy_move_counter a = "a"s, b = "b"s, c = "c"s, d = "d"s; // NOLINT

	rotate_left(a, b, c, d);

	TestEqualV(b.n_copies, c.n_copies, d.n_copies, 0u);
}
} // namespace aw
