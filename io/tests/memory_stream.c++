#include <aw/io/input_memory_stream.h>
#include <aw/test/test.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <type_traits>

TestFile("memory_stream");

namespace aw {
static_assert( !std::is_copy_constructible_v<io::input_stream> );
static_assert( !std::is_copy_assignable_v<io::input_stream> );

static_assert( !std::is_copy_constructible_v<io::input_memory_stream> );
static_assert( !std::is_copy_assignable_v<io::input_memory_stream> );

// holds buffer by value
static_assert( !std::is_move_constructible_v<io::input_memory_stream> );
// owns the buffer, moving is fine
static_assert(  std::is_move_constructible_v<io::input_stream> );

/*!
 * A stream can be built over a buffer directly, and moved: the moved-from
 * one gives up the buffer rather than sharing it.
 */
Test(stream_over_a_buffer_can_be_moved) {
	char const memory[] { "abc" };

	io::input_memory_buffer buffer{memory, memory + 3};
	io::input_stream stream{buffer};

	char c = 0;

	Preconditions {
		TestAssert( stream.get(c) );
		TestEqual( c, 'a' );
	}

	Checks {
		auto moved = std::move(stream);

		// it carries on where the original left off
		TestAssert( moved.get(c) );
		TestEqual( c, 'b' );
		TestEqual( moved.position(), 2u );
	}
}

/*!
 * Input that runs out before a delimiter still holds a record, and
 * read_until has to hand it over rather than drop it.
 */
Test(read_until_keeps_a_record_without_a_delimiter) {
	char const memory[] { "a\nb" };

	io::input_memory_stream stream{ memory, memory + 3 };
	std::string line;

	Checks {
		TestAssert( stream.read_until(line, '\n') );
		TestEqual( line, "a" );
	}

	// this is the one that used to be lost
	Checks {
		TestAssert( stream.read_until(line, '\n') );
		TestEqual( line, "b" );
	}

	// and only now is there nothing left, which ends the loop
	Checks {
		TestAssert( !stream.read_until(line, '\n') );
		TestAssert( line.empty() );
	}
}

/*!
 * A delimiter at the very end does not add a record after it.
 */
Test(read_until_stops_after_a_trailing_delimiter) {
	char const memory[] { "a\nb\n" };

	io::input_memory_stream stream{ memory, memory + 4 };
	std::string line;

	Checks {
		TestAssert( stream.read_until(line, '\n') );
		TestEqual( line, "a" );

		TestAssert( stream.read_until(line, '\n') );
		TestEqual( line, "b" );
	}

	Checks {
		TestAssert( !stream.read_until(line, '\n') );
		TestAssert( line.empty() );
	}
}

/*!
 * input_stream_iterator should not skip over bytes and both increments
 * should behave the same
 */
Test(stream_iterator_yields_every_byte_once) {
	char const memory[] { "abc" };

	Checks {
		io::input_memory_stream stream{ memory, memory + 3 };

		std::string got;
		for (auto it = io::input_stream_iterator{stream}; !(it == io::input_stream_iterator{}); ++it)
			got += char(*it);

		TestEqual( got, "abc" );
	}

	Checks {
		io::input_memory_stream stream{ memory, memory + 3 };

		std::string got;
		for (auto it = io::input_stream_iterator{stream}; !(it == io::input_stream_iterator{}); )
			got += char(*it++);

		TestEqual( got, "abc" );
	}
};

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
