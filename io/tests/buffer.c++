#include <aw/io/input_file_stream.h>
#include <aw/io/input_memory_stream.h>
#include <algorithm>
#include <string_view>

#include <aw/test/test.h>

#include "temp_file.h"

TestFile("Buffer");

namespace aw {
using test::temp_file;

Test(file_small_buffer) {
	std::string_view const str = "Test string. Where is the Pink Elephant?";

	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write(str), intmax_t(str.size()) );
	}

	std::vector<char> tmp(1024);
	io::input_file_buffer buf(file.path);

	Checks {
		auto count = buf.read(tmp.data(), tmp.size());
		TestAssert(count == intmax_t(str.size()));
		TestAssert(std::equal(str.begin(), str.end(), tmp.begin()));
	}
};

Test(file_medium_buffer) {
	std::vector<char> str(10000, 'a');

	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write(str), intmax_t(str.size()) );
	}

	std::vector<char> tmp(10000);
	io::input_file_buffer buf(file.path);

	Checks {
		auto count = buf.read(tmp.data(), tmp.size());
		TestAssert(count == intmax_t(str.size()));
		TestAssert(std::equal(str.begin(), str.end(), tmp.begin()));
	}
};

Test(mem_buffer) {
	std::vector<char> str(10000, 'a');

	Setup {
		std::fill_n(str.begin(), 5000, 'b');
		// near the end, so a copy that stops short is caught
		str[9990] = 'c';
	}

	std::vector<char> tmp(10000);
	io::input_memory_buffer buf(str.data(), str.data() + str.size());

	Checks {
		auto count = buf.read(tmp.data(), tmp.size());
		TestAssert(count == intmax_t(str.size()));
		TestAssert(std::equal(str.begin(), str.end(), tmp.begin()));
	}
};
} // namespace aw
