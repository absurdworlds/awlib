#include <aw/io/file.h>
#include <aw/io/buffered_file.h>
#include <aw/test/test.h>
#include <cstring>
#include <algorithm>

#include "round_trip.h"

TestFile("File IO");

namespace aw {
using test::temp_file;

Test(basic_rw) {
	test::test_round_trip<io::file>(_context.name);
};

Test(size_reports_error) {
	io::file file{ io::invalid_fd };

	TestCatch(fs::filesystem_error, file.size());
};

Test(buffered_file_move_keeps_path) {
	char const data[] { "abcde" };

	temp_file tmp{_context.name};

	auto const fm = io::file_mode::write|io::file_mode::create|io::file_mode::truncate;
	io::buffered_file file(tmp.path, fm);
	file.write(data, sizeof(data) - 1);
	file.flush();

	Preconditions {
		TestAssert(file.is_open());
	}

	auto const old_path = file.path();

	io::buffered_file moved(std::move(file));

	Checks {
		TestAssert(moved.is_open());
		TestEqual(moved.path().string(), old_path.string());
		TestEqual(moved.size(), intmax_t(sizeof(data) - 1));
	}

	moved.close();
};

Test(basic_buf_rw) {
	test::test_round_trip<io::buffered_file>(_context.name);
};
} // namespace aw
