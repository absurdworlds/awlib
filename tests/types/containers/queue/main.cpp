#include <iostream>
#include <vector>

#include <aw/types/containers/queue.h>
#include <aw/utility/ranges/value_range.h>
#include <aw/utility/ranges/reverse.h>

template<typename...Args>
void print(Args... args)
{
	(std::cout << ... << args) << "\n";
}

int main()
{
	using namespace aw;
	using namespace std;
	queue<long> k;

	k.push_front(0xbeafdead);
	k.push_back(42);

	print(k.front());
	print(k.back());

	assert(k.front() == 0xbeafdead);
	assert(k.back() == 42);

	k.pop_back();
	assert(k.front() == k.back());
	assert(k.front() == 0xbeafdead);

	k.clear();
	assert(k.empty());

	k.push_back(0xbeafdead);
	k.push_front(42);

	assert(k.back() == 0xbeafdead);
	assert(k.front() == 42);

	k.pop_back();
	assert(k.front() == k.back());
	assert(k.front() == 42);

	k.pop_back();
	assert(k.empty());

	for (auto v : reverse(range(17u)))
		k.push_back(v);

	for (auto v : range(17u, 32u))
		k.push_front(v);

	for (auto v : reverse(range(32u)))
		assert(k[31-v] == v);

	for (auto v : range(100))
		k.push_back(v);

	for (auto v : reverse(range(32u)))
		assert(k[31-v] == v);

	for (auto v : range(100))
		k.push_front(v);

	for (auto v : reverse(range(32u)))
		assert(k[131-v] == v);

	queue<unsigned> q0{};
	queue<unsigned> q1(11);
	queue<unsigned> q2(11, 33);
	queue<unsigned> q3{1,2,3,4,5};
	queue<unsigned> q4(std::begin(q3), std::end(q3));
	queue<unsigned> q5(std::move(q4));
	queue<unsigned> q6{1,2};

	assert(q0.empty());
	assert(q4.empty());

	assert(q1.size() == 11);
	assert(q2.size() == 11);
	assert(q3.size() == 5);
	assert(q5.size() == 5);
	assert(q6.size() == 2);
}
