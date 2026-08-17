#include <aw/types/containers/priority_queue.h>

#include <aw/test/test.h>

#include <memory>

TestFile( "aw::priority_queue" );

namespace aw {
namespace {
//! Move-only element
struct move_only {
	std::unique_ptr<int> value;

	move_only(int v)
		: value(std::make_unique<int>(v))
	{
	}

	move_only(move_only&&) = default;
	move_only& operator=(move_only&&) = default;

	bool operator<(move_only const& other) const
	{
		return *value < *other.value;
	}
};

//! A stateful comparator with order selectable at construction time.
struct ordering {
	bool reverse = false;

	bool operator()(int a, int b) const
	{
		return reverse ? b < a : a < b;
	}
};
} // namespace

// The greatest element comes out first, regardless of the push order
Test(priority_queue_order)
{
	priority_queue<int> queue;
	Preconditions {
		TestAssert(queue.empty());
		TestEqual(queue.size(), 0u);
	}

	Checks {
		queue.push(2);
		queue.push(5);
		queue.push(1);
		queue.push(4);

		TestAssert(!queue.empty());
		TestEqual(queue.size(), 4u);
	}

	Checks {
		TestEqual(queue.pop(), 5);
		TestEqual(queue.pop(), 4);
		TestEqual(queue.pop(), 2);
		TestEqual(queue.pop(), 1);
	}

	Postconditions {
		TestAssert(queue.empty());
		TestEqual(queue.size(), 0u);
	}
}

// The smallest element comes out first for the min_priority_queue
Test(priority_queue_min)
{
	min_priority_queue<int> queue;
	Checks {
		queue.push(2);
		queue.push(5);
		queue.push(1);
		queue.push(4);

		TestEqual(queue.pop(), 1);
		TestEqual(queue.pop(), 2);
		TestEqual(queue.pop(), 4);
		TestEqual(queue.pop(), 5);
	}
}

// top() returns the element the next pop() will return, and leaves it there
Test(priority_queue_top)
{
	priority_queue<int> queue;
	queue.push(2);
	queue.push(5);
	queue.push(1);

	Checks {
		TestEqual(queue.top(), 5);
		TestEqual(queue.size(), 3u);
		TestEqual(queue.pop(), 5);

		TestEqual(queue.top(), 2);
		TestEqual(queue.pop(), 2);
	}

	// A const queue can be observed via top()
	Checks {
		priority_queue<int> const& ref = queue;
		TestEqual(ref.top(), 1);
	}
}

// Elements can be built in place from their constructor arguments
Test(priority_queue_emplace)
{
	priority_queue<std::pair<int, int>> queue;
	Checks {
		queue.emplace(1, 10);
		queue.emplace(3, 30);
		queue.emplace(2, 20);

		TestEqual(queue.pop().second, 30);
		TestEqual(queue.pop().second, 20);
		TestEqual(queue.pop().second, 10);
	}
}

// An element that cannot be copied still 
Test(priority_queue_move_only)
{
	priority_queue<move_only> queue;
	Checks {
		queue.emplace(2);
		queue.push(move_only{5});
		queue.emplace(move_only{1});

		TestEqual(*queue.pop().value, 5);
		TestEqual(*queue.pop().value, 2);
		TestEqual(*queue.pop().value, 1);
	}
}

// Stateful comparator correctly decides the order
// given at the construction time
Test(priority_queue_stateful_compare)
{
	priority_queue<int, ordering> queue1{ordering{true}};
	Checks {
		queue1.push(2);
		queue1.push(5);
		queue1.push(1);

		TestEqual(queue1.pop(), 1);
		TestEqual(queue1.pop(), 2);
		TestEqual(queue1.pop(), 5);
	}

	priority_queue<int, ordering> queue2{ordering{false}};
	Checks {
		queue2.push(2);
		queue2.push(5);
		queue2.push(1);

		TestEqual(queue2.pop(), 5);
		TestEqual(queue2.pop(), 2);
		TestEqual(queue2.pop(), 1);
	}
}

// Dropping the top element brings the next one up
Test(priority_queue_discard_top)
{
	priority_queue<int> queue;
	queue.push(2);
	queue.push(5);
	queue.push(1);

	Checks {
		queue.discard_top();

		TestEqual(queue.size(), 2u);
		TestEqual(queue.top(), 2);
	}

	Postconditions {
		queue.discard_top();
		queue.discard_top();
		TestAssert(queue.empty());
	}
}

Test(priority_queue_push_range)
{
	int const values[] = {2, 5, 1, 4};

	// A range of elements can be pushed in one call.
	Checks {
		priority_queue<int> queue;
		queue.push(values, values + 4);

		TestEqual(queue.size(), 4u);
		TestEqual(queue.pop(), 5);
		TestEqual(queue.pop(), 4);
		TestEqual(queue.pop(), 2);
		TestEqual(queue.pop(), 1);
	}

	// Elements already in the queue keep their place in the order.
	Checks {
		priority_queue<int> queue;
		queue.push(3);
		queue.push(6);
		queue.push(values, values + 4);

		TestEqual(queue.size(), 6u);
		TestEqual(queue.pop(), 6);
		TestEqual(queue.pop(), 5);
		TestEqual(queue.pop(), 4);
		TestEqual(queue.pop(), 3);
		TestEqual(queue.pop(), 2);
		TestEqual(queue.pop(), 1);
	}

	// Pushing an empty range leaves the queue as it was.
	Checks {
		priority_queue<int> queue;
		queue.push(7);
		queue.push(values, values);

		TestEqual(queue.size(), 1u);
		TestEqual(queue.top(), 7);
	}
}
} // namespace aw
