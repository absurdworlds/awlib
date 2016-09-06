#include <aw/utility/string/compose.h>
#include <aw/utility/test.h>

TestFile("Compose tests");

namespace aw {
Test(compose) {
	std::string formats[] {
		"%0, %1, %3, %5 [% %%]",
		"%0%2%0 %1%7%7;",
		"%1=%5",
	};


	std::string results[3] {
		"%**5%a, $ARG, łôап ныæî°, 0.2548 [% %]",
		"%**5%a,%**5%a $ARG . .;",
		"$ARG=0.2548",
	};

	std::string actual[3];

	Checks {
#define ARGS "%**5%a", "$ARG", ",", "łôап ныæî°", "[", "0.2548", "]", "  ."
		actual[0] = string::compose(formats[0], ARGS);
		actual[1] = string::compose(formats[0], ARGS);
		actual[2] = string::compose(formats[0], ARGS);
#undef ARGS
	}

	Postconditions {
		TestEqual(actual[0], actual[0]);
		TestEqual(actual[1], actual[1]);
		TestEqual(actual[2], actual[2]);
	}
}
} // namespace aw
