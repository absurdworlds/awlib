#include <aw/string/compose.h>
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

Test(trailing_delimiter) {
	std::string buffer = "%7 and more";
	string_view truncated(buffer.data(), 1);

	Checks {
		// the '7' is out of bounds and must not be read as an index
		TestEqual(string::compose(truncated, "a"), "%");
		TestEqual(string::compose("%"), "%");
		TestEqual(string::compose("100%"), "100%");
		TestEqual(string::compose("%0%", "a"), "a%");
		// '%%' at the end is still an escape
		TestEqual(string::compose("100%%"), "100%");
	}
}

Test(non_ascii_after_delimiter) {
	Checks {
		// the byte after '%' is not a digit, and must not be
		// sign-extended on its way into isdigit()
		TestEqual(string::compose("%°"), "%°");
		TestEqual(string::compose("%ъ%0", "э"), "%ъэ");
	}
}

Test(huge_index) {
	Checks {
		// a number too large to be an argument number substitutes
		// nothing, like any other argument which was not passed
		TestEqual(string::compose("%99999999999999999999", "a"), "");
		TestEqual(string::compose("[%0|%99999999999999999999|%1]", "a", "b"),
		          "[a||b]");

		if constexpr(sizeof(size_t) == sizeof(u32))
		{
			TestEqual(string::compose("%4294967296", "a", "b", "c"), "");
			TestEqual(string::compose("%4294967297", "a", "b", "c"), "");
		}
		else if constexpr(sizeof(size_t) == sizeof(u64))
		{
			TestEqual(string::compose("%18446744073709551616", "a", "b", "c"), "");
			TestEqual(string::compose("%18446744073709551617", "a", "b", "c"), "");
		}
	}
}
} // namespace aw
