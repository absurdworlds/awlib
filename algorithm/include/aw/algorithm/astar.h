#ifndef aw_algorithm_astar_h
#define aw_algorithm_astar_h

#include <optional>
#include <queue>
#include <cassert>

namespace aw {
namespace detail {
template<typename Cell>
using distance_type = decltype( std::declval<Cell>().distance( std::declval<Cell>() ) );

template<typename Grid, typename Cell>
using cost_type = decltype(
	std::declval<Grid>().cost(
		std::declval<Cell>(),
		std::declval<Cell>() )
);
} // namespace detail

template<
	typename Grid,
	typename Cell = typename Grid::location_type,
	typename Distance = detail::cost_type<Grid, Cell>,
	typename Strategy,
	typename Cost_map,
	typename Came_from_map>
auto astar( const Grid& grid, Cell start, Strategy&& strategy,
            Cost_map& cost, Came_from_map& came_from )
	-> std::optional<Cell>
{
	struct node {
		Distance priority;
		Cell pos;

		bool operator<(const node& b) const
		{
			const node& a = *this;
			// Use > so that the smallest is on top
			return a.priority > b.priority;
		}
	};

	std::priority_queue<node> queue;

	cost[start] = 0;
	came_from[start] = start;

	queue.push({ 0, start });

	while (!queue.empty()) {
		const auto [prev_priority, pos] = queue.top();
		const auto dist = *cost[pos];

		queue.pop();

		if (strategy.goal(pos, dist))
			return pos;

		if (strategy.limit(pos, dist))
			continue;

		const auto neighbors = grid.neighbors(pos);
		for (auto next : neighbors) {
			const auto next_cost = grid.cost( pos, next );
			if (next_cost < 0)
				continue;
			const auto total_cost = dist + next_cost;
			if (cost[next] && *cost[next] <= total_cost)
				continue;

			cost[next] = total_cost;
			came_from[next] = pos;

			const auto priority = total_cost + strategy.heuristic( next );
#if AW_ASTAR_DEBUG_HEURISTIC
			assert( priority >= prev_priority );
#endif
			queue.push({ priority, next });
		}
	}

	return {};
}
} // namespace aw

#endif // aw_algorithm_astar_h
