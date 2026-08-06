#include <aw/types/char_buffer.h>

#include <aw/test/test.h>

#include <string>

TestFile( "aw::char_buffer" );

namespace aw {
namespace {
std::string contents(char_buffer const& buf)
{
	return std::string(buf.begin(), buf.end());
}
} // namespace

Test(char_buffer_view_keeps_length) {
	// a prefix of a longer string: strlen would run on past the fifth char
	std::string source = "hello world";
	string_view prefix{source.data(), 5};

	char_buffer buf{prefix};

	Checks {
		TestEqual(buf.size(), size_t(5));
		TestEqual(buf.view_size(), size_t(5));
		TestEqual(contents(buf), std::string("hello"));
	}
}

Test(char_buffer_view_stops_at_embedded_nul) {
	// strlen would stop at the NUL and report 2 instead of 5
	static const char data[] = "ab\0cd";
	string_view view{data, 5};

	char_buffer buf{view};

	Checks {
		TestEqual(buf.size(), size_t(5));
		TestEqual(buf.view_size(), size_t(5));
		TestEqual(contents(buf), std::string(data, 5));
	}
}

Test(char_buffer_owning_copy) {
	std::string source = "hello world";
	string_view prefix{source.data(), 5};

	char_buffer buf{prefix, char_buffer::copy_data};

	Checks {
		TestEqual(buf.size(), size_t(5));
		TestEqual(buf.view_size(), size_t(5));
		TestEqual(contents(buf), std::string("hello"));

		// the copy is independent of the source
		source[0] = 'j';
		TestEqual(contents(buf), std::string("hello"));
	}
}

Test(char_buffer_move_transfers_ownership) {
	std::string source = "hello world";
	char_buffer buf{string_view{source.data(), 5}, char_buffer::copy_data};

	char_buffer moved{std::move(buf)};

	Checks {
		TestEqual(moved.size(), size_t(5));
		TestEqual(contents(moved), std::string("hello"));

		// the moved-from buffer keeps a view of the data it gave up
		TestEqual(contents(buf), std::string("hello"));
	}
}
} // namespace aw
