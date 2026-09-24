#include <aw/hudf/value.h>

#include <aw/test/test.h>

TestFile("hudf::value");

namespace aw::hudf {
Test(self_assignment) {
	value val("String");

	Checks {
		val = val;
		TestEqual(val.try_get("Wrong"), "String");
	}

	Checks {
		using namespace std::string_literals;
		val = std::move(val);
		TestEqual(val.try_get("Wrong"s), "String");
	}
}
} // namespace aw::hudf
