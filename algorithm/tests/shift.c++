#include <aw/algorithm/shift.h>
#include <aw/algorithm/find.h>
#include <aw/types/string_view.h>
#include <aw/test/test.h>
#include <vector>


TestFile( "algorithm::shift" );

namespace aw {
Test(shift_one) {
	std::vector<std::string> strs {"A", "B", "C"};
	string_view delim{"-"};

	auto vec1 = strs;
	shift(find(vec1, "A"), find(vec1, "C"));

	auto vec2 = vec1;
	shift(find(vec2, "C"), find(vec2, "B"));

	Checks {
		TestEqual(vec1, decltype(vec1){ "B", "C", "A" });
		TestEqual(vec2, decltype(vec2){ "C", "B", "A" });
	}
}

Test(shift_multiple) {
	std::vector<std::string> strs {"A", "B", "C", "D"};
	string_view delim{"-"};

	auto vec1 = strs;
	shift(find(vec1, "A"), std::next(find(vec1, "B")), find(vec1, "D"));

	auto vec2 = vec1;
	shift(find(vec2, "C"), std::next(find(vec2, "D")), find(vec2, "B"));

	Checks {
		TestEqual(vec1, decltype(vec1){ "C", "D", "A", "B" });
		TestEqual(vec2, decltype(vec2){ "A", "B", "C", "D" });
	}
}

Test(shift_multiple2) {
	std::vector<std::string> strs {"A", "B", "C", "D"};
	string_view delim{"-"};

	auto vec1 = strs;
	shift(find(vec1, "A"), find(vec1, "D"), 2);

	auto vec2 = vec1;
	shift(find(vec2, "C"), find(vec2, "B"), 2);

	Checks {
		TestEqual(vec1, decltype(vec1){ "C", "D", "A", "B" });
		TestEqual(vec2, decltype(vec2){ "A", "B", "C", "D" });
	}
}

Test(shift_container_one) {
	std::vector<std::string> strs {"A", "B", "C", "D"};

	auto vec1 = strs;
	shift(vec1, 0, 3);

	auto vec2 = vec1;
	shift(vec2, 2, 1);

	Checks {
		TestEqual(vec1, decltype(vec1){ "B", "C", "D", "A" });
		TestEqual(vec2, decltype(vec2){ "B", "D", "C", "A" });
	}
}

Test(shift_container_multiple) {
	std::vector<std::string> strs {"A", "B", "C", "D"};

	auto vec1 = strs;
	shift(vec1, 0, 3, 2);

	auto vec2 = vec1;
	shift(vec2, 2, 1, 2);

	Checks {
		TestEqual(vec1, decltype(vec1){ "C", "D", "A", "B" });
		TestEqual(vec2, decltype(vec2){ "C", "A", "B", "D" });
	}
}

Test(shift_identity) {
	std::vector<std::string> strs {"A", "B", "C"};
	string_view delim{"-"};

	auto vec1 = strs;
	shift(vec1.begin(), vec1.begin());

	auto vec2 = vec1;
	shift(vec2.begin(), vec2.end(), vec2.begin());

	auto vec3 = vec2;
	shift(vec3, 1, 1);

	Checks {
		TestEqual(vec1, strs);
		TestEqual(vec2, strs);
		TestEqual(vec3, strs);
	}
}
} // namespace aw
