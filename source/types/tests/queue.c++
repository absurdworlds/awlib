#include <deque>
#include <aw/types/containers/queue.h>

#include <aw/utility/ranges/value_range.h>
#include <aw/utility/ranges/reverse.h>
#include <aw/utility/test.h>

// TODO: test exception-safety

TestFile( "aw::queue" );

namespace aw {
Test(queue_ctors) {
	queue<unsigned> q0{};
	queue<unsigned> q1(11);
	queue<unsigned> q2(11, 33);
	queue<unsigned> q3{1,2,3,4,5};
	queue<unsigned> q4(std::begin(q3), std::end(q3));
	queue<unsigned> q5(std::move(q4));
	queue<unsigned> q6{1,2};

	Checks {
		TestAssert(q0.empty());
		TestAssert(q4.empty());

		TestEqual(q1.size(), 11);
		TestEqual(q2.size(), 11);
		TestEqual(q3.size(), 5);
		TestEqual(q5.size(), 5);
		TestEqual(q6.size(), 2);
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
} // namespace aw
