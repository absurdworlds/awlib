#include <aw/io/native_file.h>
#include <aw/test/test.h>
#include <cstdio>
#include <cstring>
#include <algorithm>

TestFile("Native file");

namespace aw {
Test(native_basic_rw) {
	char const filename[] { "~temp_io_test.bin" };
	constexpr size_t buf_size = 0x12023;

	std::vector<char> buf1(buf_size, 'a');
	std::vector<char> buf2(buf_size, 'x');
	buf1[buf_size - 0x10] = 'b';

	auto fm = io::file_mode::write|io::file_mode::create|io::file_mode::truncate;
	io::native::file file(filename, fm);

	Preconditions {
		TestAssert(file.is_open());
	}

	Checks {
		auto ret = file.write(buf1.data(), buf1.size());
		TestAssert(ret > 0);
	}

	Setup {
		file.close();
		file = io::native::file(filename, io::file_mode::read);
	}

	Preconditions {
		TestAssert(file.is_open());
	}

	Checks {
		auto ret = file.read(buf2.data(), buf2.size());
		TestAssert(ret > 0);
	}

	Postconditions {
		// buf_size is too large to be properly displayed,
		// so TestAssert here instead of TestEqual
		TestAssert( buf1 == buf2 );
	}

	file.close();
	fs::remove( filename );
};

/*!
 * truncate without create must behave like POSIX O_TRUNC without O_CREAT:
 * fail on a missing file, succeed on an existing one and truncate it to 0 bytes.
 */
Test(native_truncate_without_create) {
	char const filename[] { "~temp_io_truncate_test.bin" };
	char const initial[]  { "some initial data" };

	auto fm = io::file_mode::write|io::file_mode::truncate;

	Preconditions {
		fs::remove(filename);
	}

	Checks {
		std::error_code ec;
		io::native::file missing(filename, fm, ec);
		TestAssert(!missing.is_open());
	}

	Setup {
		io::native::file seed(filename, io::file_mode::write|io::file_mode::create);
		seed.write(initial, sizeof(initial) - 1);
	}

	Checks {
		std::error_code ec;
		io::native::file existing(filename, fm, ec);
		TestAssert(existing.is_open());
		TestEqual(existing.size(), 0u);
	}

	fs::remove(filename);
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
