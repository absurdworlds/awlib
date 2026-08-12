#include <aw/io/istream_adapter.h>
#include <sstream>

#include <aw/test/test.h>

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

Test(wrapped_stream_is_still_usable_after_eof) {
	std::string str{"short"};

	std::istringstream is{str};

	Checks {
		char c;
		{
			io::istream_adapter stream{is};
			while (stream.get(c)) {}
		}
	}

	Postconditions {
		TestAssert(is.tellg() != std::streampos(-1));
	}
};

/*!
 * Reading from the parent stream while an adapter holds it should fail
 * cleanly rather than fault
 */
Test(wrapped_stream_fails_cleanly_while_adapted) {
	std::istringstream is{"0123456789"};

	Checks {
		io::istream_adapter stream{is};

		std::string word;
		is >> word;

		TestAssert( is.fail() );
		TestAssert( word.empty() );
	}

	// and the parent is usable again once the adapter is gone
	Postconditions {
		is.clear();

		std::string word;
		is >> word;
		TestEqual( word, "0123456789" );
	}
}

/*!
 * Parent stream should resume where it left off after the adapter is gone
 */
Test(wrapped_stream_is_restored_cleanly) {
	std::istringstream is{"0123456789"};

	char buf[3];
	is.read(buf, sizeof(buf));

	Checks {
		io::istream_adapter stream{is};

		std::string word;
		is >> word;

		TestAssert( is.fail() );
		TestAssert( word.empty() );
	}

	Postconditions {
		is.clear();

		std::string word;
		is >> word;
		TestEqual( word, "3456789" );
	}
}

/*!
 * Reading after a seek yields the bytes at the position sought to
 */
Test(reads_resume_where_a_seek_landed) {
	std::istringstream is{"0123456789"};

	io::istream_buffer buffer{ is.rdbuf() };
	io::input_stream stream{ buffer };

	char c = 0;

	Preconditions {
		TestAssert( stream.get(c) );
		TestEqual( c, '0' );
	}

	Checks {
		buffer.seekpos(4);
		TestAssert( stream.get(c) );
		TestEqual( c, '4' );
	}

	// and again to a position before the one already read
	Checks {
		buffer.seekpos(1);
		TestAssert( stream.get(c) );
		TestEqual( c, '1' );
	}
};

/*!
 * A relative seek counts from the position already read to
 */
Test(relative_seek_counts_from_the_read_position) {
	std::istringstream is{"0123456789"};

	io::istream_buffer buffer{ is.rdbuf() };
	io::input_stream stream{ buffer };

	char c = 0;

	Preconditions {
		// read as far as '2'
		TestAssert( stream.get(c) );
		TestAssert( stream.get(c) );
		TestAssert( stream.get(c) );
		TestEqual( c, '2' );
	}

	Checks {
		buffer.seekoff(2);
		TestAssert( stream.get(c) );
		TestEqual( c, '5' );
	}

	Checks {
		buffer.seekoff(-3);
		TestAssert( stream.get(c) );
		TestEqual( c, '3' );
	}
};
} // namespace aw

