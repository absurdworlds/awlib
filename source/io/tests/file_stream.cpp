#include <aw/io/input_file_stream.h>
#include <aw/utility/test.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <algorithm>

TestFile("file_stream");

namespace aw {
Test(file_stream_rw) {

	char const filename[] { "~temp_io_test.bin" };
	constexpr size_t buf_size = 0x12023;

	char* buf1 = new char[buf_size];
	char* buf2 = new char[buf_size];
	std::fill_n(buf1, buf_size, 'a');
	buf1[buf_size - 0x10] = 'b';

	Setup {
		std::ofstream fs{ filename };
		fs.write(buf1, buf_size);
	}

	io::input_file_stream ifs{ filename };

	Preconditions {
		TestAssert(ifs.is_open());
	}

	Checks {
		ifs.read(buf2, buf_size);
	}

	Postconditions {
		TestAssert( std::equal(buf1, buf1+buf_size, buf2, buf2 + buf_size) );
	}

	fs::remove( filename );
};
} // namespace aw
