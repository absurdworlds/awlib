#include <aw/io/file.h>
#include <aw/io/buffered_file.h>
#include <aw/io/write_file.h>
#include <aw/test/test.h>
#include <aw/test/helpers/sandbox.h>
#include <cstring>
#include <algorithm>

#include <aw/test/helpers/round_trip.h>

TestFile("File IO");

namespace aw {
using test::temp_file;

Test(basic_rw) {
	test::test_round_trip<io::file>(_context.name);
};

/*!
 * Default file mode for write_file should be equivalent to "wb":
 * clear the existing file, and create it if it doesn't
 */
Test(write_file_creates_and_truncates) {
	char const shorter[] { "ab" };
	char const longer[]  { "0123456789" };

	temp_file tmp{_context.name};

	Preconditions {
		TestAssert( !tmp.exists() );
	}

	Checks {
		io::write_file<io::file> file(tmp.path);

		TestAssert( file.is_open() );
		TestEqual( file.write(shorter, sizeof(shorter) - 1), intmax_t(sizeof(shorter) - 1) );
	}

	Preconditions {
		TestEqual( tmp.write(longer), intmax_t(sizeof(longer) - 1) );
	}

	// nothing of the longer contents may survive
	Checks {
		io::write_file<io::file> file(tmp.path);

		TestAssert( file.is_open() );
		TestEqual( file.write(shorter, sizeof(shorter) - 1), intmax_t(sizeof(shorter) - 1) );
	}

	Postconditions {
		TestEqual( tmp.read(), std::vector<char>(shorter, shorter + sizeof(shorter) - 1) );
	}
}

Test(file_size_reports_error) {
	io::file file{ io::invalid_fd };

	TestCatch(fs::filesystem_error, file.size());
};

Test(file_self_swap) {
	temp_file tmp{_context.name};
	tmp.write("");

	io::file file{ tmp.path, io::file_mode::read };
	file.swap(file);

	Checks {
		TestAssert( file.is_open() );
		TestEqual( file.path(), tmp.path );
	}
}

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
/*!
 * A file that can no longer be closed must not take the process
 * down with it when it goes out of scope.
 */
Test(file_destructor_survives_close_failure) {
	temp_file tmp{_context.name};
	tmp.write("");

	auto const fm = io::file_mode::read;

	auto const scenario = [&] {
		// hack: we rely on fd reuse, open() guarantees to give
		// the lowest free descriptor, so we open a file, save its fd,
		// and close it
		auto const fd = io::native::file{ tmp.path, fm }.descriptor();

		// file uses native::file under the hood
		io::file file{ tmp.path, fm };

		// ... then we pull the descriptor out from under the wrapper
		::close(fd);

		// ~file() fails to close the invalid fd
		// the exception should not escape
	};

	TestEqual( test::run_sandboxed(scenario), test::outcome::completed );
};
#endif

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
