#include <aw/utility/string/compose.h>
#include <aw/test/test.h>

TestFile("Compose tests");

namespace aw {
Test(compose_empty) {
	using namespace std::string_literals;
	Checks {
		TestEqual(string::compose(""), ""s);
	}
}

Test(compose_fuzz) { // TODO: real fuzz test
	const std::string formats[] {
		"%0, %1, %3, %5 [% %%]",
		"%0%2%0 %1%7%7;",
		"%1=%5",
	};


	std::string actual[3];

	Setup {
#define ARGS "%**5%a", "$ARG", ",", "łôап ныæî°", "[", "0.2548", "]", "  ."
		actual[0] = string::compose(formats[0], ARGS);
		actual[1] = string::compose(formats[1], ARGS);
		actual[2] = string::compose(formats[2], ARGS);
#undef ARGS
	}

	const std::string expected[3] {
		"%**5%a, $ARG, łôап ныæî°, 0.2548 [% %]",
		"%**5%a,%**5%a $ARG  .  .;",
		"$ARG=0.2548",
	};

	Checks
	{
		TestEqual(actual[0], expected[0]);
		TestEqual(actual[1], expected[1]);
		TestEqual(actual[2], expected[2]);
	}
}

Test(special_cases) {
	std::string percent = "% %% %%% %0 %%1";
	std::string not_enough_args = "%0 %1 %5 %100";
	std::string too_many_args   = "%0";
	std::string select_third    = "%2";

	Checks {
		TestEqual(string::compose(percent), "% % %%  %1");
		TestEqual(string::compose(not_enough_args, "a", "b"), "a b  ");
		TestEqual(string::compose(too_many_args, "a", "b"), "a");
		TestEqual(string::compose(select_third, "a", "b", "c"), "c");
	}
}
} // namespace aw
