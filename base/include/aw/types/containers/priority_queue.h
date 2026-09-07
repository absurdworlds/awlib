#ifndef aw_containers_priority_queue_h
#define aw_containers_priority_queue_h
#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>
#include <vector>

namespace aw {

/*!
 * \brief Binary heap over a contiguous buffer.
 *
 * Priority queue provides O(1) lookup for its top element.
 * It pops its elements in the order imposed by \a Compare, the greatest first.
 *
 * \note The main difference from the std::priority_queue is that pop() returns
 *       the popped value, avoiding copies, and is more convenient to use.
 */
template<typename T, typename Compare = std::less<T>>
class priority_queue {
public:
	using container_type  = std::vector<T>;
	using value_compare   = Compare;
	using value_type      = container_type::value_type;
	using reference       = container_type::reference;
	using const_reference = container_type::const_reference;
	using size_type       = container_type::size_type;

	priority_queue() = default;

	//! Copy-constructs the comparison functor
	explicit priority_queue(value_compare const& compare)
		: comp{compare}
	{
	}

	bool empty() const
	{
		return heap.empty();
	}

	size_type size() const
	{
		return heap.size();
	}

	void push(value_type const& element)
	{
		heap.push_back(element);
		sift_up();
	}

	void push(value_type&& element)
	{
		heap.push_back(std::move(element));
		sift_up();
	}

	template<typename... Args>
	void emplace(Args&&... args)
	{
		heap.emplace_back(std::forward<Args>(args)...);
		sift_up();
	}

	//! Push a range of elements, re-establishing the heap once.
	template<typename Iterator>
		requires std::input_iterator<Iterator>
	void push(Iterator begin, Iterator end)
	{
		heap.insert(heap.end(), begin, end);
		std::make_heap(heap.begin(), heap.end(), comp);
	}

	//! The element at the top of the queue.
	//! It is the element the next pop() will return.
	const_reference top() const
	{
		return heap.front();
	}

	//! Remove the top element from the priority queue, and
	//! return it.
	value_type pop()
	{
		std::pop_heap(heap.begin(), heap.end(), comp);
		auto top = std::move(heap.back());
		heap.pop_back();
		return top;
	}

	//! Discard the top element without inspecting it.
	void discard_top()
	{
		std::pop_heap(heap.begin(), heap.end(), comp);
		heap.pop_back();
	}

private:
	void sift_up()
	{
		std::push_heap(heap.begin(), heap.end(), comp);
	}

	container_type heap;
	value_compare  comp;
};

//! Priority queue where the minimum element is on top
template<typename T>
using min_priority_queue = priority_queue<T, std::greater<T>>;

} // namespace aw

#endif // aw_containers_priority_queue_h
