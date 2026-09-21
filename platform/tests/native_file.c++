#include <aw/io/native_file.h>
#include <aw/test/test.h>
#include <cstring>
#include <algorithm>

#include <aw/test/helpers/round_trip.h>

TestFile("Native file");

namespace aw {
using test::temp_file;

Test(native_basic_rw) {
	test::test_round_trip<io::native::file>(_context.name);
}

Test(native_file_move_assignment_releases_old_file) {
	auto path1 = std::string(_context.name) + "1";
	auto path2 = std::string(_context.name) + "2";
	temp_file tmp1{path1};
	temp_file tmp2{path2};
	tmp1.write("");
	tmp2.write("");

	io::native::file file1{ tmp1.path, io::file_mode::read };
	io::native::file file2{ tmp2.path, io::file_mode::read };

	io::native::file old{ file1.descriptor() }; // non-owning

	file1 = std::move(file2);

	std::error_code ec;
	old.size(ec);

	Checks {
		TestAssert( bool(ec) );
	}
}

/*!
 * truncate without create must behave like POSIX O_TRUNC without O_CREAT:
 * fail on a missing file, succeed on an existing one and truncate it to 0 bytes.
 */
Test(native_truncate_without_create) {
	char const initial[] { "some initial data" };

	auto fm = io::file_mode::write|io::file_mode::truncate;

	temp_file tmp{_context.name};

	Preconditions {
		TestAssert(!tmp.exists());
	}

	Checks {
		std::error_code ec;
		io::native::file missing(tmp.path, fm, ec);
		TestAssert(!missing.is_open());
	}

	Setup {
		io::native::file seed(tmp.path, io::file_mode::write|io::file_mode::create);
		seed.write(initial, sizeof(initial) - 1);
	}

	Checks {
		std::error_code ec;
		io::native::file existing(tmp.path, fm, ec);
		TestAssert(existing.is_open());
		TestEqual(existing.size(), 0u);
	}
};

Test(native_size_reports_error_on_bad_fd) {
	std::error_code ec;
	auto ret = io::native::size(io::invalid_fd, ec);

	Checks {
		TestAssert(bool(ec));
		TestEqual(ret, uintmax_t(-1));
	}
};
} // namespace aw
