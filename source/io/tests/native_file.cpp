#include <aw/io/native_file.h>
#include <aw/utility/test.h>
#include <cstdio>
#include <cstring>
#include <algorithm>

TestFile("Native file");

namespace aw {
Test(native_basic_rw) {
	char const filename[] { "~temp_io_test.bin" };
	constexpr size_t buf_size = 0x12000;

	char* buf1 = new char[buf_size];
	char* buf2 = new char[buf_size];
	std::fill_n(buf1, buf_size, 'a');
	buf1[buf_size - 0x10] = 'b';

	auto fm = io::file_mode::write|io::file_mode::create|io::file_mode::truncate;
	io::native::file file(filename, fm);

	Preconditions {
		TestAssert(file.is_open());
	}

	Checks {
		auto ret = file.write(buf1, buf_size);
		TestAssert(ret > 0);
	}

	Setup {
		file.close();
		file = io::native::file(filename, io::file_mode::read);
	}

	Preconditions {
		TestAssert(file.is_open());
	}

	Checks {
		auto ret = file.read(buf2, buf_size);
		TestAssert(ret > 0);
	}

	Postconditions {
		TestAssert( std::equal(buf1, buf1+buf_size, buf2, buf2 + buf_size) );
	}

	file.close();
	fs::remove( filename );
};
} // namespace aw
