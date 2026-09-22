#include <aw/io/buffered_file.h>
#include <aw/test/test.h>
#include <aw/test/helpers/sandbox.h>

#include <aw/test/helpers/round_trip.h>

TestFile("buffered_file");

namespace aw {
using test::temp_file;

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

#if (AW_PLATFORM_SPECIFIC == AW_PLATFORM_LINUX)
Test(buffered_file_close_reports_failure) {
	char const data[] { "a" };

	// every write to /dev/full fails with ENOSPC
	io::buffered_file file("/dev/full", io::file_mode::write);

	Preconditions {
		TestAssert( file.is_open() );
		TestEqual( file.write(data, 1), intmax_t(1) );
	}

	// the idea is that the write reaches the acual file only when the
	// internal buffer is flushed, so a failed write would show up in close()
	Checks {
		TestAssert( file.close() != 0 );
		TestAssert( !file.is_open() );
	}
};
#endif

#if (AW_PLATFORM == AW_PLATFORM_POSIX)
/*!
 * Closing a file that is already closed does nothing.
 */
Test(buffered_file_close_twice) {
	temp_file tmp{_context.name};
	tmp.write("");

	auto const scenario = [&] {
		io::buffered_file file(tmp.path, io::file_mode::read);
		file.close();
		file.close();
	};

	TestEqual( test::run_sandboxed(scenario), test::outcome::completed );
}
#endif

/*!
 * Positions past 4 GiB (32-bit long) are reachable
 */
Test(buffered_file_seek_past_4gib) {
	temp_file tmp{_context.name};
	tmp.write("");

	intmax_t const far = intmax_t(5) << 30; // ~5GiB

	io::buffered_file file(tmp.path, io::file_mode::read);

	Preconditions {
		TestAssert( file.is_open() );
	}

	Checks {
		TestEqual( file.seek(far, io::seek_mode::set), far );
		TestEqual( file.tell(), far );
	}

	Checks {
		TestEqual( file.seek(-far, io::seek_mode::cur), intmax_t(0) );
		TestEqual( file.tell(), intmax_t(0) );
	}
}

Test(basic_buf_rw) {
	test::test_round_trip<io::buffered_file>(_context.name);
};
} // namespace aw
