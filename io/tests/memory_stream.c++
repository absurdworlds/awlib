#include <aw/io/input_memory_stream.h>
#include <aw/test/test.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <algorithm>

TestFile("memory_stream");

namespace aw {
Test(memory_stream_reports_eof) {
	char const memory[] { "abcdefghijkilmno" };
	constexpr size_t buf_size = sizeof(memory);

	io::input_memory_stream mstream(memory);

	Preconditions {
		TestAssert(!mstream.eof());
	}

	char buf[buf_size] = {};

	Checks {
		mstream.read(buf, buf_size);
		mstream.read(buf, 1);
		TestAssert(mstream.eof());
	}
}

Test(memory_stream_read_after_eof) {
	char const memory[] { "abcdefghijkilmno" };
	constexpr size_t buf_size = sizeof(memory);

	io::input_memory_stream mstream(memory);

	char buf[buf_size] = {};

	Preconditions {
		mstream.read(buf, buf_size);
		mstream.read(buf, 1);
		TestAssert(mstream.eof());
	}

	// once the source is exhausted every further read yields nothing
	Checks {
		TestEqual( mstream.read(buf, 1), 0u );
		TestAssert( mstream.eof() );
	}
}
