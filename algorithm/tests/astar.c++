#include <aw/algorithm/shortest_path.h>

#include <aw/math/vector2d.h>
#include <aw/math/vector_compare.h>
#include <aw/test/test.h>
#include <aw/utility/to_string/math/vector.h>

TestFile( "algorithm::astar" );

namespace aw {
using vec2 = math::vector2d<int>;

struct test_grid {
	using location_type = vec2;

	std::vector<std::vector<double>> grid;

	double cost(location_type a, location_type b) const
	{
		auto cost = grid[b.y()][b.x()];
		if (b.y() != a.y() && b.x() != a.x())
			cost *= sqrt(2);
		return cost;
	}

	bool in_bounds(location_type p) const
	{
		if (p.x() < 0 || p.y() < 0)
			return false;
		size_t max_y = grid.size();
		if (p.y() > max_y)
			return false;
		size_t max_x = grid[0].size();
		if (p.x() > max_x)
			return false;
		return true;
	}

	std::vector<location_type> neighbors(location_type p) const
	{
		std::vector<location_type> neighbors;
		std::vector<location_type> candidates{
			{ p.x() - 1, p.y() - 1 },
			{ p.x() - 1, p.y()     },
			{ p.x() - 1, p.y() + 1 },
			{ p.x()    , p.y() - 1 },
			{ p.x()    , p.y() + 1 },
			{ p.x() + 1, p.y() - 1 },
			{ p.x() + 1, p.y()     },
			{ p.x() + 1, p.y() + 1 },
		};
		for (auto p : candidates)
			if (in_bounds(p))
				neighbors.push_back(p);
		return neighbors;
	}

};

struct test_strategy {
	vec2 start;
	vec2 end_goal;

	bool goal(vec2 pos, int dist) const
	{
		return pos == end_goal;
	}

	bool limit(vec2 pos, int dist) const
	{
		return false;
	}

	double heuristic(vec2 pos) const
	{
		return distance(pos, end_goal);
	};
};

struct vec2_hash {
	std::hash<int> int_hash;
	size_t operator()(vec2 v) const
	{
		return int_hash(v.x()) + int_hash(v.y());
	}
};

template<typename Container>
struct map_wrapper {
	Container c;

	using key_type = Container::key_type;
	using value_type = Container::value_type;

	template<typename K>
	value_type* operator[](K&& key)
	{
		auto it = c.find(std::forward<K>(key));
		if (it == c.end())
			return {};
		return it->second;
	}

	template<typename K>
	const value_type* operator[](K&& key) const
	{
		auto it = c.find(std::forward<K>(key));
		if (it == c.end())
			return {};
		return it->second;
	}

};

struct test_cost_map : std::unordered_map<vec2, std::optional<double>, vec2_hash> {
	std::optional<double>& operator[](vec2 p)
	{
		return std::unordered_map<vec2, std::optional<double>, vec2_hash>::operator[](p);
	}

	std::optional<double> operator[](vec2 p) const
	{
		auto it = find(p);
		if (it == end())
			return {};
		return it->second;
	}
};

struct test_came_from_map : std::unordered_map<vec2, std::optional<vec2>, vec2_hash> {

	std::optional<vec2>& operator[](vec2 p)
	{
		return std::unordered_map<vec2, std::optional<vec2>, vec2_hash>::operator[](p);
	}

	std::optional<vec2> operator[](vec2 p) const
	{
		auto it = find(p);
		if (it == end())
			return {};
		return it->second;
	}
};

Test(astar_shortest_path) {
	constexpr int X = -1;
	test_grid grid{{
		{ 1, 1, 9, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 9, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 9, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 9, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 9, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 9, 1, 1, X, X, X, 1 },
		{ 1, 1, 1, 1, 1, X, 1, X, 1 },
		{ 1, 1, 1, 1, 1, X, X, X, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	}};

	test_cost_map cost;
	test_came_from_map came_from;
	{
		vec2 start{0,0};
		vec2 goal{4,0};

		auto path = find_path( grid, start, test_strategy{ start, goal }, cost, came_from );
		TestAssert(!path.empty());
		TestEqual(path, std::vector<vec2>{ {1,0}, {2,0}, {3,0}, {4,0} });
	}

	{
		vec2 start{0,2};
		vec2 goal{4,0};

		auto path = find_path( grid, start, test_strategy{ start, goal }, cost, came_from );
		TestEqual(path, std::vector<vec2>{
			{0, 3}, {0, 4}, {1, 5}, {2, 6}, {3, 5},
			{3, 4}, {3, 3}, {3, 2}, {3, 1}, {4, 0} });
	}

	{
		vec2 start{0,0};
		vec2 goal{6,6};

		auto path = find_path( grid, start, test_strategy{ start, goal }, cost, came_from );
		TestAssert(path.empty());
	}
}


} // namespace aw
