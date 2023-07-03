#include <aw/string/repeat.h>
#include <aw/test/test.h>
#include <aw/types/array_view.h>

TestFile( "string::repeat" );

namespace aw {
Test(repeat_zero) {
	Checks {
		TestAssert(string::repeat(" ", 0).empty());
		TestAssert(string::repeat("---", 0).empty());
		TestAssert(string::extend(" ", 0).empty());
		TestAssert(string::extend("---", 0).empty());
	}
}

Test(repeat_correct_size) {
	Checks {
		TestAssert(string::repeat(" ", 1).size() == 1);
		TestAssert(string::repeat("---", 2).size() == 6);
		TestAssert(string::repeat(" ", 10).size() == 10);
		TestAssert(string::repeat("-", 16).size() == 16);
		TestAssert(string::repeat("-", 17).size() == 17);
		TestAssert(string::repeat("--", 16).size() == 32);
		TestAssert(string::repeat("--", 17).size() == 34);
	}
}

Test(extend_correct_size) {
	Checks {
		TestAssert(string::extend(" ", 10).size() == 10);
		TestAssert(string::extend("---", 1).size() == 1);
	}
}

Test(repeat_simple_case) {
	Checks {
		TestAssert(string::repeat(" ", 10) == "          ");
		TestAssert(string::repeat("-", 16) == "----------------");
		TestAssert(string::repeat("-", 17) == "-----------------");
		TestAssert(string::repeat("--", 16) == "--------------------------------");
		TestAssert(string::repeat("--", 17) == "----------------------------------");
	}
}

Test(extend_simple_case) {
	Checks {
		TestAssert(string::extend(" ", 10) == "          ");
		TestAssert(string::extend("123", 10) == "1231231231");
		TestAssert(string::extend("123", 2) == "12");
	}
}
Test(extend_large_sizes) {
	Checks {
		TestAssert(string::extend(" ", 1000000) == std::string(1000000, ' '));
		TestAssert(string::extend("   ", 1000000).size() == 1000000);
	}
}
Test(repeat_large_sizes) {
	Checks {
		TestAssert(string::repeat(" ", 1000000) == std::string(1000000, ' '));
		TestAssert(string::repeat("  ", 1000000).size() == 2000000);
	}
}

Test(string_repeat_operator) {
	using namespace string::operators;
	using namespace std::string_literals;
	Checks {
		TestAssert("  "s * 100 == std::string(200, ' '));
	}
}
} // namespace aw
