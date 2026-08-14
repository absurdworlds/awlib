/*
 * Copyright (C) 2026  Hedede <dev@hedede.me>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_io_tests_round_trip_h
#define aw_io_tests_round_trip_h
#include <aw/io/file_mode.h>
#include <aw/test/test.h>

#include <string_view>
#include <vector>

#include "temp_file.h"

namespace aw::test {
/*!
 * Write a buffer through \a File, read it back, and compare.
 */
template<typename File>
void test_round_trip(std::string_view name)
{
	using fm = io::file_mode;

	constexpr size_t buf_size = 0x12000;

	std::vector<char> written(buf_size, 'a');
	std::vector<char> got(buf_size, 'x');

	// away from either end, so a copy that stops short is caught
	written[buf_size - 0x10] = 'b';

	temp_file tmp{name};

	File file(tmp.path, fm::write|fm::create|fm::truncate);

	Preconditions {
		TestAssert( file.is_open() );
	}

	Checks {
		TestEqual( file.write(written.data(), written.size()), intmax_t(buf_size) );
	}

	Setup {
		file.close();
		file = File(tmp.path, fm::read);
	}

	Preconditions {
		TestAssert( file.is_open() );
	}

	Checks {
		TestEqual( file.read(got.data(), got.size()), intmax_t(buf_size) );
	}

	Postconditions {
		// buf_size is too large to be displayed on failure,
		// so TestAssert here instead of TestEqual
		TestAssert( written == got );
	}
}
} // namespace aw::test
#endif//aw_io_tests_round_trip_h
