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

/*!
 * seekend(n) seeks back n bytes from the end
 */
Test(seekend_counts_back_from_the_end) {
	std::string_view const str = "0123456789";
	constexpr size_t from_end = 4;

	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write(str), intmax_t(str.size()) );
	}

	io::input_file_buffer   from_file{ file.path };
	io::input_memory_buffer from_memory{ str.data(), str.data() + str.size() };

	char in_file = 0;
	char in_memory = 0;

	Checks {
		from_file.seekend(from_end);
		from_memory.seekend(from_end);

		TestAssert( from_file.get(in_file) );
		TestAssert( from_memory.get(in_memory) );
	}

	Postconditions {
		TestEqual( in_file, in_memory );
		TestEqual( in_memory, '6' );
	}
}
} // namespace aw
