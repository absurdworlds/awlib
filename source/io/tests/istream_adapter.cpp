#include <aw/io/istream_adapter.h>
#include <sstream>

#include <aw/utility/test.h>

TestFile("istream_adapter");

namespace aw {
Test(basic_test) {
	std::string str{"I am a test zstring."};

	std::istringstream is{str};

	Checks {
		char tmp[32] {};
		char* ptr = tmp;
		io::istream_adapter stream{is};
		while( stream.get(*ptr) ) {
			if (*ptr++ == 'z')
				break;
		}
		TestEqual(std::string{tmp}, "I am a test z");
	}

	Postconditions {
		std::string tmp;
		is >> tmp;
		TestEqual(tmp, "string.");
	}
};
} // namespace aw

RunTests();
