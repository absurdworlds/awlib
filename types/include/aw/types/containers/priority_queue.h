#ifndef priority_queue_h
#define priority_queue_h

#include <queue>

namespace aw {

template<typename T, typename Compare = std::less<T>>
class priority_queue {
	using base_type = std::priority_queue<
		T,
		std::vector<T>,
		Compare>;

	base_type impl;
public:

	using value_type      = base_type::value_type;
	using reference       = base_type::reference;
	using const_reference = base_type::const_reference;
	using size_type       = base_type::size_type;
	using container_type  = base_type::container_type;
	using value_compare   = base_type::value_compare;

	priority_queue() = default;


	bool empty() const
	{
		return impl.empty();
	}

	size_type size() const
	{
		return impl.size();
	}

	void push(const value_type& element)
	{
		impl.push(element);
	}

	void push(value_type&& element)
	{
		impl.push(std::move(element));
	}

	template <typename... Args>
	void emplace(Args&&... args)
	{
		impl.emplace(std::forward<Args>(args)...);
	}

	value_type& top()
	{
		return impl.top();
	}

	const value_type& top() const
	{
		return impl.top();
	}

	value_type pop()
	{
		auto top = impl.top();
		impl.pop();
		return top;
	}
};

// Priority queue where the minimum element is on top
template<typename T>
using min_priority_queue = priority_queue<T, std::greater<T>>;

} // namespace aw

#endif // priority_queue_h
