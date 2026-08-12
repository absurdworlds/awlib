#include <aw/io/native_file.h>
#include <aw/test/test.h>
#include <cstring>
#include <algorithm>

#include "temp_file.h"

TestFile("Native file");

namespace aw {
using test::temp_file;

Test(native_basic_rw) {
	constexpr size_t buf_size = 0x12023;

	std::vector<char> buf1(buf_size, 'a');
	std::vector<char> buf2(buf_size, 'x');
	buf1[buf_size - 0x10] = 'b';

	temp_file tmp{_context.name};

	auto fm = io::file_mode::write|io::file_mode::create|io::file_mode::truncate;
	io::native::file file(tmp.path, fm);

	Preconditions {
		TestAssert(file.is_open());
	}

	Checks {
		auto ret = file.write(buf1.data(), buf1.size());
		TestAssert(ret > 0);
	}

	Setup {
		file.close();
		file = io::native::file(tmp.path, io::file_mode::read);
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
};

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
