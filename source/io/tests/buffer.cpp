#include <aw/io/input_file_stream.h>
#include <aw/io/input_memory_stream.h>
#include <fstream>

#include <aw/utility/test.h>

TestFile("Buffer");

namespace aw {
Test(file_small_buffer) {
	char const str[] = "Test string. Where is the Pink Elephant?";

	Setup {
		std::ofstream ofs("testfile");
		ofs << str;
	}

	char tmp[1024] {};
	io::input_file_buffer buf("testfile");

	Checks {
		auto count = buf.read(tmp, 1024);
		TestAssert(count == sizeof(str)-1);
		TestEqual(std::string(tmp), str);
	}

	fs::remove("testfile");
};

Test(file_medium_buffer) {
	char str[10000];
	std::fill_n(str, 10000, 'a');

	Setup {
		std::ofstream ofs("testfile");
		ofs << str;
	}

	char tmp[10000] {};
	io::input_file_buffer buf("testfile");

	Checks {
		auto count = buf.read(tmp, 10000);
		TestAssert(count == sizeof(str));
		TestAssert(std::equal(std::begin(str), std::end(str), std::begin(tmp)));
	}

	fs::remove("testfile");
};

Test(mem_buffer) {
	char str[10000];

	Setup {
		std::fill_n(str, 10000, 'a');
		std::fill_n(str, 5000,  'b');
		str[9990] = 'c';
	}

	char tmp[10000] {};
	io::input_memory_buffer buf(std::begin(str), std::end(str));

	Checks {
		auto count = buf.read(tmp, 10000);
		TestAssert(count == sizeof(str));
		TestAssert(std::equal(std::begin(str), std::end(str), std::begin(tmp)));
	}
};
} // namespace aw
