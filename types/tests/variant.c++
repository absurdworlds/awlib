#include <stdexcept>
#include <aw/types/variant.h>
#include <aw/test/test.h>

TestFile( "aw::variant" );

Test(variant_basic_get) {
	using namespace std::string_literals;
	aw::variant<int, float, std::string> var1;

	Checks {
		var1.set("A string."s);
		TestEqual(*var1.get<std::string>(), "A string."s);
		var1.set(100);
		TestEqual(*var1.get<int>(), 100);
		var1.set(1.01f);
		TestEqual(*var1.get<float>(), 1.01f);

		TestAssert(!var1.get<int>());
		TestAssert(!var1.get<std::string>());
	}
}

Test(variant_basic_copy) {
	using namespace std::string_literals;
	aw::variant<int, float, std::string> var1;
	aw::variant<int, float, std::string> var2;

	var1.set(10.01f);

	Preconditions {
		TestEqual(*var1.get<float>(), 10.01f);
		TestAssert(var2.empty());
	}

	Checks {
		var2 = var1;
		TestEqual(*var1.get<float>(), *var2.get<float>());
	}
}

template<int> struct dummy{};
template<int i> float operator*(dummy<i>, int) { return {}; }

Test(variant_const_variant) {
	using namespace std::string_literals;
	aw::variant<int, float, dummy<0>, dummy<1>, dummy<2>, dummy<3>, dummy<4>, dummy<5>, dummy<6>, dummy<7>, dummy<8>> var1;

	var1.set(10.01f);

	Checks {
		const auto& cvar = var1;

		float v = cvar.apply([] (auto& v) {
			return v * 2;
		});

		TestEqual(v, 10.01f*2);
	}
}

Test(variant_copy_5types) {
	using namespace std::string_literals;
	aw::variant<int, float, bool, unsigned, std::string> var1;
	aw::variant<int, float, bool, unsigned, std::string> var2;

	auto test_val = "Test string!"s;

	var1.set(test_val);

	Preconditions {
		TestEqual(*var1.get<std::string>(), test_val);
		TestAssert(var2.empty());
	}

	Checks {
		var2 = var1;
		TestEqual(*var1.get<std::string>(), *var2.get<std::string>());
		TestEqual(*var1.get<std::string>(), test_val);
	}

	auto test_set = [&] (auto value) {
		var1.set(value);
		var2 = var1;
		TestEqual(*var2.get<decltype(value)>(), value);
	};

	Checks {
		test_set(1);
		test_set(1.0f);
		test_set(true);
		test_set(1u);
		test_set("1"s);
	}
}

Test(variant_basic_move) {
	using namespace std::string_literals;
	aw::variant<int, float, std::string> var1;
	aw::variant<int, float, std::string> var2;

	var1.set<std::string>("Test string!"s);

	Preconditions {
		TestEqual(*var1.get<std::string>(), "Test string!"s);
		TestAssert(var2.empty());
	}

	Checks {
		var2 = std::move(var1);
		TestEqual(*var2.get<std::string>(), "Test string!"s);
		TestAssert(var1.empty());
	}
}

Test(variant_assign_subset) {
	using namespace std::string_literals;
	aw::variant<int, float, std::string> var1;
	aw::variant<int,        std::string> var2;

	var2.set<std::string>("Test string!");

	Preconditions {
		TestAssert(var1.empty());
		TestEqual(*var2.get<std::string>(), "Test string!"s);
	}

	Checks {
		var1 = var2;
		TestEqual(*var1.get<std::string>(), *var2.get<std::string>());
	}
}

Test(variant_self_assign) {
	using namespace std::string_literals;
	aw::variant<int, std::string> var1("Test string!"s);

	Checks {
		var1 = var1;
		TestEqual(*var1.get<std::string>(), "Test string!"s);
	}
}
Test(variant_reassign) {
	using namespace std::string_literals;
	aw::variant<int, std::string> var;

	Checks {
		var.set("Test string!"s);
		TestEqual(*var.get<std::string>(), "Test string!"s);
		var.set("Tost string!"s);
		TestEqual(*var.get<std::string>(), "Tost string!"s);
	}
}

Test(variant_construct_from_subset) {
	using namespace std::string_literals;
	aw::variant<std::string, int> varx{ "asdasd"s };
	aw::variant<std::string, int, float> vary{ varx };

	Checks {
		TestEqual(*varx.get<std::string>(), *vary.get<std::string>());
	}
}

Test(variant_construct_in_place) {
	using namespace std::string_literals;
	aw::variant<std::string, int> varx{ "asdasd" };
	aw::variant<std::string, char const*> vary{ +"asdasd" };

	Checks {
		TestEqual(*varx.get<std::string>(), "asdasd");
		TestEqual(*vary.get<char const*>(), "asdasd");
	}
}

#include <aw/test/test_runner.h>
