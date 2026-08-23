#include <aw/types/array_view.h>
#include <vector>

#include <aw/utility/ranges/ipairs.h>
#include <aw/test/test.h>

TestFile( "aw::array_view" );

namespace aw {
Test(array_view_1) {
	std::vector<std::string> vec{
		"abc", "bcd", "cde", "rgh"
	};
	int arr[] { 1,2,23,8,4,4,4,4,4,5,5,6,6,6,7,54,36,34,63,6,563,456 };
	
	Checks {
		array_view<std::string> view1{vec};
		array_view<int> view2{arr};
		array_view<int> view3 = view2;

		std::vector<std::string> vec2;
		for (auto str : view1)
			vec2.emplace_back(std::move(str));
		std::vector<int> vec3;
		for (int i : view2)
			vec3.push_back( i );

		TestEqual(view1.back(), vec.back());
		TestEqual(view2, view3);
		TestEqual(vec2, vec);
		TestEqual(vec3, std::vector<int>{ std::begin(arr), std::end(arr) });
	}
}
} // namespace aw
