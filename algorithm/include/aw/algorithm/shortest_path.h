#ifndef aw_algo_shortest_path_h
#define aw_algo_shortest_path_h

#include "astar.h"

#include <algorithm>
#include <unordered_map>

#if AW_ASTAR_DEBUG_CYCLES
#include <unordered_set>
#endif

namespace aw {
template<typename Cell, typename Came_from_map>
auto reconstruct_path( Cell start, Cell goal, const Came_from_map& came_from )
	-> std::vector<Cell>
{
#if AW_ASTAR_DEBUG_CYCLES
	std::unordered_set<Cell> visited;
#endif

	std::vector<Cell> path;

	if (!came_from[goal])
		return path;

	Cell current = goal;
	while (current != start) {
#if AW_ASTAR_DEBUG_CYCLES
		auto [_,cycle] = visited.emplace(current);
		if (cycle)
			return break;
#endif

		path.push_back(current);
		current = *came_from[current];
	}

	std::reverse(path.begin(), path.end());
	return path;
}

template<
	typename Grid,
	typename Cell = typename Grid::location_type,
	typename Distance = detail::cost_type<Grid, Cell>,
	typename Cost_map,
	typename Came_from_map,
	typename Strategy>
auto find_path( const Grid& grid, Cell start,
                Strategy&& strategy,
                Cost_map& cost,
                Came_from_map& came_from)
	-> std::vector<Cell>
{
	const auto goal = astar( grid, start, strategy, cost, came_from );
	if (!goal)
		return {};

	return reconstruct_path( start, *goal, came_from );
}

} // namespace aw

#endif // aw_algo_shortest_path_h
