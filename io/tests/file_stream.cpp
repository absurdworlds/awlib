#include <aw/io/input_file_stream.h>
#include <aw/test/test.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <algorithm>

TestFile("file_stream");

namespace aw {
Test(file_stream_rw) {

	char const filename[] { "~temp_io_test.bin" };
	constexpr size_t buf_size = 0x12023;

	std::vector<char> buf1(buf_size, 'a');
	std::vector<char> buf2(buf_size, 'x');
	buf1[buf_size - 0x10] = 'b';

	Setup {
		std::ofstream fs{ filename };
		fs.write(buf1.data(), buf1.size());
	}

	io::input_file_stream ifs{ filename };

	Preconditions {
		TestAssert(ifs.is_open());
	}

	Checks {
		ifs.read(buf2.data(), buf2.size());
	}

	Postconditions {
		// buf_size is very large, so TestEquals would flood
		// the output too much on failure
		TestAssert( buf1 == buf2 );
	}

	fs::remove( filename );
};

/*!
 * position() counts the bytes handed to the caller: after reading n bytes
 * it reports n, whatever amount the stream reads at a time.
 */
Test(file_stream_position_counts_bytes_read) {
	char const filename[] { "~temp_io_position_test.bin" };
	constexpr size_t file_size = 64;
	constexpr size_t consumed  = 5;

	char content[file_size];
	std::fill_n(content, file_size, 'x');

	Setup {
		std::ofstream fs{ filename };
		fs.write(content, file_size);
	}

	io::input_file_stream ifs{ filename };

	Preconditions {
		TestAssert(ifs.is_open());
		TestEqual(ifs.position(), size_t(0));
	}

	char discard[consumed];

	Checks {
		TestEqual(ifs.read(discard, consumed), consumed);
		TestEqual(ifs.position(), size_t(consumed));
	}

	fs::remove( filename );
};

/*!
 * seekoff(n) moves n bytes on from the current position, so the next byte
 * read is the one at position + n, however far away the destination is.
 */
Test(file_seekoff_moves_relative_to_position) {
	char const filename[] { "~temp_io_seekoff_test.bin" };
	constexpr size_t file_size = 64;
	constexpr size_t buf_size  = 16;
	constexpr size_t consumed  = 5;
	constexpr ptrdiff_t jump   = 40;

	char content[file_size];
	for (size_t i = 0; i < file_size; ++i)
		content[i] = char('A' + (i % 26));

	Setup {
		std::ofstream fs{ filename };
		fs.write(content, file_size);
	}

	io::input_file_buffer buffer{ filename, buf_size };

	Preconditions {
		TestAssert(buffer.is_open());
	}

	char discard[consumed];
	TestAssert(buffer.read(discard, consumed) == consumed);

	char got = 0;
	Checks {
		buffer.seekoff(jump);
		TestAssert(buffer.read(&got, 1) == 1);
	}

	Postconditions {
		TestEqual(got, content[consumed + jump]);
	}

	fs::remove( filename );
};
} // namespace aw
