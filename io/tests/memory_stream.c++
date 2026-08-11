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

/*!
 * The stream stops before EOF, so position() should report that
 */
Test(memory_position_at_eof_is_end_of_source) {
	char const memory[] { "abcdefghijkilmno" };
	constexpr size_t buf_size = sizeof(memory);

	io::input_memory_stream mstream(memory);
	char buf[buf_size] = {};

	Preconditions {
		mstream.read(buf, buf_size);
		mstream.read(buf, 1);
		TestAssert( mstream.eof() );
	}

	Checks {
		TestEqual( mstream.position(), buf_size );
	}
}

/*!
 * Running out of input is not permanent: seeking back to a position that
 * still holds data makes the stream readable again.
 */
Test(memory_seek_back_from_eof_resumes_reading) {
	char const memory[] { "abcdefghijkilmno" };
	constexpr size_t buf_size = sizeof(memory);

	char buf[buf_size] = {};

	auto exhaust = [&] (io::input_memory_buffer& buffer) {
		buffer.read(buf, buf_size);
		buffer.read(buf, 1);
		return buffer.eof();
	};

	io::input_memory_buffer from_start{memory, memory + buf_size};
	io::input_memory_buffer one_back{memory, memory + buf_size};

	Preconditions {
		TestAssert( exhaust(from_start) );
		TestAssert( exhaust(one_back) );
	}

	// seeking to an absolute position
	Checks {
		from_start.seekpos(0);
		TestAssert( !from_start.eof() );
		TestEqual( from_start.position(), 0u );
		TestEqual( from_start.read(buf, 1), 1u );
		TestEqual( buf[0], memory[0] );
	}

	// and seeking relative to where the stream stopped
	Checks {
		one_back.seekoff(-1);
		TestAssert( !one_back.eof() );
		TestEqual( one_back.position(), buf_size - 1 );
		TestEqual( one_back.read(buf, 1), 1u );
		TestEqual( buf[0], memory[buf_size - 1] );
	}
}
} // namespace aw
