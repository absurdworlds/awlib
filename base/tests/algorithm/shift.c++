#include <aw/algorithm/shift.h>
#include <aw/algorithm/find.h>
#include <aw/types/string_view.h>
#include <aw/test/test.h>
#include <vector>


TestFile( "algorithm::shift" );

namespace aw {
//! Shifting an empty range is a no-op
Test(shift_empty) {
	std::vector<std::string> strs{ "a", "b", "c" };

	auto vec = strs;
	shift(vec.begin() + 1, vec.begin() + 1, vec.begin());
	shift(vec.begin() + 1, vec.begin() + 1, vec.begin() + 2);

	Checks {
		TestEqual(vec, strs);
	}
}

Test(shift_one) {
	std::vector<std::string> strs {"A", "B", "C"};

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

template<typename T>
std::vector<T> reference_shift(std::vector<T> v, size_t from, size_t n, size_t to)
{
	auto first = v.begin() + from;
	std::vector<T> run(first, first + n);

	v.erase(first, first + n);
	auto offset = (to > from ? to - n + 1 : to);
	v.insert(v.begin() + offset, run.begin(), run.end());
	return v;
}

Test(shift_one_positions) {
	std::vector<int>         ints{ 0, 1, 2, 3, 4, 5 };
	std::vector<std::string> strs{ "a", "b", "c", "d", "e", "f" };

	Checks {
		for (size_t f = 0; f < ints.size(); ++f)
		for (size_t t = 0; t < ints.size(); ++t) {
			if (t == f)
				continue;

			auto vec1 = ints;
			shift(vec1.begin() + f, vec1.begin() + t);
			TestEqual(vec1, reference_shift(ints, f, 1, t));

			auto vec2 = strs;
			shift(vec2.begin() + f, vec2.begin() + t);
			TestEqual(vec2, reference_shift(strs, f, 1, t));
		}
	}
}

Test(shift_block_positions) {
	std::vector<int>         ints{ 0, 1, 2, 3, 4, 5 };
	std::vector<std::string> strs{ "a", "b", "c", "d", "e", "f" };

	Checks {
		for (size_t n = 2; n <= 3; ++n)
		for (size_t f = 0; f + n <= ints.size(); ++f)
		for (size_t t = 0; t < ints.size(); ++t) {
			if (t >= f && t < f + n)
				continue;

			auto vec1 = ints;
			shift(vec1.begin() + f, vec1.begin() + t, n);
			TestEqual(vec1, reference_shift(ints, f, n, t));

			auto vec2 = strs;
			shift(vec2.begin() + f, vec2.begin() + t, n);
			TestEqual(vec2, reference_shift(strs, f, n, t));
		}
	}
}
} // namespace aw
