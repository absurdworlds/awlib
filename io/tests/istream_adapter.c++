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
 * The adapter takes the parent's buffer for its lifetime and leaves a
 * placeholder behind. 
 * Reading from the parent while the buffer is borrowed should fail cleanly. 
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
} // namespace aw

