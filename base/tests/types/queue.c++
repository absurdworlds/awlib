#include <deque>
#include <memory_resource>
#include <aw/types/containers/queue.h>

#include <aw/ranges/value_range.h>
#include <aw/ranges/reverse.h>
#include <aw/test/test.h>
#include <aw/test/helpers/lifetime_tracker.h>
#include <aw/test/helpers/copy_move_tracker.h>

// TODO: test exception-safety

TestFile( "aw::queue" );

namespace aw {
namespace {
/*!
 * Element which can be made to fail on relocation, however the container
 * chooses to relocate it. Moving it away leaves \a moved_from behind.
 */
struct fragile {
	static constexpr int moved_from = -1;

	//! How many more relocations to let through before throwing
	static inline int budget = 0;

	explicit fragile(int val) : value{val} {}

	fragile(fragile const& other)
		: value{ other.value }
	{
		spend();
	}

	fragile(fragile&& other)
		: value{ std::exchange(other.value, moved_from) }
	{
		spend();
	}

	static void spend()
	{
		if (--budget < 0)
			throw std::runtime_error("fragile");
	}

	int value;
};

/*!
 * Fill \a q up to its capacity, numbering the elements from 0, so that the
 * next insertion is the one that has to grow it.
 */
template<typename Queue>
void fill_to_capacity(Queue& q)
{
	q.reserve(4);
	while (q.size() < q.capacity())
		q.push_back(typename Queue::value_type{int(q.size())});
}
} // namespace

Test(queue_ctors) {
	queue<unsigned> q0{};
	queue<unsigned> q1(11);
	queue<unsigned> q2(11, 33);
	queue<unsigned> q3{1,2,3,4,5};
	queue<unsigned> q4(std::begin(q3), std::end(q3));
	queue<unsigned> q5(std::move(q4));
	queue<unsigned> q6{1,2};
	queue<unsigned> q7(q3);

	Checks {
		TestAssert(q0.empty());
		TestAssert(q4.empty());

		TestEqual(q1.size(), 11);
		TestEqual(q2.size(), 11);
		TestEqual(q3.size(), 5);
		TestEqual(q5.size(), 5);
		TestEqual(q6.size(), 2);
		TestEqual(q7.size(), q3.size());
	}
}

Test(queue_comparisons) {
	queue<unsigned> q0{1,2,3,4};
	queue<unsigned> q1{1,2,3,4};
	queue<unsigned> q2{2,2,3,4};
	queue<unsigned> q3{2,3,3,4};
	
	Checks {
		TestAssert(q0 == q1);
		TestAssert(q0 < q2);
		TestAssert(q1 < q2);
		TestAssert(q3 > q1);
		TestAssert(q3 > q2);
		TestAssert(q3 == q3);
	}
}

Test(queue_ctors_const) {
	const queue<unsigned> q0{1,2,3,4};
	queue<unsigned> q1(q0);
	
	Checks {
		TestEqual(q0,q1);
	}
}

Test(queue_push_pop) {
	queue<long> k;

	Checks {
		k.push_front(0xbeafdead);
		k.push_back(42);

		TestAssert(k.front() == 0xbeafdead);
		TestAssert(k.back() == 42);
	}

	Checks {
		k.pop_back();
		TestAssert(k.front() == k.back());
		TestAssert(k.front() == 0xbeafdead);
	}

	Checks {
		k.clear();
		TestAssert(k.empty());

		k.push_back(0xbeafdead);
		k.push_front(42);

		TestAssert(k.back() == 0xbeafdead);
		TestAssert(k.front() == 42);

		k.pop_back();
		TestAssert(k.front() == k.back());
		TestAssert(k.front() == 42);

		k.pop_back();
		TestAssert(k.empty());
	}
}

Test(queue_push_pop2) {
	std::deque<long> d;
	queue<long> k;

	Setup {
		for (auto v : reverse(range(101))) {
			k.push_back(v);
			d.push_back(v);
		}

		for (auto v : range(101, 200)) {
			k.push_front(v);
			d.push_front(v);
		}
	}

	Checks {
		TestAssert(std::equal(k.begin(), k.end(), d.begin(), d.end()));
	}
}

Test(queue_move_with_allocator) {
	using test::lifetime_tracker;
	using alloc_type = std::pmr::polymorphic_allocator<lifetime_tracker>;
	using queue_type = queue<lifetime_tracker, alloc_type>;

	std::pmr::monotonic_buffer_resource memory, elsewhere;

	alloc_type const source  { &memory };
	alloc_type const equal   { &memory };     // compares equal to source
	alloc_type const unequal { &elsewhere };  // compares unequal

	Checks {
		lifetime_tracker::live = 0;

		queue_type src{ source };
		src.push_back(lifetime_tracker{ lifetime_tracker::payload('a') });
		src.push_back(lifetime_tracker{ lifetime_tracker::payload('b') });

		queue_type dst{ std::move(src), equal };

		TestEqual( dst.size(), size_t(2) );
		TestEqual( dst[0].value, lifetime_tracker::payload('a') );
		TestEqual( dst[1].value, lifetime_tracker::payload('b') );
	}

	Checks {
		TestEqual( lifetime_tracker::live, 0 );
	}

	// must still work if allocators are unequal
	Checks {
		lifetime_tracker::live = 0;

		queue_type src{ source };
		src.push_back(lifetime_tracker{ lifetime_tracker::payload('a') });
		src.push_back(lifetime_tracker{ lifetime_tracker::payload('b') });

		queue_type dst{ std::move(src), unequal };

		TestEqual( dst.size(), size_t(2) );
		TestEqual( dst[0].value, lifetime_tracker::payload('a') );
		TestEqual( dst[1].value, lifetime_tracker::payload('b') );
	}

	Postconditions {
		TestEqual( lifetime_tracker::live, 0 );
	}
}

Test(queue_reserve) {
	queue<unsigned> k;
	std::deque<unsigned> d;

	Setup {
		for (auto v : range(100u)) {
			k.push_back(v);
			d.push_back(v);
		}
	}

	Checks {
		// growing past the current capacity has to take effect
		k.reserve(1000);
		TestAssert(k.capacity() >= 1000);
		TestEqual(k.size(), d.size());
		TestAssert(std::equal(k.begin(), k.end(), d.begin(), d.end()));

		// asking for less than is there must not drop or move anything
		k.reserve(4);
		TestAssert(k.capacity() >= k.size());
		TestEqual(k.size(), d.size());
		TestAssert(std::equal(k.begin(), k.end(), d.begin(), d.end()));

		TestEqual(k.front(), 0u);
		TestEqual(k.back(), 99u);
	}
}

/*!
 * Elements of move-only types can be held in the queue like
 * any other type.
 */
Test(queue_holds_move_only_elements) {
	queue<std::unique_ptr<int>> q;

	Setup {
		for (auto v : range(100))
			q.push_back(std::make_unique<int>(v));
	}

	Checks {
		TestEqual( q.size(), size_t(100) );
		TestEqual( *q.front(), 0 );
		TestEqual( *q.back(), 99 );
	}
}

/*!
 * Growing moves the elements to the new storage instead of copying them.
 */
Test(queue_moves_elements_when_it_grows) {
	using tracker = test::copy_move_tracker<int>;
	static_assert(std::is_nothrow_move_constructible_v<tracker>);

	queue<tracker> q;

	Setup {
		fill_to_capacity(q);
	}

	Preconditions {
		// the next insertion is the one which has to grow the queue
		TestEqual( q.size(), q.capacity() );
	}

	Checks {
		auto const filled = q.size();
		q.push_back(tracker{99});

		TestEqual( q.size(), filled + 1 );

		// everything that was already there kept its value
		for (auto i : range(filled))
			TestEqual( q[i].value, int(i) );
		TestEqual( q[filled].value, 99 );

		// and was carried across by moving, not copying
		for (auto i : range(q.size()))
			TestEqual( q[i].n_copies, size_t(0) );
	}
}

/*!
 * If an exception is thrown during growth, the queue is untouched, with
 * every element still holding its value.
 */
Test(queue_keeps_elements_when_growth_throws) {
	queue<fragile> q;

	Setup {
		fragile::budget = std::numeric_limits<int>::max();
		fill_to_capacity(q);
	}

	Preconditions {
		TestAssert( q.size() >= 2 );
		for (auto i : range(q.size()))
			TestEqual( q[i].value, int(i) );
	}

	Checks {
		// the second element is the one that fails
		fragile::budget = 1;
		TestCatch( std::runtime_error, q.push_back(fragile{999}) );
	}

	Checks {
		for (auto i : range(q.size()))
			TestEqual( q[i].value, int(i) );
	}
}
} // namespace aw
