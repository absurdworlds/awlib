#include <aw/io/native_file.h>
#include <aw/test/test.h>
#include <cstring>
#include <algorithm>
#include <fstream>

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

//! Each seek mode seeks exactly as it says, and tell() agrees with it
Test(native_file_seek_modes) {
	temp_file tmp{_context.name};
	tmp.write("0123456789");

	io::native::file file{ tmp.path, io::file_mode::read };

	Preconditions {
		TestAssert( file.is_open() );
	}

	char c = 0;

	Checks {
		TestEqual( file.seek(3, io::seek_mode::set), 3 );
		TestEqual( file.tell(), 3 );
		file.read(&c, 1);
		TestEqual( c, '3' );
	}

	Checks {
		// from the position after the read above
		TestEqual( file.seek(2, io::seek_mode::cur), 6 );
		file.read(&c, 1);
		TestEqual( c, '6' );
	}

	Checks {
		TestEqual( file.seek(-1, io::seek_mode::end), 9 );
		file.read(&c, 1);
		TestEqual( c, '9' );
	}

	Checks {
		TestEqual( file.seek(4, io::seek_mode::set), 4 );
		TestEqual( file.tell(), 4 );
		file.read(&c, 1);
		TestEqual( c, '4' );
	}
}

Test(native_size_reports_error_on_bad_fd) {
	std::error_code ec;
	auto ret = io::native::size(io::invalid_fd, ec);

	Checks {
		TestAssert(bool(ec));
		TestEqual(ret, uintmax_t(-1));
	}
};

#if (AW_PLATFORM_SPECIFIC == AW_PLATFORM_LINUX)
/*!
 * Runs against every block device that the test can open.
 * Without privileges it's usually none, so the test passes without doing anything,
 * so ideally the test environment should have a readable loop device.
 */
Test(size_of_block_device_is_its_capacity) {
	for (auto const& entry : fs::directory_iterator("/sys/class/block")) {
		auto const name = entry.path().filename();

		std::error_code ec;
		io::native::file device{ fs::path("/dev") / name, io::file_mode::read, ec };
		if (ec)
			continue;

		constexpr uintmax_t sector_size = 512;
		uintmax_t sectors = 0;
		std::ifstream(entry.path() / "size") >> sectors;
		if (sectors == 0)
			continue;

		TestEqual( device.size(), sectors * sector_size );
	}
}
#endif
} // namespace aw
